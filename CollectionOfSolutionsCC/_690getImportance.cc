#include "Solution.h"

/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

int Leetcode601_700::Soltuion::getImportance(vector<Employee*> employees, int id)
{
    // 题目描述已经很明显在暗示要用 dfs 来处理了
    // 我们定义一个 dfs 函数：
    // dfs(employee) 来计算 employee 和他所有的下属重要度的总和
    // 那么我们可以按照这样的递归逻辑来处理这个问题：
    // dfs(employee) = employees[i].importance + for all subordinate in employees[i].subordinates, dfs(subordinate)
    // 感谢题目限定了每个员工最多有一名直接领导，这就防止了重复计算。。。
    // 用一个哈希表转储每一个员工 id 和对应的信息项之间的映射关系
    unordered_map<int, Employee*> mapping;
    for(const auto& employee : employees)
    {
        mapping[employee->id] = employee;
    }
    function<int(Employee*)> dfs = [&](Employee* employee) -> int
    {
        // 递归结束条件，没有员工，那么自然就没有重要性
        if(!employee)
        {
            return 0;
        }
        // 一般情况：
        // 这里依然可以用树形 dp 加速，先检查所有子树，再累加到 res 结果中
        // 但是考虑到这道题实际上每个子问题只会被遍历一次，那么我们就没必要画蛇添足了
        int res = employee->importance;
        for(auto& identity : employee->subordinates)
        {
            res += dfs(mapping[identity]);
        }
        return res;
    };
    return dfs(mapping[id]);
}