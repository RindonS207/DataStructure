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
/* 构建一个无向图 */  
static Graph_UND_M* CreateUndirectedGraph() {
	int Vertex_amount,edge_amount,value,x,i;
	Graph_UND_M* graph = (Graph_UND_M*)malloc(sizeof(Graph_UND_M));
	if (graph == NULL) {
		printf("申请内存失败！\n");
		return NULL;
	}
	printf("请输入需要的顶点总数量：\n");
	scanf("%d",&Vertex_amount);
	if (Vertex_amount<1 || Vertex_amount > DEFAULT_SIZE) {
		printf("请输入一个合理的值。\n");
		free(graph);
		return NULL;
	}
	for (x = 0; x < Vertex_amount; x++) {
		for (i = 0; i < Vertex_amount; i++) {
			graph->Edge[x][i] = 0;
		}
	}
	printf("请输入需要的边总数量：\n");
	scanf("%d",&edge_amount);
	if (edge_amount > Vertex_amount * (Vertex_amount - 1) / 2) {
		printf("请输入一个合理的值！\n");
		free(graph);
		return NULL;
	}
	graph->Vertex_amount = Vertex_amount;
	graph->Edge_amount = edge_amount;
	printf("现在开始构造节点的值。\n");
	for (x = 0; x < Vertex_amount; x++) {
		printf("请输入第 %d 个节点的说明：\n",x+1);
		scanf("%s", graph->Datas[x].info);
		printf("请输入第 %d 个节点的值:\n",x+1);
		scanf("%d", &value);

		graph->Datas[x].value = value;
	}
	printf("现在开始链接节点中的边。\n");
	for (x = 0; x < edge_amount; x++) {
		int a, b;
		printf("请输入第 %d 条边的第 1 个邻接点下标:\n",x+1);
		scanf("%d",&a);
		printf("请输入第 %d 条边的第 2 个邻接点下标:\n",x+1);
		scanf("%d", &b);
		if (a == b || a < 0 || b < 0 || a >= Vertex_amount || b >= Vertex_amount) {
			printf("请输入有效的值。\n");
			x -= 1;
			continue;
		}
		if (graph->Edge[a][b]) {
			printf("这两条边已经有联系了！\n");
			x -= 1;
			continue;
		}
		printf("%s 与 %s 已搭建联系。\n",graph->Datas[a].info,graph->Datas[b].info);
		graph->Edge[a][b] = 1;
		graph->Edge[b][a] = 1;
	}
	printf("图构建完成。\n");
	return graph;
}
/* 打印一个无向图 */
static void PrintUndirectedGraph(Graph_UND_M* graph) {
	int x;
	if (graph == NULL || graph->Vertex_amount == 0) {
		return;
	}
	for (x = 0; x < graph->Vertex_amount; x++) {
		PrintUndirectedVertex(graph, x);
	}
}
/* 打印单个顶点 */
static void PrintUndirectedVertex(Graph_UND_M* graph, int index)
{
	int x;
	if (graph == NULL || index < 0 || index >= graph->Vertex_amount) {
		return;
	}
	printf("节点下标 %d ，节点值 %d\n节点说明：%s\n与它链接的节点有：\n\n",index,graph->Datas[index].value,graph->Datas[index].info);
	for(x=0;x<graph->Vertex_amount;x++){
		if (graph->Edge[index][x]) {
			printf("节点下标 %d ，节点值 %d\n节点说明：%s\n",x,graph->Datas[x].value,graph->Datas[x].info);
		}
	}
	printf("\n\n");
}
/* 打印出这个无向图的矩阵 */
static void PrintVertexMatrix(Graph_UND_M* graph)
{
	int x,i;
	if (graph == NULL || graph->Vertex_amount == 0) {
		return;
	}
	for (x = 0; x < graph->Vertex_amount; x++) {
		printf("序号：%d 说明：%s  值：%d\n",x,graph->Datas[x].info,graph->Datas[x].value);
	}
	printf("打印矩阵图：\t");
	for (x = 0; x < graph->Vertex_amount; x++) {
		printf("序号：%d\t",x);
	}
	printf("\n");
	for (x = 0; x < graph->Vertex_amount; x++) {
		printf("\t序号：%d|", x);
		for (i = 0; i < graph->Vertex_amount; i++) {
			printf("%3d\t",graph->Edge[x][i]);
		}
		printf("\n");
	}
}
/* 删除一个无向图的节点 */
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
/* 向一个无向图添加一个端点 */
static BOOL AddUndirectedVertex(Graph_UND_M* graph)
{
	int value,x;
	printf("正在向无向图添加节点。\n");
	if (graph == NULL || graph->Vertex_amount == DEFAULT_SIZE) {
		return false;
	}
	printf("请输入新节点的说明：\n");
	scanf("%s",graph->Datas[graph->Vertex_amount].info);
	printf("请输入新节点的值：\n");
	scanf("%d",&value);
	graph->Datas[graph->Vertex_amount].value = value;
	for (x = 0; x <= graph->Vertex_amount; x++) {
		graph->Edge[x][graph->Vertex_amount] = 0;
		graph->Edge[graph->Vertex_amount][x] = 0;
	}
	graph->Vertex_amount += 1;
	return true;
}
/* 向一个无向图添加边 */
static BOOL AddUndirectedEdge(Graph_UND_M* graph)
{
	int edge_amount,x;
	if (graph == NULL) {
		return false;
	}
	printf("请输入要添加的边数量：\n");
	scanf("%d", &edge_amount);
	if (edge_amount<1 || edge_amount + graph->Edge_amount > graph->Vertex_amount * (graph->Vertex_amount - 1) / 2) {
		printf("请输入合理的值。\n");
		return false;
	}
	graph->Edge_amount += edge_amount;
	for (x = 0; x < edge_amount; x++) {
		int a, b;
		printf("请输入要添加的第 %d 条边的第 1 个邻接点。\n",x+1);
		scanf("%d", &a);
		printf("请输入要添加的第 %d 条边的第 2 个邻接点。\n",x+1);
		scanf("%d", &b);
		if (a == b) {
			printf("请输入有效的值！\n");
			x -= 1;
			continue;
		}
		if (graph->Edge[a][b]) {
			printf("这两条边已经有联系了。");
			x -= 1;
			continue;
		}
		printf("%s 与 %s 已搭建联系。\n", graph->Datas[a].info, graph->Datas[b].info);
		graph->Edge[a][b] = 1;
		graph->Edge[b][a] = 1;
	}
	return true;
}
