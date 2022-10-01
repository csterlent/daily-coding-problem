#include <stdio.h>
#include <stdlib.h>

// Finds the min and max of the first n elements of vals. Modifies *min and *max in place (np)
// n must be positive, and vals must have at least n elements.
void *np_MinAndMax(int *vals, int n, int *min, int *max);

int main()
{
    int a, b, c, d;
    np_MinAndMax((int[]){ 7, 1, 2, 3, 4 }, 5, &a, &b);
    np_MinAndMax((int[]){ 0, 1, 2, 3, 4 }, 4, &c, &d);
    printf("%d %d\n", a, b);
    printf("%d %d\n", c, d);
    return 0;
}

void *np_MinAndMax(int *vals, int n, int *min, int *max)
{
    *min = vals[0];
    *max = vals[0];
    // Process the next two elements with three comparisons. So comparisons
    // required is roughly 3/2 N.
    for (int i = n % 2; i < n; i += 2) // i=n%2 ensures vals[i] and vals[i+1] always exists
    {
        if (vals[i] > vals[i+1])
        {
            if (vals[i+1] < *min)
                *min = vals[i+1];
            if (vals[i] > *max)
                *max = vals[i];
        }
        else
        {
            if (vals[i] < *min)
                *min = vals[i];
            if (vals[i+1] > *max)
                *max = vals[i+1];
        }
    }
    return;
}