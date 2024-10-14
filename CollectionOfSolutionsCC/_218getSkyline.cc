#include "Solution.h"

vector<vector<int>> Leetcode201_300::Solution::getSkyline(vector<vector<int>>& buildings)
{
    // 本题可以用线段树这种高效的维护动态区间最值/和值的数据结构来完成
    // 我们正好借机会复习一波这种几乎只有在竞赛中才会用到的数据结构
    // 暴力的解法就不写了，对于一个大的常规区间进行维护，需要很多的重复最值修改，因而并不那么高效
    // 使用的数据结构和方法都是上面定义过的
    // 第一步，对 buildings 数组进行处理，拿出所有建筑的左右边界值，之后进行映射计算
    // 存储映射关系的哈希表
    unordered_map<int, int> mapping;
    // 存储所有分立值的数组
    vector<vector<int>> ans;
    for(int i = 0; i < buildings.size(); ++i)
    {
        ans.push_back(buildings[i][0]);
        ans.push_back(buildings[i][1]);
    }
    // 之后处理这个 ans 数组，先进行排序和去重
    sort(ans.begin(), ans.end());
    // 之后是 C++ STL 常用的数组去重策略
    // unique(ans.begin(), ans.end()) 代表的是把一个有序数组中唯一的部分提到数组开头，返回一个指向最后一个不重复的元素之后的第一个元素的迭代器，我们可以利用这个迭代器执行元素的删除
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    // 现在我们拿到了所有分立元素，下一步就是建立映射了
    for(int i = 0; i < ans.size(); ++i)
    {
        mapping[ans[i]] = i+1;
    }
    // 之后就只需要执行线段树相关的操作了
    // 从序号1开始构建这棵线段树
    int n = ans.size();
    build(1, 1, n);
    // 之后需要根据给定的 buildings 数组对区间进行数值修改
    for(int i = 0; i < buildings.size(); ++i)
    {
        // 注意我们最开始说过的内容，每个建筑的最右侧边界高度不能计入天际线的考虑范围，所以这里我们给右边界进行-1操作，再进行映射
        update(1, mapping[buildings[i][0]], mapping[buildings[i][1]]-1, buildings[i][2]);
    }
    // 更新完成后，我们只需要针对每个分立的下标值进行一次查询，检查这个下标处的最高高度值即可
    // 根据对天际线定义的观察，我们不难发现，只要某两个分立值处的最大高度出现了变化，那么久一定会出现对应的结果坐标，我们只需要相应地进行记录即可
    vector<int> res;
    // 记录前一个分立下标处的最大高度值
    // 初始值为 0
    int maxv = 0;
    for(int i = 0; i < buildings.size(); ++i)
    {
        int x = query(1, mapping[ans[i]]);
        if(maxv != x)
        {
            // 记录高度即可
            res.push_back({ans[i], x});
        }
        // 根据 maxv 的定义对其进行更新
        maxv = x;
    }
    // 找完了，返回结果即可
    return res;
}