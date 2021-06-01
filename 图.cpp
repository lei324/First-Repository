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

/*******������*******/
typedef struct ArcNode
{
	int adjvex;//����ָ���λ��
	struct ArcNode *next;//ָ����һ����
	int weight;//���ϵ�Ȩֵ
}ArcNode;


/*************��ͷ���*******/
typedef char TexType;
typedef struct VertexNode
{
	TexType vertex;
	ArcNode *firstArc;
}VertexNode;

typedef struct ALGraph
{
	VertexNode adjlist[MAXSIZE];
	int vexNum;//�������
	int arcNum;//������
}ALGraph;

typedef struct 
{
	int vi;//����������±�
	int vj;//��ѡ����±�
	int weight;//���ϵ�Ȩ
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


/****�����ڽӱ�洢�ṹͼ**********/
void create_ALGraph(ALGraph *G)
{
	int i,j,k;
	int weight;
	ArcNode *p;
	printf("����������,����:");
	scanf("%d%d",&G->vexNum,&G->arcNum);
	getchar();
	for(i=0;i<G->vexNum;i++)
	{
		printf("����������Ϣ:");
		scanf("%c",&G->adjlist[i].vertex);
		getchar();
		G->adjlist[i].firstArc=NULL;
	}
	for(k=0;k<G->arcNum;k++)
	{
		printf("�������ͷλ�úͱ�βλ�ü�Ȩ��:");
		scanf("%d%d%d",&i,&j,&weight);
		getchar();
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j-1;
		p->weight=weight;
		p->next=G->adjlist[i-1].firstArc;
		G->adjlist[i-1].firstArc=p;
	}
}


/********����ͼ���ڽӾ���****************/
void create_MGraph(MGraph *G)
{
	int i,j,k,num;
	int weight;
	printf("����������,����:");
	scanf("%d%d",&G->vexNum,&G->arcNum);
	getchar();
	num=G->vexNum;
	for(i=0;i<G->vexNum;i++)
	{
	    printf("������������:");
	    scanf("%c",&G->vexs[i]);
	    getchar();
	}
	for(i=0;i<G->vexNum;i++)
		for(j=0;j<G->vexNum;j++)
			G->arcs[i][j]=-1;
	for(k=0;k<G->arcNum;k++)
	{
		printf("����������ڽӹ�ϵ(vi->vj)��Ȩֵ:");
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

/***********����ͼ���ڽӾ���*******/
void create_nMGraph(MGraph *NMG)
{
	int i,j,k;
	int weight;
	int num;
	printf("����������,����:");
	scanf("%d%d",&NMG->vexNum,&NMG->arcNum);
	getchar();
	num=NMG->vexNum;
	for(i=0;i<NMG->vexNum;i++)
	{
	    printf("������������:");
	    scanf("%c",&NMG->vexs[i]);
	    getchar();
	}
	for(i=0;i<NMG->vexNum;i++)
		for(j=0;j<NMG->vexNum;j++)
			NMG->arcs[i][j]=-1;
	for(k=0;k<NMG->arcNum;k++)
	{
		printf("����������ڽӹ�ϵ(vi->vj),��Ȩֵ:");
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

/***********��ӡ�ڽӾ���*********/
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

/************�ڽӾ����������ȱ���*********/
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

/*************�ڽӱ�洢ͼ��������ȱ���*********/
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


/**********�ڽӱ�洢ͼ�Ĺ�����ȱ���************/
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

/***********�ڽӾ���洢ͼ���ж��Ƿ��л�·*******/
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
		printf("\n�л�·!\n");
		return ;
	}
	else
	{
		printf("û�л�·!");
		return ;
	}
	for(j=0;j<G->vexNum;j++)
			if(G->arcs[v][j]&&!visited[j])
				DFS_Loop(G,j,visited);

}

/**************prim�㷨����С������*********/
void prim(MGraph G)
{
	int mincost,i,j,k;//mincost�������;�����洢��СȨֵ
	LowCost *lowcost=(LowCost*)malloc(sizeof(LowCost)*G.vexNum);
	//��̬��������
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
			for(j=0;j<G.vexNum;j++)//�Ƚ�Ȩֵ,���µ�ȨֵС,�����;
			{
				if(G.arcs[k][j]<lowcost[j].weight)
				{
					lowcost[j].weight=G.arcs[k][j];
					lowcost[j].vi=k;
				}

			}

	}


}
/***************lowcost�����±�ֱ�ӱ�ʾ��С�������ı���ָ����***************/
/**********************����ͬһ����****************************************/
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

 /************Kruskal�㷨����С������************/
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
	//�����0����
	int i,j,k,t,p,q,x[MAXSIZE][4];
	ZFC c[MAXSIZE];
	for(i=0;i<G.vexNum;i++)
	{
		c[i][0]=i+48;//�����±�ת�����ַ������ַ���c��
		c[i][1]=0;
	}
	for(i=0,k=0;i<G.vexNum;i++)
	{
		for(j=i;j<G.vexNum;j++)
			if(G.arcs[i][j]!=0 && G.arcs[i][j]!=MAXCOST)
			{
				x[k][0]=i;//��ǰ�����λ��
				x[k][1]=j;//����ָ���λ��
				x[k][2]=G.arcs[i][j];//�洢Ȩֵ
				x[k][3]=0;//����ѷ���
				k++;
			}

	}

	//Ȩֵ��С��������(ð������)
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
					p=find(c,G.vexNum,x[i][0]+48);//�ж϶���x[i][0]������ͨ����
					q=find(c,G.vexNum,x[i][1]+48);//�ж�ָ����������ͨ����
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
				printf("��С�������ı�Ϊ:\n");
				printf("����\t����\tȨֵ\n");
				for(i=0;i<G.arcNum;i++)
				{
					if(x[i][3]==1)
						printf("%s\t%s\t%s\n",G.vexs[x[i][0]],G.vexs[x[i][1]],G.vexs[x[i][2]]);

				}


}

/**********dijkstra �㷨�����·�� *********/
/***
    �����и�һά����dist[]��ʾ��Դ�㵽������·������:
	���Լ����Լ���Ϊ0,��ͨ��ΪȨֵ,����ͨ��Ϊ�����
	����һ����ά����path[][],path[i]��ʾԴ�㵽vi·�����������Ľ����±�
	����ͼ
	*********/
void dijkstra(MGraph G,int v)
{
	//GΪ��Ӿ���洢������ͼ
	//��������ͼ�Ĺ��캯��
	//�����ڽ�,��Ȩֵ,������ͨ��Ϊ�����MAXCOST
	int dist[MAXSIZE];
	int path[MAXSIZE][MAXSIZE];
	int i,j,k,m,n,min,flag;
	for(i=0;i<G.vexNum;j++)
		for(j=0;j<G.vexNum;j++)
			path[i][j]=-1;//��ʼ��·��
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
		//��dist�����·��
		for(j=0;j<G.vexNum;j++)
			if(dist[j]!=0 &&dist[j]<min)
			{
				k=j;
				min=dist[j];
			}
			//��ӡ���·��
			printf("��%d�����·������Ϊ%d--",++n,min);
			for(j=0;j<G.vexNum;j++)
				if(path[k][j]!=-1)
					printf("%d",G.vexs[path[k][j]]);
			printf("\b)\n");
			//����path,dist
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


/*********����������ÿһ�Զ���֮��ľ���**********/
typedef int PATHINT[MAXSIZE];
void floyd(MGraph G)
{
	int i,j,k,m,n,p;
	int d[MAXSIZE][MAXSIZE];
	PATHINT path[MAXSIZE][MAXSIZE];
	/*��ʼ��d*/
	for(i=0;i<G.vexNum;i++)
		for(j=0;j<G.vexNum;j++)
		{
			d[i][j]=G.arcs[i][j];
			for(k=0;k<G.vexNum;k++)
				path[i][j][k]=-1;
		}
		/****��ӡ���d�ĳ�ʼֵ************/
		printf("\ndist�ĳ�ֵ:\n");
		for(i=0;i<G.vexNum;i++)
		{
			for(j=0;j<G.vexNum;j++)
				printf("%6d",d[i][j]);
			printf("\n");
		}
		/***********��ʼ��path*********/
		for(i=0;i<G.vexNum;i++)
			for(j=0;j<G.vexNum;j++)
				if(d[i][j]!=MAXCOST&&d[i][j]!=0)
				{
					path[i][j][0]=i;
					path[i][j][1]=j;
				}
				printf("\npath�ĳ�ʼֵ:\n");
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
							printf("\ndist�ĵ�%d�ε���Ч��\n",k+1);
							for(m=0;m<G.vexNum;m++)
							{
								for(n=0;n<G.vexNum;n++)
									printf("%6d",d[m][n]);
								printf("\n");
							}
							printf("\npath�ĵ�%d�ĵ������\n",k+1);
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
