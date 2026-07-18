#pragma once
/*
 * glob.hpp : Glob matching, port C++ de Russ Cox
 * Source : https://research.swtch.com/glob
 *
 * Deux fonctions publiques :
 *   glob::match_naive  : backtracking récursif, pire cas exponentiel
 *   glob::match_linear : itératif, O(|pattern| × |name|)
 *
 * Toutes deux acceptent des std::string_view : pas de copie, pas d'allocation,
 * compatibles avec const char*, std::string, et tout type converti en vue.
 */

#include <string_view>

namespace glob {

    // Backtracking récursif complet sur chaque '*'.
    // Traduction du 2e bloc Go de l'article.
    bool match_naive(std::string_view pattern, std::string_view name);

    // Ne retient que le dernier '*' vu comme point de reprise.
    // Traduction du 3e bloc Go de l'article.
    bool match_linear(std::string_view pattern, std::string_view name);

} // namespace glob