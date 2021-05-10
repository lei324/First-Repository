#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct LNode 
{
	int data;
	struct LNode *next;
}LNode,*LinkList;

/********��ʼ������************/
int InitList(LinkList *L)
{
	(*L)=(LinkList)malloc(sizeof(LNode));
	(*L)->next=NULL;
	return 1;
}

/**********����һ���������ϵ�ָ��λ��***************/

int InsertList(LinkList *L)
{
	LinkList p,q;
	char chice;
	int x,i,j=0;
	p=*L;
	do
	{
		printf("�������������λ��:");
		scanf("%d",&i);
		getchar();
		printf("������������ֵ:");
		scanf("%d",&x);
		getchar();
		while(p!=NULL&&j<i-1)
		{
			p=p->next;
			j++;
		}
		if(p==NULL||j>i-1)
		{
			printf("����λ�ô���!");
			return 0;
		}

		q=(LinkList)malloc(sizeof(LNode));
		q->data=x;
		q->next=p->next;
		p->next=q;
		printf("�Ƿ��������(Y/N):");
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
		printf("��Ϊ��\n");
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
		printf("��������Ҫ���ҵ���ֵ:");
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
				printf("�޴�����!");
				return 0;
			}
			else
			{
				printf("%d�������е�λ����%d",p->data,j);
				break;
			}

		}
		printf("�Ƿ��������(Y/N):");
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
		printf("����������Ҫɾ��������:");
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
				printf("�޴�����!\n");
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
		printf("�Ƿ����ɾ��(Y/N):");
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
	printf("�����ϵĽ�����:\n");
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
			printf("�����ϵĲ�����:\n");
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
	printf("�����ϵĲ��:\n");
	PrintList(Lc);
	return 1;
}




void menu()
{
	LinkList La,Lb,Lc;
	int n;
	int chice;
	printf("|                     1.��ʼ������                      \n");
	printf("|                     2.������ֵ                       \n");
	printf("|                     3.��ֵɾ��                       \n");
	printf("|                     4.��ֵ����                       \n");
	printf("|                     5.��ռ���                      \n");
	printf("|                     6.�󽻼�                         \n");
	printf("|                     7.�󲢼�                         \n");
	printf("|                     8.��                         \n");
	printf("|                     9. �������                      \n");
	printf("|                     0.�˳�                          \n");
	while(1)
	{
		printf("���������ѡ��:");
		scanf("%d",&chice);
		switch(chice)
		{
		case 0:exit(0);break;
		case 1:InitList(&La);
			   InitList(&Lb);break;
		case 2:printf("�Եڼ������в���(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{InsertList(&La);break;}
			if(n==2)
			{InsertList(&Lb);break;}
		case 3:printf("�Եڼ�������ɾ��(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{Delete_num(La);break;}
			if(n==2)
			{Delete_num(Lb);break;}
		case 4:printf("�Եڼ������в���(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{Search_num(La);break;}
			if(n==2)
			{Search_num(Lb);break;}
		case 5:printf("�Եڼ����������(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{DestoryList(&La);break;}
			if(n==2)
			{DestoryList(&Lb);break;}
		case 6:InterList(La,Lb,1);break;
		case 7:UnionList(La,Lb,1);break;
		case 8:difference_set(La,Lb);break;
		case 9:printf("�Եڼ����������(a[1]/b[2]:");
			scanf("%d",&n);
			getchar();
			if(n==1)
			{PrintList(La);break;}
			if(n==2)
			{PrintList(Lb);break;}
			default:printf("�������!");
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

