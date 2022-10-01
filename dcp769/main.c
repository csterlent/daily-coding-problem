#include <stdio.h>
#include <stdlib.h>

int numRollsUntilSeq(int a, int b);
int dieRoll();

int main()
{
    int numRolls56 = 0;
    int numRolls55 = 0;
    int numSimulations = 0;
    while(1)
    {
        numRolls56 += numRollsUntilSeq(5, 6);
        numRolls55 += numRollsUntilSeq(5, 5);
        numSimulations++;
        printf("%.4f %.4f\n", (float)numRolls56/numSimulations, (float)numRolls55/numSimulations);
    }
}

int numRollsUntilSeq(int a, int b)
{
    int prevRoll = dieRoll();
    int roll = dieRoll();
    int numRolls = 2;
    while(prevRoll != a && roll != b)
    {
        prevRoll = roll;
        roll = dieRoll();
        numRolls++;
    }
    return numRolls;
}

int dieRoll()
{
    return arc4random_uniform(6)+1;
}