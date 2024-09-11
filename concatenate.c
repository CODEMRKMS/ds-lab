#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Doubly Linked List structure
typedef struct DoublyLinkedList {
    Node* head;
} DoublyLinkedList;

// Function prototypes
Node* createNode(int data);
void append(DoublyLinkedList* list, int data);
void concatenate(DoublyLinkedList* list1, DoublyLinkedList* list2);
void traverse(DoublyLinkedList* list);
void freeList(DoublyLinkedList* list);

int main() {
    DoublyLinkedList list1 = {NULL};
    DoublyLinkedList list2 = {NULL};

    // Example usage
    append(&list1, 1);
    append(&list1, 2);
    append(&list1, 3);

    append(&list2, 4);
    append(&list2, 5);

    printf("List 1 before concatenation: ");
    traverse(&list1);

    printf("List 2 before concatenation: ");
    traverse(&list2);

    concatenate(&list1, &list2);

    printf("List 1 after concatenation: ");
    traverse(&list1);

    printf("List 2 after concatenation (should be empty): ");
    traverse(&list2);

    // Free memory
    freeList(&list1);
    freeList(&list2);

    return 0;
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Append a new node to the end of the list
void append(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (!list->head) {
        list->head = newNode;
        return;
    }
    Node* last = list->head;
    while (last->next) {
        last = last->next;
    }
    last->next = newNode;
    newNode->prev = last;
}

// Concatenate list2 to the end of list1
void concatenate(DoublyLinkedList* list1, DoublyLinkedList* list2) {
    if (!list1->head) {
        // If list1 is empty, make list1 head point to list2 head
        list1->head = list2->head;
    } else {
        Node* last = list1->head;
        while (last->next) {
            last = last->next;
        }
        // Connect the last node of list1 to the head of list2
        last->next = list2->head;
        if (list2->head) {
            list2->head->prev = last;
        }
    }
    // Clear list2
    list2->head = NULL;
}

// Traverse the list and print the elements
void traverse(DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Free the allocated memory of the list
void freeList(DoublyLinkedList* list) {
    Node* current = list->head;
    Node* nextNode;
    while (current) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    list->head = NULL;
}
