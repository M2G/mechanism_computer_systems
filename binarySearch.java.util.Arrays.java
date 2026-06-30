/*



*/

// bug du dépassement arithmétique dans la recherche binaire
public static int binarySearch(int[] a, int key) {
    int low = 0;
    int high = a.length - 1;

    while (low <= high) {
        /*
        En Java, "int" est un entier signé de 32 bits, donc la somme de deux entiers peut dépasser la valeur maximale d'un int (2^31 - 1).
        Du coups, si on cherche dans un tableau de 2 millards d'éléments. À un moment donnée, "low" et "high" peuvent valoir quelque chose commme :
        low = 1_000_000_000
        high = 2_000_000_000

        Leur somme équivaut à 3_000_000_000. ce qui dépasse Integer.MAX_VALUE.
        En Java, ce dépassement ne lève pas d'exception (wtf?) il enroule silencieusement en négatif (modulo 2^32). mid devient alors un nombre négatif,
        ce qui provoque un "ArrayIndexOutOfBoundsException" en l'utilisant comme index ou pire un résultat silencieusement incorrect.

        Pourquoi cela à survécu 9ans :
        Le bug a été introduit dans java.utils.Array.binarySearch() en 1993 et n'a été découvert que en 2006 (wtf?) par Joshua Bloch.
        La raison de cette longévité est simple en 1993, les tableaux de plus de 2 millards d'éléments n'existaient pas en pratique.
        Le bug était donc théoriquement présent mais pratiquement inatteignable avec les machines de l'époque.

        int mid = (low + high) / 2; // NOTE: bug de dépassement arithmétique dans la recherche binaire. risque de dépassement arithmétique

        ici high - low est compris entre 0 et Integer.MAX_VALUE (puisque high >= low dans la boucle), donc la soustraction ne déborde jamais.
        On divise ensuite ce delta par 2, puis on ajoute à low le résultat est forcément entre low et high.

        */
        // variant avec décalage de bits.
        int mid = (low + high) >>> 1; // FIX : utilisation de l'opérateur de décalage pour éviter le dépassement

        /*




        */


        int midVal = a[mid];

        if (midVal < key) {
            low = mid + 1;
        } else if (midVal > key) {
            high = mid - 1;
        } else {
            return mid; // key found
        }
    }
    return -(low + 1);  // key not found
}