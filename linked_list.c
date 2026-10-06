#include <stdio.h>
#include <stdlib.h>

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
	Node *new = malloc(sizeof(Node));
	if (!new) { // in case memory allocation fails
		printf("memory allocation failed :(");
		return;
	}
	
	new->num = value;
	new->nextNode = NULL;
	
	// if list is empty, assign both head and tail to value
	if (list->head == NULL) {
		list->head = new;
		list->bigFluffyTail = new;
	}
	
	else {
		list->bigFluffyTail->nextNode = new;
		list->bigFluffyTail = new;
	}
}

// Removes the first node containing the given integer from the linked list.
void delete(LinkedList *list, int value) {
	Node *previous = NULL;
	Node *current = list->head; // keep track of both the node to delete and the previous node
	while ((current != NULL) && (current->num != value)) {
		previous = current;
		current = current->nextNode;
	}
	
	if (current == NULL) return;  // if no matches found/list is empty, return list unchanged
	if (previous) previous->nextNode = current->nextNode; // skip the node we're deleting
	else list->head = current->nextNode; // unless we're deleting the head, in that case update the head
	if (list->bigFluffyTail == current) list->bigFluffyTail = previous; // update tail if old tail was deleted
	
	free(current);
}

// Prints the contents of the linked list from head to tail.
void printList(LinkedList *list) {
	for (Node *n = list->head; n; n = n->nextNode) {
		printf("%d -> ", n->num);
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
	
	// free the rest of the nodes in the list
	while (stuff.head) {
		Node *goAway = stuff.head;
		stuff.head = goAway->nextNode;
		free(goAway);
	}
	stuff.bigFluffyTail = NULL;
	
	return 0;
}
