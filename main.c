#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct node {
    char* val;
    struct node* next;
} node_t;

const int LINE_MAX_SIZE = 10000;
const int COLUMN_SIZE = 40;
node_t* lines;

void push(node_t* list, char* val) {
    node_t* currentNode = list;
    while(1) {
        if(currentNode->val == 0) {
            currentNode->val = malloc(sizeof(char) * LINE_MAX_SIZE);
            strcpy(currentNode->val, val);
            break;
        } else {
            if (currentNode->next == NULL)
                currentNode->next = (node_t*) malloc(sizeof(node_t));
            currentNode = currentNode->next;
        }
    }
}

void fileToList(const char* filename, node_t* list) {
    FILE* file = fopen(filename, "r");
    char* line = NULL;
    size_t len = 0;
    while(getline(&line, &len, file) != -1) {
        push(list, line);
    }
    fclose(file);
}

void printList(node_t* list) {
    node_t* currentNode = list;
    while(currentNode != NULL) {
        printf("%s", currentNode->val);
        currentNode = currentNode->next;
    }
}

void putBreakpoints(node_t* list) {
    node_t* currentNode = list;
    while(1) {
        int i = 1;
        int breaklinePos = COLUMN_SIZE;
        while (currentNode->val[breaklinePos] != '\0') {
            if (currentNode->val[breaklinePos] == ' ') {
                currentNode->val[breaklinePos] = '\n';
                if (i * COLUMN_SIZE < strlen(currentNode->val)) {
                    i++;
                    breaklinePos = i * COLUMN_SIZE;
                }
            } else {
                breaklinePos++;
            }
        }

        if(currentNode->next == NULL) break;
        currentNode = currentNode->next;
    }
}

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

int main(int argc, char* argv[]){
    lines = (node_t*) malloc(sizeof(node_t));

    fileToList(argv[1], lines);
    putBreakpoints(lines);
    printList(lines);
    //listToFile(lines, argv[1]);

    return 0;
}