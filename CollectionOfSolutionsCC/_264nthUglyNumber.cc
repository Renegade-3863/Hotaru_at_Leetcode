#include "Solution.h"

int Leetcode201_300::Solution::nthUglyNumber(int n)
{
    // 本题从思路上有些类似找质数的那道题，都是自底向上的递推类问题，不过并不完全是 DP 问题
    // 归根结底是因为本题的子问题定义并不是那么明确
    // 不过我们可以先考虑一些简单的情况
    // 前三个丑数分别是：
    // 2, 3, 5
    // 这是很显然的
    // 之后，考虑类似这样的问题：我们如何通过前面的丑树得知后面的丑数？
    // 首先，我们不难看出，2 这个丑数，目前作为所有已知丑数里最小的那一个，它分别乘上 2，3 和 5，得到的数是有可能成为第四个丑数的
    // 不过这还不是最后结果，注意到，2x3 和 2x5 这两个数其实是比较大的，所以它们只能算是下一个丑数的 "候选"
    // 那么，每个时候，这种 "候选" 有几个需要考虑的呢？
    // 不难发现应该是有三个
    // 就是当前还没有 "被2乘"，"被3乘“ 和 "被5乘" 的最小的丑数了
    // 因为后面更大的还没有 "被2乘", "被3乘" 和 "被5乘" 的丑数乘上 2, 3 或 5 的结果一定会比前面这三个乘上的结果更小
    // 基于上面的推断，我们可以作出下面的初始化：
    // 初始化三个指针，分别指向 "当前最小的还未被2乘的丑数"，"当前最小的还未被3乘的丑数" 和 "当前最小的还未被5乘的丑数"
    // 然后便可以基于这三个指针来比较，得出下一个丑数的值了，至于如何移动这三个指针，我们的策略就是维护已经找到的丑数数组，之后在这个丑数数组上移动三个指针即可
    // 存储已经找到的丑数
    vector<int> uglys = {1};
    // 按上面的思路，初始化三个指针，均指向第一个丑数1
    int ptr2 = 0, ptr3 = 0, ptr5 = 0;
    // 之后进行递推即可
    int i = 0;
    while(i < n)
    {
        // 判断出三个候选人哪一个是下一个需要添加的最小丑数
        int nxt = 0;
        int minimum = min(min(uglys[ptr2]*2, uglys[ptr3]*3), uglys[ptr5]*5);
        if(minimum == uglys[ptr2]*2)
        {
            nxt = ptr2;
        }
        else if(minimum == uglys[ptr3]*3)
        {
            nxt = ptr3;
        }
        else
        {
            nxt = ptr5;
        }
        // 添加下一个丑数，同时根据 nxt 的值移动对应的指针
        // 注意，这里还有一些细节问题，因为题目要求我们找出的丑数一定是从头开始不重复的第 n 个，但由于我们 2，3 和 5 的倍数有可能重叠，比如 6 既是 2 的倍数，又是 3 的倍数
        // 因此，我们必须对结果进行判重，不过本题不用哈希集合，因为我们的 uglys 数组本身的有序性，因而如果出现了重复，那么一定是和当前数组中的最后一个重复，所以我们只需要根据数组的最后一个元素和当前决定的结果是否相等
        // 进行判断即可
        if(nxt == ptr2)
        {
            ++ptr2;
            if(uglys[uglys.size()-1] == uglys[nxt]*2)
            {
                continue;
            }
            uglys.push_back(uglys[nxt]*2);
        }
        else if(nxt == ptr3)
        {
            ++ptr3;
            if(uglys[uglys.size()-1] == uglys[nxt]*3)
            {
                continue;
            }
            uglys.push_back(uglys[nxt]*3);
        }
        else
        {
            ++ptr5;
            if(uglys[uglys.size()-1] == uglys[nxt]*5)
            {
                continue;
            }
            uglys.push_back(uglys[nxt]*5);
        }
        ++i;
    }
    return uglys[n-1];
}