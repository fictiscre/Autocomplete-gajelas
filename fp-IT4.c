#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(TrieNode* root, const char* key) {
    TrieNode* crawl = root;
    while (*key) {
        int index = *key - 'a';
        if (!crawl->children[index]) {
            crawl->children[index] = createNode();
        }
        crawl = crawl->children[index];
        key++;
    }
    crawl->isEndOfWord = 1;
}

TrieNode* searchNode(TrieNode* root, const char* key) {
    TrieNode* crawl = root;
    while (*key) {
        int index = *key - 'a';
        if (!crawl->children[index]) {
            return NULL;
        }
        crawl = crawl->children[index];
        key++;
    }
    return crawl;
}

void suggestWordsUtil(TrieNode* root, const char* prefix) {
    if (root->isEndOfWord) {
        printf("%s\n", prefix);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            char nextPrefix[100];
            sprintf(nextPrefix, "%s%c", prefix, i + 'a');
            suggestWordsUtil(root->children[i], nextPrefix);
        }
    }
}

void suggestWords(TrieNode* root, const char* prefix) {
    TrieNode* node = searchNode(root, prefix);
    if (node) {
        suggestWordsUtil(node, prefix);
    } else {
        printf("No suggestions found.\n");
    }
}

void updateWord(TrieNode* root, const char* oldKey, const char* newKey) {
    TrieNode* node = searchNode(root, oldKey);
    if (node) {
        node->isEndOfWord = 0;
        insert(root, newKey);
    }
}

int deleteWord(TrieNode* root, const char* key) {
    TrieNode* node = searchNode(root, key);
    if (node && node->isEndOfWord) {
        node->isEndOfWord = 0;
        return 1;
    }
    return 0;
}

int main() {
    TrieNode* root = createNode();
    char input[100];
    int choice;

    while (1) {
        printf("\n==============================\n");
        printf("AutoCorrect Menu\n");
        printf("==============================\n");
        printf("1. Add Word\n");
        printf("2. Search Suggestions\n");
        printf("3. Update Word\n");
        printf("4. Delete Word\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter word to add: ");
                scanf("%s", input);
                for (int i = 0; input[i]; i++) {
                    input[i] = tolower(input[i]);
                }
                insert(root, input);
                printf("Word added successfully.\n");
                break;
            case 2:
                printf("Enter prefix to search suggestions: ");
                scanf("%s", input);
                for (int i = 0; input[i]; i++) {
                    input[i] = tolower(input[i]);
                }
                suggestWords(root, input);
                break;
            case 3:
                printf("Enter old word to update: ");
                scanf("%s", input);
                char newInput[100];
                printf("Enter new word: ");
                scanf("%s", newInput);
                updateWord(root, input, newInput);
                printf("Word updated successfully.\n");
                break;
            case 4:
                printf("Enter word to delete: ");
                scanf("%s", input);
                if (deleteWord(root, input)) {
                    printf("Word deleted successfully.\n");
                } else {
                    printf("Word not found.\n");
                }
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}
