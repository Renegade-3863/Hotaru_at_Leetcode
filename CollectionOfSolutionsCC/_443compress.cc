#include "Solution.h"

int Leetcode401_500::Solution::compress(vector<char>& chars)
{
    // 很基础的双指针类模拟题，我们按题目要求来做就行
    // 规定两个指针，一个指向每一种字符的开头，另一个用于记录每一种字符当前遍历到的位置(用于记录当前段有几个开头字符类型)
    int ptr1 = 0, ptr2 = 0, n = chars.size();
    // 最后的返回值
    int res = 0;
    vector<char> ans;
    // 重构结束标志为：第二个指针到达了 chars 数组的结尾
    // 此时我们对整个数组的遍历就结束了
    while(ptr2 < n)
    {
        // 内部循环，每一轮检查一个 ptr1 对应的同字符序列
        // 获取当前 ptr1 所在的字符序列开头的元素
        char c = chars[ptr1];
        // 利用 ptr2 进行实际遍历，别忘了防止无效地址访问
        while(ptr2 < n && chars[ptr2] == c)
        {
            ++ptr2;
        }
        ans.push_back(c);
        // 上面的循环结束的时候，ptr2 就指向了 ptr1 右侧第一个不是 chars[ptr1] 的字符下标
        // 我们需要进行一些修改和重构操作
        // 1. 如果 ptr2-ptr1 == 1，说明只有单个字符，那么 res + 1
        if(ptr2-ptr1 == 1)
        {
            ++res;
        }
        // 2. 如果 ptr2-ptr1 > 1，说明不止一个字符，那么 res + 1 + to_string(ptr2-ptr1).size()
        else
        {
            string len = to_string(ptr2-ptr1);
            for(const auto& ch : len)
            {
                ans.push_back(ch);
            }
            res += 1 + len.size();
        }
        // 需要把 ptr1 重置到 ptr2 的位置上
        ptr1 = ptr2;
    }
    chars = ans;
    // 返回结果即可
    return res;
}

// 题目优化需要 O(1) 的空间复杂度，这里简单做一下修改
// 考虑到一个事实：子字符串长度值这个数字本身永远不可能比实际的字符串更长
// 那么我们就可以通过一样的遍历算法，原地处理，来省去额外的数组空间
int compress(vector<char>& chars)
{
    // 很基础的双指针类模拟题，我们按题目要求来做就行
    // 规定两个指针，一个指向每一种字符的开头，另一个用于记录每一种字符当前遍历到的位置(用于记录当前段有几个开头字符类型)
    int ptr1 = 0, ptr2 = 0, n = chars.size();
    // 最后的返回值
    int res = 0;
    // vector<char> ans;
    // 重构结束标志为：第二个指针到达了 chars 数组的结尾
    // 此时我们对整个数组的遍历就结束了
    while(ptr2 < n)
    {
        // 内部循环，每一轮检查一个 ptr1 对应的同字符序列
        // 获取当前 ptr1 所在的字符序列开头的元素
        char c = chars[ptr1];
        // 利用 ptr2 进行实际遍历，别忘了防止无效地址访问
        while(ptr2 < n && chars[ptr2] == c)
        {
            ++ptr2;
        }
        // ans.push_back(c);
        // 上面的循环结束的时候，ptr2 就指向了 ptr1 右侧第一个不是 chars[ptr1] 的字符下标
        // 我们需要进行一些修改和重构操作
        // 1. 如果 ptr2-ptr1 == 1，说明只有单个字符，那么 res + 1
        if(ptr2-ptr1 == 1)
        {
            chars[res] = c;
            ++res;
        }
        // 2. 如果 ptr2-ptr1 > 1，说明不止一个字符，那么 res + 1 + to_string(ptr2-ptr1).size()
        else
        {
            string len = to_string(ptr2-ptr1);
            int length = len.size();
            chars[res] = c;
            for(int i = 0; i < length; ++i)
            {
                chars[res+i+1] = len[i]; 
            }
            res += 1 + length;
        }
        // 需要把 ptr1 重置到 ptr2 的位置上
        ptr1 = ptr2;
    }
    // chars = ans;
    // 返回结果即可
    return res;
}