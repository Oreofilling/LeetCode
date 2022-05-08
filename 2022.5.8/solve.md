关于括号匹配的问题

虽然自己一看到括号匹配的问题就想到了栈处理,但是实际上还需要想到动态规划这一思想,别把思维局限在里面了.

判断一个括号序列是否合法是经典问题。对于一个括号序列，我们从左向右遍历每个字符，同时维护变量 now（初值为 0）。遇到左括号时，now += 1，遇到右括号时，now -= 1。如果过程中 now 始终非负，且最后 now 变成 0 则序列合法



1.首先看一下这道题:[最长有效括号](https://leetcode-cn.com/problems/longest-valid-parentheses/)

自己当时的解法:

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
       if(s.length()==0)
        return 0;
        vector<int> dp(s.length());//dp[i]代表以字符i结尾的最长有效括号
        dp[0]=0;
        int max_num=0;
        for(int i=1;i<s.length();i++)
        {
            if(s[i] == '(')//如果以'('结尾,一定构不成有效括号
            {
                dp[i]=0;
                continue;
            }

            //下面讨论以')'为结尾的情况
            if(i-dp[i-1] && s[i-dp[i-1]-1]=='(')
            {
                //说明存在...((...))情况,i-dp[i-1],相当于一个大括号把dp[i-1]包起来了.
                dp[i]=dp[i-1]+2;
            }

            if(dp[i] && i-dp[i]>=0)
            {
                //这里是考虑以i-dp[i]结尾处是不是也存在有效括号,也要算进去,因为刚好连起来了.
                dp[i]=dp[i-dp[i]]+dp[i];
            }

            max_num=max(dp[i],max_num);

        }

        return max_num;
    }
};
```

2.再看一下今天周赛的题目:[检查是否有合法字符串路径](https://leetcode-cn.com/problems/check-if-there-is-a-valid-parentheses-string-path/)

自己用回溯不出所料的超时了==,以后得少考虑回溯的做法,dfs剪枝这道题也可以做,而且速度更快

```
class Solution {
public:
    bool hasValidPath(vector<vector<char>> &grid) {
        int m = grid.size(), n = grid[0].size();
        if ((m + n) % 2 == 0 || grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false; // 剪枝
        bool vis[m][n][(m + n) / 2 + 1]; memset(vis, 0, sizeof(vis));
        function<bool(int, int, int)> dfs = [&](int x, int y, int c) -> bool {
            if (c > m - x + n - y - 1) return false; // 剪枝：即使后面都是 ')' 也不能将 c 减为 0
            if (x == m - 1 && y == n - 1) return c == 1; // 终点一定是 ')'
            if (vis[x][y][c]) return false; // 重复访问
            vis[x][y][c] = true;
            c += grid[x][y] == '(' ? 1 : -1;
            return c >= 0 && (x < m - 1 && dfs(x + 1, y, c) || y < n - 1 && dfs(x, y + 1, c)); // 往下或者往右
        };
        return dfs(0, 0, 0);
    }
};

```

dp做法:



```
class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        if (grid[0][0] == ')') return false;

        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<bool>>> f;
        for (int i = 0; i < n; i++) {
            f.push_back(vector<vector<bool>>());
            for (int j = 0; j < m; j++) f.back().push_back(vector<bool>(n + m));
        }
        f[0][0][1] = true;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (i || j) {
            int t = (grid[i][j] == '(' ? 1 : -1);
            for (int k = 0; k < n + m; k++) {
                int kk = k - t;
                if (kk < 0 || kk >= n + m) continue;
                if (i) f[i][j][k] = f[i][j][k] || f[i - 1][j][kk];
                if (j) f[i][j][k] = f[i][j][k] || f[i][j - 1][kk];
            }
        }
        return f[n - 1][m - 1][0];
    }

};


```

bitset优化,bitset可以表示n位的二进制数.

```
using bs = bitset<128>;
class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        if (grid[0][0] == ')') return false;
        int n = size(grid), m = size(grid[0]);
        vector<vector<bs>> f(n + 1, vector<bs>(m + 1)); // f[i,j,k]=1 表示到达点(i,j)的时候括号状态可以是 k
        f[0][1].set(0); // 设个初值，保证转移到 f[1,1] 的时候 f[1,1,1]=true
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (grid[i - 1][j - 1] == '(')
                    f[i][j] = (f[i - 1][j] << 1) | (f[i][j - 1] << 1);
                else 
                    f[i][j] = (f[i - 1][j] >> 1) | (f[i][j - 1] >> 1);
            }
        }
        return f[n][m].test(0);
    }
};

```

