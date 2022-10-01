#include <stdio.h>
#include <stdlib.h>

int rand5();
int rand7();

int main()
{
    for (int i = 1; i < 101; i++)
    {
        printf("%d", rand5());
        if (i%10 == 0)
        {
            printf("\n");
        }
        else
        {
            printf(" ");
        }
    }
}

int rand5()
{
    int out = rand7();
    while (out > 5)
    {
        out = rand7();
    }
    return out;
}

int rand7()
{
    return arc4random_uniform(7)+1;
}