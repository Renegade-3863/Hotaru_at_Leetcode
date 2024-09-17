#include "Solution.h"

string Leetcode1_100::Solution::countAndSay(int n)
{
    // 根据本题的题干，最简单的思路(个人认为也是唯一有效的思路)
    // 就是简单模拟，一步一步构造出最终的答案
    // 基本情况，最初的外观数列就是 "1"
    if(n == 1)
    {
        return "1";
    }
    // 之后根据这个初始序列向后递推即可
    // tmp 是上一个外观数列
    string tmp = "1";
    // cur 是当前外观数列
    string cur = "";
    int len = tmp.size();
    // 递推求解
    // 循环 n-1 次
    while(--n > 0)
    {
        // digit 记录当前可能出现重复的那个数字字符
        // 初始为 tmp 的第一个字符
        char digit = tmp[0];
        // cnt 记录 digit 在当前本地的次数
        int cnt = 1;
        // 检查 tmp 的所有数字字符
        for(int i = 1; i < len; ++i)
        {
            // 当前本地的数据已经检查完毕，可以添加到 cur 中了
            if(tmp[i] != digit)
            {
                cur += char(cnt+'0');
                // 记录出现的数字字符
                cur += char(digit);
                // 更新 digit 和 cnt，使其对应这个新数字
                digit = tmp[i];
                cnt = 1;
            }
            // 出现了重复，递增 cnt 即可
            else
            {
                ++cnt;
            }
        }
        // 注意上面的循环结束后并没有添加最后这个连续的重复串，需要多添加一次
        cur += char(cnt+'0');
        cur += char(digit);
        // 结束后，要更新 cur 和 tmp
        len = cur.size();
        tmp = cur;
        cur = "";
    }
    // 返回最终结果即可
    return tmp;
}