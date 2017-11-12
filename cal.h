//
// Created by 张智昊 on 08/11/2017.
//

#ifndef CALCULATOR_CAL_H
#define CALCULATOR_CAL_H

#endif //CALCULATOR_CAL_H
#include <iostream>
#include <queue>
#include <cmath>
#define OK 1
#define FALSE 1
#define MAX_SIZE 100
#define INCREMENT_SIZE 20

/*
 用一个map来存储操作符大小判断 map[x][y]==1->x>y ==0->x=y ==-1->x<y ==2->error
 */
int judge(char s)
{
    if(s=='+'||s=='-'||s=='*'||s=='/'||s=='('||s==')'||s=='#'||s=='0'|s=='1'|s=='2'|s=='3'|s=='4'|s=='5'|s=='6'|s=='7'|s=='8'|s=='9'|s=='.'||s=='^')
        return true;
    return false;
}
int judge_char(char c)
{
    if(c=='x'||c=='X'||c=='y'||c=='Y')
        return 1;
    return 0;
}
void input_func(char func[100][40])
{
    printf("your function name:\n");
    char s;
    scanf("%c",&s);
    getchar();
    printf("your function:\n");
    int i=0;
    char m;
    m=getchar();
    {
        while(m!='#')
        {
            func[s][i]=m;
            i++;
            m=getchar();
        }
        //func[s][i]='#';
        func[s][i]='\0';
    }
    getchar();
//    printf("%s",func[s]);
}//输入一个函数并存到func[100][40]
void final_outcome(char function,char func[100][40],char s[200],int &j,int flag)
{
    int i=0;
    while(*(func[function]+i)!='\0')
    {
        char c=*(func[function]+i);
        if(judge(c)||judge_char(c))
        {
            s[j++]=c;
        }
        else
        {
            s[j++]='(';
            final_outcome(c,func,s,j,flag+1);
            s[j++]=')';
        }
        i++;
    }
    if(flag==0)
    {
        s[j++]='#';
    }
    s[j]='\0';
}//用来递归调用函数的函数，用func来存储函数方程式
typedef struct LNode{
    char c;
    char var[100];
    int size=0;
    LNode *next;
}LNode, *Linklist;
int map[9][9]={
        {0,0,0,0,0,0,0,0,0},
        {0,-1,-1,-1,-1,1,1,1,-1},
        {0,-1,-1,-1,-1,1,1,1,-1},
        {0,1,1,-1,-1,1,1,1,-1},
        {0,1,1,-1,-1,1,1,1,-1},
        {0,1,1,1,1,1,2,1,1},
        {0,-1,-1,-1,-1,0,1,-1,-1},
        {0,-1,-1,-1,-1,-1,2,0,-1},
        {0,1,1,1,1,1,1,1,1}
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
    else if(c=='^')
        return 8;
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
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#'||c=='^') return true;
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
        case(8):
            return pow(b,a);
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
int judge_num(char s)
{
    if(s=='0'||s=='1'||s=='2'||s=='3'||s=='4'||s=='5'||s=='6'||s=='7'||s=='8'||s=='9')
        return true;
    return false;
}
double cal(char *sen,char *number_X) {
    Stack OP;
    Stack Num;
    Init_stack(OP);
    Init_stack(Num);
    Push(OP, Tran('#'));
    Linklist L = (Linklist) malloc(sizeof(LNode));
    L->next = NULL;
    LNode *tail = L;
    int j=0;
    while (*(sen+j) != '#') {
        char s=*(sen+j);


        if (judge(s)) {
            //printf("%c",s);
            LNode *p = (Linklist) malloc(sizeof(LNode));
            p->c = s;
            p->size = 0;
            p->next = tail->next;
            tail->next = p;
            tail = p;
        } else {
            LNode *p = (Linklist) malloc(sizeof(LNode));
            int i = 0;
            while (!judge_op(s) && s != '#') {
                p->var[i] = s;
                j++;
                s=*(sen+j);
                i++;
            }j--;
            p->size = 1;
            p->next = tail->next;
            tail->next = p;
            tail = p;
        }
        if(*(sen+j) == '#')break;
        j++;
    }

    LNode *p = L;
//    getchar();
    while (p->next) {
        if (p->next->size) {
//           printf("insert value of %s end by #: \n", p->next->var);
            int i=0;
            char m;
            m = *(number_X+i);
            int f = 1;
            while (m != '#') {
                LNode *q = (Linklist) malloc(sizeof(LNode));
                q->size = 0;
                q->c = m;
                if (f == 1) {
                    q->next = p->next->next;
                    p->next = q;
                    p = p->next;
                    f = 0;
                } else {
                    q->next = p->next;
                    p->next = q;
                    p = p->next;
                }
                i++;
                m = *(number_X+i);
            }
 //           getchar();
        } else
            p = p->next;
    }
    LNode *q = (Linklist) malloc(sizeof(LNode));
    q->next = NULL;
    q->c = '#';
    q->size = 0;
    p->next = q;
//    show(L);
    LNode *t = L->next;
    int flag = 1;
    int time_step = 0;
    while (t->c != '#' || Get_top(OP) != 7) {

        if (time_step == 0 && t->c == '-')
            flag = -1;
        if (!In_OP(t->c) || flag == -1) {
            if (flag == -1) {
                flag = -flag;
                while (!judge_num(t->c)) {
                    if (t->c == '(') {
                        Push(OP, Tran(t->c));
                        t = t->next;
                    } else if (t->c == '-') {
                        flag = -flag;
                        t = t->next;
                    }
                }
            }
//            printf("%c\n",t->c);
            Push(Num, ((t->c) - 48) * flag);
            t = t->next;
            while (!judge_op(t->c) && t->c != '.') {
                Push(Num, Pop(Num) * 10 + ((t->c) - 48) * flag);
                //printf("%f",Get_top(Num));
                t = t->next;
            }
            if (t->c == '.') {
                double k = 10;
                t = t->next;
                while (!judge_op(t->c)) {
                    Push(Num, Pop(Num) + (((t->c) - 48) / k) * flag);
                    k *= 10;
                    t = t->next;
                }
            }
            if (flag == -1)
                flag = 1;
        } else {
            int m = Tran(t->c);
            int n = Get_top(OP);
            //printf("%d%d\n",m,n);
            if (map[m][n] == 1) {
                Push(OP, m);
                t = t->next;
                //printf("%d",m);
                if (t->c == '-')
                    flag = -1;
            } else if (map[m][n] == 0) {
                Pop(OP);
                t = t->next;
//                if (t->c == '-')
//                    flag = -1;
            } else if (map[m][n] == -1) {
                Push(Num, Operate(Pop(Num), Pop(OP), Pop(Num)));
//                printf("%lf\n",Get_top(Num));
            } else {
                printf("error!\n");
            }
        }
        time_step += 1;

    }
    double outcome = Get_top(Num);
    return outcome;
}