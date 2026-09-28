class Solution {
public:
    int majorityElement(vector<int>& a) {
        int x=0,c=0;
        for(int n:a){
            if(!c)x=n;
            c += n==x ? 1 : -1;
        }
        return x;
    }
};