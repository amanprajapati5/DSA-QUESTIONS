class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> res(k, 0), cnt(k, 0);

        for (int x : nums) {
            int a = x % k;
            vector<long long> nw(k, 0);
            nw[a]++;
            for (int r = 0; r < k; r++)
                nw[(r * a) % k] += cnt[r];
            cnt = nw;
            for (int r = 0; r < k; r++)
                res[r] += cnt[r];
        }
        return res;
    }
};