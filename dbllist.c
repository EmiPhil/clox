//
// Created by phil on 2021-05-03.
//

#include <stdio.h>
#include <string.h>
#include "dbllist.h"

typedef struct Nodes {
    char data[50];
    struct Nodes *prev;
    struct Nodes *next;
} Node;

typedef struct DoubleLinkedList {
    struct Nodes *first;
    struct Nodes *last;
} Dll;

void find(struct DoubleLinkedList *list, struct Nodes *node, char str[50]) {
    struct Nodes *current = list->first;
    if (!current) {
        return;
    }

    current = current->next;
    do {
        if (strcmp(current->data, str) == 0) {
            *node = *current;
            return;
        }
        current = current->next;
    } while (current);

    *node = (struct Nodes){};
}

void insertFirst(struct DoubleLinkedList *list, struct Nodes *node) {
    if (list->first) {
        node->next = list->first;
        list->first->prev = node;
    }
    list->first = node;
    list->first->prev = NULL;
}

void insertLast(struct DoubleLinkedList *list, struct Nodes *node) {
    if (list->last) {
        node->prev = list->last;
        list->last->next = node;
    }
    list->last = node;
    list->last->next = NULL;
}

void makeList(struct DoubleLinkedList *list, struct Nodes *first, struct Nodes *last) {
    list->first = first;
    list->last = last;

    first->prev = NULL;
    first->next = last;

    last->prev = first;
    last->next = NULL;
}

void insertBefore(struct DoubleLinkedList *list, struct Nodes *node, struct Nodes *newNode) {
    if (!node->prev) {
        return insertFirst(list, newNode);
    }

    newNode->next = node;
    newNode->prev = node->prev;
    node->prev->next = newNode;
    node->prev = newNode;
}

void insertAfter(struct DoubleLinkedList *list, struct Nodes *node, struct Nodes *newNode) {
    if (!node->next) {
        return insertLast(list, newNode);
    }

    newNode->prev = node;
    newNode->next = node->next;
    node->next->prev = newNode;
    node->next = newNode;
}

void removeNode(struct DoubleLinkedList *list, struct Nodes *node) {
    if (!node->prev) {
        node->next->prev = NULL;
        list->first = node->next;
        return;
    }
    if (!node->next) {
        node->prev->next = NULL;
        list->last = node->prev;
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

int main() {
    struct DoubleLinkedList dll;
    struct Nodes first;
    struct Nodes last;

    makeList(&dll, &first, &last);

    strcpy(first.data, "hello");
    strcpy(last.data, "world");

    struct Nodes newFirst;
    struct Nodes newLast;
    strcpy(newFirst.data, "START");
    strcpy(newLast.data, "END");

    insertFirst(&dll, &newFirst);
    insertLast(&dll, &newLast);

    struct Nodes before;
    strcpy(before.data, "BEFORE");
    insertBefore(&dll, &first, &before);

    struct Nodes after;
    strcpy(after.data, "AFTER");
    insertAfter(&dll, &last, &after);

    removeNode(&dll, &before);
    removeNode(&dll, &after);
    removeNode(&dll, &newFirst);
    removeNode(&dll, &newLast);

    insertBefore(&dll, &first, &newFirst);
    insertAfter(&dll, &last, &newLast);

    struct Nodes findMe;
    strcpy(findMe.data, "Find me!");
    insertAfter(&dll, &first, &findMe);

    struct Nodes found;
    find(&dll, &found, "Find me!");
    find(&dll, &found, "nothing!");

    return 0;
}