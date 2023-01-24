#include<stdio.h>
#include<stdlib.h>
#include "BOOL_DEF.c"

#define DEFAULT_SIZE 10

typedef struct Queue Queue;
typedef struct Q_Element Q_Element;
static Queue* CreateQueue();
static BOOL AddElementToQueue(Queue* que,Q_Element e);
static BOOL RemoveElementFromQueue(Queue* que,Q_Element* value);
static BOOL GetQueueHeadElement(Queue* que,Q_Element* value);

typedef struct Q_Element {
	int NextIndex;
	int value;
}Q_Element;

typedef struct Queue {
	Q_Element queue[DEFAULT_SIZE];
	int tailIndex;
	int headIndex;
}Queue;
/* ����һ������ */
static Queue* CreateQueue()
{
	int x;
	Queue* que = (Queue*)malloc(sizeof(Queue));
	if (que == NULL) {
		return NULL;
	}
	que->tailIndex = 0;
	que->headIndex = 0;
	for (x = 0; x < DEFAULT_SIZE; x++)
	{
		que->queue[x].NextIndex = x + 1;
	}
	que->queue[DEFAULT_SIZE - 1].NextIndex = 0;
	return que;
}
/* ��������Ԫ�� */
static BOOL AddElementToQueue(Queue* que, Q_Element e)
{
	if (que == NULL || e.value == NULL) {
		return false;
	}
	if ((que->tailIndex + 1) % DEFAULT_SIZE == que->headIndex) {
		return false;
	}
	que->queue[que->tailIndex].value = e.value;
	que->tailIndex = que->queue[que->tailIndex].NextIndex;
	return true;
}
/* �Ӷ�����ɾ��Ԫ�أ�
���ҷ��ر�ɾ����Ԫ����valueָ�� */
static BOOL RemoveElementFromQueue(Queue* que, Q_Element* value)
{
	if (que == NULL || value == NULL || que->headIndex == que->tailIndex)
	{
		return false;
	}
	value->value = que->queue[que->headIndex].value;
	que->headIndex = que->queue[que->headIndex].NextIndex;
	return true;
}
/* �Ӷ����л�ȡ��ͷԪ�� */
static BOOL GetQueueHeadElement(Queue* que, Q_Element* value)
{
	if (que == NULL || value == NULL || que->headIndex == que->tailIndex)
	{
		return false;
	}
	value->value = que->queue[que->headIndex].value;
	return true;
}