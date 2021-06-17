#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAXSIZE 100
#define VNUM 100
#define INF 10000
#define MAXCOST 1000
typedef struct 
{
	int vi,vj;
	int weight;
	int flag;
}Arc;
typedef struct 
{
	int vi;
	int weight;
}LOWCOST;




typedef char ZFC[MAXSIZE];
typedef char VerType[MAXSIZE];

typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *next;
	int weight;
}ArcNode;

typedef struct VerTexNode
{
	VerType vertex;
	struct ArcNode *firstArc;
	int in;
	int out;
}VerTexNode;

typedef struct ALGraph
{
	VerTexNode adjlist[MAXSIZE];
	int vexNum;
	int arcNum;
}ALGraph;

typedef struct MGraph
{
	VerType vexs[MAXSIZE];
	int arcs[MAXSIZE][MAXSIZE];
	int vexNum;
	int arcNum;
}MGraph;

typedef struct SNode
{
	int data;
	struct SNode *next;
}SNode,*Stack;

typedef struct QNode
{
	int data;
	struct QNode *next;
}QNode, *QLink;

typedef struct 
{
	QLink front;
	QLink rear;
}Queue;

void StackInit(Stack *S)
{
	*S=NULL;
}

int StackEmpty(Stack S)
{
	if(S==NULL)
		return 1;
	else
		return 0;
}

int StackGetTop(Stack S)
{
	if(StackEmpty(S))
		return -1;
	return S->data;
}

void StackPush(Stack *S,int e)
{
	Stack p=(Stack)malloc(sizeof(SNode));
	p->data=e;
	p->next=(*S);
	(*S)=p;
}

void StackPop(Stack *S)
{
	if(StackEmpty(*S))
		return ;
	Stack p=(*S);
	(*S)=p->next;
    free(p);
}

void QueueInit(Queue *Q)
{
	Q->front=Q->rear=(QLink)malloc(sizeof(QNode));
	Q->front->next=NULL;
	Q->rear->next=NULL;
}

int QueueEmpty(Queue Q)
{
	if(Q.front==Q.rear)
		return 1;
	else
		return 0;
}
int QueueGetTop(Queue Q)
{
	if(Q.front==Q.rear)
		return -1;
	return Q.front->next->data;
}

void EnQueue(Queue *Q,int e)
{
	QLink p=(QLink)malloc(sizeof(QNode));
	p->data=e;
	p->next=Q->rear->next;
	Q->rear->next=p;
	Q->rear=p;
}

void DeQueue(Queue *Q)
{
	QLink p=Q->front->next;
	if(Q->front==Q->rear)
		return ;
	if(Q->front->next==Q->rear)
		Q->rear=Q->front;
	Q->front->next=p->next;
	free(p);
}

void count_in(ALGraph *G)
{
	int i,j,k;
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
					G->adjlist[k].in++;
				p=p->next;
			}

		}

	}

}
void count_out(ALGraph *G)
{
	int i,k;
	ArcNode *p=NULL;
	for(k=0;k<G->vexNum;k++)
	{
		G->adjlist[k].out=0;
		p=G->adjlist[k].firstArc;
		while(p)
		{
			G->adjlist[k].out++;
			p=p->next;
		}

	}

}
void create_Graph(ALGraph *ALG,MGraph *MG)
{
	int i,j,k;
	int vi,vj,weight;
	int vexnum,arcnum;
	VerType x;
	ArcNode *p=NULL;
	printf("请输入结点数,弧数:");
	scanf("%d%d",&vexnum,&arcnum);
	getchar();
	ALG->vexNum=MG->vexNum=vexnum;
	ALG->arcNum=MG->arcNum=arcnum;
	for(i=0;i<vexnum;i++)
	{
		printf("请输入结点内容:");
		scanf("%s",x);
		getchar();
		strcpy(ALG->adjlist[i].vertex,x);
		ALG->adjlist[i].firstArc=NULL;
		strcpy(MG->vexs[i],x);
	}
	for(i=0;i<vexnum;i++)
		for(j=0;j<vexnum;j++)
			MG->arcs[i][j]=-1;
	for(k=0;k<arcnum;k++)
	{
		printf("请输入弧头,弧尾及边的权值:");
		scanf("%d%d%d",&vi,&vj,&weight);
		getchar();
		MG->arcs[vi-1][vj-1]=weight;
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=vj-1;
		p->next=ALG->adjlist[vi-1].firstArc;
		ALG->adjlist[vi-1].firstArc=p;
		p->weight=weight;
	}
	for(i=0;i<vexnum;i++)
	{
		for(j=0;j<vexnum;j++)
		{
			if(i==j)
				MG->arcs[i][j]=0;
			if(MG->arcs[i][j]==-1)
				MG->arcs[i][j]=INF;
		}

	}

	count_in(ALG);
	count_out(ALG);
}


int Locate_ALG(ALGraph G,VerType x)
{
	int i;
	ArcNode *p=NULL;
	for(i=0;i<G.vexNum;i++)
	{
		if(strcmp(G.adjlist[i].vertex,x)==0)
			return i;
	}
	return -1;
}

int Locate_MG(MGraph G,VerType x)
{
	int i;
	for(i=0;i<G.vexNum;i++)
	{
		if(strcmp(G.vexs[i],x)==0)
			return i;
	}
	return -1;
}

void DFS_ALG(ALGraph G,int v0,int visited[])
{
	Stack S;
	StackInit(&S);
	int v,w;
	ArcNode *p=NULL;
	printf("%s ",G.adjlist[v0].vertex);
	visited[v0]=1;
	StackPush(&S,v0);
	while(!StackEmpty(S))
	{
		v=StackGetTop(S);
		p=G.adjlist[v].firstArc;
		while(p)
		{
			w=p->adjvex;
			if(visited[w]==0)
			{
				printf("%s ",G.adjlist[w].vertex);
				visited[w]=1;
				StackPush(&S,w);
				break;
			}
			p=p->next;

		}
	//	if(p==NULL)
		StackPop(&S);
	}
	putchar('\n');
}

void DFS_Traverse(ALGraph G,int v0,int visited[])
{
	int w;
	ArcNode *p=NULL;
	printf("%s ",G.adjlist[v0].vertex);
	visited[v0]=1;
	p=G.adjlist[v0].firstArc;
	while(p)
	{
		w=p->adjvex;
		if(visited[w]==0)
			DFS_Traverse(G,w,visited);
		p=p->next;
	}


}

void DF_Traverse(ALGraph G)
{
	int visited[MAXSIZE]={0};
	int i;
	for(i=0;i<G.vexNum;i++)
		if(visited[i]==0)
			DFS_Traverse(G,i,visited);
}

void BFS_ALG(ALGraph G,int v0)
{
	Queue Q;
	QueueInit(&Q);
	int v,w;
	ArcNode *p=NULL;
	int visited[MAXSIZE]={0};
	printf("%s ",G.adjlist[v0].vertex);
	visited[v0]=1;
	EnQueue(&Q,v0);
	while(!QueueEmpty(Q))
	{
		v=QueueGetTop(Q);
		p=G.adjlist[v].firstArc;
		while(p)
		{
			w=p->adjvex;
			if(visited[w]==0)
			{
				printf("%s ",G.adjlist[w].vertex);
				visited[w]=1;
				EnQueue(&Q,w);
			}
			p=p->next;
		}
		DeQueue(&Q);

	}
	putchar('\n');

}

void BF_Traverse(ALGraph G)
{
	Queue Q;
	QueueInit(&Q);
	ArcNode *p=NULL;
	int v,w;
	int visited[MAXSIZE]={0};
	int i;
	for(i=0;i<G.vexNum;i++)
	{
		if(visited[i]==0)
		{
			printf("%s ",G.adjlist[i].vertex);
			visited[i]=1;
			EnQueue(&Q,i);
			while(!QueueEmpty(Q))
			{
				v=QueueGetTop(Q);
				p=G.adjlist[v].firstArc;
				while(p)
				{
					w=p->adjvex;
					if(visited[w]==0)
					{
						printf("%s ",G.adjlist[w].vertex);
						visited[w]=1;
						EnQueue(&Q,w);
					}
					p=p->next;

				}
				DeQueue(&Q);

			}

		}

	}

}

void DFS1(MGraph G,int v0,int visited[],Stack *S)
{
	int i;
	visited[v0]=1;
	for(i=0;i<G.vexNum;i++)
		if(visited[i]==0 && G.arcs[v0][i]!=INF && G.arcs[v0][i]!=0)
			DFS1(G,i,visited,S);
	StackPush(S,v0);

}
void DFS2(MGraph G,int v0,int visited[])
{
	int i;
	visited[v0]=1;
	printf("%s ",G.vexs[v0]);
	for(i=0;i<G.vexNum;i++)
	{
		if(visited[i]==0 && G.arcs[v0][i]!=INF && G.arcs[v0][i]!=0)
			DFS2(G,i,visited);
	}
	
}

int Kosaraju(MGraph G)
{
	int i,count=0;
	int v;
	Stack S;
	StackInit(&S);
	int visited[MAXSIZE]={0};
	for(i=0;i<G.vexNum;i++)
		if(visited[i]==0)
			DFS1(G,i,visited,&S);
	for(i=0;i<MAXSIZE;i++)
		visited[i]=0;
	while(!StackEmpty(S))
	{
		v=StackGetTop(S);
		StackPop(&S);
		printf("{");
		if(visited[v]==0)
		{
			count++;
			DFS2(G,v,visited);
		}
		printf("}\n");
	}
	return count;
}

void Print_ALGraph(ALGraph G)
{
	ArcNode *p=NULL;
	int i;
	for(i=0;i<G.vexNum;i++)
	{
		printf("顶点\t权值\t邻接点----\n");
		printf("%s\t",G.adjlist[i].vertex);
		p=G.adjlist[i].firstArc;
		while(p)
		{
			printf("%d\t%d\t",p->weight,p->adjvex);
			p=p->next;
		}
		putchar('\n');

	}

}
void Print_MG(MGraph G)
{
	int i,j,k;
	printf("结点数:%d\n",G.vexNum);
	printf("弧数:%d\n",G.arcNum);
	printf("结点内容:\n");
	for(i=0;i<G.vexNum;i++)
	{
		printf("%s\t",G.vexs[i]);
	}
	printf("邻接矩阵:\n");
	for(i=0;i<G.vexNum;i++)
	{
		for(j=0;j<G.vexNum;j++)
			printf("%d ",G.arcs[i][j]);
		printf("\n");
	}
}

int find(ZFC *s,MGraph G,char c)
{
	int i,j;
	for(i = 0; i < G.vexNum; i++)
	{
		for(j = 0; j < strlen(s[i]); j++)
		{
			if(s[i][j] == c)
				return i;
		}
	}
	return -1;
}

void count_ALG(ALGraph G,int v0)
{
	printf("%s的入度为:%d\n",G.adjlist[v0].vertex,G.adjlist[v0].in);
	printf("%s的出度为:%d\n",G.adjlist[v0].vertex,G.adjlist[v0].out);
	printf("%s的度数为:%d\n",G.adjlist[v0].vertex,G.adjlist[v0].in+G.adjlist[v0].out);
	
}

void Kruskal(MGraph G)
{
	int i,j,k=0;
	int p,q;
	ZFC c[MAXSIZE];
	Arc x[MAXSIZE];
	Arc t;
	for(i=0;i<G.vexNum;i++)
	{
		c[i][0]=i+48;
		c[i][1]='\0';
	}
	for(i=0;i<G.vexNum;i++)
		for(j=0;j<G.vexNum;j++)
		{
			if(G.arcs[i][j]!=INF)
			{
				x[k].vi=i;
				x[k].vj=j;
				x[k].weight=G.arcs[i][j];
				x[k].flag=0;
				k++;
			}

		}

		for(i=0;i<G.vexNum;i++)
		{
			for(j=0;j<G.vexNum-1;j++)
			{
				if(x[j].weight>x[j+1].weight)
				{
					t=x[j];
					x[j]=x[j+1];
					x[j+1]=t;
				}

			}

		}
		for(i=0,k=0;i<G.arcNum;i++)
		{
			p=find(c,G,x[i].vi+48);
			q=find(c,G,x[i].vj+48);
			if(p!=q)
			{
				strcat(c[p],c[q]);
				c[q][0]='\0';
				k++;
				x[i].flag=1;
			}
			if(k==G.vexNum-1)
				break;
		}
		printf("最小生成树:\n");
		printf("顶点\t顶点\t权值\t\n");
		for(i=0;i<G.arcNum;i++)
			if(x[i].flag==1)
				printf("%s\t%s\t%d\t\n",G.vexs[x[i].vi],G.vexs[x[i].vj],x[i].weight);


}



void Prim(MGraph G)
{
	int mincost;
	int i,j,k;
	LOWCOST *lowcost=(LOWCOST*)malloc(sizeof(LOWCOST)*G.vexNum);
	for(i=0;i<G.vexNum;i++)
	{
		lowcost[i].vi=0;
		lowcost[i].weight=G.arcs[0][i];
	}
	lowcost[0].weight=0;
	for(i=1;i<G.vexNum;i++)
	{
		mincost=MAXCOST;
		for(j=0;j<G.vexNum;j++)
		{
			if(lowcost[j].weight<mincost && lowcost[j].weight!=0)
			{
				mincost=lowcost[j].weight;
					k=j;
			}

		}
		printf("%s-->%s=%d\n",G.vexs[lowcost[k].vi],G.vexs[k],mincost);
		lowcost[k].weight=0;
		for(j=0;j<G.vexNum;j++)
		{
			if(G.arcs[k][j]<lowcost[k].weight)
			{
				lowcost[k].weight=G.arcs[k][j];
				lowcost[j].vi=k;
			}

		}


	}

	

}


void Dijkstra(MGraph G,int v0)
{
	int i,j,k,m,flag=1;
	int v1;
	int min,count;
	int path[MAXSIZE][MAXSIZE];
	int dist[MAXSIZE];
	for(i=0;i<G.vexNum;i++)
		for(j=0;j<G.vexNum;j++)
			path[i][j]=-1;
	for(i=0;i<G.vexNum;i++)
	{
		dist[i]=G.arcs[v0][i];
		if(dist[i]!=0 && dist[i]!=INF)
		{
			path[i][0]=v0;
			path[i][1]=i;
		}

	}
	count=0;
	while(flag)
	{
		k=0;
		min=INF;
		for(i=0;i<G.vexNum;i++)
		{
			if(dist[i]<min && dist[i]!=0)
			{
				min=dist[i];
				k=i;
			}

		}
		printf("第%d条最短路径为:%d--",++count,min);
	for(i=0;i<G.vexNum;i++)
		if(path[k][i]!=-1)
			printf("%s ",G.vexs[path[k][i]]);
	printf("\b)\n");

	for(i=0;i<G.vexNum;i++)
	{
		if(i!=k && dist[i]!=0)
		{
			if(G.arcs[k][i]+dist[k]<dist[i])
			{
				dist[i]=G.arcs[k][i]+dist[k];
				for(j=0;j<G.vexNum;j++)
					path[i][j]=path[k][j];
				for(m=0;m<G.vexNum&&path[i][m]!=-1;)
					m++;
				path[i][m]=i;
			}

		}

	}
	dist[k]=0;
	flag=0;
	for(i=0;i<G.vexNum;i++)
		if(dist[i]!=0  && dist[i]<INF)
			flag=1;
	}
	
}

void floyd(MGraph G)
{
	int i,j,k;
	int D[MAXSIZE][MAXSIZE];
	int P[MAXSIZE][MAXSIZE];
	for(i=0;i<G.vexNum;i++)
		for(j=0;j<G.vexNum;j++)
		{
			D[i][j]=G.arcs[i][j];
			P[i][j]=j;
		}
		for(k=0;k<G.vexNum;k++)
			for(i=0;i<G.vexNum;i++)
				for(j=0;j<G.vexNum;j++)
				{
					if(D[i][k]+D[k][j]<D[i][j])
					{
						D[i][j]=D[i][k]+D[k][j];
						P[i][j]=P[i][k];
					}

				}

				printf("D矩阵:\n");
				for(i=0;i<G.vexNum;i++)
				{
					for(j=0;j<G.vexNum;j++)
					{
						printf("%d ",D[i][j]);
					}
					printf("\n");
				}
				printf("P矩阵:\n");
				for(i=0;i<G.vexNum;i++)
				{
					for(j=0;j<G.vexNum;j++)
					{
						printf("%d ",D[i][j]);
					}
					printf("\n");
				}
				for(i=0;i<G.vexNum;i++)
				{
					for(j=0;j<G.vexNum;j++)
					{
						if(i!=j)
						{
							printf("%s到%s的距离为:%d\n",G.vexs[i],G.vexs[j],D[i][j]);
							printf("路径如下:\n");
							printf("%s",G.vexs[i]);
							k=P[i][j];
							while(k!=j)
							{
								printf("-->%s",G.vexs[k]);
								k=P[k][j];
							}
							printf("-->%s",G.vexs[j]);
						}
						printf("\n");
					}

				}
				printf("\n");
}

int Topology_sort(ALGraph G)
{
	int i,m=0;
	int v,w;
	Stack S;
	StackInit(&S);
	ArcNode *p=NULL;
	for(i=0;i<G.vexNum;i++)
		if(G.adjlist[i].in==0)
			StackPush(&S,i);
	while(!StackEmpty(S))
	{
		v=StackGetTop(S);
		StackPop(&S);
		printf("%s ",G.adjlist[v].vertex);
		m++;
		p=G.adjlist[v].firstArc;
		while(p)
		{
			w=p->adjvex;
			G.adjlist[w].in--;
			if(G.adjlist[w].in==0)
				StackPush(&S,w);
			p=p->next;

		}


	}
	if(m<G.vexNum)
		return 0;
	return 1;

}

void Critical_Path(ALGraph G)
{
	int i,j,k;
	int v,w;
	int ve[MAXSIZE]={0};
	int vl[MAXSIZE]={0};
	int ee[MAXSIZE]={0};
	int el[MAXSIZE]={0};
	Stack S1,S2;
	StackInit(&S1),StackInit(&S2);
	ArcNode *p=NULL;
	for(i=0;i<G.vexNum;i++)
		if(G.adjlist[i].in==0)
			StackPush(&S1,i);
	while(!StackEmpty(S1))
	{
		v=StackGetTop(S1);
		StackPop(&S1);
		StackPush(&S2,v);
		p=G.adjlist[v].firstArc;
		while(p)
		{
			w=p->adjvex;
			G.adjlist[w].in--;
			if(G.adjlist[w].in==0)
				StackPush(&S1,w);
			if(ve[v]+p->weight>ve[w])
				ve[w]=ve[v]+p->weight;
			p=p->next;
		}

	}
	for(i=0;i<G.vexNum;i++)
		vl[i]=ve[G.vexNum-1];
	while(!StackEmpty(S2))
	{
		v=StackGetTop(S2);
		StackPop(&S2);
		p=G.adjlist[v].firstArc;
		while(p)
		{
			w=p->adjvex;
			if(vl[w]-p->weight<vl[v])
				vl[v]=vl[w]-p->weight;
			p=p->next;
		}


	}
	i=0;
	printf("关键路径:\n");
	for(j=0;j<G.vexNum;j++)
	{
		p=G.adjlist[j].firstArc;
		while(p)
		{
			k=p->adjvex;
			ee[i]=ve[j];
			el[i]=vl[k]-p->weight;
			if(ee[i]==el[i])
				printf("%s---%d---%s ",G.adjlist[j].vertex,p->weight,G.adjlist[k].vertex);
			i++;
			p=p->next;
		}

	}
	printf("\n关键活动:\n");
	for(j=0;j<G.vexNum;j++)
		if(ee[j]==el[j])
			printf("a%d ",j+1);
	printf("\n");
}


void menu()
{
	ALGraph ALG;
	MGraph MG;
	int visited[MAXSIZE]={0};
	int chice;
	int v0,v1;
	int i;
	VerType s;
	printf("-----------------有向图---------------|\n");
	printf("|         1.创建图                    |\n");
	printf("|         2.打印邻接表                |\n");
	printf("|         3.求连通分量                |\n");
	printf("|         4.深度优先遍历              |\n");
	printf("|         5.广度优先遍历              |\n");
	printf("|         6.求给定顶点的度            |\n");
	printf("|         7.打印邻接矩阵              |\n");
	printf("|         8.Dijkstra最短路径         |\n");
	printf("|         9.floyd最短路径            |\n");
	printf("|         10.拓扑排序                |\n");
	printf("|         11.关键路径                |\n");
	printf("|         12.prim求最小生树           |\n");
	printf("|         13.kruskal算法求最小生成   |\n");
	printf("|         0.退出                     |\n");
	printf("|------------------------------------|\n");
	while(1)
	{
		printf("请输入你的选择:");
		scanf("%d",&chice);
		getchar();
		switch(chice)
		{
		case 0:system("cls");
			printf("正在退出...\n");
			exit(0);
			break;
		case 1:create_Graph(&ALG,&MG);
			printf("创建完成.....\n");
			break;
		case 2:Print_ALGraph(ALG);
			break;
		case 3:printf("该图有%d个连通分量\n",Kosaraju(MG));
			break;
		case 4:for(i=0;i<MAXSIZE;i++)
				   visited[i]=0;
			printf("请输入结点内容:");
			scanf("%s",s);
			getchar();
			v0=Locate_ALG(ALG,s);
			printf("连通图:\n");
			DFS_Traverse(ALG,v0,visited);
			printf("\n全图:\n");
			DF_Traverse(ALG);
			putchar('\n');
			break;
		case 5:printf("请输入结点内容:");
			scanf("%s",s);
			getchar();
			v0=Locate_ALG(ALG,s);
			BFS_ALG(ALG,v0);
			break;
		case 6:printf("请输入结点内容:");
			scanf("%s",s);
			getchar();
			v0=Locate_ALG(ALG,s);
			count_ALG(ALG,v0);
			break;
		case 7:Print_MG(MG);
			printf("\n");
			break;
		case 8:printf("请输入结点内容:");
			scanf("%s",s);
			getchar();
			v0=Locate_ALG(ALG,s);
			Dijkstra(MG,v0);
			break;
		case 9:floyd(MG);
			break;
		case 10:Topology_sort(ALG);
			putchar('\n');
			break;
		case 11:Critical_Path(ALG);
			break;
		case 12:Prim(MG);
			break;
		case 13:Kruskal(MG);
			break;
		default:printf("选择错误!\n");
			menu();
		}

	}

}

 
int main()
{
	menu();
	system("pause");
	getchar();
	return 0;
}