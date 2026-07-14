/*
 * glob.c : Port en C des deux algorithmes décrits par Russ Cox dans
 * "Glob Matching Can Be Simple And Fast Too" (research.swtch.com/glob)
*/

#include <string_view>

bool match_naive(std::string_view pattern, std::string_view name) {}
bool match_linear(std::string_view pattern, std::string_view name) {}