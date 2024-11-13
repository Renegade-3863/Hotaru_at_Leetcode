#include "Solution.h"

bool Leetcode301_400::Solution::validUtf8(vector<int>& data)
{
    // 根据题目条件
    // 0xxx 代表是一个一字节字符
    // 110x 代表是一个两字节字符
    // 1110 代表是一个三字节字符
    // 以此类推
    // 所以我们不难总结出下面的流程
    // 第一步：检出这个数据的总字节数
    // 记录每个编码的总字节数
    int bytes = 0;
    // 之后，不断检查每个数字的最后一字节中连续的1，直到遇到第一个0为止，这些1的总个数就是数据的字节数
    // 这个掩码是用来检查连续的1的，它最开始是最后一字节的最高位为1，之后不断右移
    int mask = 0x00000080;
    int idx = 0, n = data.size();
    while(idx < n)
    {
        bytes = 0;
        mask = 0x00000080;
        // 我们保证每次这一轮循环开始时，idx 指向的都是一个包含下一段编码长度的数据
        // 死循环，直到遇到第一个0的数为止
        while(1)
        {
        // 每当 mask 变为零，说明我们就已经完成了一个数的检查，此时要重置 mask，并移动到下一个数据
            while(mask)
            {
                // 出现了第一个0，就直接退出即可
                if((mask & data[idx]) == 0)
                {
                    break;
                }
                // 右移一位
                mask >>= 1;
                ++bytes;
                // 出现这种情况，说明给出的编码长度大于4了，此时直接返回 false 即可
                if(mask < 0x00000008)
                {
                    return false;
                }
            }
            // 如果退出不是因为 mask == 0 了，那么说明我们已经找到了第一个 0
            // 此时 bytes 变量就记录的数据的总字节长度
            // 如果只有一个连续的1，那么显然不合法，返回 false 即可
            // cout << bytes << endl;
            if(bytes == 1)
            {
                return false;
            }
            // 如果 bytes 为零，说明这是一个 1 字节的数据，我们把 bytes 变为 1
            if(bytes == 0)
            {
                bytes = 1;
            }
            break;
        }
        // cout << idx << endl;
        // 同时，退出时，我们还检出了 "长度" 部分和 "实际存储" 的部分的分界数下标
        // 就是 data[idx] 这个数据
        // 剩下的步骤就很简单了，我们检查；
        // 1. 从 idx+1 开始直到结尾，是不是有 bytes - (idx+1) 个数
        // 2. 后面这些数的最低8位是不是均以 "10" 开头
        // 根据 bytes，从 idx 向后检查 bytes - 1 个数，看看它们是不是均为 "10" 开头，不是的话就返回 false，此过程持续移动 idx
        ++idx;
        // cout << bytes << endl;
        for(int i = 0; i < bytes-1; ++i)
        {
            if(idx >= n)
            {
                return false;
            }
            // 看最低8位的最高位
            // cout << data[idx] << endl;
            if((data[idx] | 0x00000080) > data[idx] || (data[idx] | 0x00000040) == data[idx])
            {
                return false;
            }
            // 检查完一个数，后移一步 idx 指针
            ++idx;
        }
        // 上面的循环结束后，我们保证了 idx 停留在下一个编码的长度字节处，如果还有下一段编码的话
    }
    // 通过了全部检查，返回 true
    return true;
}