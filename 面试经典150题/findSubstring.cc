#include <iostream>

class Solution
{
public:
    vector<int> findSubstring(string s, vector<string>& words)
    {
        // 可以用滑动窗口来解决这个问题
        // 拿题目中的示例一来举例：
        // s = "barfoothefoobarman", words = ["foo", "bar"]
        // 那么我们可以先看一下 words 中的各个单词
        // 每个单词的长度均为 3
        // 我们可以把 s 拆分成多个长度为 3 的 "子部分"
        // 之后用长度为 6 (3x2) 的窗口在 s 上进行滑动
        // 每次移动去掉最左侧的长度为 3 的 "子部分"，加上最右侧的长度为 3 的 "子部分"
        // 并用一个哈希表来记录每一种 "子部分" 出现的次数
        // 再用一个额外的变量记录总距离，如果总距离为 0，那么就认为我们找到了一个合适的开始索引
        // 不过我们可能会需要考虑一下 "滑动开始点"
        // 对于上面这个样例，我们只需要从 0-2 这三个起点开始窗口遍历即可
        // 也就是，只需要从 [0, words[0].size()-1] 这些下标开始窗口遍历即可
        // 先处理 diff 变量，用于记录 words 与 当前窗口中单词的 "距离"
        int diff = 0, n = s.size();
        unordered_map<string, int> memo;
        vector<int> res;
        // 用一个固定变量记录 words 中所有单词的总长度
        const int len = words[0].size() * words.size();
        for(const auto& word : words)
        {
            // 如果当前 word 是第一次出现，我们更新 diff
            if(memo.find(word) == memo.end())
            {
                ++diff;
            }
            // 记录当前 word 出现过一次
            ++memo[word];
        }
        // 处理完成，我们可以考虑开始执行滑动窗口了，不过我们可能需要在每一轮开始都复制一份 memo 的副本来使用
        // 对于每一轮滑动，我们先在最外层循环选定起始点
        // 注意：如果某个 start 后面剩余的长度不到 len 了，那么我们就可以退出循环了
        for(int start = 0; start < words[0].size() && start+len <= n; ++start)
        {   
            unordered_map<string, int> tmp = memo;
            // diff 也要复制一份
            int cnt = diff;
            // 开始滑动窗口
            // 首先是第一个窗口
            for(int i = 0; i < words.size(); ++i)
            {
                string str = s.substr(start+i*words[0].size(), words[0].size());
                // 判断当前 str 是否在 words 中
                if(tmp.find(str) != tmp.end())
                {
                    // 如果在 words 中，那么我们修改 tmp 对应字段的值
                    if(--tmp[str] == 0)
                    {
                        --cnt;
                    }
                    // 而如果 tmp[str] 在减少 1 后变成了负数，我们还需要把 diff 再增加 1
                    if(tmp[str] == -1)
                    {
                        ++cnt;
                    }
                }
            }
            // 处理完第一个窗口后，我们先判断此时 diff 是否为 0
            // 如果是，那么就把 start 记录到答案中
            if(cnt == 0)
            {
                res.push_back(start);
            }
            // 之后开始滑动窗口
            for(int i = start; i+len <= n; i += words[0].size())
            {
                // 先去掉最左侧的 "子部分"
                string left = s.substr(i, words[0].size());
                if(tmp.find(left) != tmp.end())
                {
                    // 把 tmp[left] 加 1
                    if(++tmp[left] == 1)
                    {
                        ++cnt;
                    }
                    if(tmp[left] == 0)
                    {
                        --cnt;
                    }
                }
                // 之后是加上右侧新的 "子部分"
                // 如果没法添加了，我们就结束循环
                string right = s.substr(i+len, words[0].size());
                if(right.size() < words[0].size())
                {
                    break;
                }
                if(tmp.find(right) != tmp.end())
                {
                    if(--tmp[right] == 0)
                    {
                        --cnt;
                    }
                    if(tmp[right] == -1)
                    {
                        ++cnt;
                    }
                }
                if(cnt == 0)
                {
                    res.push_back(i+words[0].size());
                }
            }
        }
        return res;
    }
};