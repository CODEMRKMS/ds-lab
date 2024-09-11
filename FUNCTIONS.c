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
void insertRear(DoublyLinkedList* list, int data);
void deleteRear(DoublyLinkedList* list);
void insertAtPosition(DoublyLinkedList* list, int data, int position);
void deleteAtPosition(DoublyLinkedList* list, int position);
void insertAfter(DoublyLinkedList* list, int targetData, int newData);
void insertBefore(DoublyLinkedList* list, int targetData, int newData);
void traverse(DoublyLinkedList* list);
void reverse(DoublyLinkedList* list);
void freeList(DoublyLinkedList* list);

int main() {
    DoublyLinkedList list = {NULL};
    int choice, data, position, targetData, newData;

    while (1) {
        printf("\nDoubly Linked List Menu:\n");
        printf("1. Insert element at rear end of the list\n");
        printf("2. Delete element from rear end of the list\n");
        printf("3. Insert element at a given position\n");
        printf("4. Delete element from a given position\n");
        printf("5. Insert element after another element\n");
        printf("6. Insert element before another element\n");
        printf("7. Traverse the list\n");
        printf("8. Reverse the list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertRear(&list, data);
                break;
            case 2:
                deleteRear(&list);
                break;
            case 3:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(&list, data, position);
                break;
            case 4:
                printf("Enter position: ");
                scanf("%d", &position);
                deleteAtPosition(&list, position);
                break;
            case 5:
                printf("Enter target data: ");
                scanf("%d", &targetData);
                printf("Enter new data to insert after %d: ", targetData);
                scanf("%d", &newData);
                insertAfter(&list, targetData, newData);
                break;
            case 6:
                printf("Enter target data: ");
                scanf("%d", &targetData);
                printf("Enter new data to insert before %d: ", targetData);
                scanf("%d", &newData);
                insertBefore(&list, targetData, newData);
                break;
            case 7:
                printf("List: ");
                traverse(&list);
                break;
            case 8:
                reverse(&list);
                printf("List reversed.\n");
                break;
            case 9:
                freeList(&list);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Insert element at the rear end of the list
void insertRear(DoublyLinkedList* list, int data) {
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

// Delete element from the rear end of the list
void deleteRear(DoublyLinkedList* list) {
    if (!list->head) {
        printf("List is empty.\n");
        return;
    }
    if (!list->head->next) {
        free(list->head);
        list->head = NULL;
        return;
    }
    Node* last = list->head;
    while (last->next) {
        last = last->next;
    }
    last->prev->next = NULL;
    free(last);
}

// Insert element at a given position
void insertAtPosition(DoublyLinkedList* list, int data, int position) {
    Node* newNode = createNode(data);
    if (position == 0) {
        newNode->next = list->head;
        if (list->head) {
            list->head->prev = newNode;
        }
        list->head = newNode;
        return;
    }
    Node* temp = list->head;
    for (int i = 0; temp && i < position - 1; i++) {
        temp = temp->next;
    }
    if (!temp) {
        printf("Position out of bounds.\n");
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    if (temp->next) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Delete element from a given position
void deleteAtPosition(DoublyLinkedList* list, int position) {
    if (!list->head) {
        printf("List is empty.\n");
        return;
    }
    if (position == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        if (list->head) {
            list->head->prev = NULL;
        }
        free(temp);
        return;
    }
    Node* temp = list->head;
    for (int i = 0; temp && i < position; i++) {
        temp = temp->next;
    }
    if (!temp) {
        printf("Position out of bounds.\n");
        return;
    }
    if (temp->next) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev) {
        temp->prev->next = temp->next;
    }
    free(temp);
}

// Insert element after another element
void insertAfter(DoublyLinkedList* list, int targetData, int newData) {
    Node* temp = list->head;
    while (temp && temp->data != targetData) {
        temp = temp->next;
    }
    if (!temp) {
        printf("Node with data %d not found.\n", targetData);
        return;
    }
    Node* newNode = createNode(newData);
    newNode->next = temp->next;
    if (temp->next) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Insert element before another element
void insertBefore(DoublyLinkedList* list, int targetData, int newData) {
    if (!list->head) {
        printf("List is empty.\n");
        return;
    }
    if (list->head->data == targetData) {
        Node* newNode = createNode(newData);
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
        return;
    }
    Node* temp = list->head;
    while (temp && temp->data != targetData) {
        temp = temp->next;
    }
    if (!temp) {
        printf("Node with data %d not found.\n", targetData);
        return;
    }
    Node* newNode = createNode(newData);
    newNode->prev = temp->prev;
    newNode->next = temp;
    if (temp->prev) {
        temp->prev->next = newNode;
    }
    temp->prev = newNode;
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

// Reverse the list
void reverse(DoublyLinkedList* list) {
    if (!list->head) {
        return;
    }
    Node* temp = NULL;
    Node* current = list->head;
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp) {
        list->head = temp->prev;
    }
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
