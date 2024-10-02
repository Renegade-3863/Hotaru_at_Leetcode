#include "Solution.h"

string Leetcode101_200::Solution::reverse(string s)
{
    // 要我们反转一个给定字符串中所有单词的顺序，并且要清除所有多余的空格
    // 考虑这样的方案：
    // 我们规定两个指针 left 和 right
    // left 指向需要反转的字符串的左侧边界，right 指向需要反转的字符串的右侧边界
    // 使用类似状态机的方案进行字符串的反转
    // 我们写一个对 [l, r] 之间的字符进行反转的子函数
    function<void(int, int)> subRev = [&](int left, int right)
    {
        int l = left, r = right;
        while(l < r)
        {
            swap(s[l], s[r]);
            ++l; --r;
        }
    };
    // 先把整个字符串中所有的字符进行反转，在这个过程中去掉多余的空格
    int n = s.size();
    int left = 0, right = 0;
    int start = -1, end = n;
    while(right < n)
    {
        // 定位到下一个需要反转的单词的第一个字符为止
        while(right < n && s[right] == ' ')
        {
            ++left; ++right;
        }
        // 如果检查完后我们拿到的下一个需要反转的单词的第一个字符下标是 n，那么说明我们就检查到了字符串的结尾，而此时最后这部分都是尾随空格，不能更新 end
        if(right == n)
        {
            break;
        }
        // 定位到了第一个非空字符的位置
        // 如果 start 值还是没有赋值的状态(即值为-1)，那么就把这个第一个有效字符的位置赋给 start
        if(start == -1)
        {
            start = left;
        }
        // 之后检出当前这个单词的右边界
        while(right < n && s[right] != ' ')
        {
            ++right;
        }
        // 循环结束时，right 指向的是当前单词后面的第一个空格的位置
        // 我们这里把 [left, right-1] 之间的字符串进行反转
        subRev(left, right-1);
        // 动态更新有效字符串末尾的位置下标 end
        end = right-1;
        // 把两个指针挪到可能有下一个单词的开始下标处
        left = right+1; ++right;
    }
    // 循环结束后，我们把 s [start, end] 之间的字符反转
    s = s.substr(start, end-start+1);
    subRev(0, end-start);
    // 注意，上面的操作没有清除字符串之间多余的空格，所以我们还要再遍历一轮去除多余的单词间空格
    // 考虑不使用新字符串 res 存储去除了中间空格的字符串来进行中间字符串的去除
    // 还是使用循环不变式
    // 规定 left 指向最后一个已经去除了所有多余空格的下标处，right 用于遍历整个 s 子串
    left = -1; right = 0; n = s.size();
    while(right < n)
    {
        // 填充一个字符串
        while(right < n && s[right] != ' ')
        {
            swap(s[++left], s[right]);
            ++right;
        }
        // 如果已经遍历完了整个字符串，就可以直接退出了
        if(right == n)
        {
            break;
        }
        // 尾部添加一个空格
        swap(s[++left], s[right]);
        // 跨过所有空格
        ++right;
        while(right < n && s[right] == ' ')
        {
            ++right;
        }
    }
    // 结束后，截取前 left 个字符即可
    s = s.substr(0, left+1);
    return s;
}