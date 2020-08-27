#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct node {
    char* val;
    struct node* next;
} node_t;

const int LINE_MAX_SIZE = 10000;

FILE* file;
node_t* lines;

void push(node_t* list, char* val) {
    node_t* currentNode = list;
    while(1) {
        if(currentNode->val == 0) {
            currentNode->val = malloc(sizeof(char) * LINE_MAX_SIZE);
            strcpy(currentNode->val, val);
            break;
        } else if (currentNode->next == NULL) {
            currentNode->next = (node_t*) malloc(sizeof(node_t));
            currentNode = currentNode->next;
        } else {
            currentNode = currentNode->next;
        }
    }
}

void fileToList(FILE* file, node_t* list) {
    char* line = NULL;
    size_t len = 0;
    while(getline(&line, &len, file) != -1) {
        push(list, line);
    }
}

void printList(node_t* list) {
    node_t* currentNode = list;
    while(currentNode != NULL) {
        printf("> %s", currentNode->val);
        currentNode = currentNode->next;
    }
}

int main(int argc, char* argv[]){

    file = fopen(argv[1], "r+");

    lines = (node_t*) malloc(sizeof(node_t));

    fileToList(file, lines);
    printList(lines);

    fclose(file);

    return 0;
}