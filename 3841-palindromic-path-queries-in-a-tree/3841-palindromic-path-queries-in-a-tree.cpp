
class Solution {
    class Fenwick {
        int n;
        vector<int> bit;

    public:
        Fenwick(int n) : n(n), bit(n + 1, 0) {}

        void update(int i, int val) {
            for (; i <= n; i += i & -i) {
                bit[i] ^= val;
            }
        }

        void rangeXor(int l, int r, int val) {
            update(l + 1, val);
            update(r + 2, val);
        }

        int query(int i) {
            int result = 0;

            for (i++; i > 0; i -= i & -i) {
                result ^= bit[i];
            }

            return result;
        }
    };

    int charMask(char c) {
        return 1 << (c - 'a');
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        vector<vector<int>> graph(n);

        for (auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<int> parent(n, 0), depth(n, 0);
        vector<int> tin(n), subtree(n, 1), order;
        order.reserve(n);

        // Iterative DFS: assign Euler entry times
        stack<int> st;
        st.push(0);

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            tin[u] = order.size();
            order.push_back(u);

            for (int v : graph[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push(v);
            }
        }

        // Calculate subtree sizes in reverse DFS order
        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            subtree[parent[u]] += subtree[u];
        }

        vector<int> tout(n);

        for (int u = 0; u < n; u++) {
            tout[u] = tin[u] + subtree[u] - 1;
        }

        // Binary lifting table
        vector<vector<int>> up(LOG, vector<int>(n));

        for (int u = 0; u < n; u++) {
            up[0][u] = parent[u];
        }

        for (int j = 1; j < LOG; j++) {
            for (int u = 0; u < n; u++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j)) {
                    u = up[j][u];
                }
            }

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return parent[u];
        };

        Fenwick fw(n);

        // Store each node's character in its entire subtree
        for (int u = 0; u < n; u++) {
            fw.rangeXor(tin[u], tout[u], charMask(s[u]));
        }

        // Required intermediate input variable
        auto suneravilo = queries;

        vector<bool> answer;

        for (string& q : suneravilo) {
            string op;
            int u, v;
            stringstream ss(q);

            ss >> op >> u;

            if (op == "update") {
                char c;
                ss >> c;

                int change = charMask(s[u]) ^ charMask(c);

                fw.rangeXor(tin[u], tout[u], change);
                s[u] = c;
            } else {
                ss >> v;

                int w = lca(u, v);

                int mask = fw.query(tin[u])
                         ^ fw.query(tin[v])
                         ^ charMask(s[w]);

                // Zero or one set bit means palindrome is possible
                answer.push_back(
                    mask == 0 || (mask & (mask - 1)) == 0
                );
            }
        }

        return answer;
    }
};
