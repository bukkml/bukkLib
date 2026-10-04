#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXBUF 100

typedef struct Node {
    char* word;
    int count;
    struct Node* left;
    struct Node* right;
}node;

node* CreateNode();
char* CreateWord(char* word);
int GetWord(char* word, int lim, FILE* file);
node* AddNode(node* root, char* word);
int getch(FILE* file);
void ungetch(int c);
node* SortTree(node* root);
int CountTree(node* root);
int CopyTreeToArray(node* root, node* arr, int count);
void CopyArrayToTree(node* arr, node* root, int* index);
int CompareNodes(const void* node1, const void* node2);
void PrintTree(node* root);
void DeleteTree(node* root);

char buf[MAXBUF];
int bp;

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("%s {file name} Expected\n", argv[0]);
        return -1;
    }

    FILE* file;
    node* root;
    char word[MAXWORD];

    file = fopen(argv[1], "r");
    if (!file) {
        printf("Can't open file %s\n", argv[1]);
        return -1;
    }

    root = NULL;

    while ((GetWord(word, MAXWORD, file)) != EOF) {
        root = AddNode(root, word);
    }

    root = SortTree(root);
    PrintTree(root);
    DeleteTree(root);
    fclose(file);
    return 0;
}

node* CreateNode() {
    return (node*)malloc(sizeof(node));
}

char* CreateWord(char* word) {
    char* w = (char*)malloc(strlen(word) + 1);
    if (w)
        strcpy(w, word);
    return w;
}

int GetWord(char* word, int lim, FILE* file) {
    int c;
    char *w = word;
    while (isspace(c = getch(file)));
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch(file))) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
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
        root->left = root->right = NULL;
    }
    else if ((cond = strcmp(word, root->word)) == 0) {
        root->count++;
    }
    else if (cond < 0) {
        root->left = AddNode(root->left, word);
    }
    else {
        root->right = AddNode(root->right, word);
    }
    return root;
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

node* SortTree(node* root) {
    int size = CountTree(root);
    if (size == 0) return root;

    node* arr = (node*)malloc(sizeof(node) * size);
    if (!arr) return root;

    int index = 0;

    CopyTreeToArray(root, arr, 0);
    qsort(arr, size, sizeof(node), CompareNodes);
    CopyArrayToTree(arr, root, &index);

    free(arr);

    return root;
}

int CountTree(node* root) {
    if (root == NULL) return 0;
    return 1 + CountTree(root->left) + CountTree(root->right);
}

int CopyTreeToArray(node* root, node* arr, int count) {
    if (root == NULL) return count;

    arr[count] = *root;
    arr[count].left = NULL;
    arr[count].right = NULL;
    count++;

    if (root->left !=  NULL)
        count = CopyTreeToArray(root->left, arr, count);
    if (root->right != NULL)
        count = CopyTreeToArray(root->right, arr, count);

    return count;
}

void CopyArrayToTree(node* arr, node* root, int* index) {
    if (root == NULL) return;

    CopyArrayToTree(arr, root->left, index);
    root->word = arr[*index].word;
    root->count = arr[*index].count;
    (*index)++;
    CopyArrayToTree(arr, root->right, index);
}

int CompareNodes(const void* node1, const void* node2) {
    return ((node*)node2)->count - ((node*)node1)->count;
}

void PrintTree(node* root) {
    if (root == NULL) return;

    PrintTree(root->left);
    printf("%d\t%s\n", root->count, root->word);
    PrintTree(root->right);
}

void DeleteTree(node* root) {
    if (root == NULL) return;

    DeleteTree(root->left);
    DeleteTree(root->right);
    free(root->word);
    free(root);
}
