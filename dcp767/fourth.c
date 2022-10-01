// copy of third.c but with more natural names
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Output: -1 terminated array of all starting indexes in superstring which are anagrams of word
// Time complexity: O(superstring)
int *AnagramFirstInds(char *word, char *superstring);

int main()
{
    int *test = AnagramFirstInds("ab", "abaxba");
    for (int i = 0; test[i] >= 0; i++)
    {
        printf("%d\n", test[i]);
    }
    free(test);
    return 0;
}

int *AnagramFirstInds(char *word, char *superstring)
{
    int wordlen = strlen(word); // length of word, the substrings we're going to find, and the next local variable

    // Each element b[c] represents the count of the char c within word, minus the count of the char c within the substring
    // Therefore, if b is full of zeros, no character in word is underrepresented in the substring, and a valid anagram is found.
    int *mapCharToDiff = malloc(128*sizeof(int));

    // For every element b[i], make *b[i] the number of instances of word[i] in word
    for (int i = 0; i < wordlen; i++)
    {
        char ch = word[i];
        mapCharToDiff[ch]++;
    }

    // Next, subtract from the counters, based on the first wordlen elements of superstring
    // Also, return if superstring is shorter than word
    for (int i = 0; i < wordlen; i++)
    {
        if (!superstring[i])
        {
            return 0;
        }
        char ch = superstring[i];
        mapCharToDiff[ch]--;
    }

    // Linked list storing the valid anagram indexes in reverse order
    struct Node
    {
        struct Node *next;
        int value;
    };
    struct Node *head = NULL;
    int anagramsFound = 0;

    int substringFirst = 0;
    int substringLast = wordlen-1;
    while(true) // breaks after checking success of the last substring, the one where superstring[substringLast] is '\0'
    {
        // Check if substring is an anagram of word, and if so add it to our linked list
        bool solved = true;
        for (int i = 0; i < 128; i++)
        {
            if (mapCharToDiff[i] != 0)
            {
                solved = false;
                break;
            }
        }
        if (solved)
        {
            struct Node *newHead = malloc(sizeof(struct Node));
            newHead->next = head;
            newHead->value = substringFirst;
            head = newHead;
            anagramsFound++;
        }
        if (!superstring[substringLast+1])
        {
            break;
        }

        // Maintaining that the counters store (# in word) - (# in substring) in response to substringFirst advancing
        char leaving = superstring[substringFirst];
        mapCharToDiff[leaving]++;
        
        substringFirst++;
        substringLast++;

        char arrived = superstring[substringLast];
        mapCharToDiff[arrived]--;
    }

    // Enter the contents of the LinkedList into a -1 terminated array, simultaneously freeing each Node
    // Corrupts the value of head
    int *output = malloc((anagramsFound+1)*sizeof(int));
    output[anagramsFound] = -1;
    int n = 1;
    while (head)
    {
        output[anagramsFound-n] = head->value;
        struct Node *p = head;
        head = head->next;
        free(p);
        n++;
    }

    return output;
}