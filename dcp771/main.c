#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isMappable(char *s1, char *s2);

int main()
{
    printf("%d\n", isMappable("bcdbbbbbbb", "abceeeeeee"));
    printf("%d\n", isMappable("foo", "bar"));
}

bool isMappable(char *s1, char *s2)
{
    if (strlen(s1) != strlen(s2))
    {
        return false;
    }
    char map[128];
    for (int i = 0; i < 128; i++)
    {
        map[i] = '\0';
    }
    for (int i = 0; i < strlen(s1); i++)
    {
        char ch = s1[i];
        if (!map[ch])
        {
            map[ch] = s2[i];
        }
        else if (map[ch] != s2[i])
        {
            return false;
        }
    }
    return true;
}