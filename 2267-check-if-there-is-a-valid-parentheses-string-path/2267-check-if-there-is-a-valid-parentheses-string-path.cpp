class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();

        if ((m + n - 1) % 2 != 0) return false;
     
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;

        vector<vector<bitset<205>>> dp(m, vector<bitset<205>>(n));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bitset<205> cur;
                if (i == 0 && j == 0) {
                    cur[0] = 1;              
                } else {
                    if (i > 0) cur |= dp[i - 1][j];
                    if (j > 0) cur |= dp[i][j - 1];
                }

                if (grid[i][j] == '(') {
                    cur <<= 1;              
                } else {
                    cur >>= 1;               
                }
                dp[i][j] = cur;
            }
        }
        return dp[m - 1][n - 1][0];
    }
};