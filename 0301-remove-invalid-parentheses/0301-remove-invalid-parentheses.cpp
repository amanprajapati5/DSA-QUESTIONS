class Solution {
public:
    vector<string> ans;

    void dfs(string &s, int start, int leftRemove,
             int rightRemove, int balance) {

        // If we removed the required number of brackets
        if (leftRemove == 0 && rightRemove == 0) {

            // Check whether remaining string is valid
            int count = 0;

            for (char c : s) {
                if (c == '(')
                    count++;
                else if (c == ')') {
                    count--;

                    if (count < 0)
                        return;
                }
            }

            if (count == 0)
                ans.push_back(s);

            return;
        }

        for (int i = start; i < s.size(); i++) {

            // Skip duplicate parentheses
            if (i > start && s[i] == s[i - 1])
                continue;

            // Remove '('
            if (s[i] == '(' && leftRemove > 0) {

                s.erase(i, 1);

                dfs(s, i, leftRemove - 1,
                    rightRemove, balance);

                s.insert(i, 1, '(');
            }

            // Remove ')'
            else if (s[i] == ')' && rightRemove > 0) {

                s.erase(i, 1);

                dfs(s, i, leftRemove,
                    rightRemove - 1, balance);

                s.insert(i, 1, ')');
            }
        }
    }

    vector<string> removeInvalidParentheses(string s) {

        ans.clear();

        int leftRemove = 0;
        int rightRemove = 0;
        int balance = 0;

        // Find minimum removals
        for (char c : s) {

            if (c == '(') {
                balance++;
            }
            else if (c == ')') {

                if (balance > 0)
                    balance--;
                else
                    rightRemove++;
            }
        }

        leftRemove = balance;

        dfs(s, 0, leftRemove, rightRemove, 0);

        return ans;
    }
};