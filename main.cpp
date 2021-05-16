/**************���Ļ�������*************/
/*
���Ļ�������ʵ�֣�Ҫ���в˵���
Ҫ�󣺽���е���������Ϊ�ַ��������ú����ֵ�����洢
���ܣ�1���ö��߷�����һ�����ĺ����ֵ�����洢��
2�����Ҹ���ֵ�Ľ�㣬���ؽ��ָ�룻
3������һ����㵽ָ��λ�ã�
4��ɾ����ĳ���Ϊ����������
5�����հ���������
6���������Ҷ�ӽ���·��

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


/**********������***********/

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

/*************���Ľ�����************/
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

//**************��������ͷŽ��ռ�***********/

void postDelTree(CSTree T)
{
	if(T)
	{
		postDelTree(T->firstchild);
		postDelTree(T->nextsibling);
		free(T);
	}

}

/*************������ɾ��**********/

void delete_(CSTree p,CSTree f)
{
	//p����Ҫɾ�������ĸ��ڵ�,f�Ǵ洢p�ڴ洢�ṹ��˫��,�������ؽ�������������������
	//Ҳ����˵:f���߼�����p��˫��
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
/************���Ľ��ɾ��***********/
void delete_CSTree(CSTree *T,char fa[],char ch[])
{
	CSTree pfa=NULL,pch=NULL;
	if(strcmp(fa,"#")==0)//���ɾ������������
	{
		postDelTree(*T);
		*T=NULL;
		return ;//
	}
	else
	{
		pre_Search_Node(*T,fa,&pfa);//��˫��,pfa����˫�׽��ĵ�ַ
		pre_Search_Node(*T,ch,&pch);//�Һ���,pch���溢�ӽ��ĵ�ַ
		if(pfa==NULL||pch==NULL)
		{
			printf("��������!δ�ҵ�ɾ�����\n");
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
/*************���뷨��ʾ��************/
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
	CSTree T,p=NULL;//p�ǽ����ҵ�����λ��
	int choice;
	int level=0;
	char fa[50],ch[50],fa_d[50],ch_d[50],kval[50];
	LinkStack S;LinkStackInit(&S);
	printf("|                             ���Ļ�������                                |\n");
	printf("|                           1.������                                     |\n");
	printf("|                           2.���ҽ���Ƿ����                            |\n");
	printf("|                           3.�����½ڵ�                                 |\n");
	printf("|                           4.ɾ�����                                   |\n");
	printf("|                           5.���뷨��ʾ                                 |\n");
	printf("|                           6.�������                                   |\n");
	printf("|                           7.���·��                                   |\n");
	printf("|                           0. �˳�                                     |\n");
	while(1)
	{
		printf("����������Ҫִ�еĲ���(0-5):");
		scanf("%d",&choice);
		switch(choice)
		{
		case 0:exit(0);
		case 1:printf("����������˫�׽��,Ҷ�ӽ��(���ÿո����):\n");
			create_CSTree(&T);
			printf("�����ɹ�!(�������,�����6\n");
			break;
		case 2:printf("��������ҵĽ������:");
	        scanf("%s",kval);
	        getchar();
	        pre_Search_Node(T,kval,&p);
			if(p==NULL)
			{
				printf("�������ݲ�������!\n");
			}
			else if(p!=NULL)
			{
				 printf("����%s���ݴ���!\n",p->Tdata );
				 p=NULL;
			}
			break;
		case 3:printf("������������˫�׽��:");
	        scanf("%s",fa);
	        getchar();
	        printf("���������������:");
	        scanf("%s",ch);
	        getchar();
	        insert_CSTree(&T,fa,ch);
	        printf("�������!\n");
			break;
		case 4:printf("������ɾ���������:");
			scanf("%s",ch_d);
			getchar();
			printf("������ɾ�����˫�׽������:");
			scanf("%s",fa_d);
			getchar();
			delete_CSTree(&T,fa_d,ch_d);
			printf("ɾ����������!\n");
			break;
		case 5:printf("���뷨��ʾ����:\n");
			dispTree(T,level);
			break;
		case 6:printf("�����������:\n");
			pre_Order_CSTree(T);
			break;
		case 7:AllTreePath(T,&S);
			break;
		default :printf("�����������!\n");
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
