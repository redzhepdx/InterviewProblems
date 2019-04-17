/*
 Solution of NQueens Problem with Non-Recursive Dynamic Programming
*/

#include<stdio.h>
#include<conio.h>
#define QUEEN_COUNT 15

typedef struct Position{
	int xPos;
	int yPos;
}Position;

typedef struct Stack
{
	Position *positions;
	int top;

}Stack;

void initStack(Stack *stack);//Stack initialization

void push(Stack *stack, Position pos);//PUSH CELL INTO THE STACK

Position pop(Stack *stack);//POP LAST PUSHED CELL FROM STACK

int isContains(Stack *stack, Position wantToSearch);//CHECK STACK IS CONTAINS GIVEN CELL

int isFull(Stack *stack);//CHECK STACK IS FULL

int isEmpty(Stack *stack);//CHECK STACK IS EMPTY

int CheckForValidPosition(Stack* stack, Position targetPos);//CONTROL THE POSITION

int IsInMapRange(Position pos);//CHECK POSITION FOR IN TABLE RANGE

int main(){

	Position* posList;
	Stack* stack;
	char** table;

	posList = (Position*)malloc(QUEEN_COUNT * sizeof(Position));

	stack = (Stack*)malloc(sizeof(Stack));

	table = (char**)malloc(QUEEN_COUNT*sizeof(char*));

	for (int i = 0; i < QUEEN_COUNT; i++){
		table[i] = (char*)malloc(QUEEN_COUNT*sizeof(char));
	}

	initStack(stack);

	Position tempPos;
	tempPos.xPos = 0;
	tempPos.yPos = 0;
	
	while (stack->top != QUEEN_COUNT && IsInMapRange(tempPos))
	{
		if (CheckForValidPosition(stack, tempPos)){
			//Push stack and go next row
			push(stack, tempPos);
			tempPos.xPos++;
			tempPos.yPos = 0;
		}
		else{
			if (tempPos.yPos < QUEEN_COUNT - 1){
				tempPos.yPos++;
			}
			else{
				tempPos = pop(stack);
				while (tempPos.yPos == QUEEN_COUNT - 1){
					tempPos = pop(stack);
				}
				tempPos.yPos++;
				
			}
		}
		
	}

	for (int k = 0; k < QUEEN_COUNT; k++){
		printf("%d %d\n", stack->positions[k].xPos , stack->positions[k].yPos);
	}

	fflush(stdin);
	getchar();

	for (int k = 0; k < QUEEN_COUNT; k++){
		for (int i = 0; i < QUEEN_COUNT; i++){
			for (int j = 0; j < QUEEN_COUNT; j++){
				if ((k == stack->positions[j].xPos) && (i == stack->positions[j].yPos)){
					table[k][i] = 'Q';
				}
			}
		}
	}

	for (int i = 0; i < QUEEN_COUNT; i++){
		for (int j = 0; j < QUEEN_COUNT; j++){
			printf("%c\t", table[i][j]);
		}
		printf("\n\n");
	}


	getchar();
}

void initStack(Stack *stack) {
	stack->positions = (Position*)malloc(QUEEN_COUNT * sizeof(Position));
	stack->top = 0;
}

int isEmpty(Stack *stack) {
	if (!stack->top)
		return 1;
	else
		return 0;
}

int isFull(Stack *stack) {
	if (stack->top == QUEEN_COUNT * QUEEN_COUNT)
		return 1;
	else
		return 0;
}

void push(Stack *stack, Position pos) {

	if (isFull(stack)) {
		printf("Stack is full can not push");
		fflush(stdin);
		getchar();
		exit(-1);
	}
	else {
		stack->positions[stack->top] = pos;
		stack->top++;
	}
}

Position pop(Stack *stack) {

	Position cell;

	if (isEmpty(stack)) {
		printf("Stack empty can not pop");
	}
	else {
		stack->top--;
		cell = stack->positions[stack->top];
		return cell;
	}

}

int IsInMapRange(Position pos){

	return pos.xPos >= 0 && pos.yPos >= 0 && pos.xPos < QUEEN_COUNT && pos.yPos < QUEEN_COUNT;
}

int CheckForValidPosition(Stack* stack, Position targetPos){
	int foundSafe = 1;
	//IF CURRENT QUEEN UNDER ATTACK FROM PREVIOUS QUEENS
	for (int index = 0; index < stack->top; index++){
		if ((stack->positions[index].yPos == targetPos.yPos) ||
			((stack->positions[index].xPos - stack->positions[index].yPos) == (targetPos.xPos - targetPos.yPos)) ||
			((stack->positions[index].xPos + stack->positions[index].yPos) == (targetPos.xPos + targetPos.yPos))){
			foundSafe = 0;
			break;
		}
	}

	return foundSafe;
}
