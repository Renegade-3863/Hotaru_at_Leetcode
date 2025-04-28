#include "Solution.h"

char Leetcode701_800::Soltuion::nextGreatestLetter(vector<char>& letters, char target)
{
    // 简单的二分查找问题
    // 不多写注释了（）
    int left = 0, right = letters.size()-1;
    char res = letters[0];
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // 检查 letters[mid] 与 target 的关系
        // 如果 letters[mid] <= target，那么说明 mid 以及左边的字符都不可能是答案了
        if(letters[mid] <= target)
        {
            left = mid+1;
        }
        // 否则，mid 可以是备选答案，但是 mid 左边可能还有更小的结果
        else
        {
            res = letters[mid];
            right = mid-1;
        }
    }
    return res;
}