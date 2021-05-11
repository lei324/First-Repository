#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>

# define STACKMAXSIZE 100
#define QUEUEMAXSIZE 100

typedef char DataType ;

typedef struct BiTNode
{
	DataType data;
	struct BiTNode *leftchild;
	struct BiTNode *rightchild;

}BiTNode,*BiTree;


typedef struct 
{
	BiTree ptr;
	int task;
}ElemType;

typedef struct Node
{
	ElemType *Sdata;
	int top;
	int stacksize;
}SqStack;


typedef BiTree  QElemType;

typedef struct
{
	int front;
	int rear;
	int queueSize;
	QElemType Qdata[QUEUEMAXSIZE];
}SqQueue;

/*****初始化***************/

int SqStackInit(SqStack *S)
{
	S->Sdata=(ElemType*)malloc(STACKMAXSIZE*sizeof(ElemType));
	if(S->Sdata==NULL)
	{
		return 0;
	}

	S->top=-1;
	S->stacksize=STACKMAXSIZE;
	return 1;
}

/*************判断栈空********/
int SqStackEmpty(SqStack S)
{
	if(S.top==-1)
		return 1;
	else
		return 0;
}
/**************取栈长********/

int SqStackLength(SqStack S)
{
	return S.top+1;
}

/********取栈顶********/
void SqStackGetTop(SqStack S,ElemType *e)
{
	if(S.top==-1)
	{
		return ;
	}
	*e=S.Sdata[S.top];
}


/********入栈*************/

int SqStackPush(SqStack *S,ElemType e)
{
	if(S->top+1==S->stacksize)
	{
		return 0;
	}
	S->top++;
	S->Sdata[S->top]=e;
	return 1;

}

/*********出栈**************/
int  SqStackPop(SqStack *S,ElemType *e)
{
	if(S->top==-1)
	{
		return 0;
	}
	*e=S->Sdata[S->top];
	S->top--;
	return 1;

}




int SqQueueInit(SqQueue *Q)
{
	Q->front=Q->rear=0;
	Q->queueSize=QUEUEMAXSIZE;
	return 1;
}

int SqQueueEmpty(SqQueue Q)
{
	if(Q.front==Q.rear)
		return 1;
	else
		return 0;
}


int SqQueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+Q.queueSize)%Q.queueSize;
}


int EnQueue(SqQueue *Q,QElemType e)
{
	if((Q->rear+1)%Q->queueSize==Q->front)
		return 0;
	Q->Qdata[Q->rear]=e;
	Q->rear=(Q->rear+1)%Q->queueSize;
	return 1;
}


int SqDeQueue(SqQueue *Q,QElemType *e)
{
	if(Q->rear==Q->front)
		return 0;
	*e=Q->Qdata[Q->front];
	Q->front=(Q->front+1)%Q->queueSize;
	return 1;
}


int SqQueueGetHead(SqQueue Q,QElemType *e)
{
	if(Q.rear==Q.front)
		return 0;
	*e=Q.Qdata[Q.front];
	return 1;
}


/*************递归先序遍历************/

void preorder(BiTree T)
{
	if(T)
	{
		printf("%c ",T->data);
		preorder(T->leftchild);
		preorder(T->rightchild);
	}
	

}

/********递归后序遍历*******/

void postorder(BiTree T)
{
	if(T)
	{
		postorder(T->leftchild);
		postorder(T->rightchild);
		printf("%c ",T->data);
	}
}
/**************递归中序遍历************/

void inorder(BiTree T)
{
	if(T)
	{
		inorder(T->leftchild);
		printf("%c ",T->data);
		inorder(T->rightchild);
	}

}


/*********任务分析法中序遍历*********/

void in_Order_iter(BiTree T)
{
	SqStack S;
	BiTree p;
	SqStackInit(&S);
	ElemType e;
	e.ptr=T;e.task=1;
	if(T)
	{
		SqStackPush(&S,e);
	}
	while(!SqStackEmpty(S))
	{
		SqStackPop(&S,&e);
		if(e.task==0)
		{
			printf("%c ",e.ptr->data);
		}
		else
		{
			p=e.ptr;
			e.ptr=p->rightchild;
			//此处e.task==1仍然成立,故不必再操作
			if(e.ptr)
			{
				SqStackPush(&S,e);
			}

			e.ptr=p;
			e.task=0;
			SqStackPush(&S,e);//改变根节点任务后,进栈执行访问操作

			e.ptr=p->leftchild;
			e.task=1;
			if(e.ptr)
			{
				SqStackPush(&S,e);
			}
		}


	}



}

void post_Order_iter(BiTree T)
{
	SqStack S;
	SqStackInit(&S);
	BiTree p;
	ElemType e;
	e.ptr=T;
	e.task=1;
	if(e.ptr)
	{
		SqStackPush(&S,e);
	}
	while(!SqStackEmpty(S))
	{
		SqStackPop(&S,&e);
		if(e.task==0)
			printf("%c ",e.ptr->data);
		else
		{
			p=e.ptr;

			e.task=0;
			SqStackPush(&S,e);

			e.ptr=p->rightchild;
			e.task=1;
			if(e.ptr)
			SqStackPush(&S,e);


			e.ptr=p->leftchild;
			e.task=1;
			if(e.ptr)
				SqStackPush(&S,e);
		}

	}

}


/*************任务分析前序遍历*************/
void pre_Order_iter(BiTree T)
{
	SqStack S;
	SqStackInit(&S);
	BiTree p;
	ElemType e;
	e.ptr=T;
	e.task=1;
	if(e.ptr)
	{
		SqStackPush(&S,e);
	}
	while(!SqStackEmpty(S))
	{
		SqStackPop(&S,&e);
		if(e.task==0)
			printf("%c ",e.ptr->data);
		else
		{
			p=e.ptr;

			e.ptr=p->rightchild;
			e.task=1;
			if(e.ptr)
			SqStackPush(&S,e);

			e.ptr=p->leftchild;
			e.task=1;
			if(e.ptr)
			SqStackPush(&S,e);

			e.ptr=p;
			e.task=0;
			SqStackPush(&S,e);

		}

	}
}


/***********层次遍历*************/

void layer(BiTree bt)
{
	SqQueue Q;
	BiTree q;
	SqQueueInit(&Q);
	if(bt)
	{
		EnQueue(&Q,bt);
	}
	while(!SqQueueEmpty(Q))
	{
		SqDeQueue(&Q,&q);
		printf("%c ",q->data);
		if(q->leftchild)
			EnQueue(&Q,q->leftchild);
		if(q->rightchild)
			EnQueue(&Q,q->rightchild);
	}


}


/**************先序遍历创建二叉链表*******/

void create_pre_tree(BiTree *T)
{
	char ch;
	printf("请输入结点:");
	scanf("%c",&ch);
	getchar();
	if(ch=='#')
		*T=NULL;
	else
	{
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=ch;
		create_pre_tree(&(*T)->leftchild);
		create_pre_tree(&(*T)->rightchild);
	}

}

/************非递归边读边创建二叉树**************/

void Create_BiTree(BiTree *T)
{
	BiTree p1,s,r;
	char fa,ch;
	int lrflag;
	SqQueue Q;
	SqQueueInit(&Q);
	*T=NULL;
	scanf("%c%c%d",&fa,&ch,&lrflag);
	getchar();
	while(ch!='#')
	{
		p1=(BiTree)malloc(sizeof(BiTNode));
		p1->data=ch;
		p1->leftchild=p1->rightchild=NULL;
		EnQueue(&Q,p1);
		if(fa=='#')
			*T=p1;
		else
		{
			SqQueueGetHead(Q,&s);
			while(s->data!=fa)
			{
				SqDeQueue(&Q,&r);
				SqQueueGetHead(Q,&s);
			}
			if(lrflag==0)
				s->leftchild=p1;
			else
				s->rightchild=p1;
		}
	    scanf("%c%c%d",&fa,&ch,&lrflag);
		getchar();
	}


}

/***********求数的深度**********/
int  depth(BiTree T)
{
	int depl=0,depr=0;
	if(T==NULL)
	{
		return 0;
	}
	else
	{
		depl=depth(T->leftchild);
		depr=depth(T->rightchild);
		if(depl>depr)
			return depl+1;
		else
			return (depr+1);
	}


}
/**********中序遍历求叶子结点**********/
void CountLeaf_in(BiTree T,int *count)
{ 
	if(T==NULL)
		return ;
	else
	{
	CountLeaf_in(T->leftchild,count);
	if(T->leftchild==NULL&&T->rightchild==NULL)
		(*count)++;
	CountLeaf_in(T->rightchild,count);
	}
}
/**************前序遍历求叶子结点***************/
void CountLeaf_pre(BiTree T,int *count)
{
	if(T==NULL)
		return ;
	else
	{
		if(T->leftchild==NULL&&T->rightchild==NULL)
		(*count)++;
		CountLeaf_pre(T->leftchild,count);
	CountLeaf_pre(T->rightchild,count);
	}

}
/*************后续遍历求叶子数************/
void CountLeaf_post(BiTree T,int *count)
{
	if(T==NULL)
		return ;
	else
	{
		
		CountLeaf_post(T->leftchild,count);
	CountLeaf_post(T->rightchild,count);
	if(T->leftchild==NULL&&T->rightchild==NULL)
		(*count)++;
	}

}
/*************二叉树性质求叶子结点数*******************/
int CountLeaf_2(BiTree T)
{
	if(!T)
		return 0;
	if(!T->leftchild&&!T->rightchild)
		return 1;
	else
	{
		int m=CountLeaf_2(T->leftchild);
		int n=CountLeaf_2(T->rightchild);
		return m+n;
	}

}


/*********求结点数*********/
int CountLeaf (BiTree T)
{
   if (!T) return 0;
   if (!T->leftchild&&!T->rightchild) 
          return 1;
   else
   {
      int m = CountLeaf(T->leftchild);  
       int n = CountLeaf(T->rightchild); 
	   return m+n+1;
   } 
} 
/**********求二叉树层次***/

void LeafDepth(BiTree T , int level)
{ 
   if ( T ) {
        printf("%c %d\t", T->data,level);
        LeafDepth( T->leftchild, level+1);
        LeafDepth( T->rightchild, level+1);
   } 
}


/*************凹入法显示二叉树**************/
void dispBitree(BiTree T,int level,char c)
{
	int i,k;
	if(T)
	{
		for(i=1;i<level;i++)
			putchar(' ');
		printf("%c(%c)+",T->data,c);
		for(k=i+4;k<20;k++)
			putchar('-');
		putchar('\n');
		dispBitree(T->leftchild,level+2,'L');
		dispBitree(T->rightchild,level+2,'R');
	}

}

int Search(char ino[],char x)
{
	int i=0;
	while(ino[i]!='\0')
	{
		if(ino[i]!=x)
		{
			i++;
		}
		else
		return i;
	}
	return -1;

	
}
/**************求二叉树宽度*******************/
int width(BiTree T)
{
	int width=0;
	int len=0;
	int i;
	SqQueue Q;
	BiTree p,s;
	SqQueueInit(&Q);
	if(!T)
	{
		return 0;
	}
	EnQueue(&Q,T);
	while(!SqQueueEmpty(Q))
	{
		len=SqQueueLength(Q);
		width=len>width?len:width;
		for(i=0;i<len;i++)
		{
			SqQueueGetHead(Q,&p);
			SqDeQueue(&Q,&s);
			if(p->leftchild)
				EnQueue(&Q,p->leftchild);
			if(p->rightchild)
				EnQueue(&Q,p->rightchild);
		}

	}
	return width;

}

void menu()
{
	int chice;
	BiTree T;
	int count_in=0,count_pre=0,count_post=0;
	int level=1;//节点层次
	printf("|******************************那些年我们曾写过的bc二叉树*************************|\n");
	printf("|*********************1.              创建二叉树        *************************|\n");
	printf("|*********************2.            任务分析法遍历      *************************|\n");
	printf("|*********************3.              递归遍历树        *************************|\n");
	printf("|*********************4.              层次遍历树        *************************|\n");
	printf("|*********************5.             求二叉树结点数     *************************|\n");
	printf("|*********************6.             求叶子结点数       *************************|\n");
	printf("|*********************7.             求二叉树深度       *************************|\n");
	printf("|*********************8.             二叉树 层次        *************************|\n");
	printf("|*********************9.             凹入法表示树       *************************|\n");
	printf("|*********************10.            二叉树宽度         *************************|\n");
	printf("|*********************0.             退出系统           *************************|\n");
    while(1)
	{
		printf("请输入你的选择(0-9):");
		scanf("%d",&chice);
		getchar();
		switch(chice)
		{
		case 0:exit(0);break;
		case 1:create_pre_tree(&T);
			printf("先序遍历创建二叉树完成!\n");
			break;
		case 2:printf("任务分析法先序遍历:\n");
			   pre_Order_iter(T);
			   printf("\n任务分析中序遍历:\n");
			   in_Order_iter(T);
			   printf("\n任务分析后序遍历:\n");
			   post_Order_iter(T);
			   printf("\n");
			   break;
		case 3: printf("\n先序递归遍历:\n");
			   preorder(T);
			   printf("\n中序递归遍历:\n");
			   inorder(T);
			   printf("\n中序递归遍历:\n");
			   postorder(T);
			   printf("\n");
			   break;
		case 4: printf("\n层次遍历\n");
			    layer(T);
				printf("\n");
				break;
		case 5:printf("结点数为:%d\n",CountLeaf(T));
			   break;
	
		case 6:
			   CountLeaf_in(T,&count_in);
	           printf("中序遍历求叶子数为:%d\n",count_in);
	           CountLeaf_post(T,&count_post);
	           printf("后续遍历求叶子结点数:%d\n",count_post);
	           CountLeaf_pre(T,&count_pre);
	           printf("先序遍历求叶子结点数:%d\n",count_pre);
	           printf("二叉树性质求叶子结点数%d\n",CountLeaf_2(T));
			   break;
		case 7: int dep;
	            dep=depth(T);
	            printf("树的深度为:%d\n",dep);
				break;
		case 8:LeafDepth(T,level);
	           printf("\n");
			   break;
		case 9:dispBitree(T,level,'T');
			   break;
		case 10:printf("二叉树的宽度为:%d\n",width(T));
			break;
		default :printf("输入选择错误!\n");
	           
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
