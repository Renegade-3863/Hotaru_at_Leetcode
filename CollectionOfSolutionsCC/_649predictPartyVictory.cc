#include "Solution.h"

string Leetcode601_700::Soltuion::predictPartyVictory(string senate)
{
    // 一眼贪心类问题
    // 考虑如何贪心处理
    // 用下面的例子来思考：
    // RDDRRRD
    // 第一个 R 会 ban 第一个 R
    // 之后，第二个 R 应该 ban 第一个 R
    // 原因在于：
    // 虽然第一个 R 在本轮已经没有投票权了
    // 但是他依然会在下一轮拥有更优先的投票权
    // 而这一轮如果不 ban 他
    // 下一轮他就会 ban 掉当前的这个 R
    // 所以从直觉上说，肯定越早拥有投票权的对家参议员，越需要被优先 ban 掉
    // 我们后面会考虑如何进行证明这种 impulse
    // 那么这就引出了一种类似模拟的方法
    queue<int> Rs, Ds;
    // 先遍历一轮，填充 Rs 和 Ds 数组
    int n = senate.size();
    for(int i = 0; i < n; ++i)
    {
        if(senate[i] == 'R')
        {
            Rs.push(i);
        }
        else
        {
            Ds.push(i);
        }
    }
    // 处理完成，可以开始贪心过程了
    // for(const auto& numD : Ds)
    // {
    //     cout << numD << endl;
    // }
    // cout << endl;
    // for(const auto& numR : Rs)
    // {
    //     cout << numR << endl;
    // }
    // 循环，直到某个阵营的人被全 ban
    while(!Ds.empty() && !Rs.empty())
    {
        // 检查两队队头的元素值
        // 小的那个可以弹出大的那个队头的元素
        if(Ds.front() < Rs.front())
        {
            Ds.push(Ds.front()+n);
        }
        else
        {
            Rs.push(Rs.front()+n);
            // Ds.pop();
            // Rs.pop();
        }
        // 上面两步可以挪出来放到公共部分
        Rs.pop();
        Ds.pop();
    }
    // 过程结束，选择最后的赢家
    return !Ds.empty() ? "Dire" : "Radiant";
}