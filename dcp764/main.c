#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *greatestJoin(char **arr, int n);

int main()
{
    printf("%s\n", greatestJoin((char *[]){ "1", "2", "3" }, 3));
    printf("%s\n", greatestJoin((char *[]){ "3", "1", "3" }, 3));
    printf("%s\n", greatestJoin((char *[]){ "31", "2", "3" }, 3));
    printf("%s\n", greatestJoin((char *[]){ "212", "21", "2" }, 3));
    printf("%s\n", greatestJoin((char *[]){ "211", "21", "2" }, 3));
    return 0;
}

int compare(const void *va, const void *vb)
{
    char *a = *(char **)va;
    char *b = *(char **)vb;
    char *ab, *ba;
    asprintf(&ab, "%s%s", a, b);
    asprintf(&ba, "%s%s", b, a);
    int out = strcmp(ba, ab);
    free(ab);
    free(ba);
    return out;
}

char *greatestJoin(char **arr, int len_arr)
{
    // Create a copy of arr and sort the copy
    char **sorted = malloc(len_arr*sizeof(char *));
    memcpy(sorted, arr, len_arr*sizeof(char *));
    qsort(sorted, len_arr, sizeof(char *), compare);

    // Create a char *out that will be returned
    int len_out = 0;
    for (int i = 0; i < len_arr; i++)
    {
        len_out += strlen(arr[i]);
    }
    char *out = malloc(len_out*sizeof(char));

    // Join the contents of sorted into out
    char *iter = out;
    for (int i = 0; i < len_arr; i++)
    {
        for (int j = 0; sorted[i][j]; j++)
        {
            *iter++ = sorted[i][j];
        }
    }
    *iter = '\0';

    free(sorted);
    return out;
}