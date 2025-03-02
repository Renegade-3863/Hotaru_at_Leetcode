#include "Solution.h"

// 很麻烦的一道题，这里就不自己写了，拿题解区一个看着还不错的题解来写一下注解了。。
// 这里感谢 jklp2 大佬的题解：
// https://leetcode.cn/problems/design-excel-sum-formula/solutions/514424/jian-shuang-xiang-tu-by-jklp2-8jam/

// 创建一个抽象数据结构，用来表示 "一个格子" 的相关信息
struct node
{
    int val;
    vector<node*> come; // 记录当前 node 的值由哪些其它结点计算而来
    vector<node*> from; // 记录哪些 node 参与了哪些结点值的计算
    node(int _val = 0) : val(_val) {}
};

// 按题目限制，划定一个 30x30 的矩阵区域
node* matrix[30][30];

Leetcode601_700::Soltuion::Excel::Excel(int height, char width)
{
    this->m = height, this->n = width-'A'+1;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            matrix[i][j] = new node();
        }
    }
}

void Leetcode601_700::Soltuion::Excel::set(int row, char column, int val)
{
    int i = row-1, j = column-'A';
    // clear 函数，用于清除所有和当前值有关的其它 sum 计算式
    // 这是题目本身的要求
    clear(matrix[i][j]);
    // 把之前记录过的，当前所有和这个格子有关的 sum 关系都累加到 value 中，重新赋值给 matrix[i][j]
    // 但我们前面已经做了 clear，所以这里就只会把 val 赋值给 matrix[i][j]
    update(matrix[i][j], val);
}

int Leetcode601_700::Soltuion::Excel::get(int row, int column)
{
    int i = row-1, j = c-'A';
    return matrix[i][j]->val;
}

int Leetcode601_700::Soltuion::Excel::sum(int row, char column, vector<string> numbers)
{
    int x = row-1, y = column-'A';
    // 新求和公式需要覆盖旧的，调用 clear 清除相关的关系
    clear(matrix[x][y]);
    int ret = 0;
    for(string number : numbers)
    {
        vector<int> anchor = translate(number);
        for(int i = anchor[0]; i <= anchor[2]; ++i)
        {
            for(int j = anchor[1]; j <= anchor[3]; ++j)
            {
                matrix[x][y]->come.push_back(matrix[i][j]);
                matrix[i][j]->from.push_back(matrix[x][y]);
                ret += matrix[i][j]->val;
            }
        }
    }
    update(matrix[x][y], ret);
    return ret;
}

vector<int> translate(string s)
{
    vector<int> ret;
    for(int i = 0; i < s.size(); ++i)
    {
        // 这是一个区间，那么解析出对应的范围
        if(s[i] == ':')
        {
            auto a = helper(s.substr(0, i));
            ret.push_back(a.first);
            ret.push_back(a.second);
            a = helper(s.substr(i+1));
            ret.push_back(a.first);
            ret.push_back(a.second);
            return ret;
        }
    }
    // 否则，这是单一的格子
    auto a = helper(s);
    return {a.first, a.second, a.first, a.second};
}

pair<int, int> helper(string str)
{
    pair<int, int> ret;
    ret.second = str[0]-'A';
    ret.first = stoi(s.substr(1))-1;
    return ret;
}

void clear(node* cur)
{
    // 把所有被我修改过的结点，记录的 "我被 cur 修改过" 的记录清除掉
    for(auto c : cur->come)
    {
        auto it = come->f.begin();
        while(*it != cur)
        {
            ++it;
        }
        c->f.erase(it);
    }
    // 清除掉 cur 修改过的所有记录
    cur->come.clear();
}

void update(node* t, int val)
{
    int ori = t->val;
    queue<node*> q;
    q.push(t);
    while(!q.empty())
    {
        node* cur = q.front();
        q.pop();
        cur->val += ori;
        for(auto f : cur->from)
        {
            q.push(f);
        }
    }
}