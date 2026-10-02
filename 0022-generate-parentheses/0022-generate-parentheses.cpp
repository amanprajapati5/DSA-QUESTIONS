class Solution {
public:
    vector<string> ans;

    void solve(string &s, int open, int close, int n) {
        if (s.size() == 2 * n) {
            ans.push_back(s);
            return;
        }

        if (open < n) {
            s.push_back('(');
            solve(s, open + 1, close, n);
            s.pop_back();
        }

        if (close < open) {
            s.push_back(')');
            solve(s, open, close + 1, n);
            s.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        string s;
        solve(s, 0, 0, n);
        return ans;
    }
};