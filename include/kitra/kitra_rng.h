#ifndef KITRA_RNG_H_
#define KITRA_RNG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "kitra_types.h"

#include <stdint.h>
#include <stdbool.h>

    /**
     * @brief State for a PCG pseudo-random number generator.
     *
     * Holds the internal state and increment for a PCG32 generator. Each
     * @p KitraRng instance is independent, allowing multiple deterministic
     * streams to run concurrently. @p inc must be odd.
     *
     * @see KitraRngSeed, KitraRngNext
     */
    typedef struct KitraRng
    {
        uint64_t state; /**< Current generator state, advanced on each call. */
        uint64_t inc;   /**< Stream selector — must be odd. */
    } KitraRng;

    /**
     * @brief Seeds a @p KitraRng with an explicit seed and stream.
     *
     * Initializes @p rng using the PCG32 seeding sequence. @p stream selects
     * an independent output sequence — two generators with different streams
     * and the same @p seed produce entirely different output.
     *
     * @param rng     RNG instance to initialize.
     * @param seed    Initial state seed.
     * @param stream  Stream selector; identifies the output sequence.
     *
     * @see KitraRngSeedAuto, KitraRng
     */
    void KitraRngSeed(KitraRng *rng, uint64_t seed, uint64_t stream);

    /**
     * @brief Seeds a @p KitraRng automatically from the system clock.
     *
     * Mixes the high-resolution performance counter with wall-clock time to
     * produce a seed and stream that are unique in practice, even when two
     * generators are seeded within the same millisecond.
     *
     * @param rng  RNG instance to initialize.
     *
     * @see KitraRngSeed, KitraRng
     */
    void KitraRngSeedAuto(KitraRng *rng);

    /**
     * @brief Returns the next raw 32-bit value from a @p KitraRng.
     *
     * Advances the generator state and returns a uniformly distributed
     * unsigned 32-bit integer.
     *
     * @param rng  RNG instance to advance.
     * @return     Next pseudo-random @p uint32_t.
     *
     * @see KitraRngUint, KitraRngFloat
     */
    uint32_t KitraRngNext(KitraRng *rng);

    /**
     * @brief Returns a uniformly distributed random integer in [0, @p bound).
     *
     * Uses Lemire's nearly-divisionless algorithm to eliminate modulo bias
     * without a division on the fast path.
     *
     * @param rng    RNG instance to advance.
     * @param bound  Exclusive upper bound. Returns @p 0 if @p bound is 0 or 1.
     * @return       Uniform random value in [0, @p bound).
     *
     * @see KitraRngInt, KitraRngNext
     */
    uint32_t KitraRngUint(KitraRng *rng, uint32_t bound);

    /**
     * @brief Returns a uniformly distributed random integer in [@p min, @p max].
     *
     * @param rng  RNG instance to advance.
     * @param min  Inclusive lower bound.
     * @param max  Inclusive upper bound. Returns @p min if @p min >= @p max.
     * @return     Uniform random value in [@p min, @p max].
     *
     * @see KitraRngUint, KitraRngFloat
     */
    int KitraRngInt(KitraRng *rng, int min, int max);

    /**
     * @brief Returns a uniformly distributed random float in [0.0, 1.0).
     *
     * @param rng  RNG instance to advance.
     * @return     Uniform random value in [0.0, 1.0).
     *
     * @see KitraRngFloatRange, KitraRngNext
     */
    float KitraRngFloat(KitraRng *rng);

    /**
     * @brief Returns a uniformly distributed random float in [@p min, @p max).
     *
     * @param rng  RNG instance to advance.
     * @param min  Inclusive lower bound.
     * @param max  Exclusive upper bound.
     * @return     Uniform random value in [@p min, @p max).
     *
     * @see KitraRngFloat, KitraRngInt
     */
    float KitraRngFloatRange(KitraRng *rng, float min, float max);

    /**
     * @brief Returns a random point within a rectangle.
     *
     * Both axes are sampled uniformly over the interior of @p bounds,
     * inclusive of all edges.
     *
     * @param rng     RNG instance to advance.
     * @param bounds  Rectangle defining the sampling region.
     * @return        Random @p KitraPoint within @p bounds.
     *
     * @see KitraRngInt, KitraRngDirection
     */
    KitraPoint KitraRngPoint(KitraRng *rng, KitraRect bounds);

    /**
     * @brief Returns a random unit vector.
     *
     * Uses rejection sampling on the unit disk to produce an unbiased
     * direction without trigonometric functions.
     *
     * @param rng  RNG instance to advance.
     * @return     A normalized @p KitraVec2f with length 1.0.
     *
     * @see KitraRngFloat, KitraRngPoint
     */
    KitraVec2f KitraRngDirection(KitraRng *rng);

    /**
     * @brief Returns @p true with probability @p p.
     *
     * @param rng  RNG instance to advance.
     * @param p    Probability of returning @p true, in [0.0, 1.0].
     * @return     @p true with probability @p p, @p false otherwise.
     *
     * @see KitraRngFloat
     */
    bool KitraRngChance(KitraRng *rng, float p);

    /**
     * @brief Seeds the global RNG with an explicit seed and stream.
     * @see KitraRngSeed
     */
    void KitraRandSeed(uint64_t seed, uint64_t stream);

    /**
     * @brief Seeds the global RNG automatically from the system clock.
     * @see KitraRngSeedAuto
     */
    void KitraRandSeedAuto(void);

    /**
     * @brief Returns the next raw 32-bit value from the global RNG.
     * @see KitraRngNext
     */
    uint32_t KitraRandNext(void);

    /**
     * @brief Returns a bounded random integer from the global RNG.
     * @see KitraRngUint
     */
    uint32_t KitraRandUint(uint32_t bound);

    /**
     * @brief Returns a random integer in [@p min, @p max] from the global RNG.
     * @see KitraRngInt
     */
    int KitraRandInt(int min, int max);

    /**
     * @brief Returns a random float in [0.0, 1.0) from the global RNG.
     * @see KitraRngFloat
     */
    float KitraRandFloat(void);

    /**
     * @brief Returns a random float in [@p min, @p max) from the global RNG.
     * @see KitraRngFloatRange
     */
    float KitraRandFloatRange(float min, float max);

    /**
     * @brief Returns a random point within @p bounds from the global RNG.
     * @see KitraRngPoint
     */
    KitraPoint KitraRandPoint(KitraRect bounds);

    /**
     * @brief Returns a random unit vector from the global RNG.
     * @see KitraRngDirection
     */
    KitraVec2f KitraRandDirection(void);

    /**
     * @brief Returns @p true with probability @p p from the global RNG.
     * @see KitraRngChance
     */
    bool KitraRandChance(float p);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_RNG_H_ */