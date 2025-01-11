#include "Solution.h"

bool Leetcode501_600::Soltuion::detectCapitalUse(string word)
{
    if(word.size() == 0)
    {
        return true;
    }
    // 轻松惬意的模拟题，按要求做就行
    // 根据要求，我们只需要两个标记变量即可记录所有状态：
    // 1. hasCapital，标记 word 是否 "有大写字母"
    // 2. cntCapital，如果 hasCapital 为 true，那么这个变量记录从开头开始，连续的大写字母的个数
    // 注意：如果不是从开头开始连续的大写字母，那么直接就可以返回 false 了
    // 单词中全部是小写的情况可以用 hasCapital == false 来代替，不需要一个额外的变量
    bool hasCapital = isupper(word[0]);
    int cntCapital = hasCapital, n = word.size();
    // 我们可以直接从第二个字符开始检查
    for(int i = 1; i < n; ++i)
    {
        // 如果 hasCapital == true，而当前字符也是一个大写字符，那么只有 cntCapital == i 的时候，我们才继续循环，因为这说明开头的大写字母到这里是连续的，没有中断
        if(hasCapital)
        {
            if(isupper(word[i]))
            {
                if(cntCapital < i)
                {
                    return false;
                }
                ++cntCapital;
            }
            // 否则，我们需要检查 cntCapital 是不是依旧为 1，对应情况3
            else if(cntCapital > 1)
            {
                // 不只有开头的一个大写字母，不合法，返回 false
                return false;
            }
            // 否则，cntCapital 为 1，合法
        }
        else
        {
            // 没有开头的大写字母，那么只要这个字母是大写的，我们就直接返回 false 即可，不合法
            if(isupper(word[i]))
            {
                return false;
            }
            // 否则，可以正常继续循环
        }
    }
    // 检查完成，合法，返回 true 即可
    return true;
}