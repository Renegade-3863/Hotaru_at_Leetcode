#include "Solution.h"

string Leetcode401_500::Soltuion::validIPAddress(string queryIP)
{
    // 字符串模拟题，按题目给出的 IP 地址格式进行检验即可
    // 我们对整个字符串进行遍历
    // 在开始实际的遍历之前，我们可以先进行一下预处理，检查一下这可能是一个 IPv4 还是一个 IPv6
    // 同样是通过遍历的方式
    // type == 1 代表可能是一个 IPv4
    // type == -1 代表可能是一个 IPv6
    int type = 0;
    queryIP.push_back('#');
    // cout << queryIP << endl;
    string first;
    function<bool(char)> valid = [&](char c) -> bool
    {
        return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    };
    for(const auto& c : queryIP)
    {
        if(c == '.')
        {
            type = 1;
            break;
        }
        if(c == ':')
        {
            type = -1;
            break;
        }
        // 这里也可以提前筛掉一些一定不合法的字符串
        if(!isdigit(c) && !valid(c))
        {
            return "Neither";
        }
        first.push_back(c);
        if(first.size() > 4)
        {
            return "Neither";
        }
    }
    // 如果没有检出可能的类型，直接返回 false 即可
    if(type == 0)
    {
        return "Neither";
    }
    // 用于记录当前被分割出来的子数据
    string cur;
    // 用于记录子节数量和分隔符数量
    int cntSeg = 0;
    for(const auto& c : queryIP)
    {
        // 对于每一个字符，我们分情况进行讨论
        // 可能有以下几种情况
        // 1. 前面确定了这可能是一个 IPv4
        if(type == 1)
        {
            // 1.1 c 是非数字字符，并且不是点号
            // 此时直接判定不合法即可
            if(!isdigit(c) && c != '.' && c != '#')
            {
                return "Neither";
            }
            // 1.2 c 是数字字符
            // 那么先添加到 cur 中
            else if(c != '.' && c != '#')
            {
                // 如果 cur 有前导零，或者长度已到了 3，那么直接返回 "Neither"
                if(cur == "0" || cur.size() == 3)
                {
                    return "Neither";
                }
                // 否则，正常添加
                cur.push_back(c);
            }
            // 1.3 c 是个点号，或者是最后的结束符
            else
            {
                if(cur.size() == 0)
                {
                    return "Neither";
                }
                // 那么我们需要判断这个截出来的数是不是在 [0, 255] 之间的数
                // 这里我们可以取巧一下，因为这个范围不大，所以没必要再写一个大数比较函数
                // 转化成数字进行比较即可
                int num = 0;
                for(int i = 0; i < cur.size(); ++i)
                {
                    num = num*10+(cur[i]-'0');
                }
                // cout << num << endl;
                // 负数实际上已经在符号部分被过滤掉了，不用考虑了
                if(num > 255)
                {
                    return "Neither";
                }
                // 否则，可以继续判断，不过需要先把 cur 重置
                cur = "";
                // 节数不对了，返回不合法
                if(++cntSeg > 4)
                {
                    return "Neither";
                }
            }
        }
        // 2. 前面确定了这可能是一个 IPv6
        else
        {
            // 1.1 这个字符是一个数字字符，或者是一个 'a'-'f' 或 'A'-'F' 之间的字符
            // 可以进行添加，但要判断子节长度
            if(isdigit(c) || valid(c))
            {
                cur.push_back(c);
                // 长度超出了限制，直接返回即可
                if(cur.size() > 4)
                {
                    return "Neither";
                }
            }
            // 1.2 这个字符既不是一个数字字符，也不是一个 'a'-'f' 和 'A'-'F' 之间的字符
            // 那么除非它是个冒号，或者是最后的结束符，不然都要直接返回
            else if(c == ':' || c == '#')
            {
                if(cur.size() == 0)
                {
                    return "Neither";
                }
                // 如果是个冒号，那么我们记录子节个数，同时重置 cur
                cur = "";
                if(++cntSeg > 8)
                {
                    return "Neither";
                }
            }
            else
            {
                return "Neither";
            }
        }
    }
    if(type == 1 && cntSeg == 4)
    {
        return "IPv4";
    }
    if(type == -1 && cntSeg == 8)
    {
        return "IPv6";
    }
    return "Neither";
}