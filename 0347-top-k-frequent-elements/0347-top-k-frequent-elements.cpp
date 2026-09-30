class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> mp;
        for (int x : nums) mp[x]++;

        vector<vector<int>> bucket(nums.size()+1);

        for (auto [x,f] : mp)
            bucket[f].push_back(x);

        vector<int> ans;

        for (int f = nums.size(); f >= 1 && ans.size() < k; f--)
            for (int x : bucket[f]) {
                ans.push_back(x);
                if (ans.size() == k) break;
            }

        return ans;
    }
};
