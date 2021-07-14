#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>

# define MAXCOST 10000 //��ʾ�����
# define MAX   1000  //��ʾ���䲻��ͨ
# define MAXSIZE  100 //�������
# define VNUM 100//
#define QUEUEMAX 100

typedef char VertexType;//�����������

//ͼ���ڽӾ���ṹ��
typedef struct 
{
	VertexType vexs[VNUM];//�������
	int arcs[VNUM][VNUM];//�ڽӹ�ϵ
	int vexNum;//�����
	int arcNum;//����
}MGraph;

/**************�ڽӱ����ݽṹ*******/

//������

typedef struct ArcNode
{
	int adjvex;//����ָ���λ��
	struct ArcNode *next;
	int weight;//Ȩֵ
}ArecNode;

//��ͷ���
typedef struct VertexNode
{
	VertexType vertex;//�������
	int in;//���
	int out;
	ArcNode *firstArc;//ͷ���
}VertexNode;

//�ڽӱ�洢ͼ
typedef struct ALGraph
{
	VertexNode adjlist[MAXSIZE];
	int vexNum;
	int arcNum;
}ALGraph;

typedef int QueueType;
typedef struct
{
	QueueType Qdata[QUEUEMAX];
	int rear;
	int front;
	int queuesize;

}SqQueue;

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

void create_Graph(MGraph *MG,ALGraph *ALG)
{
	int i,j,k;
	int arcnum,vexnum,weight;
	VertexType x;
	int count;
	ArcNode *p;
	printf("����������,����:");
	scanf("%d%d",&vexnum,&arcnum);
	getchar();
	MG->vexNum=ALG->vexNum=vexnum;
	MG->arcNum=ALG->arcNum=arcnum;
	for(i=0;i<vexnum;i++)
	{
		printf("����������Ϣ:");
		scanf("%c",&x);
		getchar();
		ALG->adjlist[i].vertex=x;
		ALG->adjlist[i].firstArc=NULL;
		MG->vexs[i]=x;
	}
	for(i=0;i<MG->vexNum;i++)
		for(j=0;j<MG->vexNum;j++)
			MG->arcs[i][j]=-1;
	
	for(k=0;k<arcnum;k++)
	{
		printf("�������ͷλ�úͱ�βλ�ü�Ȩ��:");
		scanf("%d%d%d",&i,&j,&weight);
		getchar();
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j-1;
		p->weight=weight;
		p->next=ALG->adjlist[i-1].firstArc;
		ALG->adjlist[i-1].firstArc=p;
		MG->arcs[i-1][j-1]=weight;
		//MG->arcs[j-1][i-1]=weight;
	}
	for(k=0;k<vexnum;k++)
	{
		for(j=0;j<vexnum;j++)
		{
			if(k==j)
				MG->arcs[k][j]=0;
			if(MG->arcs[k][j]==-1)
				MG->arcs[k][j]=MAX;
		}
	}

}

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
/****************�����************/
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
/*****************�ڽӱ�洢ͼ��������ȱ���*************/
void df_Traver_ALG(ALGraph G,int v,int visited[])
{
	LinkStack S;
	LinkStackInit(&S);
	ArcNode *p;
	int k;
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

	putchar('\n');
}

void DFS_1(ALGraph G,int visited[])
{
	int i;
	for(i=0;i<G.vexNum;i++)
		if(visited[i]==0)
			df_Traver_ALG(G,i,visited);
	printf("--------------------\n");
}



/**********�ڽӱ�洢ͼ�Ĺ�����ȱ���************/
//���ȱ�֤��ͨͼ
void bf_Traver_ALGraph(ALGraph G,int v0)
{
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
			p=p->next;
		}

	}

	printf("\n");
}

/************�������ĶȺ��ڽӱ�************/
void digree_side(MGraph MG,int v0)
{
	int i;
	int in_degree=0,out_degree=0;
	for(i=0;i<MG.vexNum;i++)
	{
		if(MG.arcs[v0][i]!=0 &&MG.arcs[v0][i]!=MAX)
		{
			out_degree++;
			printf("%c---%d--->%c\n",MG.vexs[v0],MG.arcs[v0][i],MG.vexs[i]);
		}
		if(MG.arcs[i][v0]!=0 && MG.arcs[i][v0]!=MAX)
		{
			in_degree++;
			printf("%c---%d--->%c\n",MG.vexs[i],MG.arcs[i][v0],MG.vexs[v0]);
		}

	}

}

/************������б�(���Ƿ���ͨͼ)********/
void show(MGraph MG)
{
	int i,j;
	int count=0;
	for(i=0;i<MG.vexNum;i++)
	{
		for(j=0;j<MG.vexNum;j++)
		{
			if(MG.arcs[i][j]!=0&&MG.arcs[i][j]!=MAX)
			{
				count++;
				printf("%c---->%c\n",MG.vexs[i],MG.vexs[j]);
			}

		}

	}
	printf("����%d����\n",count);

}

/**************����������ļ�·��******/

void Hamilton(MGraph MG,int v0,int v1,int path[],int *n,int visited[],int found)
{
	visited[v0]=1;
	path[*n]=v0;
	(*n)++;
	if(v0==v1)
	{
		for(int i=0;i<(*n);i++)
			printf("%c ",MG.vexs[path[i]]);
		found=1;
		return ;
	}
	for(int i=0;i<MG.vexNum;i++)
	{
		if(MG.arcs[v0][i]&& !visited[i] &&!found)
		{
			Hamilton(MG,i,v1,path,n,visited,found);
		}

	}
	visited[v0]=0;
	(*n)--;
}
/************ͼ�����޻�************/
void DFS_Loop(MGraph MG,int v0,int visited[])
{
	visited[v0]=1;
	int v1=0,d1=0;
	for(int i=0;i<MG.vexNum;i++)
	{
		if(MG.arcs[v0][i])
		{
			v1++;
			if(visited[i])
				d1++;
		}

	}
	if(v1==d1&&d1!=1)
	{
		printf("�л�·!\n");
		return ;
	}
	for(int i=0;i<MG.vexNum;i++)
	{
		if(visited[i]==0&&MG.arcs[v0][i])
			DFS_Loop(MG,i,visited);
	}


}


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
	for(i=1;i<G.vexNum;i++)
	{
		mincost=MAXCOST;
		for(j=0;j<G.vexNum;j++)
			if(lowcost[j].weight<mincost&&lowcost[j].weight!=0)
			{
				mincost=lowcost[j].weight;
				k=j;
			}
			printf("%c---%d--->%c\n",G.vexs[lowcost[k].vi],mincost,G.vexs[k]);
			lowcost[k].weight=0;
			for(j=0;j<G.vexNum;j++)
				if(G.arcs[k][j]<lowcost[j].weight)
				{
					lowcost[j].weight=G.arcs[k][j];
					lowcost[j].vi=k;
				}


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
	for(i=0;i<G.vexNum;i++)
		for(j=0;j<G.vexNum;j++)
			path[i][j]=-1;//��ʼ��·��
	for(i=0;i<G.vexNum;i++)
	{
		dist[i]=G.arcs[v][i];
	       if(dist[i]!=0 && dist[i]!=MAX)
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
				
					printf("%c ",G.vexs[path[k][j]]);
			printf("\b)\n");
				
			//����path,dist
			for(j=0;j<G.vexNum;j++)
				if(j!=k && dist[j]!=0 && dist[j]!=MAX)
					if(dist[k]+G.arcs[k][j]<dist[j])
					{
						dist[j]=dist[k]+G.arcs[k][j];
						for(m=0;m<G.vexNum;m++)
							path[j][m]=path[k][m];
						for(m=0;m<G.vexNum&&path[j][m]!=-1;m++)
						path[j][m]=j;
					}
					dist[k]=0;
					flag=0;
					for(j=0;j<G.vexNum;j++)
						if(dist[j]!=0 && dist[j]<MAXCOST)
							flag=1;
	}

}

/***********���������㷨�����·��********/
typedef int PATHINT[MAXSIZE];
void floyd(MGraph G)
{
	int i,j,k,m,n,p;
	int d[MAXSIZE][MAXSIZE];
	PATHINT path[MAXSIZE][MAXSIZE];
	for(i=0;i<G.vexNum;i++)
		for(j=0;j<G.vexNum;j++)
		{
			d[i][j]=G.arcs[i][j];
			for(k=0;k<G.vexNum;k++)
				path[i][j][k]=-1;
		}
		printf("\n dist�ĳ�ֵ\n");
		for(i=0;i<G.vexNum;i++)
		{
			for(j=0;j<G.vexNum;j++)
				printf("%6d",d[i][j]);
			putchar('\n');
		}
		for(i=0;i<G.vexNum;i++)
			for(j=0;j<G.vexNum;j++)
				if(d[i][j]!=MAX&& d[i][j]!=0)
				{
					path[i][j][0]=i;
					path[i][j][0]=j;
				}
				printf("\n path�ĳ�ֵ\n");
				for(i=0;i<G.vexNum;i++)
				{
					for(j=0;j<G.vexNum;j++)
					{
						for(k=0;path[i][j][k]!=-1;k++)
							printf("%d ",path[i][j][k]);
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
								for(m=0;m<G.vexNum&&path[i][k][m]!=-1;m++)
									path[i][j][m]=path[i][k][m];
								for(n=1;n<G.vexNum;m++,n++)
									path[i][j][m]=path[k][j][n];
							}
							printf("\n dist�ĵ�%d�ε������\n",k+1);
							for(m=0;m<G.vexNum;m++)
							{
								for(n=0;n<G.vexNum;n++)
									printf("%6d",d[m][n]);
								printf("\n");
							}
							printf("\n path�ĵ�%d�ε��������\n",k+1);
							for(i=0;i<G.vexNum;i++)
							{
								for(j=0;j<G.vexNum;j++)
								{
									for(m=0;path[i][j][m]!=-1;m++)
										printf("%d,",path[i][j][m]);
									if(m!=0)
										printf("\b");
									printf("\t\t");
								}
								printf("\n");
							}


				}


}


void menu()
{
	int choice;
	MGraph MG;
	ALGraph ALG;
	int n=0,found=0;
	int visited[MAXSIZE]={0},path[MAXSIZE]={0};
	int a[MAXSIZE]={0},b[MAXSIZE]={0},c[MAXSIZE]={0};
	int v,v0,v1;
	printf("                                 ��ͼɶ                                 \n");
	printf("                              1.����ͼ(�����ڽӾ�����ڽӱ�)              \n");
	printf("                              2.��ӡ��Ӿ���                             \n");
	printf("                              3.���ֱ��������ͨ��                        \n");
	printf("                              4.��ȱ���                                 \n");
	printf("                              5.��ȱ���                                 \n");
	printf("                              6.��ͼ�����б�                             \n");
	printf("                              7.��·��                                 \n");
	printf("                              8.���·��                                 \n");
	printf("                              9.����С������                            \n");
	printf("                              0.�˳�����                                 \n");
	while(1)
	{
		printf("���������ѡ��:");
		scanf("%d",&choice);
		getchar();
		switch(choice)
		{
		case 0:exit(0);
			break;
		case 1:create_Graph(&MG,&ALG);
			find_in_degree(&ALG);
			find_out_degree(&ALG);
			printf("�������!\n");
			break;
		case 2:print_MG(MG);
			break;
		case 3:printf("������һ�����λ��:");
			scanf("%d",&v0);
			getchar();
			df_Traver_ALG(ALG,v0,visited);
			printf("---------------------\n");
			DFS_1(ALG,visited);
			break;
		case 4:printf("������һ�����:");
			scanf("%d",&v0);
			getchar();
			printf("��ȱ�������:\n");
			df_Traver_ALG(ALG,v0,a);
			printf("\n");
			break;
		case 5:printf("������һ�����:");
			scanf("%d",&v0);
			getchar();
			printf("��ȱ�������:\n");
			bf_Traver_ALGraph(ALG,v0);
			break;
		case 6:show(MG);
			break;
		case 7:printf("�������ʼ����ĩβ���:");
			scanf("%d%d",&v0,&v1);
			getchar();
			Hamilton(MG,v0,v1,path,&n,c,found);
			putchar('\n');
			break;
		case 8:printf("��������λ��:");
			scanf("%d",&v);
			getchar();
			dijkstra(MG,v);
			break;
		case 9:prim_1(MG);
			break;
		default :printf("�������!");
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
