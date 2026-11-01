#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

typedef struct node {
    struct node* next;
    char* name;
    char* defn;
} hnode;

hnode* hashtab[HASHSIZE];

unsigned int hash(char* s);
hnode* lookup(char* s);
hnode* install(char* name, char* defn);
void undef(char* name);

int main() {

    return 0;
}

unsigned int hash(char* s) {
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

hnode* lookup(char* s) {
    hnode* np;
    
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

hnode* install(char* name, char* defn) {
    hnode* np;
    unsigned int hashval;
    
    if (!(np = lookup(name))) {
        np = (hnode*)malloc(sizeof(*np));
        if (!np || !(np->name = strdup(name))) return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((char*)np->defn);
    }
    if (!(np->defn = strdup(defn))) return NULL;

    return np;
}

void undef(char* name) {
    hnode* np;
    if (!np = lookup(name)) return;

    unsigned int hashval = hash(name);

    if (hashtab[hashval] == np) {
        hashtab[hashval] = np->next;
    } else {
        hnode* prev = hashtab[hashval];
        while (prev->next != np) prev = prev->next;
        prev->next = np->next;
        }
    free(np->name);
    free(np->defn);
    free(np);
}
