#include "additup.h"
/**
 * ADDITUP - a utility to add arbitrarily large numbers.
 * Simon Ever-Hale
 * 11/9/2014
 * CS241/Prof. Kuperman
 * ---------------------
 * Reads in numbers line by line, ignore leading whitespace and 0s and stopping at the first non-integer character.
 * The numbers are stored in a doubly linked list with each node holding one digit.
 * As numbers are read in, they're added together with the previous sum to keep a running total of all numbers read.
 * Stops at EOF.
 */

int main() {
	BigInt *head,*tail,*s_head,*s_tail = NULL;
	int size, s_size;
	s_head = c_malloc(sizeof(BigInt));
	s_head->next = NULL;
	s_head->prev = NULL;
	s_head->digit = 0;
	s_tail=s_head;
	s_size = 0;
	BigInt *temp = NULL;
	while((size=readline(&head,&tail)) != -1) {
		if(size == 1 && head->digit == 0) {
			clean_head(head);
		}
		else {
			// print_big(head);
			// printf("\n");
			if(temp) {
				clean_tail(temp);
			}
			deep_copy(s_tail, &temp);
			clean_tail(s_tail);
			s_size = add(tail,temp,size,s_size,&s_head,&s_tail);
			clean_tail(tail);
		}
		printf("Total: ");
		print_big(s_head);
		printf("\n");
	}
	clean_head(s_head);
	clean_tail(temp);
	clean_head(head);
	return 0;
}

/* Attempt to malloc size bytes, and exit if it fails. */
void* c_malloc(size_t size) {
    void *result = malloc(size);
    if(result == NULL) {
	printf("No space for malloc.\n");
	exit(1);
    }
    return result;
}

/* Add the two numbers whose tails are pointed to by t1 and t2. s1 and s2 are the size of t1 and t2.*/
int add(BigInt *tail_1, BigInt *tail_2, int size_1, int size_2, BigInt **s_head, BigInt **s_tail) {
	BigInt *solution = (*s_tail = c_malloc(sizeof(BigInt)));
	BigInt *t1,*t2;
	int total_size = 0;
	if(size_1 > size_2) {
		t1 = tail_1;
		t2 = tail_2;
		total_size = size_1;
	}
	else {
		total_size = size_2;
		t1 = tail_2;
		t2 = tail_1;
	}
	solution->digit=0;
	solution->next=NULL;
	while(t2 != NULL) {
		if(t1 == NULL) {
			printf("ERROR: t1 must be at least as long as t2.");
			exit(1);
		}
		// printf("Current t1: %d, Current t2: %d\n", t1->digit, t2->digit);
		int sum = t1->digit + t2->digit + solution->digit;
		solution->digit = sum % 10;
		solution->prev = c_malloc(sizeof(BigInt));
		solution->prev->digit = (sum > 9);
		solution->prev->next=solution;
		t1=t1->prev;
		t2=t2->prev;
		solution=solution->prev;
	}
	while(t1 != NULL) {
		int sum = solution->digit + t1->digit;
		solution->digit = sum % 10;
		solution->prev = c_malloc(sizeof(BigInt));
		solution->prev->digit = (sum > 9);
		solution->prev->next=solution;
		t1 = t1->prev;
		solution = solution->prev;
	}
	total_size++;
	if(solution->digit == 0) {
		solution=solution->next;
		free(solution->prev);
		total_size--;
	}
	solution->prev = NULL;
	*s_head = solution;
	return total_size;
}

/* Print the BigInt whose head is pointed to by head. */
void print_big(BigInt *head) {
	while(head != NULL) {
		printf("%d", head->digit);
		head=head->next;
	}
}

/* Creates a deep copy (copys values, not just references) and stores it in target */
void deep_copy(BigInt *tail, BigInt **target) {
	BigInt* result = c_malloc(sizeof(BigInt));
	*target = result;
	result->next = NULL;
	while(tail != NULL) {
		result->digit = tail->digit;
		// printf("Copied over digit %d\n",result->digit);
		if(tail->prev != NULL) {
			result->prev = c_malloc(sizeof(BigInt));
			result->prev->next = result;
		}
		else {
			result->prev=NULL;
		}
		result=result->prev;
		tail=tail->prev;
	}
}

/* Read and print a line. Return the number of digits in head. Also tail will point to the least significant digit. */
int readline(BigInt **head, BigInt** tail) {
	char c;
	*head = c_malloc(sizeof(BigInt));
	for( ;(c=getchar()) == '0' || isspace(c); ) {
	}
	int index = 0;
	BigInt *big = *head;
	big->prev=NULL;
	for( ; c <= '9' && c >= '0'; index++, c=getchar()) {
		big->digit = c-'0';
		big->next = c_malloc(sizeof(BigInt));
		big->next->prev = big;
		big=big->next;
	}
	if(index != 0) {
		big=big->prev;
		free(big->next);
	}
	else {
		if(c == EOF) {
				index = -1;
			}
		else {
			big->digit = 0;
			index = 1;
		}
	}
	big->next=NULL;
	*tail=big;
	while(c != EOF && c != '\n') {
		c = getchar();
	}
	return index;
}

/* Starting at the tail, frees every node of a linked list. */
void clean_tail(BigInt* tail) {
	while(tail != NULL && tail->prev != NULL) {
		tail=tail->prev;
		free(tail->next);
	}
	free(tail);
}

/* Starting at the head, frees every node of a linked list. */
void clean_head(BigInt* head) {
    while(head != NULL && head->next != NULL) {
	head = head->next;
	free(head->prev);
    }
    free(head);

}
