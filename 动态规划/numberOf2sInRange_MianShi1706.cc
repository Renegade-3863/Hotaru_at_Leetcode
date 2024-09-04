#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <deque>
#include <numeric>

/* 题目描述：编写一个方法，计算从 0 到 n (含 n) 中数字 2 出现的次数。*/

using namespace std;

int main()
{
    /* 第二种定义dp数组的方法，分立式 */
    // 假设dp[i]代表给定的数字转换成字符串表示后，对应下标为i的数位上出现2的次数，那么最后的答案就是整个dp数组的和
    // 第一步是先把这个整数转换成对应的数字数组
    function<int(int)> numberOf2sInRange = [&](int num) -> int {
        deque<int> digits;
        int power = 1;
        int tmp = num;
        while(tmp)
        {
            digits.push_front(tmp%10);
            tmp /= 10;
            if(tmp)
            {
                power *= 10;
            }
        }
        // power记录了当前位的位信息(万位、千位、百位，etc)
        // 循环结束后，digits中存储的是num中所有数位上的数字
        
        // 依据上面给出的DP数组定义创建数组
        // 注意最开始每个数位上2出现的次数都初始化为0，因为我们还没有开始计算
        // vector<int> dp(digits.size(), 0);

        // 注意到实际计算过程中dp数组记录的数据本身只会被使用一次，因此可以直接在计算的同时进行累加，丢掉冗余的数组即可
        int sum = 0;
        // 开始逐位计算
        // left记录当前位左侧的数位构成的值，right记录当前位右侧的数位构成的值
        int left = 0, right = num-digits[0]*power;

        for(int i = 0; i < digits.size(); ++i)
        {
            // 根据当前digits[i]与2的大小关系决定如何计算dp[i]
            if(digits[i] > 2)
            {
                // dp[i] = (left+1)*power;
                sum += (left+1)*power;
            }
            else if(digits[i] == 2)
            {
                // dp[i] = (left)*power+right+1;
                sum += left*power+right+1;
            }
            else
            {
                // dp[i] = (left)*power;
                sum += left*power;
            }
            // 更新左右侧的值信息
            left = left * 10 + digits[i];
            power /= 10;
            right = i < digits.size() ? right-digits[i+1]*power : 0;
        }
        // return accumulate(dp.begin(), dp.end(), 0);
        return sum;
    };

    std::cout << "There are " << numberOf2sInRange(1000000000) << " 2's existances from 0 to 1000000000\n";
    std::cout << "There are " << numberOf2sInRange(483127807) << " 2's existances from 0 to 483127807\n";
    std::cout << "There are " << numberOf2sInRange(25) << " 2's existances from 0 to 25\n";
    return 0;
}