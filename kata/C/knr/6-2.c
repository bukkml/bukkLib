#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXBUF 100

typedef struct Node {
    char* word;
    int count;
    struct Node* left;
    struct Node* right;
} node;

char buf[MAXBUF];
size_t bp;

void* CreateNode();
node* AddNode(node* root, char* word);
char* CreateWord(char* word);
int GetWord(char* word, int lim, FILE* file);
int getch(FILE* file);
void ungetch(int c);
void PrintTree(node* root);
void DeleteTree(node* root);

int main(int argc, char** argv) {
    
    if (argc < 2) {
        printf("Need C programm name\n");
        return -1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Can't open file\n");
        return -1;
    }

    int PREFIX_COUNT  = ( argc == 3 &&
                          atoi(argv[2]) > 0 &&
                          atoi(argv[2]) < MAXWORD)
                          ? atoi(argv[2]) : 6;

    node* root = NULL;
    char word[MAXWORD];

    while ((GetWord(word, MAXWORD, file)) != EOF) {
        if ((isalpha(word[0]) || word[0] == '_') && strlen(word) >= PREFIX_COUNT) {
            for (int i = 0; i < PREFIX_COUNT; i++)
                word[i] = tolower(word[i]);
            word[PREFIX_COUNT] = '\0';
            root = AddNode(root, word);
            if (root == NULL) {
                break;
            }
        }
    }
    
    fclose(file);
    if (root != NULL) {
        PrintTree(root);
        DeleteTree(root);
    }

    return 0;
}

void* CreateNode() {
    return (node*)malloc(sizeof(struct Node));
}

node* AddNode(node* root, char* word) {
    int cond;
    if (root == NULL) {
        if(!(root = CreateNode()))
            return NULL;
        if(!(root->word = CreateWord(word))) {
            free(root);
            return NULL;
        }
        root->count = 1;
        root->left = root->right = NULL;
    }
    else if ((cond = strcmp(word, root->word)) == 0) {
        root->count++;
    }
    else if (cond < 0)
        root->left = AddNode(root->left, word);

    else
        root->right = AddNode(root->right, word);

    return root;
}

char* CreateWord(char* word) {
    char* w = (char*)malloc(sizeof(char) * strlen(word) + 1);
    if (w)
        w = strcpy(w, word);
    return w;
}

int GetWord(char* word, int lim, FILE* file) {
   int c; 
   char* w = word;
   while (isspace(c = getch(file)));
   if (c != EOF)
       *w++ = c;
   if (c == '\"') {
        for (; --lim > 0; w++) {
            if ((*w = getch(file)) == '\"')
                break;
        }
        *++w = '\0';
        return word[0];
   }
   if (c == '/') {
        c = getch(file);
        if (c == '/') {
            for ((*w++ = c) && (--lim > 0); --lim > 0; w++) {
                if ((*w = getch(file)) == '\n') {
                    *w++ = '\0';
                    return word[0];
                }
            }
        }
        else if (c == '*') {
            for ((*w++ = c) && (--lim > 0); --lim > 0; w++) {
                 if ((*w = getch(file)) == '/') {
                     if (*(w - 1) == '*') {
                         *++w = '\0';
                         return word[0];
                     }
                 }
            }
        }
        else {
            ungetch(c);
            *w = '\0';
            return '/';
        }
   }
   if (c == '#') {
        for (; --lim > 0; w++) {
            if ((*w = getch(file)) == '\n') {
                break;
            }
        }
   }
   if (!isalpha(c) && c != '_') {
       *w = '\0';
       return c;
   }
   for (; --lim > 0; w++) {
       if (!isalnum(*w = getch(file)) && *w != '_') {
           ungetch(*w);
           break;
       }
   }
   *w = '\0';
   return word[0];
}

int getch(FILE* file) {
    return (bp > 0) ? buf[--bp] : fgetc(file);
}

void ungetch(int c) {
    if (bp == MAXBUF) {
        printf("Buffer Owerflow\n");
        return;
    }
    buf[bp++] = c;
}

void PrintTree(node* root) {
    if (root == NULL) return;

    PrintTree(root->left);
    if (root->count > 1)
        printf("%4d %s\n", root->count, root->word);
    PrintTree(root->right);
}
void DeleteTree(node* root) {
    if (root == NULL) return;

    DeleteTree(root->left);
    DeleteTree(root->right);
    free(root->word);
    free(root);
}
