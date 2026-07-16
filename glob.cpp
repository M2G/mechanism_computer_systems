/*
 * glob.c : Port en C des deux algorithmes décrits par Russ Cox dans
 * "Glob Matching Can Be Simple And Fast Too" (research.swtch.com/glob)
*/

#include <string_view>

bool match_naive(std::string_view pattern, std::string_view name) {
    std::size_t px = 0, nx = 0;
    while (px < pattern.size() || nx < name.size()) {
        if (px < pattern.size()) {
            char c = pattern[px];
            if (c == '*') {
                // ...
            } else if (c == '?') {
                // ...
            } else {
                // ...
            }
        }
    }

    return true;
}
bool match_linear(std::string_view pattern, std::string_view name) {}