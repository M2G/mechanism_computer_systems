/*
 * glob_test.cpp : Tests unit.  glob::match_naive /
 *                 glob::match_linear.
 *
 * Usage :
 *   ./glob_test [max_n] [name_len]
 *   ./glob_test 12 100     # défaut
 */

#include "glob.hpp"

#include <chrono>
#include <string>
#include <vector>

// Tests unitaires
struct TestCase {
    std::string_view pattern;
    std::string_view name;
    bool expected;
};

static int run_unit_tests()
{
    const std::vector<TestCase> cases = {
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
        {"a*bx*cy*d",    "abxbxcyd",        true},   // piège : premier bx, pas le second
        {"a*bx*cy*d",    "a_cy_d",          false},
        {"*a*a*a*a*b",   "aaaaaaaaaaaab",   true},
        {"*a*a*a*a*b",   "aaaaaaaaaaaac",   false},
        {"",             "",                true},
        {"",             "x",               false},
        {"abc",          "",                false},
    };

    int failures = 0;
    for (const auto& tc : cases) {
        bool rn = glob::match_naive (tc.pattern, tc.name);
        bool rl = glob::match_linear(tc.pattern, tc.name);
        bool ok = (rn == tc.expected) && (rl == tc.expected);
        std::printf("[%s] pattern=%-18.*s name=%-16.*s attendu=%-5s naive=%-5s linear=%-5s\n",
            ok ? "OK" : "FAIL",
            (int)tc.pattern.size(), tc.pattern.data(),
            (int)tc.name.size(),    tc.name.data(),
            tc.expected ? "true" : "false",
            rn          ? "true" : "false",
            rl          ? "true" : "false");
        if (!ok) ++failures;
    }
    std::printf("\n%d/%d tests réussis\n",
        (int)cases.size() - failures, (int)cases.size());
    return failures;
}

int main()
{
    std::printf("=== Tests unitaires ===\n");
    int failures = run_unit_tests();

    return failures ? 1 : 0;
}