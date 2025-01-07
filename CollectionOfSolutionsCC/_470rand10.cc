// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

#include "Solution.h"

int Leetcode401_500::Soltuion::rand10()
{
    // 很经典的一道进位脑筋急转弯智力题
    // 我们按概率的方式思考这道题
    // 我们知道，rand7() 生成 1-7 之间的值是等概率的，那么如果我们调用两次 rand7()，就会有下面 49 种可能的组合情况：
    /*
            1  2  3  4  5  6  7
        1   
        2   
        3
        4
        5
        6
        7
        上面每一种情况出现的概率都是 1/49，这是每一个学过正经概率论的人都应该会的
        接下来，我们无非要的就是一个 1/10 的概率
        这个 1/10 完全可以等于 (1/49) / (10/49)
        换句话说，我们只需要取出上面 49 种情况中的 10 种，让这 10 种情况分别对应 1-10 即可完成题目的要求！
        那么这就简单了
        我们使用进制数的方式即可完成映射：
        这里用七进制即可，把上面列表的每一项减1:
            0  1  2  3  4  5  6
        0   0  1  2  3  4  5  6
        1   7  8  9  10 11 12 13
        2   14 15 16 17 18 19 20
        3   21 22 23 24 25 26 27
        4   28 29 30 31 32 33 34
        5   35 36 37 38 39 40 41
        6   42 43 44 45 46 47 48
    */
    // 观察上面的数表，我们发现，所有值都是不同的，那么我们就只需要取前面 0-9 这十个值，分别映射到 1-10 上，丢弃其它的组合结果即可
    // 想法有了，实现就非常简单了
    // 我们取两次 rand7() 的结果，如果二者进行7进制运算的结果大于等于10，那么我们丢弃这个值重新生成，否则我们输出结果
    // 这样得到的每种可能结果就是 1/10 概率的
    int res = 0;
    while(res == 0)
    {
        int first = rand7()-1, second = rand7()-1;
        // 使用生成的 first 和 second 执行七进制计算
        if(first+7*second < 10)
        {
            // 只有可行的时候，才进行赋值和返回，否则需要重新生成
            res = first+7*second+1;
        }
    } 
    return res;
}