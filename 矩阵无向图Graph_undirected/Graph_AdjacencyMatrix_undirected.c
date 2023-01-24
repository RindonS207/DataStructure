#include<stdio.h>
#include<stdlib.h>
#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif

#define GRAPH_MATRIX_UND_INCLUDED 1
#define DEFAULT_SIZE 20
#define DEFAULT_CHAR_AMOUNT 30

typedef struct Graph_UND_M Graph_UND_M;
typedef struct Vertex Vertex;
static Graph_UND_M* CreateUndirectedGraph();
static void PrintUndirectedGraph(Graph_UND_M* graph);
static void PrintUndirectedVertex(Graph_UND_M* graph,int index);
static void PrintVertexMatrix(Graph_UND_M* graph);
static BOOL RemoveUndirectedVertex(Graph_UND_M* graph,int index);
static BOOL AddUndirectedVertex(Graph_UND_M* graph);
static BOOL AddUndirectedEdge(Graph_UND_M* graph);

typedef struct Vertex {
	char info[DEFAULT_CHAR_AMOUNT];
	int value;
}Vertex;

typedef struct Graph_UND_M {
	Vertex Datas[DEFAULT_SIZE];
	int Edge[DEFAULT_SIZE][DEFAULT_SIZE];
	int Vertex_amount;
	int Edge_amount;
}Graph_UND_M;
/* ����һ������ͼ */  
static Graph_UND_M* CreateUndirectedGraph() {
	int Vertex_amount,edge_amount,value,x,i;
	Graph_UND_M* graph = (Graph_UND_M*)malloc(sizeof(Graph_UND_M));
	if (graph == NULL) {
		printf("�����ڴ�ʧ�ܣ�\n");
		return NULL;
	}
	printf("��������Ҫ�Ķ�����������\n");
	scanf("%d",&Vertex_amount);
	if (Vertex_amount<1 || Vertex_amount > DEFAULT_SIZE) {
		printf("������һ�������ֵ��\n");
		free(graph);
		return NULL;
	}
	for (x = 0; x < Vertex_amount; x++) {
		for (i = 0; i < Vertex_amount; i++) {
			graph->Edge[x][i] = 0;
		}
	}
	printf("��������Ҫ�ı���������\n");
	scanf("%d",&edge_amount);
	if (edge_amount > Vertex_amount * (Vertex_amount - 1) / 2) {
		printf("������һ�������ֵ��\n");
		free(graph);
		return NULL;
	}
	graph->Vertex_amount = Vertex_amount;
	graph->Edge_amount = edge_amount;
	printf("���ڿ�ʼ����ڵ��ֵ��\n");
	for (x = 0; x < Vertex_amount; x++) {
		printf("������� %d ���ڵ��˵����\n",x+1);
		scanf("%s", graph->Datas[x].info);
		printf("������� %d ���ڵ��ֵ:\n",x+1);
		scanf("%d", &value);

		graph->Datas[x].value = value;
	}
	printf("���ڿ�ʼ���ӽڵ��еıߡ�\n");
	for (x = 0; x < edge_amount; x++) {
		int a, b;
		printf("������� %d ���ߵĵ� 1 ���ڽӵ��±�:\n",x+1);
		scanf("%d",&a);
		printf("������� %d ���ߵĵ� 2 ���ڽӵ��±�:\n",x+1);
		scanf("%d", &b);
		if (a == b || a < 0 || b < 0 || a >= Vertex_amount || b >= Vertex_amount) {
			printf("��������Ч��ֵ��\n");
			x -= 1;
			continue;
		}
		if (graph->Edge[a][b]) {
			printf("���������Ѿ�����ϵ�ˣ�\n");
			x -= 1;
			continue;
		}
		printf("%s �� %s �Ѵ��ϵ��\n",graph->Datas[a].info,graph->Datas[b].info);
		graph->Edge[a][b] = 1;
		graph->Edge[b][a] = 1;
	}
	printf("ͼ������ɡ�\n");
	return graph;
}
/* ��ӡһ������ͼ */
static void PrintUndirectedGraph(Graph_UND_M* graph) {
	int x;
	if (graph == NULL || graph->Vertex_amount == 0) {
		return;
	}
	for (x = 0; x < graph->Vertex_amount; x++) {
		PrintUndirectedVertex(graph, x);
	}
}
/* ��ӡ�������� */
static void PrintUndirectedVertex(Graph_UND_M* graph, int index)
{
	int x;
	if (graph == NULL || index < 0 || index >= graph->Vertex_amount) {
		return;
	}
	printf("�ڵ��±� %d ���ڵ�ֵ %d\n�ڵ�˵����%s\n�������ӵĽڵ��У�\n\n",index,graph->Datas[index].value,graph->Datas[index].info);
	for(x=0;x<graph->Vertex_amount;x++){
		if (graph->Edge[index][x]) {
			printf("�ڵ��±� %d ���ڵ�ֵ %d\n�ڵ�˵����%s\n",x,graph->Datas[x].value,graph->Datas[x].info);
		}
	}
	printf("\n\n");
}
/* ��ӡ���������ͼ�ľ��� */
static void PrintVertexMatrix(Graph_UND_M* graph)
{
	int x,i;
	if (graph == NULL || graph->Vertex_amount == 0) {
		return;
	}
	for (x = 0; x < graph->Vertex_amount; x++) {
		printf("��ţ�%d ˵����%s  ֵ��%d\n",x,graph->Datas[x].info,graph->Datas[x].value);
	}
	printf("��ӡ����ͼ��\t");
	for (x = 0; x < graph->Vertex_amount; x++) {
		printf("��ţ�%d\t",x);
	}
	printf("\n");
	for (x = 0; x < graph->Vertex_amount; x++) {
		printf("\t��ţ�%d|", x);
		for (i = 0; i < graph->Vertex_amount; i++) {
			printf("%3d\t",graph->Edge[x][i]);
		}
		printf("\n");
	}
}
/* ɾ��һ������ͼ�Ľڵ� */
static BOOL RemoveUndirectedVertex(Graph_UND_M* graph, int index)
{
	int x, i;
	if (graph == NULL || index < 0 || index >= graph->Vertex_amount) {
		return false;
	}
	i = 0;
	for (x = 0; x < graph->Vertex_amount; x++) {
		if (graph->Edge[index][x]) {
			i += 1;
		}
	}
	graph->Edge_amount -= i;
	for (x = index; x < graph->Vertex_amount - 1; x++) {
		graph->Datas[x] = graph->Datas[x + 1];
		for (i = 0; i < graph->Vertex_amount; i++) {
			graph->Edge[x][i] = graph->Edge[x + 1][i];
		}
	}
	for (x = 0; x < graph->Vertex_amount; x++) {
		for (i = index; i < graph->Vertex_amount - 1; i++) {
			graph->Edge[x][i] = graph->Edge[x][i + 1];
		}
	}
	graph->Vertex_amount -= 1;
	return true;
}
/* ��һ������ͼ���һ���˵� */
static BOOL AddUndirectedVertex(Graph_UND_M* graph)
{
	int value,x;
	printf("����������ͼ��ӽڵ㡣\n");
	if (graph == NULL || graph->Vertex_amount == DEFAULT_SIZE) {
		return false;
	}
	printf("�������½ڵ��˵����\n");
	scanf("%s",graph->Datas[graph->Vertex_amount].info);
	printf("�������½ڵ��ֵ��\n");
	scanf("%d",&value);
	graph->Datas[graph->Vertex_amount].value = value;
	for (x = 0; x <= graph->Vertex_amount; x++) {
		graph->Edge[x][graph->Vertex_amount] = 0;
		graph->Edge[graph->Vertex_amount][x] = 0;
	}
	graph->Vertex_amount += 1;
	return true;
}
/* ��һ������ͼ��ӱ� */
static BOOL AddUndirectedEdge(Graph_UND_M* graph)
{
	int edge_amount,x;
	if (graph == NULL) {
		return false;
	}
	printf("������Ҫ��ӵı�������\n");
	scanf("%d", &edge_amount);
	if (edge_amount<1 || edge_amount + graph->Edge_amount > graph->Vertex_amount * (graph->Vertex_amount - 1) / 2) {
		printf("����������ֵ��\n");
		return false;
	}
	graph->Edge_amount += edge_amount;
	for (x = 0; x < edge_amount; x++) {
		int a, b;
		printf("������Ҫ��ӵĵ� %d ���ߵĵ� 1 ���ڽӵ㡣\n",x+1);
		scanf("%d", &a);
		printf("������Ҫ��ӵĵ� %d ���ߵĵ� 2 ���ڽӵ㡣\n",x+1);
		scanf("%d", &b);
		if (a == b) {
			printf("��������Ч��ֵ��\n");
			x -= 1;
			continue;
		}
		if (graph->Edge[a][b]) {
			printf("���������Ѿ�����ϵ�ˡ�");
			x -= 1;
			continue;
		}
		printf("%s �� %s �Ѵ��ϵ��\n", graph->Datas[a].info, graph->Datas[b].info);
		graph->Edge[a][b] = 1;
		graph->Edge[b][a] = 1;
	}
	return true;
}
