
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        vector<int> bits(31, 0);

        for (int x : nums) {
            for (int b = 0; b < 31; b++) {
                if (x & (1 << b)) {
                    bits[b]++;
                }
            }
        }

        long long ans = 0;

        while (k--) {
            long long x = 0;

            for (int b = 30; b >= 0; b--) {
                if (bits[b] > 0) {
                    x |= (1LL << b);
                    bits[b]--;
                }
            }

            ans = (ans + x * x) % MOD;
        }

        return ans;
    }
};
