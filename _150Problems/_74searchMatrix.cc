class Solution
{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        // 矩阵转树形式的二分查找问题
        // 我们可以这样简化搜索复杂度：
        // 从矩阵的右上角位置 (0, n-1) 开始
        // 如果 matrix[i][j] == target，那么直接返回 true
        // 否则，如果 matrix[i][j] > target，那么我们便可以断定：matrix[i+1][j] 到 matrix[m-1][j] 的所有元素均大于 target
        // 此时把 j 减 1 即可
        // 如果 matrix[i][j] < target，那么我们便可以断定：matrix[i][0] 到 matrix[i][j] 的所有元素均小于 target
        // 此时把 i 加 1 即可
        // 时间复杂度为 O(m+n)
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = n-1;
        while(i < m && j >= 0)
        {
            if(matrix[i][j] > target)
            {
                --j;
            }
            else if(matrix[i][j] == target)
            {
                return true;
            }
            else
            {
                ++i;
            }
        }
        return false;
    }
};