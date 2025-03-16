#include "Solution.h"

int Leetcode601_700::Soltuion::repeatedStringMatch(string a, string b)
{
    // KMP 算法运用题
    // 我们可以枚举 a 的不同倍数串，之后检查每一个倍数串是否是 b 的子串即可
    // 先设计 KMP 算法的代码
    // next 数组，用于记录每一个 a 的倍数串的前缀信息
    vector<int> next;
    function<void(const string&)> getNext = [&](const string& t) -> void
    {
        // 重建 next 数组元素，大小为 t 的大小
        // 先清空原信息
        next.clear();
        next.resize(t.size());
        // 如果第一个字符无法匹配，那么我们用 -1 代表需要同时后移母串和匹配串的指针
        next[0] = -1;
        // j 用于填写 next 数组，k 代表可以匹配的下标
        int j = 0, k = -1, n = t.size();
        while(j < n)
        {
            if(k == -1 || t[j] == t[k])
            {
                // 此时 t[j-k, j] 和 t[0, k] 可以匹配，我们可以对
                // next[j+1] 进行赋值了
                // 当 s[i] 与 t[j+1] 无法匹配时，我们可以把 j+1 这个下标挪到 k+1 处
                ++j; ++k;
                // j+1 可能会等于 n，我们需要加一步判断
                if(j < n)
                {
                    // 而如果回溯到的那个字符本身就等于 t[j]，那么我们即便回溯回去，也没法匹配，所以进行递归赋值
                    if(t[k] == t[j])
                    {
                        next[j] = next[k];
                    }
                    else
                    {
                        next[j] = k;
                    }
                }
            }
            // t[j] 和 t[k] 没法匹配，我们只能递归回溯 k 值
            else
            {
                k = next[k];
            }
        }
        // 填写完成
    };  
    // KMP 函数
    // 寻找 t 在 s 中出现的起始下标，如果不存在，就返回 -1
    function<int(const string&, const string&, vector<int>&)> KMP = [&](const string& s, const string& t, vector<int>& next) -> int
    {
        int i = 0, j = 0, n = t.size(), m = s.size();
        while(i < m)
        {
            if(j == -1 || s[i] == t[j])
            {
                // j == -1 代表需要同步后移两个指针
                // s[i] == t[j] 的话，我们也可以后移两个指针，进一步匹配
                ++i; ++j;
                // 如果 j == n，说明我们匹配完了，返回 i-n 作为起始下标
                if(j == n)
                {
                    return i-n;
                }
            }
            else
            {
                // 没法匹配，我们需要回溯 j，继续尝试将 s[i] 和 t[next[j]] 匹配
                j = next[j];
            }
        }
        // 没找到匹配下标，返回 -1 即可
        return -1;
    };
    // 写好了 KMP 算法，我们只需要调用它即可
    // 遍历 a 的每一种倍数串
    int time = 1, aLen = a.size(), bLen = b.size();
    string t = a, s = b;
    getNext(s);
    while(true)
    {
        if(KMP(t, s, next) != -1)
        {
            return time;
        }
        if(t.size() > aLen+bLen)
        {
            return -1;
        }
        ++time;
        t += a;
    }
    return -1;
}