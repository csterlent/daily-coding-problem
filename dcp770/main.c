#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// O(2^sum(heaps))
bool isWinningRecursive(int *heaps, size_t len_heaps);
// O(product(heaps)*len_heaps)
bool isWinningIterative(int *heaps, size_t len_heaps);

int main()
{
    printf("%d\n", isWinningIterative((int[]){2, 3, 4, 5, 6, 1, 2, 0}, 8));
    printf("%d\n", isWinningRecursive((int[]){2, 3, 4, 5, 6, 1, 2, 0}, 8));
    printf("%d\n", isWinningIterative((int[]){400, 400}, 2));
    printf("%d\n", isWinningRecursive((int[]){400, 400}, 2));
    return 0;
}

bool isWinningRecursive(int *heaps, size_t len_heaps)
{
    bool heapsEmpty = true;
    for (int i = 0; i < len_heaps; i++)
    {
        for (int j = 0; j < heaps[i]; j++)
        {
            heapsEmpty = false;
            int temp = heaps[i];
            heaps[i] = j;
            if (!isWinningRecursive(heaps, len_heaps))
            {
                heaps[i] = temp;
                return true;
            }
            heaps[i] = temp;
        }
    }
    return heapsEmpty;
}

bool isWinningIterative(int *heaps, size_t len_heaps)
{
    // Initialize a map that can range from (0, 0, 0, ...) to (heaps[0], heaps[1], heaps[2], ...)
    // Therefore map is a len_heaps-dimensional space
    // The map queried at any position will give back true if that position is winning
    // To query the map at (a, b, c, ...) use the index mapBasises[0]*a + mapBasises[1]*b + mapBasises[2]*c + ...
    size_t len_map = 1;
    int *mapBasises = malloc(len_heaps*sizeof(int)+sizeof(int));
    for (int i = len_heaps-1; i >= 0; i--)
    {
        mapBasises[i] = len_map;
        len_map *= heaps[i]+1;
    }
    bool *map = malloc(len_map*sizeof(bool));
    for (int i = 0; i < len_map; i++)
    {
        map[i] = false;
    }

    // Use the following rules to fill map: Set (0, 0, 0, ...) to be considered a winning position
    // Any position that is forced to go to a winning position (eg 1, 0, 0, ...) is a losing position
    // Any position that can reach a losing position is a winning position
    map[0] = true;
    for (int i = 0; i < len_map; i++)
    {
        if (!map[i])
        {
            // i is a losing position. Set all positions that can reach i as winning.
            // To do this, iterate over all the dimensions of map
            for (int axis = 0; axis < len_heaps; axis++)
            {
                // Set every position in that direction to true
                int diMax = axis ? mapBasises[axis-1] : len_map;
                for (int di = 0; di < diMax; di += mapBasises[axis])
                {
                    map[i+di] = true;
                }
            }
        }
    }
    bool output = map[len_map-1];
    free(map);
    free(mapBasises);
    return output;
}