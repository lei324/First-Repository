#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef char ElemType;

typedef struct snode
{
	ElemType data;
	struct snode *next;
}sonde,*LinkStack;


int LinkStackInit(LinkStack *LS)
{
	*LS=NULL;
	return 1;
}

int LinkStackEmpty(LinkStack LS)
{
	if(LS==NULL)
		return 1;
	else
		return 0;
}

ElemType LinkStackGetHead(LinkStack LS)
{
	if(LS==NULL)
		return 0;
	return LS->data;
}


int LinkStackLength(LinkStack LS)
{
	int length=0;
	if(LS==NULL)
		return 0;
		LinkStack p=LS;
	while(p)
	{
		length++;
		p=p->next;
	}
	return length;
}

void LinkStackPush(LinkStack *LS,ElemType e)
{
	LinkStack p;
	p=(LinkStack)malloc(sizeof(snode));
	p->data=e;
	p->next=*LS;
	*LS=p;
	//ͷ�巨
}


ElemType LinkStackPop(LinkStack *LS)
{
	if(*LS==NULL)
		return 0 ;
	LinkStack p=*LS;
	*LS=(*LS)->next;
	ElemType x=p->data;
	free(p);
	return x;
}

int LinkStackTraver(LinkStack LS)
{
	LinkStack p=LS;
	if(p==NULL)
	{
		printf("ջΪ��!\n");
		return 0;
	}
	while(p)
	{
		printf("%c ",p->data);
		p=p->next;
	}
	printf("\n");
	return 1;

}
/*********���׺���ʽ��ֵ********/

void suffix_value(char a[])
{
	int i=0;
	int x1,x2;
	LinkStack S;
	LinkStackInit(&S);//////////////x1,x2��Ϊint����,��LinkStackPop(&S)�õ�char(ElemType)����
	while(a[i]!='#')
	{
		switch(a[i])
		{
		case '+':
			x1=LinkStackPop(&S);
			x2=LinkStackPop(&S);
			LinkStackPush(&S,x2+x1);
			break;
		case '-':
			x1=LinkStackPop(&S);
			x2=LinkStackPop(&S);
			LinkStackPush(&S,x2-x1);
			break;
		case '*':
			x1=LinkStackPop(&S);
			x2=LinkStackPop(&S);
			LinkStackPush(&S,x2*x1);
			break;
		case '/':
			x1=LinkStackPop(&S);
			x2=LinkStackPop(&S);
			if(x1!=0)
			LinkStackPush(&S,x2/x1);
			else
			{
				printf("��ĸ����Ϊ��!\n");
				return ;
			}
			break;
		default:LinkStackPush(&S,a[i]-48);
		}
		i++;
	}
	int value=LinkStackPop(&S);
	printf("���Ϊ:%d\n",value);
}



/***********�������ȼ��ж�************/

int prior(char a)
{
	if(a=='*'||a=='/')
		return 4;
	else if(a=='+'||a=='-')
		return 3;
	else if(a=='(')
		return 2;
	else if(a=='#')
		return 1;
	else
		return 0;
}

/******�������ʽת���׺���ʽ************/
//�˴�a[]��ʾ�ַ�������,������ʱ������ĩβ����'#'
void transform(char a[],char stff[])
{
	int i=0,k=0,n;
	char ch;
	LinkStack LS;
	LinkStackInit(&LS);
	LinkStackPush(&LS,'#');
	n=strlen(a);
	a[n]='#';
	a[n+1]='\0';
	while(a[i]!='\0')
	{
		if(a[i]>='0'&&a[i]<='9')
			stff[k++]=a[i];
		else
			switch(a[i])
		{
			case '(':
				LinkStackPush(&LS,a[i]);
				break;
			case ')':
				ch=LinkStackPop(&LS);
				while(ch!='(')
				{
					stff[k++]=ch;
					ch=LinkStackPop(&LS);
				}
				break;
			default:
				ch=LinkStackGetHead(LS);
				while(prior(ch)>=prior(a[i]))
				{
					stff[k++]=ch;
					ch=LinkStackPop(&LS);
					ch=LinkStackGetHead(LS);
				}

				if(a[i]!='#')
					LinkStackPush(&LS,a[i]);
		}
		i++;

	}
	stff[k]='\0';
}

void menu()
{
	char a[]={0};
	char stff[]={0};
	char yn;
	do
	{
	printf("��������ʽ:");
	gets(a);
	transform(a,stff);
	printf("ת��Ϊ��׺���ʽΪ:");
	puts(stff);
	suffix_value(stff);
	printf("�Ƿ������ֵ(y/n):");
	scanf("%c",&yn);
	getchar();
	}while(yn=='Y'||yn=='y');

}



int main()
{
	menu();
	system("pause");
	getchar();
	return 0;
}