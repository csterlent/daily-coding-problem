#include <stdio.h>
#include <stdlib.h>
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

// Create a tree and return a pointer to it. The leaves are solutions to the IP problem.
struct ipifyTree *ipifyBuildTree(const char *input, const char *prefix, const int segsNeeded, int *p_counter);

// Recursively reads values from tree into the arraying out. Frees all sub-trees as it goes
// p_index should point to 0 when called by an outside function.
void ipifyReadAndFreeTree(struct ipifyTree *tree, char **out, int *p_index);

char **ipify(const char *input, int *p_len_out)
{
    // Build a tree and count the number of solutions, using a recursive function
    *p_len_out = 0;
    struct ipifyTree *tree = ipifyBuildTree(input, "", 4, p_len_out);

    // Dump all the solutions stored in the tree into an array, using a recursive function
    char **out = malloc(*p_len_out*sizeof(char *));
    int p_index = 0;
    ipifyReadAndFreeTree(tree, out, &p_index);
    return out;
}

struct ipifyTree
{
    bool leaf;
    // if leaf:
    char *val;
    // else:
    struct ipifyTree *left;
    struct ipifyTree *right;
};

struct ipifyTree *ipifyBuildTree(const char *input, const char *prefix, const int segsNeeded, int *p_counter)
{
    struct ipifyTree *mytree = NULL;
    char seg[4] = {'\0', '\0', '\0', '\0'};

    // i is an index to seg, and add one to i for the first index to input that is not in seg
    // Check starting segments with length 1, 2, and 3. Recursively check the rest of input
    // All solutions will be stored as leaves in mytree, which gets returned
    for (int i = 0; i < 3; i++)
    {
        if (!input[i]) break;
        seg[i] = input[i];
        
        if (i == 2)
        {
            if (seg[0] > '2') break;
            if (seg[0] == '2' && seg[1] > '5') break;
            if (seg[0] == '2' && seg[1] == '5' && seg[2] > '5') break;
        }
        // When finding the last segment, don't recurse- instead, return a leaf
        if (segsNeeded == 1)
        {
            // Make sure to use all of input before getting past this point
            if (input[i+1]) continue;

            // Keep track of the number of times this point has been reached
            (*p_counter)++;
            
            // Create and return a leaf
            mytree = malloc(sizeof(struct ipifyTree));
            mytree->leaf = true;
            asprintf(&mytree->val, "%s%s", prefix, seg);
            return mytree;
        }

        // Recursively get the tree of subsolutions starting with seg.
        // First, get the prefix to be passed to the recursive call.
        char *subprefix;
        asprintf(&subprefix, "%s%s.", prefix, seg);
        struct ipifyTree *subsols = ipifyBuildTree(input+i+1, subprefix, segsNeeded-1, p_counter);
        free(subprefix);

        // Make mytree contain both mytree and subsols. The preexisting values and the values just found.
        struct ipifyTree *new_mytree = malloc(sizeof(struct ipifyTree));
        new_mytree->leaf = false;
        new_mytree->left = mytree;
        new_mytree->right = subsols;
        mytree = new_mytree;

        // Prevent segs starting with '0' from containing any more characters
        if (seg[0] == '0') break;
    }
    return mytree;
}

void ipifyReadAndFreeTree(struct ipifyTree *tree, char **out, int *p_index)
{
    if (!tree) return;
    if (tree->leaf)
    {
        out[*p_index] = tree->val;
        (*p_index)++;
    }
    else
    {
        ipifyReadAndFreeTree(tree->left, out, p_index);
        ipifyReadAndFreeTree(tree->right, out, p_index);
    }
    free(tree);
}