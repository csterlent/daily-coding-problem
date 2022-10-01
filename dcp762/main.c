#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int numWordsBetween(char *a, char *b, char *string);

int main()
{
    printf("%d", numWordsBetween("hello", "world", "helloa world dog cat hello cat dog dog hello cat      w world"));
}

int numWordsBetween(char *a, char *b, char *string)
{
    bool bestSet = false;
    bool currentSet = false;

    bool multiSpace = false;
    bool matcha = true;
    bool matchb = true;
    int wi = 0;

    int best;
    int current;

    int len_string = strlen(string);
    int len_a = strlen(a);
    int len_b = strlen(b);
    for (int i = 0; i <= len_string; i++)
    {
        if (string[i] == ' ' || !string[i])
        {
            if (multiSpace)
            {
                continue;
            }
            if (currentSet && matchb && !b[wi] && (current < best || !bestSet))
            {
                bestSet = true;
                best = current;
            }
            current++;
            if (matcha && !a[wi])
            {
                currentSet = true;
                current = 0;
            }
            wi = 0;
            matcha = true;
            matchb = true;
            multiSpace = true;
        }
        else {
            multiSpace = false;
            if (matcha && a[wi] != string[i])
            {
                matcha = false;
            }
            if (matchb && b[wi] != string[i])
            {
                matchb = false;
            }
            wi++;
        }
    }
    return best;
}