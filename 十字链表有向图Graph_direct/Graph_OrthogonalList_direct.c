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

/* 构造一个十字链表边有向图 */
static Graph_OL* CreateOrthogonalListGraph()
{
	int Arc_amount,Vertex_amount,x,input;
	Graph_OL* graph = (Graph_OL*)malloc(sizeof(Graph_OL));
	if (graph == NULL) {
		return NULL;
	}
	printf("请输入需要创建图的顶点数量：\n");
	scanf("%d",&Vertex_amount);
	if (Vertex_amount < 1 || Vertex_amount> DEFAULT_SIZE) {
		printf("请输入合理的数值。\n");
		free(graph);
		return NULL;
	}
	printf("请输入需要创建图的边数量：\n");
	scanf("%d",&Arc_amount);
	if (Arc_amount < 0 || Arc_amount > Vertex_amount * (Vertex_amount - 1)) {
		printf("请输入合理的数值。\n");
		free(graph);
		return NULL;
	}
	graph->Arc_amount = Arc_amount;
	graph->Vertex_amount = Vertex_amount;
	for (x = 0; x < Vertex_amount; x++) {
		printf("请输入第 %d 个顶点的描述：\n",x+1);
		scanf("%s",&graph->datas[x].Vinfo);
		printf("请输入第 %d 个顶点的值：\n",x+1);
		scanf("%d", &input);
		graph->datas[x].value = input;
		graph->datas[x].firstIN = NULL;
		graph->datas[x].firstOUT = NULL;
	}
	for (x = 0; x < Arc_amount; x++) {
		int out, in;
		printf("输入第 %d 条边的弧尾下标：\n",x+1);
		scanf("%d",&out);
		printf("输入第 %d 条边的弧头下标：\n",x+1);
		scanf("%d", &in);

		if (out == in || out < 0 || in < 0 || out >= Vertex_amount || in >= Vertex_amount) {
			printf("请输入合理的数值。\n");
			x -= 1;
			continue;
		}

		Arc* new_arc = (Arc*)malloc(sizeof(Arc));
		
		if (new_arc == NULL) {
			printf("创建出现问题，空间不足！.\n");
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
				printf("这个关系已经存在！\n");
				free(new_arc);
				x -= 1;
				continue;
			}
			while (arc->NextSameTail) {
				if (arc->headIndex == in) {
					printf("这个关系已经存在！\n");
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
		printf("弧尾 %s 与弧头 %s 建立关系成功。\n",graph->datas[out].Vinfo,graph->datas[in].Vinfo);
	}
	return graph;
}
/* 打印一个十字链表边有向图 */
static void PrintOListGraph(Graph_OL* graph)
{
	int x;
	if (graph == NULL || graph->Vertex_amount == 0) {
		return;
	}
	for (x = 0; x < graph->Vertex_amount; x++) {
		printf("节点 %s 值 %d 下标 %d 的所有出度:\n",graph->datas[x].Vinfo,graph->datas[x].value,x);
		PrintOListGraphTailArc(graph, x);
	}
}
/* 打印以某个节点为弧尾的所有边信息 */
static void PrintOListGraphTailArc(Graph_OL* graph, int index) {
	Arc* arc;
	if (graph == NULL || graph->Arc_amount == 0 || index < 0 || index >= graph->Vertex_amount) {
		return;
	}
	arc = graph->datas[index].firstOUT;
	while (arc) {
		printf("弧尾 %s 下标 %d 弧头 %s 下标 %d\n",graph->datas[index].Vinfo,index,graph->datas[arc->headIndex].Vinfo, arc->headIndex);
		arc = arc->NextSameTail;
	}
}
/* 打印以某个节点为弧头的所有边信息 */
static void PrintOListGraphHeadArc(Graph_OL* graph, int index)
{
	Arc* arc;
	if (graph == NULL || graph->Arc_amount == 0 || index < 0 || index >= graph->Vertex_amount) {
		return;
	}
	arc = graph->datas[index].firstIN;
	while (arc) {
		printf("弧尾 %s 下标 %d 弧头 %s 下标 %d\n", graph->datas[index].Vinfo, index, graph->datas[arc->headIndex].Vinfo, arc->headIndex);
		arc = arc->NextSameHead;
	}
}