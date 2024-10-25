#include "Solution.h"

string Leetcode201_300::Solution::Codec::encode(vector<string>& strs)
{
    // 这道题感觉很像是 Google 会出的题，毕竟 protobuf 就是 Google 开发的高效网络传输协议。。。
    // 我们考虑如何把一串独立的文本转换成一个字符串进行发送
    // 我们需要一种机制，使得在接收方能够正确拆分出发送方原有的单词结构
    // 最简单的方法是定义一种绝对不会在发送数据中出现的特殊字符
    // 不过实际的网络传输中，肯定不会是这么简单的组合方法，而且这种方法的限制太多，也不适用于真正的网络传输
    // 考虑一种新的方法
    // 我们计算 strs 中每个 str 的长度，把这个长度值转换成定长的字符串 (例如，限制为4位字符串) 放到原来 str 的前面，再把这个字符串组合到最终的发送字符串中
    // 之后在接收端，我们只需要按协议规定，先读四位的长度，之后按长度值读取对应子串，之后以此类推直到读取完成整份数据为止
    // 不过，这种方式有一个隐性要求：每个 str 都不能超过四位数可以表示的长度，即不能不小于 10000 个字符
    // 明确了这种方案，就可以开始写代码了
    // 代表每个子串的长度的字符串
    string len = "";
    // 结果字符串
    string res = "";
    int n = strs.size();
    for(int i = 0; i < n; ++i)
    {
        // 重置 len 字符串
        len = "";
        len += to_string((int)strs[i].size());
        // 长度串长度不足4的部分补上零
        while(len.size() < 4)
        {
            len.insert(0, "0");  
        }
        res += len;
        res += strs[i];
    }
    return res;
}

vector<string> Leetcode201_300::Solution::Codec::decode(string s)
{
    // 对称地进行字符串拆分即可
    int m = s.size();
    int idx = 0;
    // 存储解码后的字符串
    vector<string> res;
    // 存储每个解码出来的子串
    string nxt = "";
    while(idx < m)
    {
        nxt = "";
        // 每次先走四位，找出长度串
        int len = 0;
        for(int i = 0; i < 4; ++i)
        {
            len = len*10+(s[idx++]-'0');
        }
        // 根据长度读取后面的字符串
        for(int i = 0; i < len; ++i)
        {
            nxt.push_back(s[idx++]);
        }
        res.push_back(nxt);
    }
    // 解析完成，返回结果即可
    return res;
}