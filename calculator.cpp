#include <iostream>
#define OK 1
#define FALSE 1
#define MAX_SIZE 100
#define INCREMENT_SIZE 20
#include "cal.h"
int main()
{
    char func[100][40];
    printf("the number of functions that you will define:\n");
    int n;
    scanf("%d",&n);
    getchar();
    for(int i=0;i<n;i++)
    {
        input_func(func);
    }
    printf("your final function to run: \n");
    char final;
    scanf("%c",&final);
    getchar();
    char s[200];
    int j=0;
    final_outcome(final,func,s,j,0);
    char var[20];
    printf("Please enter the value of X: (end by #)\n");
    gets(var);
    printf("%s在x=%s时的值为%lf",s,var,cal(s,var));
    return 0;
}
