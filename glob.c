#include "glob.h"

#include <string.h>

bool glob_match_naive(const char *pattern, size_t plen,
                      const char *name,    size_t nlen) {

    size_t px = 0, nx = 0;

    while (px < plen || nx < nlen) {
        if (px < plen) {
            char c = pattern[px];
            if (c == '*') {
                for (size_t k = nx; k <= nlen; k++) {
                    if (glob_match_naive(pattern + px + 1, plen - px - 1, name + k, nlen - k)) return true;
                }
                return false;
            }
            if (c == '?') {
                if (nx < nlen) {
                    ++px;
                    ++nx;
                    continue;
                }
            } else {
                if (nx < nlen && name[nx] == c) {
                    ++px;
                    ++nx;
                    continue;
                }
            }
        }
        return false;
    }
    return true;
}

bool glob_match_linear(const char *pattern, size_t plen,
                       const char *name,    size_t nlen) {
    size_t px = 0, nx = 0;
    size_t next_px = 0, next_nx = 0;
    bool have_star = false;
    while (px < plen || nx < nlen) {
        if (px < plen) {
            char c = pattern[px];
            if (c == '*') {
                next_px = px;
                next_nx = nx + 1;
                have_star = true;
                ++px;
                continue;
            }
            // same logic
            if (c == '?') {
                if (nx < nlen) {
                    ++px;
                    ++nx;
                    continue;
                }
            } else {
                if (nx < nlen && name[nx] == c) {
                    ++px;
                    ++nx;
                    continue;
                }
            }
            // if have_star = true
            // ...
        }
        return false;
    }
    return true;
}

bool glob_naive(const char *pattern, const char *name)
{
    return glob_match_naive(pattern, strlen(pattern), name, strlen(name));
}

bool glob_linear(const char *pattern, const char *name)
{
    return glob_match_linear(pattern, strlen(pattern), name, strlen(name));
}
