#include<stdio.h>
#include<stdlib.h>
#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif

#define GRAPH_CROSS_INCLUEDED 1
#define DEFAULT_SIZE 20
#define DEFAULT_CHAR_SIZE 30

typedef struct Graph_OL Graph_OL;
typedef struct Vertex Vertex;
typedef struct Arc Arc;
static Graph_OL* CreateOrthogonalListGraph();
static void PrintOListGraph(Graph_OL* graph);
static void PrintOListGraphTailArc(Graph_OL* graph, int index);
static void PrintOListGraphHeadArc(Graph_OL* graph, int index);

typedef struct Vertex {
	char Vinfo[DEFAULT_CHAR_SIZE];
	int value;
	Arc* firstIN;
	Arc* firstOUT;
}Vertex;

typedef struct Graph_OL {
	Vertex datas[DEFAULT_SIZE];
	int Vertex_amount;
	int Arc_amount;
}Graph_OL;

typedef struct Arc {
	int tailIndex;
	int headIndex;
	Arc* NextSameHead;
	Arc* NextSameTail;
}Arc;

/* ����һ��ʮ�����������ͼ */
static Graph_OL* CreateOrthogonalListGraph()
{
	int Arc_amount,Vertex_amount,x,input;
	Graph_OL* graph = (Graph_OL*)malloc(sizeof(Graph_OL));
	if (graph == NULL) {
		return NULL;
	}
	printf("��������Ҫ����ͼ�Ķ���������\n");
	scanf("%d",&Vertex_amount);
	if (Vertex_amount < 1 || Vertex_amount> DEFAULT_SIZE) {
		printf("������������ֵ��\n");
		free(graph);
		return NULL;
	}
	printf("��������Ҫ����ͼ�ı�������\n");
	scanf("%d",&Arc_amount);
	if (Arc_amount < 0 || Arc_amount > Vertex_amount * (Vertex_amount - 1)) {
		printf("������������ֵ��\n");
		free(graph);
		return NULL;
	}
	graph->Arc_amount = Arc_amount;
	graph->Vertex_amount = Vertex_amount;
	for (x = 0; x < Vertex_amount; x++) {
		printf("������� %d �������������\n",x+1);
		scanf("%s",&graph->datas[x].Vinfo);
		printf("������� %d �������ֵ��\n",x+1);
		scanf("%d", &input);
		graph->datas[x].value = input;
		graph->datas[x].firstIN = NULL;
		graph->datas[x].firstOUT = NULL;
	}
	for (x = 0; x < Arc_amount; x++) {
		int out, in;
		printf("����� %d ���ߵĻ�β�±꣺\n",x+1);
		scanf("%d",&out);
		printf("����� %d ���ߵĻ�ͷ�±꣺\n",x+1);
		scanf("%d", &in);

		if (out == in || out < 0 || in < 0 || out >= Vertex_amount || in >= Vertex_amount) {
			printf("������������ֵ��\n");
			x -= 1;
			continue;
		}

		Arc* new_arc = (Arc*)malloc(sizeof(Arc));
		
		if (new_arc == NULL) {
			printf("�����������⣬�ռ䲻�㣡.\n");
			free(graph);
			return NULL;
		}
		new_arc->tailIndex = out;
		new_arc->headIndex = in;
		new_arc->NextSameHead = NULL;
		new_arc->NextSameTail = NULL;
		if (graph->datas[out].firstOUT != NULL) {
			int flag = false;
			Arc* arc = graph->datas[out].firstOUT;
			if (arc->headIndex == in) {
				printf("�����ϵ�Ѿ����ڣ�\n");
				free(new_arc);
				x -= 1;
				continue;
			}
			while (arc->NextSameTail) {
				if (arc->headIndex == in) {
					printf("�����ϵ�Ѿ����ڣ�\n");
					flag = true;
					break;
				}
				arc = arc->NextSameTail;
			}
			if (flag) {
				x -= 1;
				free(new_arc);
				continue;
			}
			else {
				arc->NextSameTail = new_arc;
			}
		}
		else {
			graph->datas[out].firstOUT = new_arc;
		}
		if (graph->datas[in].firstIN != NULL) {
			Arc* in_arc = graph->datas[in].firstIN;
			while (in_arc->NextSameHead) {
				in_arc = in_arc->NextSameHead;
			}
			in_arc->NextSameHead = new_arc;
		}
		else {
			graph->datas[in].firstIN = new_arc;
		}
		printf("��β %s �뻡ͷ %s ������ϵ�ɹ���\n",graph->datas[out].Vinfo,graph->datas[in].Vinfo);
	}
	return graph;
}
/* ��ӡһ��ʮ�����������ͼ */
static void PrintOListGraph(Graph_OL* graph)
{
	int x;
	if (graph == NULL || graph->Vertex_amount == 0) {
		return;
	}
	for (x = 0; x < graph->Vertex_amount; x++) {
		printf("�ڵ� %s ֵ %d �±� %d �����г���:\n",graph->datas[x].Vinfo,graph->datas[x].value,x);
		PrintOListGraphTailArc(graph, x);
	}
}
/* ��ӡ��ĳ���ڵ�Ϊ��β�����б���Ϣ */
static void PrintOListGraphTailArc(Graph_OL* graph, int index) {
	Arc* arc;
	if (graph == NULL || graph->Arc_amount == 0 || index < 0 || index >= graph->Vertex_amount) {
		return;
	}
	arc = graph->datas[index].firstOUT;
	while (arc) {
		printf("��β %s �±� %d ��ͷ %s �±� %d\n",graph->datas[index].Vinfo,index,graph->datas[arc->headIndex].Vinfo, arc->headIndex);
		arc = arc->NextSameTail;
	}
}
/* ��ӡ��ĳ���ڵ�Ϊ��ͷ�����б���Ϣ */
static void PrintOListGraphHeadArc(Graph_OL* graph, int index)
{
	Arc* arc;
	if (graph == NULL || graph->Arc_amount == 0 || index < 0 || index >= graph->Vertex_amount) {
		return;
	}
	arc = graph->datas[index].firstIN;
	while (arc) {
		printf("��β %s �±� %d ��ͷ %s �±� %d\n", graph->datas[index].Vinfo, index, graph->datas[arc->headIndex].Vinfo, arc->headIndex);
		arc = arc->NextSameHead;
	}
}