#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef char VerType;
#define MAXSIZE 100
#define INF   10000
#define MAX   1000
#define QUEUEMAX 100
#define STACKMAX 100

typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextArc;
	int weight;
}ArcNode;

typedef struct VerTexNode
{
	VerType vertex;
	ArcNode * firstArc;
	int in;
	int out;
}VerTexNode;

typedef struct
{
	VerTexNode adjlist[MAXSIZE];
	int vexNum;
	int arcNum;
}ALGraph;

typedef int QueueType;
typedef int LinkStackType;
typedef struct
{
	QueueType Qdata[QUEUEMAX];
	int rear;
	int front;
	int queuesize;

}SqQueue;
typedef struct SNode
{
	LinkStackType Sdata;
	struct SNode *next;
}SNode,*LinkStack;

void LinkStackInit(LinkStack *S)
{
	*S=NULL;
}
int LinkStackEmpty(LinkStack S)
{
	if(S==NULL)
		return 1;
	else
		return 0;
}

int LinkStackLength(LinkStack S)
{
	LinkStack p=S;
	int length=0;
	if(p)
	{
		length++;
		p=p->next ;
	}
	return length;
}

LinkStackType LinkStackGetTop(LinkStack S)
{
	if(S==NULL)
		return 0;
	return S->Sdata;
	
}
void LinkStackPush(LinkStack *S,LinkStackType e)
{
	LinkStack p=(LinkStack)malloc(sizeof(SNode));
	p->Sdata=e;
	p->next =(*S) ;
	(*S)=p;

}

void LinkStackPop(LinkStack *S)
{
	if(*S==NULL)
		return ;
	LinkStack p=*S;
	(*S)=(*S)->next ;
	free(p);
}

void LinkStackPrint(LinkStack *S)
{
	LinkStack p=*S;
	while(p)
	{
		printf("%s\n",p->Sdata );
		p=p->next ;
	}

}


void SqQueueInit(SqQueue *Q)
{
	Q->front=Q->rear=0;
	Q->queuesize=QUEUEMAX;

}

int SqQueueEmpty(SqQueue Q)
{
	if(Q.front==Q.rear)
		return 1;
	else
		return 0;
}

QueueType SqQueueGetTop(SqQueue Q)
{
	if(Q.front==Q.rear)
		return 0;
	return Q.Qdata[Q.front];
}


void SqEnQueue(SqQueue *Q,QueueType e)
{
	if((Q->rear+1)%Q->queuesize==Q->front)
		return ;
	Q->Qdata[Q->rear]=e;
	Q->rear=(Q->rear+1)%Q->queuesize;
}

QueueType SqDeQueue(SqQueue *Q)
{
	if(Q->front==Q->rear)
		return 0;
	QueueType *e=Q->Qdata;
	Q->front=(Q->front+1)%Q->queuesize;
	return *e;
}


void create_ALGraph(ALGraph *G)
{
	int i,j;
	int m,n;
	int vi,vj,weight;
	ArcNode *p;
	printf("请输入结点数和弧数:");
	scanf("%d%d",&m,&n);
	getchar();
	G->vexNum=m;
	G->arcNum=n;
	for(i=0;i<m;i++)
	{
		printf("请输入结点内容:");
		scanf("%c",&G->adjlist[i].vertex);
		getchar();
		G->adjlist[i].firstArc=NULL;
	}
	for(j=0;j<n;j++)
	{
		printf("请输入弧的顶点和尾点以及弧上的权值:");
		scanf("%d%d%d",&vi,&vj,&weight);
		getchar();
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=vj-1;
		p->nextArc=G->adjlist[vi-1].firstArc;
		G->adjlist[vi-1].firstArc=p;
		p->weight=weight;
	}
}

/*************求结点的入度***********/
void find_in_degree(ALGraph *G)
{
	int i,k;
	ArcNode *p=NULL;
	for(k=0;k<G->vexNum;k++)
	{
		G->adjlist[k].in=0;
		for(i=0;i<G->vexNum;i++)
		{
			p=G->adjlist[i].firstArc;
			while(p)
			{
				if(p->adjvex==k)
					(G->adjlist[k].in)++;
				p=p->nextArc;
			}

		}

	}

}
/****************求出度************/
void find_out_degree(ALGraph *G)
{
	int i,k;
	ArcNode *p=NULL;
	for(k=0;k<G->vexNum;k++)
	{
		G->adjlist[k].out=0;
			p=G->adjlist[k].firstArc;
			while(p!=NULL)
			{
				G->adjlist[k].out++;
				p=p->nextArc;
			}

	}

}


void df_Traver_ALGraph(ALGraph G,int vi,int visited[])
{
	LinkStack S;
	int v,w;
	ArcNode *p;
	LinkStackInit(&S);
	printf("%c ",G.adjlist[vi].vertex);
	LinkStackPush(&S,vi);
	while(!LinkStackEmpty(S))
	{
		v=LinkStackGetTop(S);
		p=G.adjlist[v].firstArc;
		while(p)
		{
			w=p->adjvex;
			if(visited[w]==0)
			{
				printf("%c ",G.adjlist[w].vertex);
				visited[w]=1;
				LinkStackPush(&S,w);
				break;
			}
			p=p->nextArc;
		}

		if(p==NULL)
			LinkStackPop(&S);
	}
	printf("----------------------\n");
}
void DFS_1(ALGraph G,int visited[])
{
	int i;
	for(i=0;i<G.vexNum;i++)
		if(visited[i]==0)
			df_Traver_ALGraph(G,i,visited);
}


void bf_Traver_ALGraph(ALGraph G,int v0)
{
	int i,j;
	SqQueue Q;
	SqQueueInit(&Q);
	int visited[MAXSIZE]={0};
	ArcNode *p=NULL;
	int v,w;
	printf("%c ",G.adjlist[v0].vertex);
	visited[v0]=1;
	SqEnQueue(&Q,v0);
	while(!SqQueueEmpty(Q))
	{
		v=SqDeQueue(&Q);
		p=G.adjlist[v].firstArc;
		while(p!=NULL)
		{
			w=p->adjvex;
			if(visited[w]==0)
			{
				printf("%c ",G.adjlist[w].vertex);
				visited[w]=1;
				SqEnQueue(&Q,w);

			}
			p=p->nextArc;
		}

	}


}

void print(ALGraph G)
{
	ArcNode *p=NULL;
	int i,v;
	SqQueue Q;
	SqQueueInit(&Q);
	for(i=0;i<G.vexNum;i++)
	{
		printf("%c-->",G.adjlist[i].vertex);
		p=G.adjlist[i].firstArc;
		while(p)
		{
			v=p->adjvex;
			printf("%c-->",G.adjlist[v].vertex);
			p=p->nextArc;
		}
		putchar('\n');
	}


}

int count_digree(ALGraph G,int v0)
{
	int degree=G.adjlist[v0].in+G.adjlist[v0].out;
	return degree;
}

int Locate(ALGraph G,VerType elem)//定位这个结点在数组中的位置
{	int i;
for(i=0;i<G.vexNum;i++)
{	if(elem==G.adjlist[i].vertex)
		return i; 
	}
	return 0;//找不到对应元素，返回-1表示不存在 
}

/*void Dijkstra(ALGraph g,VerType start)
{	int i,j,min,minnum,pa=0;
	int sumweight[MAXSIZE];//目前起始点到该点路径的权值和 
	int lastroad[MAXSIZE];//当前最短路径 
	int lastnum; //当前最短路径长度
	int lastweight=0;//当前最短路径权值 
	int judge[MAXSIZE]={0};//判断该点是否已经找到路径 
	sumweight[pa]=0;
	lastroad[0]=start;
	 
	//初始化操作 
	pa=Locate(g,start); 
	lastnum=1;
	lastroad[0]=start;
	judge[pa]=1;
	for(i=0;i<g.vexNum;i++)
	{	if(judge[i]==1)//已经找到 
		continue;
	sumweight[i]=lastweight+g.adjlist[i].firstArc->weight;//刷新权值表 
	}

for(j=1;j<g.vexNum;j++)	
{
	min=MAX;
	for(i=0;i<g.vexNum;i++)
	{	if(sumweight[i]>0&&judge[i]==0&&sumweight[i]<min)
			{	min=sumweight[i];//找到权值最小 
				minnum=i; //权值最小的位置 
			}	
	}
	//向最短路径数组中增加 
	printf("%d-->%d：",lastroad[0],g.adjlist[minnum].vertex);
	for(i=0;i<lastnum;i++)
	{
		printf("%d--->",lastroad[i]);
	}
	printf("%d 总权值为%d\n",g.adjlist[minnum].vertex,sumweight[minnum]);
	judge[minnum]=1;
	lastroad[lastnum]=g.adjlist[minnum].vertex;
	lastweight=sumweight[minnum]; 
	lastnum++;
	start=g.adjlist[minnum].vertex;
	for(i=0;i<g.vexNum;i++)
	{	if(judge[i]==1)//已经找到 
		continue;
	if(g.adjlist[i].firstArc->weight!=INF&&(g.adjlist[i].firstArc->weight+lastweight<sumweight[i]||sumweight[i]==-1))
		sumweight[i]=lastweight+g.adjlist[i].firstArc->weight;//刷新权值表 
	}
}
}*/
 /**************弗洛伊德算法求最短路径**********/


int main()
{
	ALGraph G;
	create_ALGraph(&G);
	/*find_in_degree(&G);
	find_out_degree(&G);
	int visited[MAXSIZE]={0};
	find_in_degree(&G);
	find_out_degree(&G);
	df_Traver_ALGraph(G,0,visited);
	for(int i=0;i<MAXSIZE;i++)
    visited[i]=0;*/
	bf_Traver_ALGraph(G,0);
	Dijkstra(G,'A');
	/*print(G);
	DFS_1(G,visited);*/
	system("pause");
	getchar();
	return 0;
}
