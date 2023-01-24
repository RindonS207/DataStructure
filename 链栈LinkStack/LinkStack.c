#include<stdio.h>
#include<stdlib.h>
#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif 

#define L_STACK_INCLUDED 1
typedef struct Element Element;
typedef struct LinkStack LinkStack;
static LinkStack* CreateLinkStack();
static BOOL AddElementToLinkStack(LinkStack* stack, Element value);
static BOOL RemoveElementFromLinkStack(LinkStack* stack,Element* value);
static BOOL GetTopElementFromLinkStack(LinkStack* stack, Element* value);

typedef struct Element {
	int value;
	Element* NextNode;
}Element;

typedef struct LinkStack {
	Element *TopElement;
	int Count;
}LinkStack;
/* ����һ����ջ */
static LinkStack* CreateLinkStack()
{
	LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
	if (stack == NULL)
	{
		return NULL;
	}
	else {
		stack->Count = 0;
		stack->TopElement = NULL;
		return stack;
	}
}
/* ����ջ���Ԫ�� */
static BOOL AddElementToLinkStack(LinkStack* stack, Element value)
{
	Element* new_value = (Element*)malloc(sizeof(Element));
	if (new_value == NULL) {
		return false;
	}
	else {
		new_value->NextNode = stack->TopElement;
		new_value->value = value.value;
		stack->TopElement = new_value;
		stack->Count += 1;
	}
	return true;
}
/* ʹջ��Ԫ�س�ջ������Ԫ�ص�ֵ���Ƹ�valueָ�� */
static BOOL RemoveElementFromLinkStack(LinkStack* stack, Element* value)
{
	Element* pointer = stack->TopElement;
	if (stack == NULL || value == NULL || stack->Count == 0)
	{
		return false;
	}
	value->value = stack->TopElement->value;
	value->NextNode = stack->TopElement->NextNode;
	stack->TopElement = pointer->NextNode;
	stack->Count -= 1;
	free(pointer);
	return true;
}
/* ��ȡջ��Ԫ�أ�������valueָ�� */
static BOOL GetTopElementFromLinkStack(LinkStack* stack, Element* value)
{
	if (stack == NULL || stack->Count == 0 || value == NULL) {
		return false;
	}
	value->value = stack->TopElement->value;
	value->NextNode = stack->TopElement->NextNode;
	return true;
}