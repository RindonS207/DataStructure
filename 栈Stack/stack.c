#include<stdio.h>
#include<stdlib.h>

#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif 

#define DEFAULT_SIZE 10
#define STACK_INCLUDED 1

typedef struct Stack Stack;
typedef struct Element Element;
static Stack* CreateStack();
static BOOL StackPush(Stack* stack,Element value);
static BOOL StackPop(Stack* stack, Element* value);
static BOOL GetStackTop(Stack* stack, Element* value);

typedef struct Element
{
	int value;
}Element;

typedef struct Stack
{
	Element datas[DEFAULT_SIZE];
	int Top_Index;
}Stack;
/* 初始化一个栈 */
static Stack* CreateStack()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->Top_Index = -1;
	return stack;
}
/* 添加元素至栈中 */
static BOOL StackPush(Stack* stack, Element value)
{
	if ( stack->Top_Index == DEFAULT_SIZE - 1 || stack == NULL)
	{
	
		return false;
	}
	stack->Top_Index += 1;
	stack->datas[stack->Top_Index].value = value.value;
	return true;
}
/* 出栈并且返回被删除的元素到指针，返回操作结果为函数返回值 */
static BOOL StackPop(Stack* stack, Element* value)
{
	if (stack == NULL || stack->Top_Index == -1)
	{

		value = NULL;
		return false;
	}
	value->value = stack->datas[stack->Top_Index].value;
	stack->Top_Index -= 1;
	return true;
}
/* 获取栈顶元素 */
static BOOL GetStackTop(Stack* stack, Element* value)
{
	if (stack->Top_Index == -1 || stack == NULL)
	{
		return false;
	}
	value->value = stack->datas[stack->Top_Index].value;
	return true;
}