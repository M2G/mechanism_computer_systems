/*
 * glob.c : Port en C des deux algorithmes décrits par Russ Cox dans
 * "Glob Matching Can Be Simple And Fast Too" (research.swtch.com/glob)
*/

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static bool match_naive(const char *pattern, size_t pattern_len, const char *name, size_t name_len){}
static bool match_linear(const char *pattern, size_t pattern_len, const char *name, size_t name_len){}
static bool glob_naive(const char *pattern, const char *name){}
static bool glob_linear(const char *pattern, const char *name){}