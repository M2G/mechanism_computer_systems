#define _POSIX_C_SOURCE 200809L
/*
 * glob_test.c : Tests unitaires pour glob_match_naive et glob_match_linear.
 */

#include "glob.h"
#include <stdio.h>

// TU
typedef struct {
    const char *pattern;
    const char *name;
    bool        expected;
} TestCase;

static int run_unit_tests(void)
{
    static const TestCase cases[] = {
        {"a",            "a",               true},
        {"a",            "b",               false},
        {"*",            "",                true},
        {"*",            "anything",        true},
        {"a*b",          "ab",              true},
        {"a*b",          "aXXXb",           true},
        {"a*b",          "aXXXbY",          false},
        {"a?c",          "abc",             true},
        {"a?c",          "ac",              false},
        {"a*bx*cy*d",    "a123bx456cy789d", true},
        {"a*bx*cy*d",    "abxbxcyd",        true},  //  NB: piège : premier bx
        {"a*bx*cy*d",    "a_cy_d",          false},
        {"*a*a*a*a*b",   "aaaaaaaaaaaab",   true},
        {"*a*a*a*a*b",   "aaaaaaaaaaaac",   false},
        {"",             "",                true},
        {"",             "x",               false},
        {"abc",          "",                false},
    };
    int n = (int)(sizeof(cases) / sizeof(cases[0]));
    int failures = 0;

    for (int i = 0; i < n; ++i) {
        bool rn = glob_naive (cases[i].pattern, cases[i].name);
        bool rl = glob_linear(cases[i].pattern, cases[i].name);
        bool ok = (rn == cases[i].expected) && (rl == cases[i].expected);
        printf("[%s] pattern=%-18s name=%-16s attendu=%-5s naive=%-5s linear=%-5s\n",
            ok ? "OK" : "FAIL",
            cases[i].pattern,
            cases[i].name,
            cases[i].expected ? "true" : "false",
            rn                ? "true" : "false",
            rl                ? "true" : "false");
        if (!ok) ++failures;
    }
    printf("\n%d/%d tests réussis\n", n - failures, n);
    return failures;
}

int main()
{
    printf("=== Tests unitaires ===\n");
    int failures = run_unit_tests();

    return failures ? 1 : 0;
}