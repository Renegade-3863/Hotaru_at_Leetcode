#include "Solution.h"

bool Leetcode701_800::Soltuion::isOneBitCharacter(vector<int>& bits)
{
    int n = bits.size(), i = 0;
    while (i < n - 1) 
    {
        i += bits[i] + 1;
    }
    return i == n - 1;
}