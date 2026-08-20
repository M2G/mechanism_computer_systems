#include "glob.h"

#include <string.h>

bool glob_match_naive(const char *pattern, size_t plen,
                      const char *name,    size_t nlen)
{}

bool glob_match_linear(const char *pattern, size_t plen,
                       const char *name,    size_t nlen)
{}

bool glob_naive(const char *pattern, const char *name)
{
    return glob_match_naive(pattern, strlen(pattern), name, strlen(name));
}

bool glob_linear(const char *pattern, const char *name)
{
    return glob_match_linear(pattern, strlen(pattern), name, strlen(name));
}
