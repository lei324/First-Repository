/**************树的基本操作*************/
/*
树的基本操作实现，要求有菜单：
要求：结点中的数据类型为字符串，采用孩子兄弟链表存储
功能：1）用读边法创建一棵树的孩子兄弟链表存储；
2）查找给定值的结点，返回结点指针；
3）插入一个结点到指定位置；
4）删除以某结点为根的子树；
5）按照凹入表法输出；
6）输出根到叶子结点的路径

*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>
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
	CSTree p,s,r;
	SqQueueInit(&Q);*T=NULL;
	TreeType fa[50],ch[50];
	scanf("%s%s",fa,ch);
	while(strcmp(ch,"#"))
	{
		p=(CSTree)malloc(sizeof(TNode));
		strcpy(p->Tdata,ch);
		p->firstchild=NULL;
		p->nextsibling=NULL;
		SqEnQueue(&Q,p);
		if(!strcmp(fa,"#"))
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


/**********结点查找***********/

void pre_Search_Node(CSTree T,char kval[],CSTree *p)
{
	if(T)
	{
		if(strcmp(kval,T->Tdata)==0)
		{
			*p=T;
			return ;
		}
			pre_Search_Node(T->firstchild,kval,p);
			pre_Search_Node(T->nextsibling,kval,p);

	}

}

/*************树的结点插入************/
int insert_CSTree(CSTree *T,char fa[],char ch[])
{
	CSTree p=NULL;
	CSTree q,s;
	pre_Search_Node(*T,fa,&p);
	if(p)
	{
		s=(CSTree)malloc(sizeof(TNode));
		strcpy(s->Tdata,ch);
		s->firstchild=NULL;
		s->nextsibling=NULL;
		if(!p->firstchild)
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

//**************后序遍历释放结点空间***********/

void postDelTree(CSTree T)
{
	if(T)
	{
		postDelTree(T->firstchild);
		postDelTree(T->nextsibling);
		free(T);
	}

}

/*************子树的删除**********/

void delete_(CSTree p,CSTree f)
{
	//p是需要删除子树的根节点,f是存储p在存储结构的双亲,并用于重接他的左子树与右子树
	//也就是说:f在逻辑上是p的双亲
	if(f->firstchild==p)
	{
		f->firstchild=p->nextsibling;
		p->nextsibling=NULL;
		postDelTree(p);
	}
	if(f->nextsibling==p)
	{
		f->nextsibling=p->nextsibling;
		p->nextsibling=NULL;
		postDelTree(p);
	}


}
/************树的结点删除***********/
void delete_CSTree(CSTree *T,char fa[],char ch[])
{
	CSTree pfa=NULL,pch=NULL;
	if(strcmp(fa,"#")==0)//如果删除的是整棵树
	{
		postDelTree(*T);
		*T=NULL;
		return ;//
	}
	else
	{
		pre_Search_Node(*T,fa,&pfa);//找双亲,pfa保存双亲结点的地址
		pre_Search_Node(*T,ch,&pch);//找孩子,pch保存孩子结点的地址
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
			delete_(pch,pfa);

		}


	}


}
/*************凹入法表示树************/
void dispTree(CSTree T,int level)
{
	int len,i,k;
	if(T)
	{
		len=strlen(T->Tdata);
		for(i=0;i<level;i++)
			putchar(' ');
		printf("%s",T->Tdata);
		putchar('+');
		for(k=i+len;k<70;k++)
			putchar(' ');
		putchar('\n');
		dispTree(T->firstchild,level+4);
		dispTree(T->nextsibling,level);
	}

}

void AllTreePath(CSTree T,LinkStack *S)
{
	LinkStackType e[100];
	while(T)
	{
		LinkStackPush(S,T->Tdata );
		if(T->firstchild ==NULL)
			LinkStackPrint(S);
		else
			AllTreePath(T->firstchild ,S);
		LinkStackPop(S);
		T=T->nextsibling ;

	}

}


void menu()
{
	CSTree T,p=NULL;//p是结点查找到结点的位置
	int choice;
	int level=0;
	char fa[50],ch[50],fa_d[50],ch_d[50],kval[50];
	LinkStack S;LinkStackInit(&S);
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
		printf("请输入你需要执行的操作(0-5):");
		scanf("%d",&choice);
		switch(choice)
		{
		case 0:exit(0);
		case 1:printf("请依次输入双亲结点,叶子结点(并用空格隔开):\n");
			create_CSTree(&T);
			printf("创建成功!(若需浏览,请键入6\n");
			break;
		case 2:printf("请输入查找的结点内容:");
	        scanf("%s",kval);
	        getchar();
	        pre_Search_Node(T,kval,&p);
			if(p==NULL)
			{
				printf("所查内容不在其中!\n");
			}
			else if(p!=NULL)
			{
				 printf("所查%s内容存在!\n",p->Tdata );
				 p=NULL;
			}
			break;
		case 3:printf("请输入插入结点的双亲结点:");
	        scanf("%s",fa);
	        getchar();
	        printf("请输入插入结点内容:");
	        scanf("%s",ch);
	        getchar();
	        insert_CSTree(&T,fa,ch);
	        printf("插入完成!\n");
			break;
		case 4:printf("请输入删除结点内容:");
			scanf("%s",ch_d);
			getchar();
			printf("请输入删除结点双亲结点内容:");
			scanf("%s",fa_d);
			getchar();
			delete_CSTree(&T,fa_d,ch_d);
			printf("删除操作结束!\n");
			break;
		case 5:printf("凹入法表示如下:\n");
			dispTree(T,level);
			break;
		case 6:printf("遍历浏览如下:\n");
			pre_Order_CSTree(T);
			break;
		case 7:AllTreePath(T,&S);
			break;
		default :printf("输入操作错误!\n");
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
