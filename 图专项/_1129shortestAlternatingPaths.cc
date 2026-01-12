class Solution
{
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges)
    {
        // 看到题目描述中出现了 ”最短路径“，应该条件反射一样想到 BFS
        // 同时题目要求 “红蓝交替”，所以我们可以引入一个状态信息 -> 带状态限制的 BFS 遍历
        // 即：当前需要从 blueEdges 中找一条边 / 当前需要从 redEdges 中找一条边
        // 最后，因为题目要求返回的是路径长度信息，我们可以保存一个 int 数组用于记录遍历的路径长度，默认都是 -1（不可达）
        vector<int> lengths(n, -1);
        // 读题不仔细，本题的边表需要转储。。
        unordered_map<int, vector<int>> reds;
        unordered_map<int, vector<int>> blues;
        for(const auto& red : redEdges)
        {
            reds[red[0]].push_back(red[1]);
        }
        for(const auto& blue : blueEdges)
        {
            blues[blue[0]].push_back(blue[1]);
        }

        function<void(int)> bfs = [&](int color) -> void
        {
            // 记录各个节点是否：
            // 由一条蓝色边访问过来过
            // 由一条红色边访问过来过
            vector<bool> blueVisited(n, false);
            vector<bool> redVisited(n, false);
            // q 用于进行 BFS 遍历，记录当前层节点信息
            queue<int> q;
            // 最开始，我们在节点 0
            // path 中也要记录对应的最短路径长度
            q.push(0);
            // 0 号节点结果直接确认为 0
            lengths[0] = 0;
            // 记录当前应该检查哪种颜色的边，最开始默认是红色边 (0)，蓝色边对应值为 1
            int steps = 1;            
            // 进行 BFS 遍历
            while(!q.empty())
            {
                int n = q.size();
                for(int i = 0; i < n; ++i)
                {
                    int cur = q.front();
                    q.pop();
                    // cout << cur << ": " << lengths[cur] << " ";
                    // cout << color << endl;
                    // 检查 cur 节点后续的对应颜色边
                    if(color == 0)
                    {
                        // 把对应红色边数组中的下一跳节点保存到队列中，之后更新对应 cur 节点的最短路径长度
                        for(const int& nxt : reds[cur])
                        {
                            // 跳过已经确认过最短路径的节点
                            if(redVisited[nxt])
                            {
                                continue;
                            }
                            // cout << nxt << " ";
                            q.push(nxt);
                            lengths[nxt] = lengths[nxt] == -1 ? steps : min(lengths[nxt], steps);
                            redVisited[nxt] = true;
                        }
                        // cout << endl;
                    }
                    else
                    {
                        for(const int& nxt : blues[cur])
                        {
                            // 跳过已经确认过最短路径的节点
                            if(blueVisited[nxt])
                            {
                                continue;
                            }
                            // cout << nxt << " ";
                            q.push(nxt);
                            lengths[nxt] = lengths[nxt] == -1 ? steps : min(lengths[nxt], steps);
                            blueVisited[nxt] = true;
                        }
                        // cout << endl;
                    }
                }
                // cout << endl;
                color = 1 ^ color;
                ++steps;
            }
        };
        bfs(0);
        bfs(1);
        // 返回结果即可
        return lengths;
    }
};