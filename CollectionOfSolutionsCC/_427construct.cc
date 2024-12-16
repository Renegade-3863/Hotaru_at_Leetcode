/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

#include "Solution.h"

Node* Leetcode401_500::Solution::construct(vector<vector<int>>& grid)
{
    // 很经典的递归类问题，我们需要考虑的就是如何标记一个矩形区域，以及如何递归地进行标记和结点创建
    // 我们可以采用对顶点标记的方法来标记一个矩形区域
    // 具体地，记录一个矩形的左下顶点和右上顶点就可以记录这个矩形本身
    // 之后，考虑如何递归地进行题目要求的转化过程
    // 我们可以定义一个递归回调函数
    // 递归函数定义为：把 (x1, y1)，(x2, y2) 两点代表的矩形区域转换成一棵四叉树进行存储
    // 返回这个生成的四叉树的根结点
    function<Node*(int, int, int, int)> subConstruct = [&](int x1, int y1, int x2, int y2) -> Node* 
    {
        // 递归结束情况，整个矩形区域只有一个格子
        if(x1 == x2 && y1 == y2)
        {
            // 这个结点一定是叶子了
            return new Node(grid[x1][y1], true);
        }
        // 我们需要对整个矩形区域进行一些检查，来决定要怎么处理这个区域
        // 检查开始前，我们先记录一个值，它们分别代表这个矩形区域内的值为全1，全0，或者均不是
        // 1 代表全 1
        // 0 代表全 0
        // 2 代表均不是
        int status = grid[x1][y1];
        // 遍历整个区域进行检查
        for(int i = x1; i <= x2; ++i)
        {
            for(int j = y1; j <= y2; ++j)
            {
                // 通过异或就能判断这个矩形区域内值的属性
                if(status ^ grid[i][j])
                {
                    // 出现了不同值，那么最后状态值一定是 2，可以提前退出循环
                    status = 2;
                    break;
                }
                // 否则，我们需要继续进行检查
            }
        } 
        // 检查结束，根据 status 值决定我们的下一步操作
        if(status == 2)
        {
            // 需要进一步递归操作，我们新建一个四叉树结点，递归它的四个子区域
            Node* newNode = new Node(1, false);
            newNode->topLeft = subConstruct(x1, y1, ((x2-x1)>>1)+x1, ((y2-y1)>>1)+y1);
            newNode->bottomLeft = subConstruct(((x2-x1)>>1)+x1+1, y1, x2, ((y2-y1)>>1)+y1);
            newNode->topRight = subConstruct(x1, ((y2-y1)>>1)+y1+1, ((x2-x1)>>1)+x1, y2);
            newNode->bottomRight = subConstruct(((x2-x1)>>1)+x1+1, ((y2-y1)>>1)+y1+1, x2, y2);
            return newNode;
        }
        // 否则，已经是一个叶子结点，我们直接根据 status 进行结点构造即可
        Node* newNode = new Node(status, true);
        return newNode;
    };
    // 对 grid 代表的最大矩阵调用上面的函数即可
    int m = grid.size(), n = grid[0].size();
    return subConstruct(0, 0, m-1, n-1);
}