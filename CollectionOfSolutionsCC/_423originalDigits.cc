#include "Solution.h"

string Leetcode401_500::Soltuion::originalDigits(string s)
{
    // 一道没什么意义的细节题，我们需要对 s 中可能出现的字符进行分类分析
    // 我们先把数字 0-9 的数字全部列出来：
    // 0 - zero
    // 1 - one
    // 2 - two
    // 3 - three
    // 4 - four
    // 5 - five
    // 6 - six
    // 7 - seven
    // 8 - eight
    // 9 - nine
    // 进行一些分析，我们可以处理出一个反向的映射
    // z - 0
    // o - 0/1/2/4
    // n - 1/7/9
    // e - 0/1/3/5/7/8/9
    // t - 2/3/8
    // w - 2
    // h - 3/8
    // r - 0/3/4
    // f - 4/5
    // u - 4
    // i - 5/8/9
    // v - 5/7
    // s - 6/7
    // x - 6
    // g - 8
    // 检查出了上面的映射关系后，我们会发现几个唯一的映射关系：
    // w - 2, u - 4, 6 - x, g - 8
    // 那么我们可以先从这些字符入手，遇到了就能先确定一部分单词了
    // 我们遵循：确定一个单词，就从字符串记录表中删除对应个数个字符即可
    // 写一部分看一部分就行，这题没更多好说的。。
    unordered_map<char, int> cnts;
    for(const auto& c : s)
    {
        ++cnts[c];
    }
    // 现在所有字符的出现总次数都记录到了 cnts 表中
    // 最终的答案要求按升序输出，所以我们先拿哈希表暂存一下
    unordered_map<int, int> res;
    // 剩下的就是进行处理了
    // 首先处理上面的唯一映射
    // z - 0 映射
    if(cnts['z'] != 0)
    {
        // 把其它和 0 有关联的字符减少对应次数
        cnts['e'] -= cnts['z'];
        cnts['r'] -= cnts['z'];
        cnts['o'] -= cnts['z'];
        res[0] = cnts['z'];
        cnts['z'] = 0;
    }
    // w - 2映射
    if(cnts['w'] != 0)
    {
        // 把其它和 2 有关联的字符减少对应次数
        cnts['t'] -= cnts['w'];
        cnts['o'] -= cnts['w'];
        // 记录 '2' 出现的次数
        res[2] += cnts['w'];
        cnts['w'] = 0;
    }
    // u - 4 映射
    if(cnts['u'] != 0)
    {
        // 把其它和 4 有关联的字符减少对应次数
        cnts['f'] -= cnts['u'];
        cnts['o'] -= cnts['u'];
        cnts['r'] -= cnts['u'];
        // 记录 '4' 出现的次数
        res[4] = cnts['u'];
        cnts['u'] = 0;
    }
    // x - 6 映射
    if(cnts['x'] != 0)
    {
        // 把其它和 6 有关的字符减少对应次数
        cnts['s'] -= cnts['x'];
        cnts['i'] -= cnts['x'];
        // 记录 '6' 出现的次数
        res[6] = cnts['x'];
        cnts['x'] = 0;
    }
    // g - 8 映射
    if(cnts['g'] != 0)
    {
        // 把其它和 8 有关的字符减少对应次数
        cnts['e'] -= cnts['g'];
        cnts['i'] -= cnts['g'];
        cnts['h'] -= cnts['g'];
        cnts['t'] -= cnts['g'];
        res[8] = cnts['g'];
        cnts['g'] = 0;
    }
    // 接下来可以处理清除了上面一一映射后出现的新的一一映射
    // o - 1 映射
    if(cnts['o'] != 0)
    {
        // 把其它和 1 有关的字符减少对应次数
        cnts['n'] -= cnts['o'];
        cnts['e'] -= cnts['o'];
        res[1] = cnts['o'];
        cnts['o'] = 0;
    }
    // t - 3 映射
    if(cnts['t'] != 0)
    {
        // 把其它和 3 有关的字符减少对应次数
        cnts['h'] -= cnts['t'];
        cnts['r'] -= cnts['t'];
        cnts['e'] -= 2*cnts['t'];
        res[3] = cnts['t'];
        cnts['t'] = 0;
    }
    // s - 7 映射
    if(cnts['s'] != 0)
    {
        // 把其它和 7 有关的字符减少对应次数
        cnts['e'] -= 2*cnts['s'];
        cnts['v'] -= cnts['s'];
        cnts['n'] -= cnts['s'];
        res[7] = cnts['s'];
        cnts['s'] = 0;
    }
    // f - 5 映射
    if(cnts['f'] != 0)
    {
        // 把其它和 5 有关的字符减少对应次数
        cnts['i'] -= cnts['f'];
        cnts['e'] -= cnts['f'];
        res[5] = cnts['f'];
        cnts['f'] = 0;
    }
    // i - 9 映射
    if(cnts['i'] != 0)
    {
        // 把其它和 9 有关的字符减少对应次数
        cnts['n'] -= 2*cnts['i'];
        cnts['e'] -= cnts['i'];
        res[9] = cnts['i'];
        cnts['i'] = 0;
    }
    // 根据哈希表输出最终结果即可
    string ans;
    for(int i = 0; i <= 9; ++i)
    {   
        for(int j = 0; j < res[i]; ++j)
        {
            ans.push_back(i+'0');
        }
    }
    return ans;
}