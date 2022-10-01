#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Output: -1 terminated array of all starting indexes in sz which are anagrams of szWord
// Time complexity: O(sz)
int *AnagramFirstInds(char *szWord, char *sz);

int main()
{
    int *rg_ichTest = AnagramFirstInds("ab", "abaxba");
    for (int i = 0; rg_ichTest[i] >= 0; i++)
    {
        printf("%d\n", rg_ichTest[i]);
    }
    free(rg_ichTest);
    return 0;
}

int *AnagramFirstInds(char *szWord, char *sz)
{
    int ichWordMax = strlen(szWord); // length of szWord, the substrings we're going to find, and the next local variable

    // Each element b[c] represents the count of the char c within szWord, minus the count of the char c within the substring
    // Therefore, if b is full of zeros, no character in szWord is underrepresented in the substring, and a valid anagram is found.
    // mp_ch_dcch means map from char to difference in counts of char
    int *mp_ch_dcchWordMinusSubstring = malloc(128*sizeof(int));

    // For every element b[i], make *b[i] the number of instances of szWord[i] in szWord
    for (int i = 0; i < ichWordMax; i++)
    {
        char ch = szWord[i];
        mp_ch_dcchWordMinusSubstring[ch]++;
    }

    // Next, subtract from the counters, based on the first ichWordMax elements of sz
    // Also, return if sz is shorter than szWord
    for (int i = 0; i < ichWordMax; i++)
    {
        if (!sz[i])
        {
            return 0;
        }
        char ch = sz[i];
        mp_ch_dcchWordMinusSubstring[ch]--;
    }

    // Linked list storing the valid anagram indexes in reverse order
    struct Node
    {
        struct Node *pNodeNext;
        int ichAnagram;
    };
    struct Node *pNodeHead = NULL;
    int cichAnagramsFound = 0;

    int ichSubstringFirst = 0;
    int ichSubstringLast = ichWordMax-1;
    while(true) // breaks after checking success of the last substring, where sz[ichSubstringLast] is '\0'
    {
        // Check if substring is an anagram of szWord, and if so add it to our linked list
        bool solved = true;
        for (int i = 0; i < 128; i++)
        {
            if (mp_ch_dcchWordMinusSubstring[i] != 0)
            {
                solved = false;
                break;
            }
        }
        if (solved)
        {
            struct Node *newHead = malloc(sizeof(struct Node));
            newHead->pNodeNext = pNodeHead;
            newHead->ichAnagram = ichSubstringFirst;
            pNodeHead = newHead;
            cichAnagramsFound++;
        }
        if (!sz[ichSubstringLast+1])
        {
            break;
        }

        // Maintaining that the counters store (# in szWord) - (# in substring) in response to ichSubstringFirst advancing
        char chLeaving = sz[ichSubstringFirst];
        mp_ch_dcchWordMinusSubstring[chLeaving]++;
        
        ichSubstringFirst++;
        ichSubstringLast++;

        char chArrived = sz[ichSubstringLast];
        mp_ch_dcchWordMinusSubstring[chArrived]--;
    }

    // Enter the contents of the LinkedList into a -1 terminated array, simultaneously freeing each Node
    // Corrupts the value of pNodeHead
    int *rgiOutput = malloc((cichAnagramsFound+1)*sizeof(int));
    rgiOutput[cichAnagramsFound] = -1;
    int n = 1;
    while (pNodeHead)
    {
        rgiOutput[cichAnagramsFound-n] = pNodeHead->ichAnagram;
        struct Node *pnd = pNodeHead;
        pNodeHead = pNodeHead->pNodeNext;
        free(pnd);
        n++;
    }

    return rgiOutput;
}