#include "Solution.h"

string Leetcode501_600::Soltuion::reverseStr(string s, int k)
{
    // 简单的模拟题，我们按要求做即可
    // 基本思路是，使用两个指针，每次右指针先移动 2k 步，之后反转左右指针之间的子串
    // 如果右指针还没走到 2k 步，但是走了多于 k 步，就到结尾了，那么依然需要反转左右指针之间的元素
    // 否则，结束循环，什么也不做
    // 我们定义一个 helper function
    // 用于反转给定指针 (left, right) 之间的元素
    function<void(const int&, const int&)> reverse = [&](const int& left, const int& right)
    {
        // 可以使用位运算来高效地进行数据交换
        // 0, 1, 2, 3
        int mid = ((right-left)>>1)+left;
        // 注意，如果区间长度为奇数，我们不能用位运算处理最中间的那个值，不然数据会出错
        if((right-left+1)%2)
        {
            --mid;
        }
        // cout << left << ", " << right << endl;
        for(int i = left; i <= mid; ++i)
        {
            // cout << s[i] << ": " << s[right-i+left] << endl;
            // a 是 s[i]，b 是 s[right-i]
            // a ^= b -> a = a^b
            // b ^= a -> b = b^(a^b) = a
            // a ^= b -> (a^b)^a = b
            s[i] ^= s[right-i+left];
            s[right-i+left] ^= s[i];
            s[i] ^= s[right-i+left];
        }
        // 交换完成，结束函数
    };
    // 我们调用上面的函数即可
    int left = 0, right = 0, n = s.size();
    while(right < n)
    {
        if(right-left+1 == 2*k)
        {
            // 达到了最基本的反转要求，那么我们执行反转即可
            reverse(left, left+k-1);
            // 重置 left，后移 right
            ++right;
            left = right;
            // cout << s << endl;
        }
        else
        {
            ++right;
        }
    }
    // 最后，我们检查剩余的字符有多少个
    // 1. 剩余个数不小于 k 但小于 2k
    // 那么反转前 k 个
    // 注意，此时 right 指向的位置下标是 n，这里没有实际的字符，我们需要用 right-left 而不是 right-left+1 来计算剩余字符长度
    // k <= right-left < 2*k
    if(right-left >= k && right-left < 2*k)
    {
        reverse(left, left+k-1);
    }
    // 2. 剩余个数少于 k 个，全部反转
    else
    {
        // 这里也要注意，right-1 才是实际的最后一个字符下标
        reverse(left, right-1);
    }
    // 返回结果即可，s 本身现在就是结果
    return s;
}