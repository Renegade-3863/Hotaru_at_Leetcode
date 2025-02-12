#include "Solution.h"

vector<vector<string>> Leetcode601_700::Soltuion::findDuplicate(vector<string>& paths)
{
    // 没什么价值的哈希表模拟题，我们按照题目要求做就行了
    // 当前如果你想手搓哈希表的实现，那我也没意见
    // 审题：一组重复的文件至少包括两个具有完全相同 "文件内容" 的文件
    // 注意，这里的 "文件内容相同" 并不意味着两个文件的文件名也要相同
    // 我们只需要确保两个文件内的内容 (也就是括号中的内容) 相同即可
    // 不过检查的时候，我们可能会需要一些标记位来确保我们找到的不是文件名中的括号，那样的话会导致我们检查出错误的文件内容
    // 首先初始化一个哈希表，用于存储 [content, {file} ] 关系对
    // 即：某段内容属于那些文件
    unordered_map<string, vector<string>> mapping;
    // 之后对 paths 中的每一个字符串进行解析
    for(const auto& path : paths)
    {
        // 对当前 path 进行解析
        // 我们调用 find 函数 (使用 KMP 实现的功能性函数，这里不再自己写了。。)
        // 找出 path 中那个分隔的单一空格的位置
        int sep = path.find(" ", 0);
        // 防御性编程
        // 如果某个 path 中没有找到任何合法的分隔空格，那么这组 paths 数组就是无效的，我们直接返回空数组即可
        if(sep == -1)
        {
            return {};
        }
        int sep1 = sep, sep2 = sep;
        // 规定 sep1 和 sep2，分别指向每个 .txt 后缀和 ')' 的位置
        string directory = path.substr(0, sep);
        while(sep1 != -1 && sep2 != -1)
        {
            // 否则，sep 找到了，sep 前面的是文件路径，sep 后面的是文件名和括号中的具体内容
            // 我们在 sep 后面的部分寻找第一个 .txt 后缀名的下标，这个位置就是文件结束的位置
            sep1 = path.find(".txt", sep);
            // 依然是防御性编程
            if(sep1 == -1)
            {
                break;
            }
            // 否则，sep1 找到了，sep1 后面的第一个右括号前的部分就是文件的内容
            // 或者，如果存储的格式都是合法的，直到倒数第二个字符之前到部分元素
            sep2 = path.find(")", sep1);
            if(sep2 == -1)
            {
                break;
            }
            // 提取出对应部分的内容，存到哈希表中
            string content = path.substr(sep1+5, sep2-sep1-5);
            mapping[content].push_back(directory+"/"+path.substr(sep+1, sep1-sep+3));
            sep = path.find(" ", sep2);
        }
    }
    // 整体处理完成，我们再遍历一轮哈希表，把每一个 content 对应数组中元素个数不小于 2 的部分都提出来
    vector<vector<string>> res;
    int idx = 0;
    for(const auto& [k, v] : mapping)
    {
        if(v.size() > 1)
        {
            res.push_back(vector<string>());
            for(const auto& dir : v)
            {
                res[idx].push_back(dir);
            }
            ++idx;
        }
    }
    return res;
}   