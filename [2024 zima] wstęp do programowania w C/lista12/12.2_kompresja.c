#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTERS_COUNT 26
typedef struct Node node;

int compare(const void* p1, const void* p2);
node* generate_huffmann_tree(node** letter_trees, int idx);
void print_compressed_letter(node* root, char letter, char* code, int depth);
void in_order(node* root);

struct Node
{
    char letter;
    int freq;
    node* left;
    node* right;
};

node* create_node(char letter, int freq, node* left, node* right)
{
    node* new_tree = (node*)malloc(sizeof(node));
    if (new_tree == NULL) return NULL;
    new_tree -> letter = letter;
    new_tree -> freq = freq;
    new_tree -> left = left;
    new_tree -> right = right;
    return new_tree;
}

int main()
{
    // tablica na wezly drzew dla kazdej litery
    node* letter_trees[LETTERS_COUNT];
    for (int i = 0; i < LETTERS_COUNT; i++) letter_trees[i] = NULL;

    // wczytywanie liter i tworzenie wezla drzewa dla kazdej wystepujacej w tekscie
    int freq = 0;
    int valid_letters_count = 0;
    for (int i = 0; i < LETTERS_COUNT; i++)
    {
        scanf("%d", &freq);
        if (freq > 0) 
        {
            letter_trees[valid_letters_count] = create_node('a' + i, freq, NULL, NULL);
            valid_letters_count++;
        }
    }

    // wczytywanie tekstu do zakodowanie
    int n = 0;
    scanf("%d", &n);
    char* text = (char*)malloc(sizeof(char) * (n + 1));
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &text[i]);
    }

    // sortowanie liter ze wzgledu na czestotliwosc, a potem porzadek alfabetyczny
    qsort(letter_trees, valid_letters_count, sizeof(node*), compare);

    // generowanie drzewa huffmanna
    node* root = generate_huffmann_tree(letter_trees, valid_letters_count - 1);

    // wypisywanie zakodowanego tekstu
    char code[100];
    for (int i = 0; i < (int)strlen(text); i++)
    {
        print_compressed_letter(root, text[i], code, 0);
        printf(" ");
    }

    // zwalnianie pamieci
    free(text);
    for (int i = 0; i < LETTERS_COUNT; i++) if (letter_trees[i] != NULL) free(letter_trees[i]);
    return 0;
}   

int compare(const void* p1, const void* p2)
{
    node* tree1 = *(node**) p1;
    node* tree2 = *(node**) p2;

    if (tree1 -> freq > tree2 -> freq) return -1;
    else if (tree1 -> freq < tree2 -> freq) return 1;
    else if (tree1 -> letter < tree2 -> letter) return -1;
    else if (tree1 -> letter > tree2 -> letter) return 1;
    else return 0;
}

node* generate_huffmann_tree(node** letter_trees, int idx)
{
    while (idx > 0)
    {
        // stworzenie nowego wezla z dwoch ostanich
        node* right = letter_trees[idx]; idx--;
        node* left = letter_trees[idx];
        node* new_node = create_node('.', (left -> freq + right -> freq), left, right);

        // przesuniecie wezlow w tablicy
        int i = idx - 1;
        while (i >= 0 && letter_trees[i] -> freq < new_node -> freq)
        {
            letter_trees[i + 1] = letter_trees[i];
            i--;
        }
        letter_trees[i + 1] = new_node;
    }
    return letter_trees[0];
}

void print_compressed_letter(node* root, char letter, char* code, int depth)
{
    if (root == NULL) return;
    if (root -> left == NULL && root -> right == NULL)
    {
        if (root -> letter == letter)
        {
            code[depth] = '\0';
            printf("%s", code);
        }
        return;
    }

    code[depth] = '0';
    print_compressed_letter(root -> left, letter, code, depth + 1);

    code[depth] = '1';
    print_compressed_letter(root -> right, letter, code, depth + 1);
}