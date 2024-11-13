#include "Solution.h"

Leetcode301_400::Solution::Logger::Logger()
{
    // 什么都不需要做，编译器会自动初始化哈希表
}

bool Leetcode301_400::Solution::Logger::shouldPrintMessage(int timestamp, string message)
{
    // 我们检查哈希表，如果这个单词压根没被打印过，直接打印+记录时间戳即可
    if(this->memo.find(message) == this->memo.end())
    {
        this->memo[message] = timestamp;
        return true;
    }
    // 否则，这个单词之前被添加过，我们需要检查它的时间戳
    // 如果两个时间戳的间隔还不到10秒，我们直接返回 false 即可，不用修改哈希表的时间戳，不过要记得把时间戳递增，因为即使没有打印，时间也在流动
    if(timestamp - this->memo[message] < 10)
    {
        return false;
    }
    // 这里两个时间戳的间隔已经达到了10秒，那么我们可以打印，同时也要更新上一次打印的时间戳
    this->memo[message] = timestamp;
    return true;
}