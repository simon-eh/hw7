#include "additup.h"

int main() {
	BigInt *head,*tail,*s_head,*s_tail;
	int size, s_size;
	s_head = malloc(sizeof(BigInt));
	s_head->next = NULL;
	s_head->prev = NULL;
	s_head->digit = 0;
	s_tail=s_head;
	s_size = 0;
	BigInt *temp;
	while((size=readline(&head,&tail)) != -1) {
		print_big(head);
		printf("\n");
		deep_copy(s_tail, &temp);
		// printf("Deep copy (backwards): ");
		// print_backwards(temp);
		// printf("\n");
		int tsize = add(tail,temp,size,s_size,&s_head,&s_tail);
		printf("Total: ");
		print_big(s_head);
		printf("\n");
		s_size = tsize;
	}
	return 0;
}

/* Add the two numbers whose tails are pointed to by t1 and t2. s1 and s2 are the size of t1 and t2. */
int add(BigInt *tail_1, BigInt *tail_2, int size_1, int size_2, BigInt **s_head, BigInt **s_tail) {
	BigInt *solution = (*s_tail = malloc(sizeof(BigInt)));
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
		solution->prev = malloc(sizeof(BigInt));
		solution->prev->digit = (sum > 9);
		solution->prev->next=solution;
		t1=t1->prev;
		t2=t2->prev;
		solution=solution->prev;
	}
	while(t1 != NULL) {
		int sum = solution->digit + t1->digit;
		solution->digit = sum % 10;
		solution->prev = malloc(sizeof(BigInt));
		solution->prev->digit = (sum > 9);
		solution->prev->next=solution;
		t1 = t1->prev;
		solution = solution->prev;
	}
	total_size++;
	if(solution->digit == 0) {
		solution=solution->next;
		total_size--;
	}
	free(solution->prev);
	solution->prev=NULL;
	*s_head = solution;
	return total_size;
}

void print_big(BigInt *head) {
	while(head != NULL) {
		printf("%d", head->digit);
		head=head->next;
	}
}

void deep_copy(BigInt *tail, BigInt **target) {
	BigInt* result = malloc(sizeof(BigInt));
	*target = result;
	result->next = NULL;
	while(tail != NULL) {
		result->digit = tail->digit;
		// printf("Copied over digit %d\n",result->digit);
		if(tail->prev != NULL) {
			result->prev = malloc(sizeof(BigInt));
			result->prev->next = result;
		}
		else {
			result->prev=NULL;
		}
		result=result->prev;
		tail=tail->prev;
	}
}

void print_backwards(BigInt *tail) {
	while(tail != NULL) {
		printf("%d", tail->digit);
		tail=tail->prev;
	}
}

/* Return the number of digits in head. Also tail will point to the least significant digit. */
int readline(BigInt **head, BigInt** tail) {
	char c;
	*head = malloc(sizeof(BigInt));
	for( ;(c=getchar()) == '0' || c == ' '; );
	ungetc(c,stdin);
	int index = 0;
	BigInt *big = *head;
	big->prev=NULL;
	for( ; (c=getchar()) <= '9' && c >= '0'; index++) {
		big->digit=c-'0';
		big->next=malloc(sizeof(BigInt));
		big->next->prev=big;
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