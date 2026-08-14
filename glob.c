/*
 * glob.c : Port en C des deux algorithmes décrits par Russ Cox dans
 * "Glob Matching Can Be Simple And Fast Too" (research.swtch.com/glob)
*/

#include <print>
#include <string_view>

namespace glob {
    bool match_naive(std::string_view pattern, std::string_view name) {

        std::println("[naive] pattern={} name={}", pattern, name);

        std::size_t px = 0, nx = 0;
        while (px < pattern.size() || nx < name.size()) {
            if (px < pattern.size()) {
                char c = pattern[px];
                if (c == '*') {
                    for (std::size_t k = nx; k < name.size(); ++k) {
                        if (match_naive(pattern.substr(px + 1), name.substr(k)))
                            return true;
                    }
                    return false;
                }
                if (c == '?') {
                    if (nx < name.size()) { ++px; ++nx; continue; }
                } else {
                    if (nx < name.size() && name[nx] == c) { ++px; ++nx; continue; }
                }
            }
            return false;
        }

        return true;
    }
    bool match_linear(std::string_view pattern, std::string_view name) {
        std::println("linear pattern={} name={}", pattern, name);

        std::size_t px = 0, nx = 0;
        std::size_t next_px = 0, next_nx = 0;
        bool have_star = false;

        while (px < pattern.size() || nx < name.size()) {
            if (px < pattern.size()) {
                char c = pattern[px];
                if (c == '*') {
                    // ...
                } else if (c == '?') {
                    if (nx < name.size()) { ++p; ++nx; continue; }
                    // ...
                } else {
                    if (nx < name.size() && name[nx] == c) { ++p; ++nx; continue; }
                    // ...
                }
                // ..
            }
        }

        return true;
    }
}