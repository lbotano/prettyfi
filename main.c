#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

#include "utils.c"

int colSize = 50;
int doPrepend = 0;

node_t* lines;


// Puts breaklines in strings of a given list.
void putBreaklines(node_t* list) {
    node_t* currentNode = list;

    while (1) {
        // Check how many tabs or spaces to put for each line
        int prependSize = 0;
            for (int i = 0; currentNode->val[i] == '\0' || currentNode->val[i] == '\n' || currentNode->val[i] == ' ' || currentNode->val[i] == '\t'; i++) {
                prependSize++;
            }
            char prepend[prependSize + 2]; // +2 because of \n and \0
            prepend[0] = '\n';
        if (doPrepend) {
            for (int i = 1; i < prependSize + 1; i++) {
                prepend[i] = currentNode->val[i - 1];
            }
            prepend[prependSize + 2] = '\0';
        }
        
        int i = 1;
        int breaklinePos = colSize;
        while (currentNode->val[breaklinePos] != '\0') {
            if (currentNode->val[breaklinePos] == ' ') {
                strcpy(currentNode->val, currentNode->val);
                if (doPrepend) {
                    char *result;
                    putStringMiddle(currentNode->val, prepend, breaklinePos, &result);
                    strcpy(currentNode->val, result);
                } else {
                    currentNode->val[breaklinePos] = '\n';
                }
                if (breaklinePos + colSize < strlen(currentNode->val)) {
                    i++;
                    breaklinePos += colSize;
                }
            } else {
                breaklinePos++;
            }
        }

        if (currentNode->next == NULL) break;
        currentNode = currentNode->next;
    }
}

void help() {
    printf("prettyfi 1.0 (2 Sep 2020, compiled %s %s)\n", __DATE__, __TIME__);
    puts("lbotano 2020");
    puts("Usage: prettyfi <file> [arguments ..]");
    puts("Arguments:");
    puts("-h or --help: Display this help message");
    puts("-c <character limit>: Set the limit of characters in the file (default is 50)");
    puts("-p: To take in count tabulation");
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

// Tokenizes the passed arguments.
void analyzeArguments(char* argv[], int argc) {
    // Display help if no arguments are passed
    if (argc <= 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        help();

    int i = 2;
    char* arg = argv[i];
    while (arg != NULL) {
        int argLength = 1;
        if (strcmp(arg, "-c") == 0) {
            argLength = 2;
            setColSize(argv[i + 1]);
        } else if (strcmp(arg, "-p") == 0) {
            doPrepend = 1;
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
    putBreaklines(lines);
    listToFile(lines, argv[1]);


    return 0;
}
