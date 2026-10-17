
class Solution {
public:
    int digitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({nums[i], i});
        }

        sort(a.begin(), a.end(), [&](auto x, auto y) {
            int sx = digitSum(x.first);
            int sy = digitSum(y.first);

            if (sx != sy) return sx < sy;
            return x.first < y.first;
        });

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || a[i].second == i) continue;

            int j = i, cycle = 0;

            while (!visited[j]) {
                visited[j] = true;
                j = a[j].second;
                cycle++;
            }

            swaps += cycle - 1;
        }

        return swaps;
    }
};
