// problem with qsort in C.
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
qsort(arr, n, sizeof(int), compare);

/*
 qsort : est une fonction générique de la libc. Pour rester générique sur n'importe quel type, elle ne peut appeler "compare" que via un pointer de fonction.
 Concrètement, à chaque comparaison dans la boucle de tri, le CPU doit :
 - Charger l'adresse de "compare" depuis la mémoire (le pointeur lui-même).
 - Faire un appel indirect ("call" [ref] plutôt qu'il "call" direct à une adresse connue à la compilation).
 - Le "void*" impose aussi un cast + déréférencement à chaque appel, ce qui ajoute du travail (overkill AF mais, c'est le but).

Notons deux pénalités mentionnées viennent de la :
- "Cache miss" l'adresse de la fonction peut ne pas être dans le cache d'instruction au moment où on nen a besoin, et surtout le CPU ne peut pas facilement précharger (prefetch)
le code de la fonction cible puisqu'il ne connait pas l'adresse qu'au "runtime".
- "Branch prediction penalty" les CPU modernes prédisent les branchements/sauts pour maintenir le pipeline plein.
Un appel direct, le predicteur de branchement indirect (BTB) doit deviner la cible, et se trompe plus souvent, ce qui vide la pipeline (pipeline flush).
 */

// solution C++ "std::sort" lamdba/template
std::sort(arr.begin(), arr.end(),
    [](int a, int b) { return a > b; })
/*
 std::sort est un template. Le type du comparateur (ici le type de la lambda, qui est unique et généré par le compilateur) fait partie du type du template lui-même.

 Résultat :
 - Le compilateur connait la fonction exacte à appeler dès la compilation, pas de pointeur de fonction, pas d'indirection).
 - Il peut donc inliner le corps de la lambda directement dans la bouche de tri.
 - Une fois inlinée a < b devient simple instruction de comparaison au milieu du code tri. pas d'appel du tout, donc ni cache miss, ni misprediction liés à un appel indirect.

 Le point clé: "zero-cost" :
 -

*/