// A classic performance issue in C
// Problem: strlen() in a loop
void process(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        s[i] = toupper(s[i]);
    }
}

// strlen() traverses the entire string up to the null character \0 to count the characters.
// This is an O(n) operation. However, the loop calls it on every iteration-resulting in an overall complexity of O(n^2) instead of O(n).
// For a string of 1,000 characters, that’s one million operations instead of a thousand.

// FIX :
void process(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        s[i] = toupper(s[i]);
    }
}

/* The length is calculated only once before the loop.
 * The PostgreSQL Patch
 * This is exactly what this patch proposes, submitted to the PostgreSQL developers mailing list in November 2019 by Ranier Vilela : to avoid repeatedly calling "strlen()" within loops in the authentication code ("auth.c").
 * The patch pre-calculates the length of the strings (secret, passwd, ident_query) before the relevant loops.
 * Patch avoid call strlen repeatedly in loop (line no. 1798) : https://www.postgresql.org/message-id/MN2PR18MB29274AF58676ACB8DDEF90D6E37B0@MN2PR18MB2927.namprd18.prod.outlook.com
*/