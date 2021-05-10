#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct LNode 
{
	int data;
	struct LNode *next;
}LNode,*LinkList;

/********初始化集合************/
int InitList(LinkList *L)
{
	(*L)=(LinkList)malloc(sizeof(LNode));
	(*L)->next=NULL;
	return 1;
}

/**********输入一个数到集合的指定位置***************/

int InsertList(LinkList *L)
{
	LinkList p,q;
	char chice;
	int x,i,j=0;
	p=*L;
	do
	{
		printf("请输入插入数的位置:");
		scanf("%d",&i);
		getchar();
		printf("请输入插入点数值:");
		scanf("%d",&x);
		getchar();
		while(p!=NULL&&j<i-1)
		{
			p=p->next;
			j++;
		}
		if(p==NULL||j>i-1)
		{
			printf("插入位置错误!");
			return 0;
		}

		q=(LinkList)malloc(sizeof(LNode));
		q->data=x;
		q->next=p->next;
		p->next=q;
		printf("是否继续插入(Y/N):");
		chice=getchar();

	}while(chice=='Y'||chice=='y');
	return 1;

}


int PrintList(LinkList L)
{
	LinkList p;
	p=L->next;
	if(p==NULL)
	{
		printf("表为空\n");
		return 0;
	}

	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
	return 1;
}

int Search_num(LinkList L)
{
	LinkList p;
	char chice;
	int x,j=0;
	p=L;
	do
	{
		printf("请输入你要查找的数值:");
		scanf("%d",&x);
		getchar();
		while(p!=NULL)
		{
			if(p->data!=x)
			{
				p=p->next;
				j++;
			}
			else if(p==NULL)
			{
				printf("无此数据!");
				return 0;
			}
			else
			{
				printf("%d在连表中的位置是%d",p->data,j);
				break;
			}

		}
		printf("是否继续查找(Y/N):");
		chice=getchar();

	}while(chice=='Y'||chice=='y');
	return 1;

}
int Delete_num(LinkList L)
{
	LinkList p=L,q=L;
	int x,j=0;
	char chice;
	do
	{
		printf("请输入你需要删除的数据:");
		scanf("%d",&x);
		getchar();
		while(p!=NULL)
		{
			if(p->data!=x)
			{
				p=p->next;
				j++;
			}
			else if(p==NULL)
			{
				printf("无此数据!\n");
				return 0;
			}
			else
			{
			  while(q->next!=p)
			  {
				  q=q->next;
			  }
			  q->next=p->next;
				free(p);
				break;
			}

		}
		printf("是否继续删除(Y/N):");
		chice=getchar();
	}while(chice=='Y'||chice=='y');
	return 1;

}
void DestoryList(LinkList *head)
{
	LinkList p,q;
	p=*head;
	while(p!=NULL)
	{
		q=p;
		p=p->next;
		free(q);
	}
	*head=NULL;
}

LinkList InterList(LinkList La,LinkList Lb,int i)
{
	LinkList pa,pb,Lc,s;
	InitList(&Lc);
	pa=La->next;
	while(pa)
	{
		pb=Lb->next;
		while(pb)
		{
			if(pa->data==pb->data)
			{
				s=(LinkList)malloc(sizeof(LNode));
				s->data=pa->data;
				s->next=Lc->next;
				Lc->next=s;
			}

			pb=pb->next;
		}

			pa=pa->next;
	}
	if(i)
	{
	printf("两集合的交集是:\n");
	PrintList(Lc);
	}
	return Lc;
}
LinkList UnionList(LinkList La,LinkList Lb,int i)
{
	LinkList Lc,s;
	InitList(&Lc);
	LinkList pa,pb;
	pa=La->next;
	pb=Lb->next;
	while(pa)
	{
		s=(LinkList)malloc(sizeof(LNode));
		s->data=pa->data;
		s->next=Lc->next;
		Lc->next=s;
		pa=pa->next;
	}
	while(pb)
	{
		pa=Lc->next;
		while(pa)
		{
			if(pa->data!=pb->data)
			{
				pa=pa->next;
			}
			else 
			{
				break;
			}


		}
		if(!pa)
		{
			s=(LinkList)malloc(sizeof(LNode));
			s->data=pb->data;
			s->next=Lc->next;
			Lc->next=s;
		}
		pb=pb->next;
	}
	if(i)
		{
			printf("两集合的并集是:\n");
			PrintList(Lc);
		}
		return Lc;

}

int difference_set(LinkList La,LinkList Lb)
{
	LinkList s1,s2,Lc,s,pa,pb;
	InitList(&Lc);
	s1=UnionList(La,Lb,0);
	s2=InterList(La,Lb,0);
	pa=La->next;
	while(pa)
	{
		pb=Lb->next;
		while(pb)
		{
			if(pb->data!=pa->data)
				pb=pb->next;
			else
				break;
		}
		if(!pb)
		{
			s=(LinkList)malloc(sizeof(LNode));
			s->data=pa->data;
			s->next=Lc->next;
			Lc->next=s;
		}
		pa=pa->next;
		
	}
	printf("两集合的差集是:\n");
	PrintList(Lc);
	return 1;
}




void menu()
{
	LinkList La,Lb,Lc;
	int n;
	int chice;
	printf("|                     1.初始化集合                      \n");
	printf("|                     2.插入数值                       \n");
	printf("|                     3.按值删除                       \n");
	printf("|                     4.按值查找                       \n");
	printf("|                     5.清空集合                      \n");
	printf("|                     6.求交集                         \n");
	printf("|                     7.求并集                         \n");
	printf("|                     8.求差集                         \n");
	printf("|                     9. 输出集合                      \n");
	printf("|                     0.退出                          \n");
	while(1)
	{
		printf("请输入你的选择:");
		scanf("%d",&chice);
		switch(chice)
		{
		case 0:exit(0);break;
		case 1:InitList(&La);
			   InitList(&Lb);break;
		case 2:printf("对第几个数列插入(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{InsertList(&La);break;}
			if(n==2)
			{InsertList(&Lb);break;}
		case 3:printf("对第几个数列删除(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{Delete_num(La);break;}
			if(n==2)
			{Delete_num(Lb);break;}
		case 4:printf("对第几个数列查找(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{Search_num(La);break;}
			if(n==2)
			{Search_num(Lb);break;}
		case 5:printf("对第几个数列清除(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{DestoryList(&La);break;}
			if(n==2)
			{DestoryList(&Lb);break;}
		case 6:InterList(La,Lb,1);break;
		case 7:UnionList(La,Lb,1);break;
		case 8:difference_set(La,Lb);break;
		case 9:printf("对第几个数列输出(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{PrintList(La);break;}
			if(n==2)
			{PrintList(Lb);break;}
			default:printf("输入错误!");
		}

	}

}
int main()
{
	menu();
	system("pause");
	getchar();
	return 1;
}

