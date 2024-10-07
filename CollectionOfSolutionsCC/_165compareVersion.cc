#include "Solution.h"

int Leetcode101_200::Solution::compareVersion(string version1, string version2)
{
    // 从描述上看本题有些类似字符串格式的字典序问题
    // 可以用类似的方案进行实现
    // 可以按每个小数点区分左右两侧来进行比较
    int cur1 = 0, cur2 = 0, m = version1.size(), n = version2.size();
    // 根据题目样例的说明，我们需要遍历到两个字符串都检查完毕才行
    // 所以这里的条件用的是"或"
    while(cur1 < m || cur2 < n)
    {
        // 我们先通过两个单独的内部循环丢掉各自左半边的前导零
        while(cur1 < m && version1[cur1] == '0')
        {
            ++cur1;
        }
        while(cur2 < n && version2[cur2] == '0')
        {
            ++cur2;
        }
        // 之后遇到的都是有效的数据部分，取出二者这个部分的值即可
        int up = 0, down = 0;
        while(cur1 < m && version1[cur1] != '.')
        {
            up = up*10+(version1[cur1++]-'0');
        }
        while(cur2 < n && version2[cur2] != '.')
        {
            down = down*10+(version2[cur2++]-'0');
        }
        // 因为题目告诉我们每个版本号的值都一定可以用32位整数进行保存，因而这里我们结束循环后得到的一定是有效的结果
        // 将二者进行比较，看哪一个更大，如果相等，就需要进一步比较，否则，我们就可以决定返回值了
        if(up > down)
        {
            return 1;
        }
        else if(up < down)
        {
            return -1;
        }
        else
        {
            // 需要进一步比较的情况，我们需要根据 cur1 和 cur2 的值决定它们在返回外层的 while 循环时的值
            if(cur1 < m)
            {
                // 如果 cur1 的值是一个小于 m 的值，那么说明 version[cur1] 一定是一个 '.'，那么此时我们就可以简单地把它+1
                ++cur1;
            }
            // 否则，cur1 已经到了结尾，那么我们就无需再移动它
            if(cur2 < n)
            {
                // cur2 的值同理
                ++cur2;
            }
        }
    }
    // 如果都比较完成了，还是完全相等的状态，那么直接返回0即可
    return 0;
}