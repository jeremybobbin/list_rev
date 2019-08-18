#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node * next;
	void * data;
} Node;


typedef struct List {
	struct Node * head;
	struct Node * tail;
	int (*push)(struct List*, void *);
	int len;
} List;

int push(List *list, void *data) {
	Node *node;
	Node *tail_node;

	if (list == NULL || (node = malloc(sizeof(Node))) == NULL)
		return 0;

	node->next = NULL;
	node->data = data;


	if (list->tail == NULL) {
		list->head = node;
		list->tail = node;
		list->len = 1;
		return 1;
	}

	list->tail->next = node;
	list->tail = node;

	list->len += 1;
	return 1;
}


int list_init(List *list_ptr) {
	list_ptr->head = NULL;
	list_ptr->tail = NULL;
	list_ptr->push = push;
	list_ptr->len = 0;
}

int * unshift(List *list, void * data) {
	Node *node;

	if (list == NULL || (node = malloc(sizeof(Node))) == NULL)
		return -1;

	node->data = data;
	node->next = list->head;
	list->head = node;

	if (!list->tail)
		list->tail = node;

	return 0;
}

void * shift(List *list) {
	Node * head;
	void * data;
	if (list == NULL || (head = list->head) == NULL) {
		return NULL;
	}

	data = head->data;
	list->head = head->next;

	free(head);

	if(list->len <= 1)
		list->tail = NULL;

	list->len--;
	return data;
}

// Iterative
int rev(List *list) {
	if(list == NULL)
		return -1;

	Node *prev;
	Node *next;
	Node *head = list->head;
	Node *node = head;

	while (node != NULL) {
		next = node->next;
		node->next = prev;
		prev = node;
		node = next;
	}

	list->head = prev;
	list->tail = head;

	return 0;
}

Node_display(Node *node) {
	if (!node)
		return;

	printf("%s\n", (char*) node->data);
	Node_display(node->next);
}

// Recursive solution
Node * Node_rev(Node *node) {
	Node * prev;
	if (node == NULL)
		return NULL;

	if((prev = Node_rev(node->next)) != NULL)
		prev->next = node;
	
	return node;
}

void List_rev(List *list) {
	Node * head = list->tail;
	list->tail = Node_rev(list->head); // node_rev returns HEAD of original list
	list->head = head;
	list->tail->next = NULL;
}

int main() {
	List list_orig;
	List *list = &list_orig;
	char * got; 

	void * s1 = "A";
	void * s2 = "B";
	void * s3 = "C";
	void * s4 = "D";

	list_init(list);

	push(list, s1);
	push(list, s2);
	push(list, s3);
	push(list, s4);

	List_rev(list);
	Node_display(list->head);
	return 0;
}
