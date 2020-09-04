#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>

typedef struct node {
    char* val;
    struct node* next;
} node_t;

const int LINE_MAX_SIZE = 10000;

int colSize = 50;
node_t* lines;

void push(node_t* list, char* val) {
    node_t* currentNode = list;
    while (1) {
        if (currentNode->val == 0) {
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

void printList(node_t* list) {
    node_t* currentNode = list;
    while (currentNode != NULL) {
        printf("%s", currentNode->val);
        currentNode = currentNode->next;
    }
}

void putBreakpoints(node_t* list) {
    node_t* currentNode = list;
    while (1) {
        int i = 1;
        int breaklinePos = colSize;
        while (currentNode->val[breaklinePos] != '\0') {
            if (currentNode->val[breaklinePos] == ' ') {
                currentNode->val[breaklinePos] = '\n';
                if (i * colSize < strlen(currentNode->val)) {
                    i++;
                    breaklinePos = i * colSize;
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

void help() {
    printf("prettyfi 1.0 (2 Sep 2020, compiled %s %s)\n", __DATE__, __TIME__);
    puts("lbotano 2020");
    puts("Usage: prettyfi <file> [arguments ..]");
    puts("Arguments:");
    puts("-h or --help: Display this help message");
    puts("-c <character limit>: Set the limit of characters in the file (default is 50)");
    exit(EXIT_SUCCESS);
}

void setColSize(char* arg) {
    if (arg == NULL) {
        puts("Error: no character limit specified.");
        exit(EXIT_FAILURE);
    }

    colSize = strtoumax(arg, NULL, 10);
    if (errno == ERANGE) {
        printf("Error: invalid character limit: %s\n", arg);
        exit(EXIT_FAILURE);
    }
}

void analyzeArguments(char* argv[], int argc) {
    if (argc <= 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        help();

    int i = 2;
    char* arg = argv[i];
    while (arg != NULL) {
        int argLength = 1;
        if (strcmp(arg, "-c") == 0) {
            argLength = 2;
            setColSize(argv[i + 1]);
        } else {
            printf("Invalid argument: %s\n", arg);
            exit(EXIT_FAILURE);
        }
        i += argLength;
        arg = argv[i];
    }
}


int main(int argc, char* argv[]){
    lines = (node_t*) malloc(sizeof(node_t));

    analyzeArguments(argv, argc);
    fileToList(argv[1], lines);
    putBreakpoints(lines);
    listToFile(lines, argv[1]);

    return 0;
}
