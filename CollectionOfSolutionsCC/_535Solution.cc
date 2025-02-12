#include "Solution.h"

// 回顾字符串哈希的基本公式：
// hash(s) = s1 * p
string Leetcode501_600::Soltuion::encode(string longUrl)
{
    // 加密过程，用字符串哈希的方法进行
    // 根据 longUrl 的字符进行哈希值计算，利用线性算法避免哈希冲突
    // 如果已经记录过这个 longUrl 的哈希值，那么直接返回对应结果即可
    if(this->memo.count(longUrl))
    {
        return string("http://tinyurl.com/") + to_string(this->memo[longUrl]);
    }
    // 否则，这个 longUrl 没有被计算过，我们利用它的每一个字符进行滚动哈希计算
    // long long 类型，防止溢出
    // power 记录 p 的指数值，第一位是 1，之后逐渐增加
    long long hashVal = 0, power = 1;
    for(const char& c : longUrl)
    {
        hashVal = (hashVal+power*c) % MOD;
        power = (power * p) % MOD;
    }
    // 如果发生哈希冲突，线性后移，避免冲突
    while(mapping.count(hashVal))
    {
        hashVal = (hashVal+1)%MOD;
    }
    // 记录映射关系
    mapping[hashVal] = longUrl;
    memo[longUrl] = hashVal;
    return string("http://tinyurl.com/") + to_string(hashVal);
}

string Leetcode501_600::Soltuion::decode(string shortUrl)
{
    // 从后往前遍历 shortUrl，找出第一个反斜线的下标，这个下标右侧就是我们用 longUrl 生成的哈希值
    int idx = shortUrl.size()-1;
    while(shortUrl[idx] != '/')
    {
        --idx;
    }
    int hashVal = stoi(shortUrl.substr(idx+1, (shortUrl.size()-idx-1)));
    return mapping[hashVal];
}