#include <stdio.h>
#include <stdlib.h>
// @see https://github.com/redis/redis/blob/unstable/src/hyperloglog.c
// redis/src/hyperloglog.c - hllPatLen()
// figures out which register an element belongs to,
// then counts the zero-run length from its hash
#define HLL_REGISTERS (1 << 14) // 16384 registers total
#define HLL_P         14        // first 14 bits pick the register

int hllPatLen(unsigned char *ele, size_t elesize, long *regp) {
    uint64_t hash, bit, index;
    int count;

    MurmurHash64A(ele, elesize, 0xadc83b19ULL, &hash);
    index = hash & HLL_P_MASK; // lower bits : register slot
    hash >>= HLL_P;

    // add a stop bit so the loop always terminates
    hash |= (uint64_t)1 << HLL_Q;
    bit = 1;
    count = 1;
    while ((hash & bit) == 0) {
        bit <<= 1;
        count++;
    }
    *regp = (long)index;
    return count; // zero streak length for this hashed element
}
// register only updates if this count beats the old max
// whole structure stays around ~12KB no matter how many items go through it