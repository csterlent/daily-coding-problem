#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Returns an array of all valid IP address combinations that have all the
// digits from input in the right order
char **ipify(const char *input, int *p_len_out);

int main(int argc, char *argv[])
{
    int len_ip;
    char **ip = ipify(argv[1], &len_ip);
    for (int i = 0; i < len_ip; i++)
    {
        printf("%s\n", ip[i]);
        free(ip[i]);
    }
    free(ip);
    return 0;
}

char **ipifyRecurse(const char *input, int *p_len_out, const int segsNeeded)
{
    *p_len_out = 0;
    char **out = NULL;
    if (segsNeeded == 1)
    {
        // If input is not valid, return NULL and keep *p_len_out 0
        if (input[0] == '0' && strlen(input) > 1) return NULL;
        if (!strlen(input)) return NULL;
        if (atoi(input) > 255) return NULL;

        // Return an array containing the one string
        *p_len_out = 1;
        out = malloc(sizeof(char *));
        *out = malloc(strlen(input));
        strcpy(*out, input);
        return out;
    }
    char seg[] = {'\0', '\0', '\0', '\0'};
    for (int i = 0, iMax = strlen(input); i < iMax; i++)
    {
        seg[i] = input[i];

        // If seg is not a valid segment, just stop because adding on won't help
        if (atoi(seg) > 255) break;

        // Get the array of new solutions that start with seg
        int len_newSols;
        char **newSols = ipifyRecurse(input+i+1, &len_newSols, segsNeeded-1);

        // Assign out to a larger array. Copy over the values. Free the old out.
        char **old_out = out;
        out = malloc((*p_len_out+len_newSols)*sizeof(char *));
        memcpy(out, old_out, *p_len_out*sizeof(char *));
        free(old_out);

        // For every newSol ns, add this to out: (seg+"."+ns) then free ns
        for (int j = 0; j < len_newSols; j++)
        {
            asprintf(&out[*p_len_out], "%s.%s", seg, newSols[j]);
            free(newSols[j]);
            (*p_len_out)++;
        }
        if (newSols) free(newSols);

        // Prevent segs starting with '0' from containing any more characters
        if (seg[0] == '0') break;
    }
    return out;
}

char **ipify(const char *input, int *p_len_out)
{
    return ipifyRecurse(input, p_len_out, 4);
}