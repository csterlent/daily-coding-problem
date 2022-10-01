#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Input: char *w, char *s
// Output: prints all starting indexes in s which are anagrams of w
// Time complexity: O(s)
// However, first.c is still faster if w is significantly less than 128 characters.
int main(int argc, char *argv[])
{
    char *w = argv[1];
    char *s = argv[2];
    size_t len_w = strlen(w); // length of w, the substrings we're going to find, and b (next line)

    // Each element b[c] represents the count of the char c within w, minus the count of the char c within the substring
    // Therefore, if b is full of zeros, no character in w is underrepresented in the substring, and a valid anagram is found.
    int *counter = malloc(128*sizeof(int));

    // For every element b[i], make *b[i] the number of instances of w[i] in w
    for (int i = 0; i < len_w; i++)
    {
        char ch = w[i];
        counter[ch]++;
    }

    // Next, subtract from the counters, based on the first len_w elements of s
    // Also, return if s is shorter than w
    for (int i = 0; i < len_w; i++)
    {
        if (!s[i])
        {
            return 0;
        }
        char ch = s[i];
        counter[ch]--;
    }

    int range_fst = 0;
    int range_end = len_w;
    while(s[range_end-1])
    {
        // Check if solved, and if so printf range_fst
        bool solved = true;
        for (int i = 0; i < 128; i++)
        {
            if (counter[i] != 0)
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
        char leaving = s[range_fst];
        counter[leaving]++;
        
        char arriving = s[range_end];
        counter[arriving]--;

        // Advance range_fst and range_end. When range_end is greater than len_w the loop terminates
        range_fst++;
        range_end++;
    }
    return 0;
}