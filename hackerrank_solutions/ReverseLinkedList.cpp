
/*
 Problem(In Place Solution) : https://www.hackerrank.com/challenges/reverse-a-linked-list/submissions/code/68447194
*/

typedef struct Node
{
   int data;
   struct Node *next;
}Node;


Node* Reverse(Node *head)
{
    Node * first  = head;
	Node * second = head->next;

	if (!second) {
		return first;
	}

	Node * third  = head->next->next;

	if (!third) {
		second->next = first;
		first->next = NULL;
		return second;
	}
	else {
		first->next = NULL;
		while (third->next) {
			second->next = first;
			first = second;
			second = third;
			third = third->next;
		}
		third->next = second;
		second->next = first;
	}

	return third;
}
