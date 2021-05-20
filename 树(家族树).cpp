
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define TREEMAX 50
#define QUEUEMAX 50
#define STACKMAX 50

typedef char TreeType;
typedef char LinkStackType;

typedef struct TNode
{
	TreeType Tdata[TREEMAX];
	struct TNode *firstchild;
	struct TNode *nextsibling;
}TNode,*CSTree;

typedef CSTree QueueType;
typedef struct
{
	QueueType Qdata[QUEUEMAX];
	int rear;
	int front;
	int queuesize;

}SqQueue;
typedef struct SNode
{
	LinkStackType Sdata[STACKMAX];
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

void LinkStackGetTop(LinkStack S,LinkStackType e[])
{
	if(S==NULL)
		return ;
	e=S->Sdata ;
}

void LinkStackPush(LinkStack *S,LinkStackType e[])
{
	LinkStack p=(LinkStack)malloc(sizeof(SNode));
	strcpy(p->Sdata,e);
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

void SqDeQueue(SqQueue *Q)
{
	if(Q->front==Q->rear)
		return;
	Q->front=(Q->front+1)%Q->queuesize;
}

void create_CSTree(CSTree *T)
{
	SqQueue Q;
	SqQueueInit(&Q);
	CSTree p=NULL,s=NULL,r=NULL;
	*T=NULL;
	TreeType fa[TREEMAX],ch[TREEMAX];
	scanf("%s%s",fa,ch);
	getchar();
	while(strcmp(ch,"#"))
	{
		p=(CSTree)malloc(sizeof(TNode));
		strcpy(p->Tdata,ch);
		p->firstchild=p->nextsibling=NULL;
		SqEnQueue(&Q,p);
		if(strcmp(fa,"#")==0)
		{
			*T=p;
		}
		else
		{
			s=SqQueueGetTop(Q);
			while(strcmp(s->Tdata,fa))
			{
				SqDeQueue(&Q);
				s=SqQueueGetTop(Q);
			}
			if(s->firstchild==NULL)
			{
				s->firstchild=p;
				r=p;
			}
			else
			{
				r->nextsibling=p;
				r=p;
			}
		} 
		scanf("%s%s",fa,ch);
		getchar();
	}
}

void pre_Order_CSTree(CSTree T)
{
	if(T)
	{
		printf("%s\n",T->Tdata);
		pre_Order_CSTree(T->firstchild);
		pre_Order_CSTree(T->nextsibling);
	}
}

void dispTree(CSTree T,int level)
{
	int len,i,k;
	if(T)
	{
		len=strlen(T->Tdata);
		for(i=0;i<level;i++)
		putchar(' ');
		printf("%s+",T->Tdata);
		for(k=i+len;k<TREEMAX;k++)
		putchar(' ');
		putchar('\n');
		dispTree(T->firstchild,level+4);
		dispTree(T->nextsibling,level);
	}
}

void AllTreePath(CSTree T,LinkStack *S)
{
	while(T)
	{
		LinkStackPush(S,T->Tdata);
		if(T->firstchild==NULL)
		LinkStackPrint(S);
		else
		AllTreePath(T->firstchild,S);
		LinkStackPop(S);
		T=T->nextsibling;
	}
} 

void Print_Node_Path(CSTree T,char ch[],LinkStack *S,int *flag)
{
	if(T&&flag)
	{
		LinkStackPush(S,T->Tdata);
		if(strcmp(T->Tdata,ch)==0)
		{
			LinkStackPrint(S);
			*flag=0;
			return ;
		}
		else
			Print_Node_Path(T->firstchild,ch,S,flag);
			LinkStackPop(S);
			Print_Node_Path(T->nextsibling,ch,S,flag);
	}
}

void search_Node(CSTree T,char ch[],CSTree *p)
{
	if(T)
	{
		if(strcmp(T->Tdata,ch)==0)
		{
			*p=T;
			return ;
		}
		search_Node(T->firstchild,ch,p);
		search_Node(T->nextsibling,ch,p);
	}

}

int insert_Node(CSTree *T,char fa[],char ch[])
{
	CSTree p=NULL,s=NULL,q=NULL;
	search_Node(*T,fa,&p);
	if(p)
	{
		s=(CSTree)malloc(sizeof(TNode));
		strcpy(s->Tdata,ch);
		s->firstchild=s->nextsibling=NULL;
		if(p->firstchild==NULL)
		{
			p->firstchild=s;
		}
		else
		{
			q=p->firstchild;
			while(q->nextsibling)
			{
				q=q->nextsibling;
			}
			q->nextsibling=s;
		}
		return 1; 
	}
	return 0;
}

void free_Tree(CSTree T)
{
	if(T)
	{
		free_Tree(T->firstchild);
		free_Tree(T->nextsibling);
		free(T);
	}
}

void delete_Tree(CSTree f,CSTree p)
{
	if(f->firstchild==p)
	{
		f->firstchild=p->nextsibling;
		p->nextsibling=NULL;
		free_Tree(p);
	}
	if(f->nextsibling==p)
	{
		f->nextsibling=p->nextsibling;
		p->nextsibling=NULL;
		free_Tree(p);
	}
}

void delete_CSTree(CSTree *T,char fa[],char ch[])
{
	CSTree pfa=NULL,pch=NULL;
	if(strcmp(fa,"#")==0)
	{
		free_Tree(*T);
		*T=NULL;
		return ;
	}
	else
	{
		search_Node(*T,fa,&pfa);//找双亲,pfa保存双亲结点的地址
		search_Node(*T,ch,&pch);//找孩子,pch保存孩子结点的地址
		if(pfa==NULL||pch==NULL)
		{
			printf("数据有误!未找到删除结点\n");
			return ;

		}
		else
     {
		if(pfa->firstchild!=pch)
		{
			pfa=pch->firstchild;
			while(pfa)
			{
				if(pfa->nextsibling==pch)
				break;
				pfa=pfa->nextsibling;
			}
		}
		delete_Tree(pfa,pch);
      }
	}
}

void menu()
{
	CSTree T=NULL,p=NULL;
	int chice,level=1,flag=0;
	char fa[TREEMAX],ch[TREEMAX];
	LinkStack S;
	LinkStackInit(&S);
	printf("|                             树的基本操作                                |\n");
	printf("|                           1.创建树                                     |\n");
	printf("|                           2.查找结点是否存在                            |\n");
	printf("|                           3.插入新节点                                 |\n");
	printf("|                           4.删除结点                                   |\n");
	printf("|                           5.凹入法表示                                 |\n");
	printf("|                           6.遍历浏览                                   |\n");
	printf("|                           7.结点路径                                   |\n");
	printf("|                           0. 退出                                     |\n");
	while(1)
	{
		printf("请输入你的选择(0-7):");
		scanf("%d",&chice);
		getchar();
		switch(chice)
		{
			case 0:exit(0);
			break;
			case 1:printf("请按照双亲结点,孩子结点(中间空格隔开:\n");
			create_CSTree(&T);
			break;
			case 2:printf("请输入将查找的结点:");
			scanf("%s",ch);
			getchar();
			search_Node(T,ch,&p);
			if(p==NULL)
			{
				printf("该成员不存在!\n");
			} 
			if(p!=NULL)
			{
				flag=1;
				printf("该结点存在,其祖先路径如下:");
				Print_Node_Path(T,ch,&S,&flag);
				LinkStackInit(&S); 
			}
			break;
			case 3:printf("请输入新结点:");
			scanf("%s",ch);
			getchar();
			printf("请输入插入结点双亲:");
			scanf("%s",fa);
			getchar();
			insert_Node(&T,fa,ch);
			printf("插入成功!可键入5,6,7查看!\n");
			break;
			case 4:printf("请输入删除结点:");
			scanf("%s",ch);
			getchar();
			printf("请输入该结点双亲结点:");
			scanf("%s",fa);
			getchar();
			delete_CSTree(&T,fa,ch);
			printf("删除成功!,可键入5,6,7查看!\n");
			break;
			case 5:dispTree(T,level);
			break;
			case 6:pre_Order_CSTree(T);
			break;
			case 7:AllTreePath(T,&S);
			break;
			default:printf("键入选项错误!\n"); 
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