#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2

// Enumeration for possible stack operation outcomes
typedef enum {
    OK,
    ERROR_MEMORY,
    ERROR_EMPTY
} Status;

// Structure for the stack
typedef struct {
    char** elements;
    int cap;
    int topIndex;
} StrStack;

// Structure for operation results
typedef struct {
    Status result;
    char* value;
} OpResult;

// Declarations
StrStack* initializeStack();
OpResult addToStack(StrStack* s, const char* str);
OpResult removeFromStack(StrStack* s);
void freeStack(StrStack* s);

// Main function
int main() {
    StrStack* s = initializeStack();
    OpResult res;

    res = addToStack(s, "Hello");
    if (res.result != OK) {
        printf("Failed to add item.\n");
    }

    res = addToStack(s, "World");
    if (res.result != OK) {
        printf("Failed to add item.\n");
    }

    // Display stack content
    for (int i = 0; i <= s->topIndex; i++) {
        printf("%s\n", s->elements[i]);
    }

    res = removeFromStack(s);
    if (res.result == OK) {
        printf("Removed: %s\n", res.value);
        free(res.value);
    } else {
        printf("Failed to remove item.\n");
    }

    // Print the stack size after popping
    printf("Stack size after popping: %d\n", s->topIndex + 1);

    freeStack(s);
    return 0;
}

StrStack* initializeStack() {
    StrStack* s = (StrStack*)malloc(sizeof(StrStack));
    if (s) {
        s->elements = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
        if (!s->elements) {
            free(s);
            return NULL;
        }
        s->cap = INITIAL_CAPACITY;
        s->topIndex = -1;
    }
    return s;
}

OpResult addToStack(StrStack* s, const char* str) {
    OpResult res;
    if (s->topIndex + 1 == s->cap) {
        int newCap = s->cap * 2;
        char** newElements = (char**)realloc(s->elements, newCap * sizeof(char*));
        if (!newElements) {
            res.result = ERROR_MEMORY;
            return res;
        }
        s->elements = newElements;
        s->cap = newCap;
    }
    s->elements[++s->topIndex] = strdup(str);
    if (!s->elements[s->topIndex]) {
        res.result = ERROR_MEMORY;
        return res;
    }
    res.result = OK;
    return res;
}

OpResult removeFromStack(StrStack* s) {
    OpResult res;
    if (s->topIndex == -1) {
        res.result = ERROR_EMPTY;
    } else {
        res.value = s->elements[s->topIndex];
        s->elements[s->topIndex--] = NULL;
        res.result = OK;
    }
    return res;
}

void freeStack(StrStack* s) {
    if (s) {
        for (int i = 0; i <= s->topIndex; i++) {
            free(s->elements[i]);
        }
        free(s->elements);
        free(s);
    }
}
