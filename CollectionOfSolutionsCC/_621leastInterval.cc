#include "Solution.h"

int Leetcode601_700::Soltuion::leastInterval(vector<char>& tasks, int n)
{
    // 贪心类的题都很有生活气息，本题也一样
    // 如何在给定的不能连续做同一类任务的限制下，用最短的时间完成要求的所有任务
    // 这很明显是一个贪心类问题
    // 举个例子：
    // ["A", "A", "A", "B", "B", "B"]
    // 那么在下面的时间轴上，我们可以这样排布任务：
    /*
        AB-AB-AB
        ------------
        中间有两行横线，是因为在该时刻，任何任务的 CD 都还没好，所以我们不能执行它们中的任何一个
    */
    // 到这里，整体的方法结构就很明确了
    // 我们可以直接对答案进行 "构造"
    // 换句话说，按照 n 的间隔排布每种任务，直到所有任务都被排布完成即可
    // 同时，任务总数最多的任务类型，我们显然需要先执行它，否则越排到后面，这个任务结束的就越晚
    // 所以我们可以先统计出每种任务的对象个数，之后对这个统计数组进行排序
    // 最后按排好序的结果对答案序列进行构造
    // 不过到这里，先停一下，我们刚刚举例的时候，是否发现了某种规律性的东西？
    // 如果我们知道出现次数最多的那一项任务，那么我们最后的结果是否会和这种任务出现的次数相关联？
    // 假设出现次数最多的任务出现了 cnt 次
    // 那么很明显，它们会构造出一个基本的 (cnt-1)*(n+1)+cnt 的格子图
    // 最后一个 cnt 单独取出来，是因为它后面不再有冻结时间，所以最后的一行不再是 "n+1"
    // 那么如果总的任务数不超过这个架构框出来的量，那么我们很明显可以把那些出现次数更少的任务插到前面去，填满冻结的那些时间节点
    // 简单证明一下：
    // 前面这些空格，每一行同列空位之间间隔都是 n，所以把两个任务放在同一列上相邻行的位置上，肯定是满足冻结时间要求的
    // 而剩下的任务，出现次数均少于 cnt 次
    // 反之，如果总的任务数超过了这个框出来的值，那么我们可以简单地把多出来的那些任务插到每一行的末尾，这样很明显比我们把它接到整个满任务序列后面更优
    vector<int> cnts(26, 0);
    for(const char& task : tasks)
    {
        ++cnts[task-'A'];
    }
    int maximum = *max_element(cnts.begin(), cnts.end()), maxCnt = 0;
    for(const auto& cnt : cnts)
    {
        maxCnt += (maximum == cnt);
    }
    // 根据 maxCnt 和 task.size() 的大小来决定最终结果
    return max(int(tasks.size()), (maximum-1)*(n+1)+maxCnt);
}