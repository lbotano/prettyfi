#include <string.h>

#define LINE_MAX_SIZE 50000

typedef struct node {
    struct node* next;
    char val[LINE_MAX_SIZE + 1];
} node_t;

// Adds a string to a linked list
void push(node_t* list, char* val) {
    node_t* currentNode = list;
    while (1) {
        if (strlen(currentNode->val) == 0) {
            strncpy(currentNode->val, val, sizeof(currentNode->val));
            currentNode->val[(sizeof(currentNode->val)/sizeof(char)) - 1] = '\0';
            break;
        } else {
            if (currentNode->next == NULL)
                currentNode->next = (node_t*) malloc(sizeof(node_t));
            currentNode = currentNode->next;
        }
    }
}

// Loads file to a linked list of strings.
void fileToList(const char* filename, node_t* list) {
    FILE* file;
    if (!(file = fopen(filename, "r"))) {
        printf("Error: %s: %s\n", strerror(errno), filename);
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t len = 0;
    while(getline(&line, &len, file) != -1) {
        push(list, line);
    }
    fclose(file);
}

// Saves strings from a linked list to a file
void listToFile(node_t* list, const char* filename) {
    FILE* file = fopen(filename, "w");
    node_t* currentNode = list;
    while(1) {
        fputs(currentNode->val, file);
        if(currentNode->next == NULL) break;
        currentNode = currentNode->next;
    }
    fclose(file);
}

// Prints a list of strings.
void printList(node_t* list) {
    node_t* currentNode = list;
    while (currentNode != NULL) {
        printf("line>%s", currentNode->val);
        currentNode = currentNode->next;
    }
}

// Puts a string2 in the middle of string1 at pos
void putStringMiddle(char* string1, char* string2, int pos, int offset, char** dest) {
    char *result = malloc(sizeof(char) * (strlen(string1) + strlen(string2)) + 1);
    *result = '\0';
    strncat(result, string1, pos);
    strcat(result, string2);
    strcat(result, string1 + pos + offset);
    
    *dest = result;
}