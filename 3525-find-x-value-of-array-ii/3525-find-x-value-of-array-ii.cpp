class Solution {
public:
    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int k;
    int size;
    vector<Node> seg;

    inline Node mergeNode(const Node& a, const Node& b) {
        Node res;

        res.prod = (a.prod * b.prod) % k;

        for (int i = 0; i < k; i++)
            res.cnt[i] = a.cnt[i];

        for (int i = 0; i < k; i++) {
            int rem = (a.prod * i) % k;
            res.cnt[rem] += b.cnt[i];
        }

        return res;
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        this->k = k;

        int n = nums.size();

   
        size = 1;
        while (size < n)
            size <<= 1;

        seg.resize(2 * size);

 
        for (int i = 0; i < n; i++) {
            int rem = nums[i] % k;

            seg[size + i].prod = rem;
            seg[size + i].cnt[rem] = 1;
        }


        for (int i = size - 1; i >= 1; i--) {
            seg[i] = mergeNode(seg[i << 1], seg[i << 1 | 1]);
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

       
            int pos = size + index;

            for (int i = 0; i < k; i++)
                seg[pos].cnt[i] = 0;

            int rem = value % k;

            seg[pos].prod = rem;
            seg[pos].cnt[rem] = 1;

            pos >>= 1;

            while (pos >= 1) {
                seg[pos] = mergeNode(
                    seg[pos << 1],
                    seg[pos << 1 | 1]
                );

                pos >>= 1;
            }

            if (start == 0) {
                ans.push_back(seg[1].cnt[x]);
                continue;
            }

       
            int l = size + start;
            int r = size + n;

            Node left;
            Node right;

            while (l < r) {
                if (l & 1) {
                    left = mergeNode(left, seg[l]);
                    l++;
                }

                if (r & 1) {
                    --r;
                    right = mergeNode(seg[r], right);
                }

                l >>= 1;
                r >>= 1;
            }

            Node result = mergeNode(left, right);

            ans.push_back(result.cnt[x]);
        }

        return ans;
    }
};