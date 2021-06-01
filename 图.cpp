#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <graphics.h>
#define MAXCOST 10000
#define VNUM 100
#define MAXSIZE 100

typedef char ZFC[MAXSIZE];

typedef char VertexType;

typedef struct 
{
	VertexType vexs[VNUM];
	int arcs[VNUM][VNUM];
	int vexNum;
	int arcNum;
}MGraph;

/*******边链表*******/
typedef struct ArcNode
{
	int adjvex;//弧所指结点位置
	struct ArcNode *next;//指向下一条弧
	int weight;//边上的权值
}ArcNode;


/*************表头结点*******/
typedef char TexType;
typedef struct VertexNode
{
	TexType vertex;
	ArcNode *firstArc;
}VertexNode;

typedef struct ALGraph
{
	VertexNode adjlist[MAXSIZE];
	int vexNum;//顶点个数
	int arcNum;//弧个数
}ALGraph;

typedef struct 
{
	int vi;//生成树结点下标
	int vj;//待选结点下标
	int weight;//边上的权
}LowCost;


typedef int QueueType;
typedef struct QNode
{
	QueueType Qdata;
	struct QNode *next;
}QNode,*LinkQueue;

typedef struct
{
	LinkQueue front;
	LinkQueue rear;
}QLink;


void LinkQueueInit(QLink *Q)
{
	Q->front=Q->rear=(LinkQueue)malloc(sizeof(QNode));
	if(Q->front==NULL)
		return  ;
	Q->front->next=NULL;
}

int LinkQueueEmpty(QLink Q)
{
	if(Q.front==Q.rear)
		return 1;
	else
		return 0;
}

int LinkQueueLength(QLink Q)
{
	LinkQueue p=NULL;
	int length=0;
	if(Q.front==Q.rear )
		return 0;
	p=Q.front->next;
	while(p)
	{
		length++;
		p=p->next;
	}
	return length;
}

QueueType GetTop(QLink Q)
{
	if(Q.front==Q.rear)
		return 0;
	return Q.front->next->Qdata ;
}

void LinkEnQueue(QLink *Q,QueueType e)
{
	LinkQueue p=(LinkQueue)malloc(sizeof(QNode));
	if(p==NULL)
		return ;
	p->Qdata=e;
	p->next=NULL;
	Q->rear->next=p;
	Q->rear=p;
}
void LinkDeQueue(QLink *Q)
{
	LinkQueue p;
	if(Q->front==Q->rear)
		return ;
	p=Q->front->next;
	if(Q->rear==p)
		Q->rear=Q->front;
	Q->front->next=p->next;
	free(p);
}

typedef int StackType;

typedef struct SNode
{
	StackType Sdata;
	struct SNode *next;
}SNode,*LinkStack;

void LinkStackInit(LinkStack *S)
{
	*S=NULL;
}

int isEmpty(LinkStack S)
{
    if(S==NULL)
		return 1;
	else
		return 0;
}

int LinkStackLength(LinkStack S)
{
	int length=0;
	if(S==NULL)
		return 0;
	LinkStack p=S;
	while(p)
	{
         length++;
		 p=p->next;
	}
	return length;
}

StackType LinkStackGetTop(LinkStack S)
{
	if(S==NULL)
		return 0;
	return S->Sdata;
}

void LinkStackPush(LinkStack *S,StackType e)
{
	LinkStack p=NULL;
	p=(LinkStack)malloc(sizeof(SNode));
	p->Sdata=e;
	p->next=*S;
	*S=p;
}

void LinkStackPop(LinkStack *S)
{
	LinkStack p=*S;
	if(*S==NULL)
		return  ;
	*S=(*S)->next;
	free(p);

}
void LinkStackTraver(LinkStack *S)
{
	LinkStack p=*S;
	if(p==NULL)
		return ;
	while(p)
	{
		printf("%d\t",p->Sdata);
		p=p->next;
	}

}


/****创建邻接表存储结构图**********/
void create_ALGraph(ALGraph *G)
{
	int i,j,k;
	int weight;
	ArcNode *p;
	printf("请输入结点数,边数:");
	scanf("%d%d",&G->vexNum,&G->arcNum);
	getchar();
	for(i=0;i<G->vexNum;i++)
	{
		printf("请输入结点信息:");
		scanf("%c",&G->adjlist[i].vertex);
		getchar();
		G->adjlist[i].firstArc=NULL;
	}
	for(k=0;k<G->arcNum;k++)
	{
		printf("请输入边头位置和边尾位置及权重:");
		scanf("%d%d%d",&i,&j,&weight);
		getchar();
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j-1;
		p->weight=weight;
		p->next=G->adjlist[i-1].firstArc;
		G->adjlist[i-1].firstArc=p;
	}
}


/********无向图的邻接矩阵****************/
void create_MGraph(MGraph *G)
{
	int i,j,k,num;
	int weight;
	printf("请输入结点数,弧数:");
	scanf("%d%d",&G->vexNum,&G->arcNum);
	getchar();
	num=G->vexNum;
	for(i=0;i<G->vexNum;i++)
	{
	    printf("请输入结点内容:");
	    scanf("%c",&G->vexs[i]);
	    getchar();
	}
	for(i=0;i<G->vexNum;i++)
		for(j=0;j<G->vexNum;j++)
			G->arcs[i][j]=-1;
	for(k=0;k<G->arcNum;k++)
	{
		printf("请输入结点的邻接关系(vi->vj)及权值:");
		scanf("%d%d%d",&i,&j,&weight);
		getchar();
		G->arcs[i-1][j-1]=weight;
		G->arcs[j-1][i-1]=weight;
	}
	for(k=0;k<num;k++)
	{
		for(j=0;j<num;j++)
		{
			if(k==j)
				G->arcs[k][j]=0;
			if(G->arcs[k][j]==-1)
				G->arcs[k][j]=MAXCOST;
		}
	}

}

/***********有向图的邻接矩阵*******/
void create_nMGraph(MGraph *NMG)
{
	int i,j,k;
	int weight;
	int num;
	printf("请输入结点数,弧数:");
	scanf("%d%d",&NMG->vexNum,&NMG->arcNum);
	getchar();
	num=NMG->vexNum;
	for(i=0;i<NMG->vexNum;i++)
	{
	    printf("请输入结点内容:");
	    scanf("%c",&NMG->vexs[i]);
	    getchar();
	}
	for(i=0;i<NMG->vexNum;i++)
		for(j=0;j<NMG->vexNum;j++)
			NMG->arcs[i][j]=-1;
	for(k=0;k<NMG->arcNum;k++)
	{
		printf("请输入结点的邻接关系(vi->vj),及权值:");
		scanf("%d%d%d",&i,&j,&weight);
		getchar();
		NMG->arcs[i-1][j-1]=weight;
	}
	for(k=0;k<num;k++)
	{
		for(j=0;j<num;j++)
		{
			if(k==j)
				NMG->arcs[k][j]=0;
			if(NMG->arcs[k][j]==-1)
				NMG->arcs[k][j]=MAXCOST;
		}
	}
}

/***********打印邻接矩阵*********/
void print_MG(MGraph MG)
{
 int i,j;
 printf("Graph vertex number: %d\n",MG.vexNum);
 printf("Graph arc number: %d\n",MG.arcNum);
 printf("Vertex set:");
 for(i=0;i<=MG.vexNum;i++)
 {
  printf("%c",MG.vexs[i]);
 }
 printf("\nAdjacency Matrix:\n");
 for(i=0;i<MG.vexNum;i++)
 {
  for(j=0;j<MG.vexNum;j++)
  {
   printf("%d\t",MG.arcs[i][j]);
  }
  printf("\n");
 }

}

/************邻接矩阵的深度优先遍历*********/
void df_Traver (MGraph *G,int v,int visited[])
{
	int j;
	printf("%c ",G->vexs[v]);
	visited[v]=1;
	for(j=0;j<G->vexNum;j++)
	{
		if(G->arcs[v][j]!=0&&G->arcs[v][j]!=MAXCOST&&visited[j]==0)
			df_Traver(G,j,visited);
	}

}

/*************邻接表存储图的深度优先遍历*********/
void df_Traver_ALG(ALGraph G,int v)
{
	LinkStack S;
	LinkStackInit(&S);
	ArcNode *p;
	int i,j,k;
	int visited[MAXSIZE]={0};
	printf("%c ",G.adjlist[v].vertex);
	visited[v]=1;
	LinkStackPush(&S,v);
	while(!isEmpty(S))
	{
		k=LinkStackGetTop(S);
		p=G.adjlist[k].firstArc;
		while(p)
		{
			if(p && visited[p->adjvex]==0)
			{
				printf("%c ",G.adjlist[p->adjvex].vertex);
				visited[p->adjvex]=1;
				LinkStackPush(&S,p->adjvex);
				break;
			}
			p=p->next;

		}
		if(!p)
			LinkStackPop(&S);
	}


}


/**********邻接表存储图的广度优先遍历************/
void bf_traver(ALGraph *G,int v0)
{
	QLink Q;
	LinkQueueInit(&Q);
	int visited[MAXSIZE]={0};
	int i,v,w;
	ArcNode *p;
	printf("%c ",G->adjlist[v0].vertex);
	visited[v0]=1;
	LinkEnQueue(&Q,v0);
	while(!LinkQueueEmpty(Q))
	{
		v=GetTop(Q);
		LinkDeQueue(&Q);
		p=G->adjlist[v].firstArc;
		while(p);
		{
			w=p->adjvex;
			if(visited[w]==0)
			{
				printf("%c ",G->adjlist[w].vertex);
	            visited[w]=1;
	            LinkEnQueue(&Q,w);
			}
			p=p->next;
		}

	}


}

/***********邻接矩阵存储图中判断是否有回路*******/
void DFS_Loop(MGraph *G,int v,int visited[])
{
	visited[v]=1;
	int di,vi,j;
	for(di=0,vi=0,j=0;j<G->vexNum;j++)
	{
		if(G->arcs[v][j])
		{
			di++;
			if(visited[j])
				vi++;
		}

	}
	if(di==vi&&di!=1)
	{
		printf("\n有回路!\n");
		return ;
	}
	else
	{
		printf("没有回路!");
		return ;
	}
	for(j=0;j<G->vexNum;j++)
			if(G->arcs[v][j]&&!visited[j])
				DFS_Loop(G,j,visited);

}

/**************prim算法求最小生成树*********/
void prim(MGraph G)
{
	int mincost,i,j,k;//mincost表无穷大;用来存储最小权值
	LowCost *lowcost=(LowCost*)malloc(sizeof(LowCost)*G.vexNum);
	//动态创建数组
	for(i=0;i<G.vexNum;i++)
	{
		lowcost[i].vi=0;
		lowcost[i].vj=i;
		lowcost[i].weight=G.arcs[0][i];
	}
	lowcost[0].weight=0;
	for(i=1;i<G.vexNum;i++)
	{
		mincost=MAXCOST;
		for(j=0;j<G.vexNum;j++)
			if(lowcost[j].weight<mincost && lowcost[j].weight!=0)
			{
				mincost=lowcost[j].weight;
				k=j;
			}

			printf("%c----%d-->%c\n",G.arcs[lowcost[k].vi+1],mincost,G.arcs[lowcost[k].vj+1]);
			lowcost[k].weight=0;
			for(j=0;j<G.vexNum;j++)//比较权值,若新的权值小,则更新;
			{
				if(G.arcs[k][j]<lowcost[j].weight)
				{
					lowcost[j].weight=G.arcs[k][j];
					lowcost[j].vi=k;
				}

			}

	}


}
/***************lowcost数组下标直接表示最小生成树的边所指向结点***************/
/**********************属于同一代码****************************************/
typedef struct
{
	int vi;
	int weight;
}LOWCOST;

void prim_1(MGraph G)
{
	int mincost,i,j,k;
	LOWCOST *lowcost=(LOWCOST *)malloc(sizeof(LOWCOST)*G.vexNum);
	for(i=0;i<G.vexNum;i++)
	{
		lowcost[i].vi=0;
		lowcost[i].weight=G.arcs[0][i];
	}
	lowcost[0].weight=0;
	for(i=0;i<G.vexNum;i++)
	{
		mincost=MAXCOST;
		for(j=0;j<G.vexNum;j++)
			if(lowcost[j].weight<mincost&&lowcost[j].weight!=0)
			{
				mincost=lowcost[j].weight;
				k=j;
			}
			printf("%c---%d--->%c\n",G.vexs[lowcost[k].vi+1],mincost,G.vexs[k+1]);
			lowcost[k].weight=0;
			for(j=0;j<G.vexNum;j++)
				if(G.arcs[k][j]<lowcost[j].weight)
				{
					lowcost[j].weight=G.arcs[k][j];
					lowcost[j].vi=k;
				}


	}


}

 /************Kruskal算法求最小生成树************/
int find(ZFC *s,int n,char c)
{
	for(int i=0;i<n;i++)
		for(int j=0;j<strlen(s[i]);j++)
			if(s[i][j]==c)
				return 1;
	return -1;

}

void Kruskal(MGraph G)
{
	//从序号0出发
	int i,j,k,t,p,q,x[MAXSIZE][4];
	ZFC c[MAXSIZE];
	for(i=0;i<G.vexNum;i++)
	{
		c[i][0]=i+48;//顶点下标转换成字符存入字符串c中
		c[i][1]=0;
	}
	for(i=0,k=0;i<G.vexNum;i++)
	{
		for(j=i;j<G.vexNum;j++)
			if(G.arcs[i][j]!=0 && G.arcs[i][j]!=MAXCOST)
			{
				x[k][0]=i;//存前驱结点位置
				x[k][1]=j;//存所指结点位置
				x[k][2]=G.arcs[i][j];//存储权值
				x[k][3]=0;//标记已访问
				k++;
			}

	}

	//权值有小到大排序(冒泡排序法)
	for(i=0;i<G.arcNum;i++)
		for(j=0;j<G.arcNum;j++)
			if(x[j][2]>x[j+1][2])
				for(p=0;p<4;p++)
				{
					t=x[j][p];
					x[j][p]=x[j+1][p];
					x[j+1][p]=t;
				}
				for(i=0,k=0;i<G.arcNum;i++)
				{
					p=find(c,G.vexNum,x[i][0]+48);//判断顶点x[i][0]所属连通分量
					q=find(c,G.vexNum,x[i][1]+48);//判断指向结点所属连通分量
					if(p!=q)
					{
						strcat(c[p],c[q]);
						c[q][0]=0;
						k++;
						x[i][3]=1;
					}
					if(k==G.vexNum-1)
						break;
				}
				printf("最小生成树的边为:\n");
				printf("顶点\t顶点\t权值\n");
				for(i=0;i<G.arcNum;i++)
				{
					if(x[i][3]==1)
						printf("%s\t%s\t%s\n",G.vexs[x[i][0]],G.vexs[x[i][1]],G.vexs[x[i][2]]);

				}


}

/**********dijkstra 算法求最短路径 *********/
/***
    引进有个一维数组dist[]表示从源点到各结点的路径长度:
	若自己到自己则为0,连通则为权值,不连通则为无穷大
	引进一个二维数组path[][],path[i]表示源点到vi路径中所经过的结点的下标
	无向图
	*********/
void dijkstra(MGraph G,int v)
{
	//G为领接矩阵存储的无向图
	//采用无向图的构造函数
	//若有邻接,则权值,若不连通则为无穷大MAXCOST
	int dist[MAXSIZE];
	int path[MAXSIZE][MAXSIZE];
	int i,j,k,m,n,min,flag;
	for(i=0;i<G.vexNum;j++)
		for(j=0;j<G.vexNum;j++)
			path[i][j]=-1;//初始化路径
	for(i=0;i<G.vexNum;i++)
	{
		dist[i]=G.arcs[v][i];
	       if(dist[i]!=0 && dist[i]!=MAXCOST)
		      path[i][0]=v;
	}
	n=0;
	flag=1;
	while(flag)
	{
		k=0;min=MAXCOST;
		//找dist中最短路径
		for(j=0;j<G.vexNum;j++)
			if(dist[j]!=0 &&dist[j]<min)
			{
				k=j;
				min=dist[j];
			}
			//打印最短路径
			printf("第%d条最短路径长度为%d--",++n,min);
			for(j=0;j<G.vexNum;j++)
				if(path[k][j]!=-1)
					printf("%d",G.vexs[path[k][j]]);
			printf("\b)\n");
			//更新path,dist
			for(j=0;j<G.vexNum;j++)
				if(j!=k && dist[j]!=0 && dist[j]!=MAXCOST)
					if(dist[k]+G.arcs[k][j]<dist[j])
					{
						dist[j]=dist[k]+G.arcs[k][j];
						for(m=0;m<G.vexNum;m++)
							path[j][m]=path[k][m];
						for(m=0;m<G.vexNum&&path[j][m]!=-1;)
							m++;
						path[j][m]=j;
					}
					dist[k]=0;
					flag=0;
					for(j=0;j<G.vexNum;j++)
						if(dist[j]!=0 && dist[j]<MAXCOST)
							flag=1;
	}

}


/*********弗洛伊德求每一对顶点之间的距离**********/
typedef int PATHINT[MAXSIZE];
void floyd(MGraph G)
{
	int i,j,k,m,n,p;
	int d[MAXSIZE][MAXSIZE];
	PATHINT path[MAXSIZE][MAXSIZE];
	/*初始化d*/
	for(i=0;i<G.vexNum;i++)
		for(j=0;j<G.vexNum;j++)
		{
			d[i][j]=G.arcs[i][j];
			for(k=0;k<G.vexNum;k++)
				path[i][j][k]=-1;
		}
		/****打印输出d的初始值************/
		printf("\ndist的初值:\n");
		for(i=0;i<G.vexNum;i++)
		{
			for(j=0;j<G.vexNum;j++)
				printf("%6d",d[i][j]);
			printf("\n");
		}
		/***********初始化path*********/
		for(i=0;i<G.vexNum;i++)
			for(j=0;j<G.vexNum;j++)
				if(d[i][j]!=MAXCOST&&d[i][j]!=0)
				{
					path[i][j][0]=i;
					path[i][j][1]=j;
				}
				printf("\npath的初始值:\n");
				for(i=0;i<G.vexNum;i++)
				{
					for(j=0;j<G.vexNum;j++)
					{
						for(k=0;path[i][j][k]!=-1;k++)
							printf("%d,",path[i][j][k]);
						if(k!=0)
							printf("\b");
						printf("\t\t");
					}
					printf("\n");
				}

				for(k=0;k<G.vexNum;k++)
				{
					for(i=0;i<G.vexNum;i++)
						for(j=0;j<G.vexNum;j++)
							if(d[i][k]+d[k][j]<d[i][j])
							{
								d[i][j]=d[i][k]+d[k][j];
								for(m=0;m<G.vexNum;m++)
									path[i][j][m]=path[i][k][m];
								for(n=1;n<G.vexNum;m++,n++)
									path[i][j][m]=path[k][j][n];
							}
							printf("\ndist的第%d次迭代效果\n",k+1);
							for(m=0;m<G.vexNum;m++)
							{
								for(n=0;n<G.vexNum;n++)
									printf("%6d",d[m][n]);
								printf("\n");
							}
							printf("\npath的第%d的迭代结果\n",k+1);
							for(i=0;i<G.vexNum;i++)
							{
								for(j=0;j<G.vexNum;j++)
								{
									for(m=0;path[i][j][k]!=-1;m++)
										printf("%d,",path[i][j][m]);
									if(m!=0)
										printf("\b");
									printf("\t\t");
								}
								printf("\n");
							}
				}
}

 

int main(void)
{
 MGraph MG;
 MGraph NMG;
 ALGraph AG;
 int visited[MAXSIZE]={0};
 /*create_ALGraph(&AG);
 df_Traver_ALG(AG,0);*/
 create_MGraph(&MG);
 print_MG(MG);
 prim(MG);
 /*create_nMGraph(&NMG);
 print_MG(NMG);
 df_Traver(&NMG,0,visited);*/
 system("pause");
 getchar();
  return 0;
} 
