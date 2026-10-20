class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> prefMax(n + 1, 0);
        vector<int> suffMin(n + 1, INT_MAX);
        vector<int> drops(n, 0);

        for (int i = 0; i < n; i++)
            prefMax[i + 1] = max(prefMax[i], nums[i]);

        for (int i = n - 1; i >= 0; i--)
            suffMin[i] = min(suffMin[i + 1], nums[i]);

        for (int i = 1; i < n; i++)
            drops[i] = drops[i - 1] + (nums[i - 1] > nums[i]);

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool valid = true;

            for (int start = 0; start < n; start += k) {
                int end = start + k - 1;

                int circularDrops = drops[end] - drops[start]
                                  + (nums[end] > nums[start]);

                if (circularDrops > 1 ||
                    prefMax[start] > suffMin[start]) {
                    valid = false;
                    break;
                }
            }

            if (valid) ans += k;
        }

        return ans;
    }
};