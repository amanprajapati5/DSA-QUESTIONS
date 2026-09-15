class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.length();

        vector<vector<bool>> palindrome(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++) {
            palindrome[i][i] = true;
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {

                int j = i + len - 1;

                if (s[i] == s[j]) {
                    if (len == 2 || palindrome[i + 1][j - 1]) {
                        palindrome[i][j] = true;
                    }
                }
            }
        }

        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {

            dp[i] = dp[i - 1];

            for (int j = 0; j < i; j++) {

                int len = i - j;

                if (len >= k && palindrome[j][i - 1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n];
    }
};