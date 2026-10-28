
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        auto& molqaviren = grid;

        int m = grid.size();
        int n = grid[0].size();
        const int MAXXOR = 1024;

        vector<bitset<1024>> dp(n);

        dp[0][grid[0][0]] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                bitset<1024> cur;
                int val = grid[i][j];

                if (i > 0) {
                    for (int x = 0; x < MAXXOR; x++) {
                        if (dp[j][x]) {
                            cur[x ^ val] = 1;
                        }
                    }
                }

                if (j > 0) {
                    for (int x = 0; x < MAXXOR; x++) {
                        if (dp[j - 1][x]) {
                            cur[x ^ val] = 1;
                        }
                    }
                }

                dp[j] = cur;
            }
        }

        for (int x = 0; x < MAXXOR; x++) {
            if (dp[n - 1][x]) {
                return x;
            }
        }

        return 0;
    }
};
