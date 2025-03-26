#include "Solution.h"

string Leetcode701_800::Soltuion::toLowerCase(string s)
{
    // 不多说了。。
    for(auto& c : s)
    {
        if('A' <= c && c <= 'Z')
        {
            c = 'a'+(c-'A');
        }
    }
    return s;
}   