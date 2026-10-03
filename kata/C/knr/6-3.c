#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXBUF 100
#define MAXSIZE 1000

typedef struct Node {
    char* word;
    int* lines;
    int count;
    struct Node* left;
    struct Node* right;
} node;

char buf[MAXBUF];
size_t bp;

size_t line;

node* CreateNode();
char* CreateWord(char *word);
node* AddNode(node* root, char* word);
int GetWord(char* word, int lim, FILE* file);
int getch(FILE* file);
void ungetch(int c);
void PrintTree(node* root);
void DeleteTree(node* root);
bool is_filler(char* word);

const char* filler_words[] = {
    "ну",
    "эм",
    "вот",
    "это",
    "как бы",
    "типа",
    "короче",
    "в общем",
    "вообще",
    "просто",
    "реально",
    "эта",
    "это",
    "и",
    "или",
    "а",
    "в",
    "к",
};

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("%s {File name} Expected.\n", argv[0]);
        return -1;
    }

    node* root;
    char word[MAXWORD];

    line = 0;
    root = NULL;
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Cant open file:%s\n", argv[1]);
        return -1;
    }

    while ((GetWord(word, MAXWORD, file)) != EOF) {
        for (int i = 0; i < strlen(word); i++)
            word[i] = tolower(word[i]);
        if (!is_filler(word)) {
            root = AddNode(root, word);
        }
    }

    PrintTree(root);
    DeleteTree(root);
    fclose(file);

    return 0;
}

node* CreateNode() {
    return (node*)malloc(sizeof(struct Node));
}

char* CreateWord(char *word) {
    char* w = (char*)malloc(strlen(word) + 1);
    if (w)
        strcpy(w, word);
    return w;
}

int* CreateLines(int size) {
    return (int*)malloc(sizeof(int) * size);
}

node* AddNode(node* root, char* word) {
    int cond;
    if (root == NULL) {
        if (!(root = CreateNode()))
            return NULL;
        if (!(root->word = CreateWord(word))) {
            free(root);
            return NULL;
        }
        root->count = 1;
        if (!(root->lines = CreateLines(root->count))) {
            free(root->word);
            free(root);
            return NULL;
        }
        root->lines[0] = line;
        root->left = root->right = NULL;
    }
    else if ((cond = strcmp(word, root->word)) == 0) {
        if (root->lines[root->count - 1] != line) {
            int *tmp = realloc(root->lines, sizeof(int) * (root->count + 1));
            if (tmp == NULL)
                return root;

            root->lines = tmp;
            root->lines[root->count++] = line;
    }
    else if (cond < 0)
        root ->left = AddNode(root->left, word);
    else
        root->right = AddNode(root->right, word);
    return root;
}

int GetWord(char* word, int lim, FILE* file) {
    int c; 
    char* w = word;
    while (isspace(c = getch(file)))
        if (c == '\n')
            line++;
    if (c != EOF)
       *w++ = c;
    if (!isalpha(c) && c != '_' && c != '#') {
        if (*w == '\n')
            line++;
        *w = '\0';
        return c;
   }
    for (; --lim > 0; w++) {
       if (!isalnum(*w = getch(file)) && *w != '_' && *w != '#') {
            if (*w == '\n') {
                line++;
                break;
            }
            ungetch(*w);
            break;
        }
    }
    if (*w == '\n')
        line++;
    *w = '\0';
    return word[0];
}

int getch(FILE* file) {
    return (bp > 0) ? buf[--bp] : fgetc(file);
}

void ungetch(int c) {
    if (bp == MAXBUF) {
        printf("Buffer owerflow\n");
        return;
    }
    buf[bp++] = c;
}

void PrintTree(node* root) {
    if (root == NULL) return;

    PrintTree(root->left);
    printf("%s: ", root->word);
    for (int i = 0; i < root->count; i++)
        printf("%d, ", root->lines[i]);
    printf("\n");
    PrintTree(root->right);
}
void DeleteTree(node* root) {
    if (root == NULL) return;

    DeleteTree(root->left);
    DeleteTree(root->right);
    free(root->word);
    free(root->lines);
    free(root);
}
bool is_filler(char* word) {
    for (int i = 0; i < sizeof(filler_words) / sizeof(*filler_words); i++) {
        if (strcmp(word, filler_words[i]) == 0)
            return true;
    }
    return false;
}
