// Simple Dynamic Strings (Redis) : gestion de chaînes de caractères dynamiques en C

/*
* Sources vérifiées
* Code source actuel : github.com/redis/redis/blob/unstable/src/sds.h
* Code source actuel : github.com/redis/redis/blob/unstable/src/sds.c
* Vrai commit des size classes (2015) : github.com/redis/redis/commit/f15df8ba5db09bdf4be58c53930799d82120cc34
*/

struct sdshdr {
    unsigned int len; // longueur de la chaîne (sans le \0)
    unsigned int free; //
    char buf[]; // chaîne de caractères flexible
};

static inline size_t sdslen(const sds s) {
    struct sdshdr *hdr = (void *)(s - sizeof(struct sdshdr)); // recule le pointeur
    return hdr->len; // O(1), pas de strlen
}