#include "solution.h"

// 第一版：完全暴力的 DFS 方案，不难预见的 TLE，因为重复区间搜索实在是太多了 O(2^n) 的复杂度。。。甚至大数计算本身都是需要复杂度的
int Leetcode201_300::Solution::strobogrammaticInRange(string low, string high)
{
    // 函数检查：
    // checkPoint1: 四种条件分析
    function<int(const string&, const string&)> cmp = [&](const string& num1, const string& num2) -> int
    {
        // 如果二者的符号不同，那么我们有可能可以直接得出二者大小关系
        // 如果 num1 < 0，num2 > 0, 那么一定有 num1 < num2
        if(num1[0] == '-' && num2[0] != '-')
        {
            return -1;
        }
        // 如果 num1 > 0，num2 < 0，那么一定有 num1 > num2
        if(num1[0] != '-' && num2[0] == '-')
        {
            return 1;
        }
        // 如果 num1 < 0，num2 < 0，那么我们可以反过来比较它们的绝对值大小，并在前面乘上一个 -1 来修正大小关系
        if(num1[0] == '-' && num2[0] == '-')
        {
            // 返回相反值
            return -1 * cmp(num1.substr(1), num2.substr(1));
        }
        // 下面的情况中，num1 和 num2 都是正数
        // 先判断二者长度
        // 长度更大的那一个数字字符串显然代表一个更大的数字
        int m = num1.size(), n = num2.size();
        if(m > n)
        {
            return 1;
        }
        // 长度更短的那一个数字字符显然代表一个更小的数字
        if(m < n)
        {
            return -1;
        }
        // 剩下的情况下，二者的长度一定是相等的，我们此时可以简单地通过字典序比较来判断二者的大小关系
        // 暴论：长度相等的两个数字字符串，它们的字典序和正常数字的值大小关系是相等的
        if(num1 == num2)
        {
            return 0;
        }
        return num1 > num2 ? 1 : -1;
    };

    function<string(const string&, const string&)> add = [&](const string& num1, const string& num2) -> string
    {
        // 加法操作这里，我们作出这样的假设：两个值不会异号，如果某一个是负数，我们应该用减法函数而不是加法函数
        // 用于计算 (num1+num2)/2 的结果字符串
        // 这是求和的部分
        int m = num1.size(), n = num2.size();
        // 回忆：两个数求和，和值的长度最长为 max(m, n)+1 个数位
        // 我们可以用一个数位数组存储这些数位上的求和结果
        vector<int> results(max(m,n)+1, 0);
        int len = results.size();
        // 填数的过程从后向前进行
        for(int i = 0; i < len-1; ++i)
        {
            // 获取 num1 的加数位
            int adder1 = i < m ? (num1[m-i-1]-'0') : 0;
            int adder2 = i < n ? (num2[n-i-1]-'0') : 0;
            // 进行求和和记录
            results[len-i-1] = adder1+adder2;
        }
        string res = "";
        // 从后向前逐个进行进位
        // 同时可以把数组中的结果转换回字符串返回结果
        for(int i = len-1; i > 0; --i)
        {
            results[i-1] += results[i] / 10;
            results[i] %= 10;
            res.insert(0, to_string(results[i]));
        }
        // 检查最高位是否有值
        if(results[0] != 0)
        {
            res.insert(0, to_string(results[0]));
        }
        return res;
    };

    function<string(const string&, const string&)> subtraction = [&](const string& num1, const string& num2) -> string
    {
        // 大数减法的过程类似大数加法，不过有很多细节问题需要处理
        // 注意到，有一些问题我们不必在减法中处理，可以转换成加法处理
        // 1. num1[0] != '-' && num2[0] == '-'
        // 此时可以直接忽略 num2 的负号
        if(num1[0] != '-' && num2[0] == '-')
        {
            return add(num1, num2.substr(1));
        }
        // 2. num1[0] == '-' && num2[0] != '-'
        // 此时也可以直接忽略 num1 的负号
        if(num1[0] == '-' && num2[0] != '-')
        {
            string ret = add(num1.substr(1), num2);
            ret.insert(0, "-");
            return ret;
        }
        // 3. num1[0] == '-' && num2[0] == '-'
        // 此时可以直接丢掉二者的负号，转换为两个正数相减
        if(num1[0] == '-' && num2[0] == '-')
        {
            return subtraction(num2.substr(1), num1.substr(1));
        }
        // 4. num1[0] != '-' && num2[0] != '-'
        // 为了使计算过程更加简单统一，可以通过 cmp 的结果来限制 num1 > num2
        // 根据二者大小关系调整减法关系
        // 如果 num1 < num2，那么我们返回结果的值部分由 num2-num1 来表示
        // 否则依然用 num1-num2 表示
        int sign = cmp(num1, num2);
        if(sign == 0)
        {
            return "0";
        }
        else if(sign == -1)
        {
            string ret = subtraction(num2, num1);
            ret.insert(0, "-");
            return ret;
        }
        // 这里我们保证了 num1 一定是大于 num2 的
        // 减法结果最大可以有 max(num1.size(), num2.size()) 位
        // 而由于我们保证了 num1 > num2 >= 0，那么我们可以简单地利用 num1 的长度来代替 max(num1.size(), num2.size())
        int m = num1.size(), n = num2.size();
        vector<int> results(m, 0);
        // 利用借位进行减法计算
        // 还是从低位开始向高位运动
        for(int i = 0; i < m; ++i)
        {
            int sub1 = num1[m-i-1]-'0';
            int sub2 = i < n ? num2[n-i-1]-'0' : 0;
            results[m-i-1] = sub1 >= sub2 ? sub1-sub2 : 20+sub1-sub2;
        }
        // 结束后，再次从低位到高位完成借位过程
        for(int i = m-1; i > 0; --i)
        {
            results[i-1] -= results[i] / 10;
            results[i] %= 10;
        }
        // 从左到右输出打印结果到一个结果字符串中，返回结果即可
        // 先丢弃前导零
        int idx = 0;
        for(; idx < m; ++idx)
        {
            if(results[idx] != 0)
            {
                break;
            }
        }
        // 剩下的部分按原序构造字符串输出即可
        string res = "";
        for(int i = idx; i < m; ++i)
        {
            res += (results[i]+'0');
        }
        return res;
    };

    function<string(string, string)> divide = [&](string num1, string num2) -> string
    {
        // 用于计算 (num1+num2)/2 的结果字符串
        // 这是求商的部分
        // 对于字符串形式的除法，了解到的可行方案是利用大数减法，不断地从被除数中减去除数*10^k
        // 其中 k 是一个初始值为 max(0, num1.size()-num2.size()) 的幂值
        // 想法不难，但是写起来细节问题可以想见地会很多
        // 首先我们需要一个用于大数减法的子过程，这个可以在上面进行定义
        // 还是先进行问题简化：
        // 由于正负号对于除法的影响仅限于最终结果的符号，我们可以对符号进行统一
        // 记录一个符号位
        int sign = 1;
        // 1. num1[0] == '-' && num2[0] == '-'
        // 此时直接全部转换为正数进行计算即可
        if(num1[0] == '-' && num2[0] == '-')
        {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
        }
        // 2. num1[0] != '-' && num2[0] == '-'
        // 记录符号位为 -1，把 num2 转换成正数
        else if(num1[0] != '-' && num2[0] == '-')
        {
            sign = -1;
            num2 = num2.substr(1);
        }
        // 3. num1[0] == '-' && num2[0] != '-'
        // 同情况2
        else if(num1[0] == '-' && num2[0] != '-')
        {
            sign = -1;
            num1 = num1.substr(1);
        }
        // num1 < num2，此时可以直接返回0
        if(cmp(num1, num2) == -1)
        {
            return "0";
        }
        // 否则，先往 num2 的副本的结尾添零，直到副本的位数和 num1 一致
        string num = num2;
        while(cmp(num+"0", num1) <= 0)
        {
            num.push_back('0');
        }
        // 之后循环进行数据减法
        vector<int> results;
        // 写一个大的死循环，内部定义退出条件
        while(1)
        {
            int digit = 0;
            while(cmp(num1, num) >= 0)
            {
                num1 = subtraction(num1, num);
                ++digit;
            }
            // 结束一轮减少，把商这一位上的数加到 results 中
            results.push_back(digit);
            // 如果当前检查的除数已经小到了 num2 本身，那么我们已经求完了商的整个整数部分，可以退出循环了
            if(cmp(num, num2) == 0)
            {
                break;
            }
            // 剔除 num 后面的一个零
            num.pop_back();
        }
        // 根据 results 的结果组合出最终的商
        string res = "";
        for(int i = 0; i < results.size(); ++i)
        {
            res.push_back(results[i]+'0');
        }
        // 别忘了返回之前把符号给加上，如果前面 sign 计算出来是 -1 的话
        if(sign == -1)
        {
            res.insert(0, "-");
        }
        return res;
    };

    function<bool(const string&)> isStrobogrammatic = [&](const string& num) -> bool
    {
        unordered_map<char, char> mapping = {{'0', '0'}, {'1', '1'}, {'8', '8'}, {'9', '6'}, {'6', '9'}};
        // 之后就是和回文数判断中类似的双指针比较
        int left = 0, right = num.size()-1;
        while(left <= right)
        {
            if(mapping.find(num[left]) != mapping.end() && mapping[num[left]] == num[right])
            {
                ++left;
                --right;
            }
            else
            {
                return false;
            }
        }
        return true;
    };

    // 不理解官方给出那种奇怪的解法的用意是什么，个人认为本题可以利用分治策略来简单解决
    // 不过由于传入的两个边界数据都是以字符串形式表示的数字，可能会需要重写一下字符串形式的数值比较的函数
    // 同时，为了对区间进行二分，我们还需要一个子过程用于求出 [low, high] 区间的两半小区间
    // 具体的，需要一个函数用于计算 ((high-low)>>1)+low
    // 基本情况
    // low == high
    // 此时可以直接判断这个值本身是不是一个中心对称数
    if(low == high)
    {
        return isStrobogrammatic(low) ? 1 : 0;
    }
    string mid = divide(add(low, high), "2");
    return strobogrammaticInRange(low, mid) + strobogrammaticInRange(add(mid, "1"), high);
}

// 第二版：尝试添加记忆化数组进行优化：不好意思，仍然 TLE
// 不过应该是可以保证前面的三种大数运算过程是正确的了。。。
// 还是需要一个用 pair<string, string> 作为哈希键的哈希表存储结果
// 我们进行一下重载
struct stringPair {
public:
    stringPair(string s1, string s2) : first(s1), second(s2) {}
    bool operator== (const stringPair& p) const
    {
        return first == p.first && second == p.second;
    }
    string first;
    string second;
};
struct hashFunc {
    size_t operator() (const stringPair& p) const
    {
        return hash<string>()(p.first) ^ hash<string>()(p.second);
    }
};
// 记忆化哈希表
unordered_map<stringPair, int, hashFunc> memo;
int strobogrammaticInRange(string low, string high)
{
    // 重载完成，可以初始化哈希表了
    unordered_map<pair<string, string>, int, hashFunc, equalFunc> memo;
    function<int(const string&, const string&)> cmp = [&](const string& num1, const string& num2) -> int
    {
        // 如果二者的符号不同，那么我们有可能可以直接得出二者大小关系
        if(num1[0] == '-' && num2[0] != '-')
        {
            return -1;
        }
        if(num1[0] != '-' && num2[0] == '-')
        {
            return 1;
        }
        if(num1[0] == '-' && num2[0] == '-')
        {
            // 返回相反值
            return -1 * cmp(num1.substr(1), num2.substr(1));
        }
        // 先判断二者长度
        // 长度更大的那一个数字字符串显然代表一个更大的数字
        int m = num1.size(), n = num2.size();
        if(m > n)
        {
            return 1;
        }
        if(m < n)
        {
            return -1;
        }
        // 剩下的情况下，二者的长度一定是相等的，我们此时可以简单地通过字典序比较来判断二者的大小关系
        if(num1 == num2)
        {
            return 0;
        }
        return num1 > num2 ? 1 : -1;
    };

    function<string(const string&, const string&)> add = [&](const string& num1, const string& num2) -> string
    {
        // 用于计算 (num1+num2)/2 的结果字符串
        // 这是求和的部分
        int m = num1.size(), n = num2.size();
        // 回忆：两个数求和，和值的长度最长为 max(m, n)+1 个数位
        // 我们可以用一个数位数组存储这些数位上的求和结果
        vector<int> results(max(m,n)+1, 0);
        int len = results.size();
        // 填数的过程从后向前进行
        for(int i = 0; i < max(m, n); ++i)
        {
            // 获取 num1 的加数位
            int adder1 = i < m ? (num1[m-i-1]-'0') : 0;
            int adder2 = i < n ? (num2[n-i-1]-'0') : 0;
            // 进行求和和记录
            results[len-i-1] = adder1+adder2;
        }
        string res = "";
        // 从后向前逐个进行进位
        // 同时可以把数组中的结果转换回字符串返回结果
        for(int i = len-1; i > 0; --i)
        {
            results[i-1] += results[i] / 10;
            results[i] %= 10;
            res.insert(0, to_string(results[i]));
        }
        // 检查最高位是否有值
        if(results[0] != 0)
        {
            res.insert(0, to_string(results[0]));
        }
        return res;
    };

    function<string(const string&, const string&)> subtraction = [&](const string& num1, const string& num2) -> string
    {
        // 大数减法的过程类似大数加法，不过有很多细节问题需要处理
        // 注意到，有一些问题我们不必在减法中处理，可以转换成加法处理
        // 1. num1[0] != '-' && num2[0] == '-'
        // 此时可以直接忽略 num2 的负号
        if(num1[0] != '-' && num2[0] == '-')
        {
            return add(num1, num2.substr(1));
        }
        // 2. num1[0] == '-' && num2[0] != '-'
        // 此时也可以直接忽略 num1 的负号
        if(num1[0] == '-' && num2[0] != '-')
        {
            string ret = add(num1.substr(1), num2);
            ret.insert(0, "-");
            return ret;
        }
        // 3. num1[0] == '-' && num2[0] == '-'
        // 此时可以直接丢掉二者的负号，转换为两个正数相减
        if(num1[0] == '-' && num2[0] == '-')
        {
            return subtraction(num1.substr(1), num2.substr(1));
        }
        // 4. num1[0] != '-' && num2[0] != '-'
        // 为了使计算过程更佳简单统一，可以通过 cmp 的结果来限制 num1 > num2
        int sign = cmp(num1, num2);
        if(sign == 0)
        {
            return "0";
        }
        else if(sign == -1)
        {
            return subtraction(num2, num1);
        }
        // 这里我们保证了 num1 一定是大于 num2 的
        // 根据二者大小关系调整减法关系
        // 如果 num1 < num2，那么我们返回结果的值部分由 num2-num1 来表示
        // 否则依然用 num1-num2 表示
        // 减法结果最大可以有 max(num1.size(), num2.size()) 位
        int m = num1.size(), n = num2.size();
        vector<int> results(m, 0);
        // 利用借位进行减法计算
        // 还是从低位开始向高位运动
        for(int i = 0; i < m; ++i)
        {
            int sub1 = num1[m-i-1]-'0';
            int sub2 = i < n ? num2[n-i-1]-'0' : 0;
            results[m-i-1] = sub1 >= sub2 ? sub1-sub2 : 20+sub1-sub2;
        }
        // 结束后，再次从低位到高位完成借位过程
        for(int i = m-1; i > 0; --i)
        {
            results[i-1] -= results[i] / 10;
            results[i] %= 10;
        }
        // 从左到右输出打印结果到一个结果字符串中，返回结果即可
        // 先丢弃前导零
        int idx = 0;
        for(; idx < m; ++idx)
        {
            if(results[idx] != 0)
            {
                break;
            }
        }
        // 剩下的部分按原序构造字符串输出即可
        string res = "";
        for(int i = idx; i < m; ++i)
        {
            res += (results[i]+'0');
        }
        return res;
    };

    function<string(string, string)> divide = [&](string num1, string num2) -> string
    {
        // 用于计算 (num1+num2)/2 的结果字符串
        // 这是求商的部分
        // 对于字符串形式的除法，了解到的可行方案是利用大数减法，不断地从被除数中减去除数*10^k
        // 其中 k 是一个初始值为 max(0, num1.size()-num2.size()) 的幂值
        // 想法不难，但是写起来细节问题可以想见地会很多
        // 首先我们需要一个用于大数减法的子过程，这个可以在上面进行定义
        // 还是先进行问题简化：
        // 由于正负号对于除法的影响仅限于最终结果的符号，我们可以对符号进行统一
        // 记录一个符号位
        int sign = 1;
        // 1. num1[0] == '-' && num2[0] == '-'
        // 此时直接全部转换为正数进行计算即可
        if(num1[0] == '-' && num2[0] == '-')
        {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
        }
        // 2. num1[0] != '-' && num2[0] == '-'
        // 记录符号位为 -1，把 num2 转换成正数
        else if(num1[0] != '-' && num2[0] == '-')
        {
            sign = -1;
            num2 = num2.substr(1);
        }
        // 3. num1[0] == '-' && num2[0] != '-'
        // 同情况2
        else if(num1[0] == '-' && num2[0] != '-')
        {
            sign = -1;
            num1 = num1.substr(1);
        }
        // num1 < num2，此时可以直接返回0
        if(cmp(num1, num2) == -1)
        {
            return "0";
        }
        // 否则，先往 num2 的副本的结尾添零，直到副本的位数和 num1 一致
        string num = num2;
        while(cmp(num+"0", num1) <= 0)
        {
            num.push_back('0');
        }
        // 之后循环进行数据减法
        vector<int> results;
        while(1)
        {
            int digit = 0;
            while(cmp(num1, num) >= 0)
            {
                num1 = subtraction(num1, num);
                ++digit;
            }
            // 结束一轮减少，把商这一位上的数加到 results 中
            results.push_back(digit);
            if(cmp(num, num2) == 0)
            {
                break;
            }
            // 剔除 num 后面的一个零
            num.pop_back();
        }
        // 根据 results 的结果组合出最终的商
        string res = "";
        for(int i = 0; i < results.size(); ++i)
        {
            res.push_back(results[i]+'0');
        }
        // 别忘了返回之前把符号给加上，如果前面 sign 计算出来是 -1 的话
        if(sign == -1)
        {
            res.insert(0, "-");
        }
        return res;
    };

    function<bool(const string&)> isStrobogrammatic = [&](const string& num) -> bool
    {
        unordered_map<char, char> mapping = {{'0', '0'}, {'1', '1'}, {'8', '8'}, {'9', '6'}, {'6', '9'}};
        // 之后就是和回文数判断中类似的双指针比较
        int left = 0, right = num.size()-1;
        while(left <= right)
        {
            if(mapping.find(num[left]) != mapping.end() && mapping[num[left]] == num[right])
            {
                ++left;
                --right;
            }
            else
            {
                return false;
            }
        }
        return true;
    };
    stringPair tmp(low, high);
    // 记忆化加速
    if(memo.find(tmp) != memo.end())
    {
        return memo[tmp];
    }
    // 不理解官方给出那种奇怪的解法的用意是什么，个人认为本题可以利用分治策略来简单解决
    // 不过由于传入的两个边界数据都是以字符串形式表示的数字，可能会需要重写一下字符串形式的数值比较的函数
    // 同时，为了对区间进行二分，我们还需要一个子过程用于求出 [low, high] 区间的两半小区间
    // 具体的，需要一个函数用于计算 ((high-low)>>1)+low
    // 基本情况
    // low == high
    // 此时可以直接判断这个值本身是不是一个中心对称数
    if(low == high)
    {
        return isStrobogrammatic(low) ? 1 : 0;
    }
    string mid = divide(add(low, high), "2");
    memo[tmp] = strobogrammaticInRange(low, mid) + strobogrammaticInRange(add(mid, "1"), high);
    return memo[tmp];
}

// 还是妥协了，用传统的 DFS 方法来进行暴搜了。。。
// 基本思路和 247 题一致，按长度进行暴力搜索
int strobogrammaticInRange(string low, string high)
{
    // 把之前的字符串整数比较函数拿过来用。。。
    function<int(const string&, const string&)> cmp = [&](const string& num1, const string& num2) -> int
    {
        // 如果二者的符号不同，那么我们有可能可以直接得出二者大小关系
        // 如果 num1 < 0，num2 > 0, 那么一定有 num1 < num2
        if(num1[0] == '-' && num2[0] != '-')
        {
            return -1;
        }
        // 如果 num1 > 0，num2 < 0，那么一定有 num1 > num2
        if(num1[0] != '-' && num2[0] == '-')
        {
            return 1;
        }
        // 如果 num1 < 0，num2 < 0，那么我们可以反过来比较它们的绝对值大小，并在前面乘上一个 -1 来修正大小关系
        if(num1[0] == '-' && num2[0] == '-')
        {
            // 返回相反值
            return -1 * cmp(num1.substr(1), num2.substr(1));
        }
        // 下面的情况中，num1 和 num2 都是正数
        // 先判断二者长度
        // 长度更大的那一个数字字符串显然代表一个更大的数字
        int m = num1.size(), n = num2.size();
        if(m > n)
        {
            return 1;
        }
        // 长度更短的那一个数字字符显然代表一个更小的数字
        if(m < n)
        {
            return -1;
        }
        // 剩下的情况下，二者的长度一定是相等的，我们此时可以简单地通过字典序比较来判断二者的大小关系
        // 暴论：长度相等的两个数字字符串，它们的字典序和正常数字的值大小关系是相等的
        if(num1 == num2)
        {
            return 0;
        }
        return num1 > num2 ? 1 : -1;
    };
    function<vector<string>(int, const int&)> dfs = [&](int len, const int& n) -> vector<string>
    {
        if(len == 0)
        {
            return {""};
        }
        if(len == 1)
        {
            vector<string> ret;
            // 分别判断三个可能结果是否在 [low, high] 区间中
            if(len < n || (cmp(low, "0") <= 0 && cmp(high, "0") >= 0))
            {
                ret.push_back("0");
            }
            if(len < n || (cmp(low, "1") <= 0 && cmp(high, "1") >= 0))
            {
                ret.push_back("1");
            }
            if(len < n || (cmp(low, "8") <= 0 && cmp(high, "8") >= 0))
            {
                ret.push_back("8");
            }
            return ret;
        }
        // 其它情况下，先利用和 247 题一样的方案把所有可能的情况进行检查，再检查每个检出的结果是否存在于给定的范围区间内(注意这个检查应该只在当前位数等于 n 的时候进行)
        vector<string> subStr = dfs(len-2, n);
        vector<string> res;
        for(int i = 0; i < subStr.size(); ++i)
        {
            if(len != n)
            {
                res.push_back("0"+subStr[i]+"0");
            }
            // 如果 len == n，此时需要判断组合出来的结果是否在 [low, high] 区间内
            // 这个流程可以通过我们前面两版中的比较函数来实现
            string nxt = "1"+subStr[i]+"1";
            if(len < n || (cmp(low, nxt) <= 0 && cmp(high, nxt) >= 0))
            {
                res.push_back(nxt);
            }
            nxt = "8"+subStr[i]+"8";
            if(len < n || (cmp(low, nxt) <= 0 && cmp(high, nxt) >= 0))
            {
                res.push_back(nxt);
            }
            nxt = "6"+subStr[i]+"9";
            if(len < n || (cmp(low, nxt) <= 0 && cmp(high, nxt) >= 0))
            {
                res.push_back(nxt);
            }
            nxt = "9"+subStr[i]+"6";
            if(len < n || (cmp(low, nxt) <= 0 && cmp(high, nxt) >= 0))
            {
                res.push_back(nxt);
            }
        }
        // 返回结果即可
        return res;
    };
    // 进行调用，注意本题我们要找的仅仅是个数，所以最后返回的值需要做处理
    // 先获取 low 和 high 的字符串长度
    int m = low.size(), n = high.size();
    // 最终的结果个数
    int ans = 0;
    for(int i = m; i <= n; ++i)
    {
        ans += dfs(i, i).size();
    }
    return ans;
}

// 暴力 DFS + 记忆化数组
// 上面简单的暴力 DFS 可以通过，不过考虑到本题的测试数据可能数量都不是很大，我们最好还是进行一下记忆化加速
int strobogrammaticInRange(string low, string high)
{
    int m = low.size(), n = high.size();
    // 初始化足够个数的记忆化数组即可
    vector<vector<string>> memo(n+1, vector<string>());
    // 下面的逻辑主体和前一版是完全一样的，只是添加了记忆化的步骤
    // 把之前的字符串整数比较函数拿过来用。。。
    function<int(const string&, const string&)> cmp = [&](const string& num1, const string& num2) -> int
    {
        // 如果二者的符号不同，那么我们有可能可以直接得出二者大小关系
        // 如果 num1 < 0，num2 > 0, 那么一定有 num1 < num2
        if(num1[0] == '-' && num2[0] != '-')
        {
            return -1;
        }
        // 如果 num1 > 0，num2 < 0，那么一定有 num1 > num2
        if(num1[0] != '-' && num2[0] == '-')
        {
            return 1;
        }
        // 如果 num1 < 0，num2 < 0，那么我们可以反过来比较它们的绝对值大小，并在前面乘上一个 -1 来修正大小关系
        if(num1[0] == '-' && num2[0] == '-')
        {
            // 返回相反值
            return -1 * cmp(num1.substr(1), num2.substr(1));
        }
        // 下面的情况中，num1 和 num2 都是正数
        // 先判断二者长度
        // 长度更大的那一个数字字符串显然代表一个更大的数字
        int m = num1.size(), n = num2.size();
        if(m > n)
        {
            return 1;
        }
        // 长度更短的那一个数字字符显然代表一个更小的数字
        if(m < n)
        {
            return -1;
        }
        // 剩下的情况下，二者的长度一定是相等的，我们此时可以简单地通过字典序比较来判断二者的大小关系
        // 暴论：长度相等的两个数字字符串，它们的字典序和正常数字的值大小关系是相等的
        if(num1 == num2)
        {
            return 0;
        }
        return num1 > num2 ? 1 : -1;
    };
    function<vector<string>(int, const int&)> dfs = [&](int len, const int& n) -> vector<string>
    {
        if(!memo[len].empty())
        {
            return memo[len];
        }
        if(len == 0)
        {
            memo[0] = {""};
            return memo[0];
        }
        if(len == 1)
        {
            vector<string> ret;
            // 分别判断三个可能结果是否在 [low, high] 区间中
            if(len < n || (cmp(low, "0") <= 0 && cmp(high, "0") >= 0))
            {
                ret.push_back("0");
            }
            if(len < n || (cmp(low, "1") <= 0 && cmp(high, "1") >= 0))
            {
                ret.push_back("1");
            }
            if(len < n || (cmp(low, "8") <= 0 && cmp(high, "8") >= 0))
            {
                ret.push_back("8");
            }
            memo[1] = ret;
            return memo[1];
        }
        // 其它情况下，先利用和 247 题一样的方案把所有可能的情况进行检查，再检查每个检出的结果是否存在于给定的范围区间内(注意这个检查应该只在当前位数等于 n 的时候进行)
        vector<string> subStr = dfs(len-2, n);
        vector<string> res;
        for(int i = 0; i < subStr.size(); ++i)
        {
            if(len != n)
            {
                res.push_back("0"+subStr[i]+"0");
            }
            // 如果 len == n，此时需要判断组合出来的结果是否在 [low, high] 区间内
            // 这个流程可以通过我们前面两版中的比较函数来实现
            string nxt = "1"+subStr[i]+"1";
            if(len < n || (cmp(low, nxt) <= 0 && cmp(high, nxt) >= 0))
            {
                res.push_back(nxt);
            }
            nxt = "8"+subStr[i]+"8";
            if(len < n || (cmp(low, nxt) <= 0 && cmp(high, nxt) >= 0))
            {
                res.push_back(nxt);
            }
            nxt = "6"+subStr[i]+"9";
            if(len < n || (cmp(low, nxt) <= 0 && cmp(high, nxt) >= 0))
            {
                res.push_back(nxt);
            }
            nxt = "9"+subStr[i]+"6";
            if(len < n || (cmp(low, nxt) <= 0 && cmp(high, nxt) >= 0))
            {
                res.push_back(nxt);
            }
        }
        // 返回结果即可
        memo[len] = res;
        return memo[len];
    };
    // 进行调用，注意本题我们要找的仅仅是个数，所以最后返回的值需要做处理
    // 最终的结果个数
    int ans = 0;
    for(int i = m; i <= n; ++i)
    {
        memo = vector<vector<string>>(n+1, vector<string>());
        ans += dfs(i, i).size();
    }
    return ans;
}

// 第三版：如果想尝试的可以自己试着写一下 DP 的方案，这里实在懒得写了。。。