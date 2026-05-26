// Simple Dynamic Strings (Redis) : gestion de chaînes de caractères dynamiques en C

struct sdshdr {
    unsigned int len; // longueur de la chaîne (sans le \0)
    unsigned int free; //
    char buf[]; // chaîne de caractères flexible
};

static inline size_t sdslen(const sds s) {
    struct sdshdr *hdr = (void *)(s - sizeof(struct sdshdr)); // recule le pointeur
    return hdr->len; // O(1), pas de strlen
}