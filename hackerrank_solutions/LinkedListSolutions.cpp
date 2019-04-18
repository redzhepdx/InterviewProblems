
/*
 Reverse(In Place Solution) : Problem : https://www.hackerrank.com/challenges/reverse-a-linked-list/submissions/problem
 Delete Duplicate(Without hashing) : Problem : https://www.hackerrank.com/challenges/delete-duplicate-value-nodes-from-a-sorted-linked-list/problem
 Cycle Detection : https://www.hackerrank.com/challenges/detect-whether-a-linked-list-contains-a-cycle/problem
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

Node* RemoveDuplicates(Node *head)
{
    Node * curr = head;
    Node * next = head->next;
    
    if(!head->next)
        return head;
    
    while(next->next){
        if(curr->data == next->data){
            curr->next = next->next;
            next = curr->next;
        }
        else {
            curr = curr->next;
            next = next->next;
        }
    }
    if(curr->data == next->data){
        curr->next = NULL;
    }
    return head; 
}

bool has_cycle(Node *head) {
    
    if (head == NULL){
        return 0;
    }
    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast){
            return true;
        }
    }

    return false;
}
