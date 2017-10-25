#include<iostream>
#include <queue>
#include <cmath>
#define OK 1
#define FALSE 1
#define MAX_SIZE 100
#define INCREMENT_SIZE 20
/*
 用一个map来存储操作符大小
 */
typedef struct LNode{
    char c;
    char var[100];
    int size=0;
    LNode *next;
}LNode, *Linklist;
int map[8][8]={
        {0,0,0,0,0,0,0,0},
        {0,1,1,-1,-1,1,1,1},
        {0,1,1,-1,-1,1,1,1},
        {0,1,1,1,1,1,1,1},
        {0,1,1,1,1,1,1,1},
        {0,1,1,1,1,1,0,1},
        {0,-1,-1,-1,-1,0,-1,-1},
        {0,-1,-1,-1,-1,-1,2,0}
};
typedef int STATUS;
using namespace std;
typedef struct Stack{
    int size;
    double *top;
    double *base;
}Stack;
/*
 将操作符转换为相应的map数字
 */
int Tran(char c)
{
    if(c=='+')
        return 1;
    else if(c=='-')
        return 2;
    else if(c=='*')
        return 3;
    else if(c=='/')
        return 4;
    else if(c=='(')
        return 5;
    else if(c==')')
        return 6;
    else if(c=='#')
        return 7;
}
STATUS Init_stack(Stack &L)
{
    L.base=(double*)malloc(MAX_SIZE* sizeof(double));
    L.size=MAX_SIZE;
    L.top=L.base;
    return OK;
}
int empty(Stack L)
{
    if(L.base==L.top)
        return 1;
    else return 0;
}
double Get_top(Stack L)
{
    if(empty(L)) exit(510);
    else 
    {
        return *(L.top-1);
    }
}
double Pop(Stack &L)
{
    if(empty(L)) exit(510);
    else
    {
        return *(--L.top);
    }
}
STATUS Push(Stack &L,double p)
{
    if(L.top-L.base>=L.size)
    {
        L.base=(double *)realloc(L.base,(MAX_SIZE+INCREMENT_SIZE)* sizeof(double));
        if(!L.base) exit(120);
        L.top=L.base+L.size;
        L.size+=INCREMENT_SIZE;
    }
    *L.top=p;
    L.top++;
    return OK;
}
/*
 判断字符是否为操作符
 */
int In_OP(char c)
{
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#') return true;
    return false;
}
double Operate(double a,int op,double b)
{
    switch(op){
        case(1):
            return a+b;
        case(2):
            return b-a;
        case(3):
            return a*b;
        case(4):
            return b/a;
        default:
            exit(0);
    }
}
int judge_op(char s)
{
    if(s=='+'||s=='-'||s=='*'||s=='/'||s=='('||s==')'||s=='#'||s=='^')
        return true;
    return false;
}
int judge(char s)
{
    if(s=='+'||s=='-'||s=='*'||s=='/'||s=='('||s==')'||s=='#'||s=='0'|s=='1'|s=='2'|s=='3'|s=='4'|s=='5'|s=='6'|s=='7'|s=='8'|s=='9'|s=='.'||s=='^')
        return true;
    return false;
}
void show(Linklist M)
{
    LNode *p=M->next;
    while(p)
    {

        if(!p->size)
            printf("%c",p->c);
        else
            printf("%s",p->var);
        p=p->next;
    }
}
int main()
{
    Stack OP;
    Stack Num;
    Init_stack(OP);
    Init_stack(Num);
    Push(OP,Tran('#'));
    Linklist L=(Linklist)malloc(sizeof(LNode));
    L->next=NULL;
    LNode *tail=L;
    char s;
    s=char(getchar());
    while(s!='#')
    {
        if(judge(s)) {
            LNode *p = (Linklist) malloc(sizeof(LNode));
            p->c = s;
            p->size=0;
            p->next = tail->next;
            tail->next = p;
            tail = p;
            s = char(getchar());
        } else{
            LNode *p = (Linklist) malloc(sizeof(LNode));
            int i=0;
            while(!judge_op(s)&&s!='#')
            {
                p->var[i]=s;
                s=char(getchar());
                i++;
            }
            p->size=1;
            p->next = tail->next;
            tail->next = p;
            tail = p;
        }
    }

    LNode *p=L;
    getchar();
    while(p->next)
    {
        if(p->next->size)
        {
            printf("insert value of %s end by #: \n",p->next->var);
            char m;
            m=char(getchar());
            int f=1;
            while(m!='#')
            {
                LNode *q = (Linklist) malloc(sizeof(LNode));
                q->size=0;
                q->c=m;
                if(f==1) {
                    q->next = p->next->next;
                    p->next = q;
                    p=p->next;
                    f=0;
                } else{
                    q->next=p->next;
                    p->next=q;
                    p=p->next;
                }
                m=getchar();
            }
            getchar();
        }
        else
            p=p->next;
    }
    LNode *q = (Linklist) malloc(sizeof(LNode));
    q->next=NULL;
    q->c='#';
    q->size=0;
    p->next=q;
    //show(L);
    LNode *t=L->next;
    int flag=1;
    while(t->c!='#'||Get_top(OP)!=7)
    {

            if(t->c=='-')
                flag=-1;
            if(!In_OP(t->c)||flag==-1)
            {
                if(flag==-1)
                {
                    while(t->next->c=='-')
                    {
                        t=t->next;
                        flag=-flag;
                    }
                    t=t->next;
                    while(t->c=='(')
                    {
                        Push(OP,Tran(t->c));
                        t=t->next;
                    }
                }
                Push(Num,((t->c)-48)*flag);
                t=t->next;
                while(!judge_op(t->c)&&t->c!='.')
                {
                    Push(Num,Pop(Num)*10+((t->c)-48)*flag);
                    //printf("%f",Get_top(Num));
                    t=t->next;
                }
                if(t->c=='.')
                {
                    double k=10;
                    t=t->next;
                    while(!judge_op(t->c))
                    {
                        Push(Num,Pop(Num)+(((t->c)-48)/k)*flag);
                        k*=10;
                        t=t->next;
                    }
                }
                if(flag==-1)
                    flag=1;
            }
            else
            {
                int m=Tran(t->c);
                int n=Get_top(OP);
                //printf("%d%d\n",m,n);
                if(map[m][n]==1)
                {
                    Push(OP,m);
                    t=t->next;
                    if(t->c=='-')
                        flag=-1;
                }
                else if(map[m][n]==0)
                {
                    Pop(OP);
                    t=t->next;
                    if(t->c=='-')
                        flag=-1;
                }
                else if(map[m][n]==-1)
                {
                    Push(Num,Operate(Pop(Num),Pop(OP),Pop(Num)));
                    //printf("%d\n",Get_top(Num));
                }
                else
                {
                    printf("error!\n");
                }
            }

    }
    double outcome=Get_top(Num);
    if(int(outcome)==outcome)
    {
        printf("%d",int(outcome));
    }
    else
    {
        printf("%f",outcome);
    }
    return 0;
}