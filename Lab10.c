//Madison Manankil
//COP 3502
//LAB 10
//April 19, 2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*NOTE FOR TA*: To run code do the command prompt and type Lab10.exe<dictionary.txt

#define ALPHABET_SIZE 26

//part 1
// Trie node structure
struct TrieNode {
    int count;                          // this will count the word occurrences
    struct TrieNode *children[ALPHABET_SIZE];  //then this id the array of child nodes
};

//part 2
// this will create a new trie node
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    node->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

//part 3
// then this inserts the word into the trie
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *node = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) {
            node->children[index] = createNode();
        }
        node = node->children[index];
    }
    node->count++;
}

//part 4
// this next will search for the word in the trie and returns its count
int search(struct TrieNode *root, char *word) {
    struct TrieNode *node = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) {
            return 0;
        }
        node = node->children[index];
    }
    return node->count;
}

//part 5
// this will deallocates the trie
void deallocateTrie(struct TrieNode *root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        deallocateTrie(root->children[i]);
    }
    free(root);
}

//part 6
// this will then read the words from the dictionary file
int readDictionary(char *filename, char **words) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 0;
    }
    int numWords;
    fscanf(file, "%d", &numWords);
    for (int i = 0; i < numWords; i++) {
        words[i] = (char *)malloc(100 * sizeof(char));
        fscanf(file, "%s", words[i]);
    }
    fclose(file);
    return numWords;
}
//part 6
//main statement
int main() {
    char *words[256];
    int numWords = readDictionary("dictionary.txt", words);

    // this part of the main will create the trie root
    struct TrieNode *root = createNode();

    // then this part of the main will insert words into the trie
    for (int i = 0; i < numWords; i++) {
        insert(root, words[i]);
    }

    // this will then search for words and print their counts 
    char *searchWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int numSearchWords = sizeof(searchWords) / sizeof(searchWords[0]);
    for (int i = 0; i < numSearchWords; i++) {
        int count = search(root, searchWords[i]);
        printf("%s : %d\n", searchWords[i], count);
    }

    // most importantly to deallocate the trie
    deallocateTrie(root);

    // then afyter we need to free the memory allocated for the words
    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }

    return 0;
}