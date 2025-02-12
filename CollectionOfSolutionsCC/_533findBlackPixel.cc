#include "Solution.h"

int Leetcode501_600::Soltuion::findBlackPixel(vector<vector<char>>& picture, int target)
{
    // 一道理解比写代码难的题目。。
    // 转述一下题目的要求：
    // 1. 黑色像素所在的行和列黑色像素的总数都是 target 个
    // 2. 满足条件 1 的黑色像素所在的列上，对应列为黑色像素的行，内容上必须全部相同
    // 那么我们只需要根据要求使用哈希表记录和计算即可
    unordered_map<int, int> row;
    unordered_map<int, int> col;
    // 为了后续检查条件 2 方便，我们可以把每一行压缩成一个字符串存储为一个哈希表的键，而值存储它们属于的序号
    // 是的，这种逻辑有点像并查集
    unordered_map<string, int> mapping;
    // 二级映射，存储行序号-组号的映射
    unordered_map<int, int> secondMapping;
    // order 代表对应 "行特征字符串" 的映射序号，从 0 开始累加
    int order = 0;
    int m = picture.size(), n = picture[0].size();
    for(int i = 0; i < m; ++i)
    {
        string cur = "";
        for(int j = 0; j < n; ++j)
        {
            if(picture[i][j] == 'B')
            {
                ++row[i];
                ++col[j];
            }
            cur.push_back(picture[i][j]);
        }
        // 如果这个特征串没有记录过，那么累加 order，进行记录
        if(mapping.count(cur) == 0)
        {
            mapping[cur] = order;
            secondMapping[i] = order++;
        }
        secondMapping[i] = mapping[cur];
    }
    // 第二轮遍历，我们只检查对应行和列黑色像素相同的那些格子即可
    int res = 0;
    for(int i = 0; i < m; ++i)
    {
        // 不满足条件的行可以直接跳过不看
        if(row[i] != target)
        {
            continue;
        }
        for(int j = 0; j < n; ++j)
        {
            // 这一行的像素个数满足 target 个
            if(col[j] == target)
            {
                // 那么我们进一步检查对应列中所有为 'B' 的那些行是否完全相同
                // 这可以通过上面记录到 secondMapping 来进行
                bool valid = true;
                int check = secondMapping[i];
                for(int k = 0; k < m; ++k)
                {
                    if(picture[k][j] == 'B' && secondMapping[k] != check)
                    {
                        valid = false;
                        break;
                    }
                }
                if(valid)
                {
                    ++res;
                }
            }
        }
    }
    return res;
}