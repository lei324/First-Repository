#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>

typedef struct SNode 
{
	char data;
	struct SNode *next;
}SNode,*LinkStack;

/*************��ʼ����ջ************/

int initStack(LinkStack *S)
{
	*S==NULL;
	return 1;
}
/***************ѹջ************/
int Push(LinkStack *S,char e)
{
	LinkStack p=(LinkStack)malloc(sizeof(SNode));
	p->data=e;
	p->next=*S;
	*S=p;
	return 1;

}
/**************��ջ*****************/
int Pop(LinkStack *S)
{
	if(*S==NULL)
	{
		printf("ջ��!");
		return 0;
	}
	LinkStack p=*S;
	*S=(*S)->next;
	free(p);
	return 1;

}
/*************ȡջ��**************/
int getTop(LinkStack  S,char *e)
{
	if(S==NULL)
	{
		printf("ջ��!");
		return 0;
	}
	*e=S->data;
	return 1;
}

void matching(char str[])
{
	LinkStack S;
	initStack(&S);
	int is=1;
	int k,i=0,length=0;
	char e;
	for(k=0;str[k]!='\0';k++)
	{
		length++;
	}

	for(k=0;str[k]!='\0'&&is==1;k++)
	{
		if(str[k]!='('&&str[k]!='{'&&str[k]!='['&&str[k]!=')'&&str[k]!='}'&&str[k]!=']')
		{
			i++;
			continue;
		}
		switch(str[k])
		{
		case '(':case '{':case '[':
			Push(&S,str[k]);
			break;
		case ')':
			if(S!=NULL)
			{
				getTop(S,&e);
				if(e=='(')
				Pop(&S);
				else
					is=0;
			}
			else
				is=0;
			break;
		case '}':
			if(S!=NULL)
			{
				getTop(S,&e);
				if(e=='{')
					Pop(&S);
				else
					is=0;
			}
			else
				is=0;
			break;
		case ']':
			if(S!=NULL)
			{
				getTop(S,&e);
				if(e=='[')
				{
					Pop(&S);
				}
				else 
					is=0;
			}
			else
				is=0;
			break;
		}
	}
	if(is==1&&S==NULL)
		printf("ƥ��ɹ�!");
	else
		printf("ƥ��ʧ��!");
}

int main()
{
	char str[80];
	printf("��������ʽ:");
	gets(str);
	matching(str);
	system("pause");
	getchar();
	return 1;
}


