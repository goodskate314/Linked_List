#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // i thought i would need it ok
#include <ctype.h>

// look i know this is probably extremely inefficient and you could probably do it with like 20% of the lines i used but it works ok it took me a long time

// A node in the linked list.
typedef struct Node {
	int num;
	struct Node *nextNode;
} Node;

// A linked list containing a head and tail pointer.
typedef struct LinkedList {
	Node *head;
	Node *bigFluffyTail;
} LinkedList;

// Initializes an empty linked list.
void initList(LinkedList *list) {
	list->head = NULL;
	list->bigFluffyTail = NULL;
}

// Adds a new integer to the end of the linked list.
void add(LinkedList *list, int value) {
	Node *addedThing = malloc(sizeof(Node));
	
	addedThing->num = value;
	addedThing->nextNode = NULL;
	
	// if list is empty, assign both head and tail to value
	if (list->head == NULL) {
		list->head = addedThing;
		list->bigFluffyTail = addedThing;
	}
	
	else {
		list->bigFluffyTail->nextNode = addedThing;
		list->bigFluffyTail = addedThing;
	}
}

// Removes the first node containing the given integer from the linked list.
void delete(LinkedList *list, int value) {
	Node *node2Delete = NULL;
	Node *temp = list->head; // use a temporary variable to find which node to delete
	while (temp != NULL) {
		if (temp->num == value) {
			node2Delete = temp;
			break;
		}
		temp = temp->nextNode;
	}
	if (node2Delete == NULL) { // if no matches found, return list unchanged
		return;
	}
	
	if (node2Delete == list->head) { // edge case for deleting head
		list->head = list->head->nextNode;
		free(node2Delete);
		return;
	}
	
	if (node2Delete == list->bigFluffyTail) { // edge case for deleting tail
		Node *temp2 = list->head;
		Node *nodeBeforeDelete = NULL;
        	while (temp2 != NULL) {
                	if (temp2->nextNode == node2Delete) {
                        	nodeBeforeDelete = temp2;
                        	break;
                	}
                	temp2 = temp2->nextNode;
        	}
		list->bigFluffyTail = nodeBeforeDelete;
		nodeBeforeDelete->nextNode = NULL;
		free(node2Delete);
		return;
	}
	
	// standard method
	// find node directly before node to delete
	Node *temp3 = list->head;
	Node *nodeBeforeDelete = NULL;
	while (temp3 != NULL) {
		if (temp3->nextNode == node2Delete) {
			nodeBeforeDelete = temp3;
			break;
		}
		temp3 = temp3->nextNode;
	}
	if (nodeBeforeDelete == NULL) { // this should (hopefully) never happen
		printf("if this error message shows, you're cooked. im sorry.\n");
	}
	
	// find node directly after node to delete
	Node *nodeAfterDelete = NULL;
	nodeAfterDelete = node2Delete->nextNode;
	
	// update pointers and free node to delete
	nodeBeforeDelete->nextNode = nodeAfterDelete;
	free(node2Delete);
}

// Prints the contents of the linked list from head to tail.
void printList(LinkedList *list) {
	Node *currentNum = list->head;
	while (currentNum != NULL) {
		printf("%d -> ", currentNum->num);
		currentNum = currentNum->nextNode;
	}
	printf("NULL\n");
}

int main() {
	// initializing an empty linked list
	LinkedList stuff;
	initList(&stuff);
	
	// printing it to make sure its empty
	printList(&stuff);
	
	// adding some integers to the list
	add(&stuff, 2);
	add(&stuff, -88);
	add(&stuff, 6969);
	add(&stuff, 0);
	add(&stuff, 6969);
	add(&stuff, -33);
	
	// printing the list
	printList(&stuff);
	
	// deleting a number
	delete(&stuff, 6969);
	printList(&stuff);
	
	// deleting a number thats not in the list (should do nothing)
	delete(&stuff, 7);
	printList(&stuff);
	
	// deleting head and then tail
	delete(&stuff, 2);
	printList(&stuff);
	
	delete(&stuff, -33);
	printList(&stuff);
	return 0;
}
