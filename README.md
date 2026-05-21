<p align="center">
  <img src="assets/kitra_1024x1024.png" width="256" alt="Kitra logo">
</p>

# Kitra

A minimal, beginner-friendly 2D graphics library for C.

[![Version](https://img.shields.io/github/v/release/UniquePython/kitra?color=orange)](https://github.com/UniquePython/kitra/releases)
[![CI](https://github.com/UniquePython/kitra/actions/workflows/ci.yml/badge.svg)](https://github.com/UniquePython/kitra/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-orange.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-red.svg)](README.md)
[![C Standard](https://img.shields.io/badge/C-C11-red.svg)](CMakeLists.txt)
[![SDL2](https://img.shields.io/badge/built%20on-SDL2-orange.svg)](https://www.libsdl.org/)
[![Docs](https://img.shields.io/badge/docs-github.io-red.svg)](https://uniquepython.github.io/kitra)

## What is Kitra

SDL2 is a powerful foundation, but it asks you to manage renderers, surfaces, and event queues before you can draw a circle. Kitra sits on top of SDL2 and collapses that setup into a single header and a straightforward game loop, so a beginner can focus on building something instead of configuring something. It is not a game engine — there are no scenes, no entities, no editor — just a clean API for a window, input, and drawing.

## Getting Started

A Kitra program looks like this:

```c
#include <kitra/kitra.h>

int main(void)
{
    if (KitraInit(KITRA_SUBSYSTEM_ALL) != KITRA_STATUS_OK)
        return 1;

    if (KitraCreateWindow(KitraDefaultWindowDesc()) != KITRA_STATUS_OK)
        return 1;

    while (KitraIsRunning())
    {
        KitraBeginFrame();

        KitraClearBackground(KITRA_BLACK);

        KitraEndFrame();
    }

    KitraQuit(); // cleans up window, renderer, and SDL
    return 0;
}
```

## Installation

> Tested on Linux and macOS. Windows support is experimental —
> MSVC has stricter C compliance requirements that may require source changes.

### Method 1: install.sh (recommended)

The easiest way. One command installs SDL2 dependencies, downloads the latest release, and sets everything up automatically.

```bash
curl -sSL https://github.com/UniquePython/kitra/releases/latest/download/install.sh | bash
```

### Method 2: Tarball

Download the prebuilt tarball for your platform from the [releases page](https://github.com/UniquePython/kitra/releases/latest). Then install SDL2 dependencies manually:

```bash
# Ubuntu/Debian
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-gfx-dev libsdl2-ttf-dev libsdl2-mixer-dev

# Arch
sudo pacman -S sdl2 sdl2_image sdl2_gfx sdl2_ttf sdl2_mixer

# Fedora
sudo dnf install SDL2-devel SDL2_image-devel SDL2_gfx-devel SDL2_ttf-devel SDL2_mixer-devel

# macOS
brew install sdl2 sdl2_image sdl2_gfx sdl2_ttf sdl2_mixer
```

Then extract and copy the files:

```bash
tar -xzf kitra-linux-x86_64.tar.gz
sudo cp -r kitra/include/kitra /usr/local/include/
sudo cp kitra/lib/libkitra.a /usr/local/lib/
```

### Method 3: From Source

```bash
# Install SDL2 dependencies first (see Method 2 above)

git clone https://github.com/UniquePython/kitra.git
cd kitra
cmake -B build
cmake --build build -j$(nproc)
sudo cmake --install build
```

---

### Using Kitra in Your Project

**CMake:**
```cmake
find_package(Kitra REQUIRED)
target_link_libraries(your_target PRIVATE Kitra::Kitra)
```

**Makefile / manual:**
```makefile
CFLAGS  += $(shell pkg-config --cflags kitra)
LIBS    += $(shell pkg-config --libs kitra)
```

**Raw gcc:**
```bash
# Linux
gcc main.c $(pkg-config --cflags --libs kitra) -Wl,--allow-shlib-undefined -o myapp

# macOS
gcc main.c $(pkg-config --cflags --libs kitra) -o myapp
```

Then include the header:

```c
#include <kitra/kitra.h>
```

## API Overview

| Module | Header | Description |
|---|---|---|
| Subsystem | `kitra/kitra_subsystem.h` | Initialize and shut down Kitra; supports `VIDEO`, `AUDIO`, `EVENTS`, or `KITRA_SUBSYSTEM_ALL` flags with rollback safety on failure |
| Window | `kitra/kitra_window.h` | Create and destroy the window with configurable flags (resizable, fullscreen, borderless, hidden); query size and per-frame resize events; access raw SDL window and renderer handles |
| Loop | `kitra/kitra_loop.h` | Main loop control — `KitraBeginFrame` processes events, updates input; `KitraEndFrame` caps FPS, and presents the frame |
| Input | `kitra/kitra_input.h` | Keyboard (down, pressed, released) and mouse (position, per-frame delta, scroll wheel, button down/pressed/released) queries |
| Drawing | `kitra/kitra_draw.h` | Points, plain and thick lines, filled and outlined circles, ellipses, triangles, polygons, and rectangles (plain and rounded); blend mode control |
| Color | `kitra/kitra_color.h` | Color construction via RGBA/HSV; lerp, fade, brighten, darken, invert, equality test, and pack/unpack to `uint32_t` |
| Textures | `kitra/kitra_texture.h` | Load images (PNG, JPG, WebP, TIFF); draw at natural size or with source/destination rects, rotation, pivot, and flip; set tint, alpha, and blend mode; save screenshots; access raw SDL texture handle |
| Surfaces | `kitra/kitra_surface.h` | CPU-side pixel buffers — create, load, read, write, and convert to texture |
| Audio | `kitra/kitra_audio.h` | Load and play WAV sound effects; load and stream music tracks with loop, pause, resume, stop, and per-source volume control |
| Text & Fonts | `kitra/kitra_text.h` | Load TTF fonts; draw plain, point-positioned, and `printf`-formatted text; pre-rasterize strings into cached textures; measure text dimensions |
| Timers | `kitra/kitra_timer.h` | Per-frame delta time, smoothed FPS, target FPS cap, and general-purpose one-shot or repeating timers |
| RNG | `kitra/kitra_rng.h` | PCG32 PRNG with per-instance (`KitraRng`) and global (`KitraRand*`) APIs; integers, bounded uints, floats, ranges, random points, unit directions, and probability checks |
| Math | `kitra/kitra_math.h` | 2D integer and float vectors (add, subtract, scale, dot, cross, normalize, rotate, lerp, angle); signed distance functions for points, rects, circles, and ellipses; quadratic, sine, and back easing curves |
| Types | `kitra/kitra_types.h` | Core data structures — `KitraVec2i`, `KitraVec2f`, `KitraPoint`, `KitraSize`, `KitraRect`, `KitraCircle`, `KitraEllipse`, `KitraColor`, `KitraBlendMode`; included transitively via `kitra.h` |
| Error & Logging | `kitra/kitra_error.h` | Log callback registration, last-error and severity retrieval, `KitraClearError`; default callback prints colored output to stdout/stderr; `KITRA_LOG` macro for internal use |

## Examples

The `examples/` directory contains Pong, Snake and Pendulum built with Kitra.

<figure align="center">
  <img src="examples/pong/assets/screenshot.png" alt="Pong game in Kitra" width="700">
  <figcaption><em>Figure 1: Pong game in Kitra</em></figcaption>
</figure>

<figure align="center">
  <img src="examples/snake/assets/screenshot.png" alt="Snake game in Kitra" width="700">
  <figcaption><em>Figure 2: Snake game in Kitra</em></figcaption>
</figure>

<figure align="center">
  <img src="examples/pendulum/assets/screenshot.png" alt="Single Pendulum simulation in Kitra" width="700">
  <figcaption><em>Figure 3: Single Pendulum simulation in Kitra</em></figcaption>
</figure>

## License

Kitra is licensed under the [MIT License](LICENSE).

## Acknowledgements

Kitra was heavily inspired by raylib and its philosophy of making graphics programming simple and accessible.