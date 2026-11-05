
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1,
                             vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());

        int ans = 0;

        for (int x : arr1) {
            int pos = lower_bound(
                arr2.begin(),
                arr2.end(),
                x - d
            ) - arr2.begin();

            if (pos == arr2.size() || arr2[pos] > x + d) {
                ans++;
            }
        }

        return ans;
    }
};

