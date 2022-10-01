#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Input: char *w, char *s
// Output: prints all starting indexes in s which are anagrams of w
// Time complexity: O(w*s)
int main(int argc, char *argv[])
{
    char *w = argv[1];
    char *s = argv[2];
    size_t len_w = strlen(w); // length of w, the substrings we're going to find, and b (next line)

    // Each element b[i] points to an int n, where n is the number of instances of the character w[i] in w minus the
    // the number of instances of the character w[i] in the substring. Therefore, if b[] is full of references to 0,
    // no character in w is underrepresented in the substring, and a valid anagram is found.
    int **b = malloc(len_w);

    // For every element b[i], make *b[i] the number of instances of w[i] in w
    for (int i = 0; i < len_w; i++)
    {
        bool unique = true;
        for (int ii = 0; ii < i; ii++)
        {
            if (w[ii] == w[i])
            {
                (*b[i])++;
                unique = false;
                break;
            }
        }
        if (unique)
        {
            b[i] = malloc(sizeof(int));
            *b[i] = 1;
        }
    }

    // Next, subtract from the counters pointed to by elements of b, based on the first len_w elements of s
    // Also, return if s is shorter than w
    for (int i = 0; i < len_w; i++)
    {
        if (!s[i])
        {
            return 0;
        }
        for (int ii = 0; ii < len_w; ii++)
        {
            if (w[ii] == s[i])
            {
                (*b[ii])--;
                break;
            }
        }
    }

    // Finally, loop over the rest of the characters in s, checking for anagrams and updating b
    int range_fst = 0;
    int range_end = len_w;
    while(s[range_end-1])
    {
        // Check if solved, and if so printf range_fst
        bool solved = true;
        for (int i = 0; i < len_w; i++)
        {
            if (*b[i] != 0)
            {
                solved = false;
                break;
            }
        }
        if (solved)
        {
            printf("%i\n", range_fst);
        }

        // Add s[range_end] to the counters, and take s[range_fst]
        // Maintains that the counters store # in w - # in substring
        for (int i = 0; i < len_w; i++)
        {
            if (w[i] == s[range_fst])
            {
                (*b[i])++;
                break;
            }
        }
        for (int i = 0; i < len_w; i++)
        {
            if (w[i] == s[range_end])
            {
                (*b[i])--;
                break;
            }
        }

        // Advance range_fst and range_end. When range_end is greater than len_w the loop terminates
        range_fst++;
        range_end++;
    }

    for (int i = 0; i < len_w; i++)
    {
        free(b[i]);
    }
    free(b);
    return 0;
}