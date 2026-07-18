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