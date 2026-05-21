# Navigating the Kitra Codebase

This document is for anyone who wants to read, understand, or contribute to Kitra's source — not just use it. It explains the layout, the key architectural decisions, the recurring patterns, and where to look when something isn't obvious.

---

## Directory Layout

```
kitra/
├── include/          # Public headers — the entire API lives here
│   ├── kitra.h       # Single umbrella include
│   ├── kitra_types.h
│   ├── kitra_status.h
│   └── kitra_*.h     # One header per module
│
├── src/              # Implementation files — one .c per module
│   ├── kitra_internal.h   # Private header: global context + internal helpers
│   └── kitra_*.c
│
└── examples/         # Pong, Snake, Pendulum — read these to see the API in use
```

The rule is strict: **public headers go in `include/`, implementation goes in `src/`**. Users never touch anything in `src/`. Every `.c` file starts by including `kitra_internal.h`, which in turn includes `kitra.h` and all SDL2 headers.

---

## The Most Important File: `kitra_internal.h`

Before reading any `.c` file, read `src/kitra_internal.h`. It defines the entire internal world of the library.

The key type is `KitraCtx` — a single global struct that holds every piece of state the library owns:

```c
typedef struct KitraCtx {
    KitraCoreState  core;     // SDL window, renderer, init flags
    KitraLoopState  loop;     // isRunning, frameBegun, resized
    KitraTimingState timing;  // deltaTime, fps, targetFPS, perfFrequency
    KitraInputState input;    // keyboard + mouse state arrays
    KitraLogState   log;      // callback, userdata, lastError, lastLevel
    KitraRng        rng;      // global PCG32 instance
} KitraCtx;

extern KitraCtx gKitraCtx;  // declared in kitra_subsystem.c
```

Almost every function in every `.c` file reads from or writes to `gKitraCtx`. When you're tracing how something works, follow the fields of this struct. There is no hidden state anywhere else.

---

## Module Map

### Startup and teardown — `kitra_subsystem.c`

This is where `gKitraCtx` is defined (the one definition in the entire program). `KitraInit` zeroes the context, initializes SDL subsystems in dependency order, seeds the global RNG, and sets up the default log callback. `KitraQuit` tears everything down in reverse: window/renderer, then SDL subsystems.

**If the library crashes on init or quits uncleanly, start here.**

### The game loop — `kitra_loop.c`

`KitraBeginFrame` and `KitraEndFrame` are the heartbeat. Reading `kitra_loop.c` in full (~80 lines) gives you the complete execution model:

```
BeginFrame:
  1. Compute deltaTime from performance counter
  2. Reset per-frame input (pressed[], released[], deltas)
  3. SDL_PollEvent loop → KitraInputProcessEvent or KitraRequestQuit

EndFrame:
  1. Sleep if targetFPS is set (busy-wait avoidance via SDL_Delay)
  2. SDL_RenderPresent
```

The `frameBegun` flag in `gKitraCtx.loop` exists purely to catch mismatched Begin/End calls.

### Input — `kitra_input.c`

Input is driven by a lookup table. At init time, `KitraInputInit` builds a reverse map from `SDL_Scancode` → `KitraKey`. On each event, `KitraInputProcessEvent` writes into the arrays in `gKitraCtx.input.keyboard` and `gKitraCtx.input.mouse`.

There are three arrays per device: `down[]` (held), `pressed[]` (went down this frame), `released[]` (went up this frame). `BeginFrame` clears `pressed[]` and `released[]` at the top of every frame, so they are only `true` for exactly one frame. `down[]` is never cleared by BeginFrame — it's set on KEYDOWN and cleared on KEYUP events.

### Error and logging — `kitra_error.c`

All logging goes through the `KITRA_LOG(level, msg)` macro, which expands to `KitraLogInternal__` with `__FILE__`, `__func__`, and `__LINE__` injected. That function stores the message in `gKitraCtx.log.lastError`, then calls the registered callback.

The default callback (`KitraDefaultLogCallback`) uses ANSI color codes and routes warnings/errors to stderr. You can replace it entirely with `KitraSetErrorCallback`. Passing `NULL` silences all logging.

**When tracking down a bug, `KitraGetError()` returns the last message, `KitraHasError()` is a quick boolean check.**

### Drawing — `kitra_draw.c`

Drawing delegates immediately to SDL2_gfx (`filledCircleRGBA`, `thickLineRGBA`, etc.) or vanilla SDL2 (`SDL_RenderFillRect`, etc.). There is very little logic here — it's mostly unpacking Kitra types into SDL types. The internal macro `KITRA_COLOR_UNPACK(c)` expands `KitraColor` into four separate `r, g, b, a` arguments that SDL2_gfx expects.

For rectangles specifically, Kitra uses `(x, y, w, h)` but SDL2_gfx uses `(x1, y1, x2, y2)`, so you'll see `rect.x + rect.w - 1` in the rounded rectangle calls.

### Textures and surfaces — `kitra_texture.c`, `kitra_surface.c`

The split is: **surfaces are CPU-side pixel buffers, textures are GPU-side**. `KitraSurfaceToTexture` bridges them.

Both types use opaque structs (defined in the `.c` files, not the headers):

```c
// kitra_texture.c
struct KitraTexture { SDL_Texture *handle; int width, height; };

// kitra_surface.c
struct KitraSurface { SDL_Surface *handle; int width, height; };
```

The `KitraTextureFromSDL` and `KitraSurfaceFromSDL` helpers (declared in `kitra_internal.h`, defined in their respective `.c` files) let other modules (like `kitra_text.c`) create Kitra-typed wrappers around SDL objects without exposing the struct internals.

### Text — `kitra_text.c`

Text has two usage modes:
- **Immediate**: `KitraDrawText` / `KitraDrawTextF` — rasterizes to a temp texture each call. Fine for dynamic strings, expensive at high frequency.
- **Cached**: `KitraCreateText` → `KitraDrawCachedText` → `KitraDestroyCachedText` — rasterizes once into a `KitraText` (which wraps an `SDL_Texture`). Use this for labels and UI that don't change every frame.

The `TTF_Init` call is lazy — it happens inside `KitraLoadFont` only if `ttfInitialized` is false.

### Timers — `kitra_timer.c`

`KitraTimer` stores two counters: `start` (when the timer began) and `last` (when it last fired). `KitraTimerDone` compares against `last`, not `start` — this matters for repeat mode, where `last` advances by exactly `duration` ticks rather than snapping to `now`, preserving sub-frame accuracy.

`KitraGetDeltaTime` and `KitraGetFPS` read from `gKitraCtx.timing`, which is computed in `KitraBeginFrame`.

### RNG — `kitra_rng.c`

Implements PCG32, with the algorithm commented and cited. Each `KitraRng` instance is independent. The global `KitraRand*` functions are thin wrappers that pass `&gKitraCtx.rng`.

`KitraRngDirection` uses rejection sampling on the unit disk rather than `cos`/`sin` — this is unbiased and avoids trig. It loops, but the expected number of iterations is 4/π ≈ 1.27.

---

## Recurring Patterns

### Opaque structs

Resource types (`KitraTexture`, `KitraFont`, `KitraSurface`, etc.) are declared as incomplete types in the public headers and defined only in the corresponding `.c` file. Users get a pointer and can't see inside. This is intentional — it lets the internals change without breaking user code.

### Double-pointer destroy

All destroy functions take `T **ptr` and set `*ptr = NULL` on exit:

```c
void KitraDestroyTexture(KitraTexture **tex);
```

This prevents use-after-free and makes accidental double-frees safe. Call them with the address of your pointer: `KitraDestroyTexture(&myTex)`.

### Convenience overloads

Most draw and query functions come in multiple variants:
- Base: raw coordinates (`int x, int y`)
- `P` suffix: takes a `KitraPoint`
- `C` suffix: takes a `KitraCircle`
- `E` suffix: takes a `KitraEllipse`

They all call the base function — nothing extra happens in the suffix versions. Pick whichever form matches what you already have.

### SDL escape hatches

Every resource type has a `GetSDL` function (`KitraTextureGetSDL`, `KitraSurfaceGetSDL`, `KitraGetSDLWindow`, `KitraGetSDLRenderer`) that returns the underlying SDL handle. These exist for when you need an SDL feature Kitra doesn't wrap. The ownership note is consistent: **Kitra still owns the handle — do not free it yourself**.

---

## Reading Order for New Contributors

If you want to understand the codebase from the inside out:

1. `include/kitra_types.h` and `include/kitra_status.h` — the primitive vocabulary
2. `src/kitra_internal.h` — the full internal state model
3. `src/kitra_subsystem.c` — init/quit lifecycle
4. `src/kitra_loop.c` — the frame model
5. `src/kitra_input.c` — how events become query results
6. Any module you care about — they're all self-contained after the above

The examples in `examples/` are the best way to see how the pieces connect at the user level. Pong is the most instructive starting point.

---

## What Lives Where (Quick Reference)

| Question | Where to look |
|---|---|
| What is the global state? | `KitraCtx` in `src/kitra_internal.h` |
| How does init work? | `src/kitra_subsystem.c` |
| How does the frame loop work? | `src/kitra_loop.c` |
| How is input processed? | `src/kitra_input.c` |
| Where are log messages routed? | `src/kitra_error.c` |
| Where are struct definitions for opaque types? | Top of the corresponding `.c` file |
| How does SDL map to Kitra types? | `KitraToSDL*` static functions in each `.c` file |
| Where is `gKitraCtx` defined? | `src/kitra_subsystem.c` (line 3) |
