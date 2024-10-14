#include "Solution.h"

vector<string> Leetcode201_300::Solution::findWords(vector<vector<char>>& board, vector<string>& words)
{
    int m = board.size(), n = board[0].size();
    // 本题要求我们找到一个字符二维表格中是否存在路径值等于某个单词组中的一个单词
    // 并输出所有存在的单词
    // 其实这种问题第一反应应该是回溯，至于字典树的解法，我们可以后面再写
    // 对于每个单词，我们对整个二维表格中的所有位置进行回溯查找
    // 如果找到了对应的单词，就把结果添加到答案数组中即可
    // 写一个 backtrack 函数，用于找出以某个下标开始，是否存在某个字符子串
    // 规定递归的四个方向
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    function<bool(int, int)> isValid = [&](int x, int y) -> bool 
    {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    // 回溯过程记录路径
    string path = "";
    // 全局的答案数组
    vector<string> res;
    function<bool(int, int, string)> backtrack = [&](int x, int y, string subString) -> bool
    {
        // 递归的结束步：
        // 如果要找的是一个空字符串，那么显然我们可以直接返回 true，因为我们明显可以从任何一个大小正常的二维字符表格中找出一个空字符串
        if(subString.size() == 0)
        {
            // 把路径添加到答案中
            res.push_back(path);
            return true;
        }
        // 递归步骤
        // 先尝试检查当前字符是否等于 subString 的第一个字符是否相同
        // 如果不相同，就可以结束递归了
        if(board[x][y] != subString[0])
        {
            return false;
        }
        // 否则，是相同的，我们可以继续检查 subString 的下一个字符
        // 需要向四个方向进行深入
        for(int i = 0; i < 4; ++i)
        {
            int nextx = x+dirs[i][0], nexty = y+dirs[i][1];
            // 需要一个方法来判断下一个坐标 (nextx, nexty) 是否是合法的
            // 在前面定义一下即可
            if(isValid(nextx, nexty))
            {
                // 进行递归
                path += subString[0];
                backtrack(nextx, nexty, subString.substr(1));
                // 回溯
                path = path.substr(0, path.size()-1);
            }
        }
    };
    // 调用时，我们只需要遍历整个 words 数组，然后从 board 的整个表上挨个位开始回溯查找即可
    int cnt = words.size();
    for(int k = 0; k < cnt; ++k)
    {
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                backtrack(i, j, words[k]);
            }
        }
    }
    // 返回结果即可
    return res;
}

struct TrieNode {
public:
    bool isEnd;
    unordered_map<char, unique_ptr<TrieNode>> mapping;
    TrieNode() : isEnd(false) {}
    ~TrieNode() = default;

    void insert(string word)
    {
        TrieNode* cur = this;
        for(const char& c: word)
        {
            if(cur->mapping.find(c) == cur->mapping.end())
            {
                cur->mapping[c] = make_unique<TrieNode>();
            }
            cur = cur->mapping[c].get();
        }
        cur->isEnd = true;
    }
};
vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    int m = board.size(), n = board[0].size();
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    TrieNode* node = new TrieNode();
    function<bool(int, int)> isValid = [&](int x, int y) -> bool
    {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    string path = "";
    vector<string> res;
    for(int i = 0; i < words.size(); ++i)
    {
        node->insert(words[i]);
    }
    function<void(int, int, TrieNode*)> backtrack = [&](int x, int y, TrieNode* node)
    {
        if(node->mapping.find(board[x][y]) == node->mapping.end()) 
        {
            return;
        }
        TrieNode* rem = node;
        node = node->mapping[board[x][y]].get();
        if(node->isEnd)
        {
            res.push_back(path);
            node->isEnd = false;
        }
        if(path.size() >= 10)
        {
            return;
        }
        if(node->mapping.empty())
        {
            rem->mapping.erase(board[x][y]);
            return;
        }
        // 否则，继续进行递归
        for(int k = 0; k < 4; ++k)
        {
            int nextx = x+dirs[k][0], nexty = y+dirs[k][1];
            char ch = board[x][y];
            board[x][y] = '#';
            if(isValid(nextx, nexty) && board[nextx][nexty] != '#')
            {
                path.push_back(board[nextx][nexty]);
                backtrack(nextx, nexty, node);
                path.pop_back();
            }
            board[x][y] = ch;
        }
    };
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            path.push_back(board[i][j]);
            backtrack(i, j, node);
            path.pop_back(); 
        }
    }
    delete node;
    return res;
}