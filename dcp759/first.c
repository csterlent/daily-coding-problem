#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Returns an array of all valid IP address combinations that have all the digits from input in the right order
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

// Tries to modify out to be an IP segment from super[start to max]. Returns true if successful
// Assumes start <= max. Assumes start is an index to super. Assumes max is at most strlen(super)+1
bool ipifyExtractSegment(char out[4], const char *super, const int start, const int max);

char **ipify(const char *input, int *p_len_out)
{
    int len_input = strlen(input);
    *p_len_out = 0;

    // Data structure to store solutions as we find them
    struct Node
    {
        char *val;
        struct Node *next;
    };
    struct Node *mylist = NULL;

    // A: [0, i)
    // B: [i, j)
    // C: [j, k)
    // D: [k, len_input)
    for (int i = 1; i <= 3; i++)
    {
        char a[4];
        if (!ipifyExtractSegment(a, input, 0, i)) break;

        for (int j = i+1; j <= i+3; j++)
        {
            char b[4];
            if (!ipifyExtractSegment(b, input, i, j)) break;

            for (int k = j+1; k <= j+3; k++)
            {
                char c[4];
                if (!ipifyExtractSegment(c, input, j, k)) break;

                char d[4];
                if (!ipifyExtractSegment(d, input, k, len_input)) continue;

                struct Node *new = malloc(sizeof(struct Node));
                asprintf(&new->val, "%s.%s.%s.%s", a, b, c, d);
                new->next = mylist;
                mylist = new;

                (*p_len_out)++;
            }
        }
    }

    // Create and fill an array named out with values from the linked list. Free the nodes of the linked list
    char **out = malloc(*p_len_out*sizeof(char *));
    for (int i = *p_len_out-1; i >= 0; i--)
    {
        out[i] = mylist->val;
        struct Node *old_mylist = mylist;
        mylist = mylist->next;
        free(old_mylist);
    }

    return out;
}

bool ipifyExtractSegment(char out[4], const char *super, const int start, const int max)
{
    if (max-start > 3) return false;
    if (max == start) return false;
    if (!super[max-1]) return false;
    for (int i = 0; i < 4; i++)
    {
        if (i < max-start)
        {
            out[i] = super[start+i];
        }
        else
        {
            out[i] = '\0';
            break;
        }
    }
    if (out[0] == '0' && out[1] != '\0') return false;
    if (out[2])
    {
        if (out[0] > '2') return false;
        if (out[0] == '2' && out[1] > '5') return false;
        if (out[0] == '2' && out[1] == '5' && out[2] > '5') return false;
    }
    return true;
}