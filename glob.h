#ifndef GLOB_H
#define GLOB_H
/*
 * glob.h : Glob matching, port C de Russ Cox
 * Source : https://research.swtch.com/glob
 *
 * Deux fonctions :
 *   glob_match_naive : backtracking récursif, pire cas exponentiel
 *   glob_match_linear : itératif
*/

#include <stdbool.h>
#include <stddef.h>

bool glob_match_naive (const char *pattern, size_t plen,
                       const char *name,    size_t nlen);

bool glob_match_linear(const char *pattern, size_t plen,
                       const char *name,    size_t nlen);

bool glob_naive (const char *pattern, const char *name);
bool glob_linear(const char *pattern, const char *name);

#endif