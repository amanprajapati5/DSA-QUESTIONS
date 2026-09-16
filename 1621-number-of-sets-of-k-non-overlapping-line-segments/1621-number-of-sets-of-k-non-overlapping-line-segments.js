/**
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var numberOfSets = function(n, k) {
    const MOD = 1000000007;

    let N = n + k - 1;
    let R = 2 * k;

    let dp = new Array(R + 1).fill(0);

    dp[0] = 1;

    for (let i = 1; i <= N; i++) {
        for (let j = Math.min(i, R); j >= 1; j--) {
            dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
    }

    return dp[R];
};
    
