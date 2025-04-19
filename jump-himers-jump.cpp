#include <bits/stdc++.h>
using namespace std;
static const long long MOD = 1000000007;
vector<long long> polyMulReduce(const vector<long long> &A,const vector<long long> &B,const vector<long long> &c) {
    int M = (int)c.size();
    vector<long long> D(2*M - 1, 0);
    for(int i = 0; i < M; i++) {
        if (!A[i]) continue;
        for(int j = 0; j < M; j++) {
            D[i+j] = (D[i+j] + A[i] * B[j]) % MOD;
        }
    }
    for(int k = 2*M-2; k >= M; k--) {
        if (!D[k]) continue;
        long long coef = D[k];
        for(int j = 0; j < M; j++) {
            D[k-1-j] = (D[k-1-j] + coef * c[j]) % MOD;
        }
    }
    vector<long long> R(M);
    for(int i = 0; i < M; i++)
        R[i] = D[i];
    return R;
}
vector<long long> poly_pow(long long exp, int M, const vector<long long> &c) {
    vector<long long> res(M, 0);
    res[0] = 1;
    vector<long long> base(M, 0);
    if (M > 1) base[1] = 1; else base[0] = c[0];
    while (exp > 0) {
        if (exp & 1) res = polyMulReduce(res, base, c);
        base = polyMulReduce(base, base, c);
        exp >>= 1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    int K;
    cin >> N >> K;
    vector<int> a(K);
    int M = 0;
    for(int i = 0; i < K; i++){
        cin >> a[i];
        M = max(M, a[i]);
    }
    vector<long long> c(M, 0);
    for(int x : a) c[x-1] = 1;
    vector<long long> dp(M, 0);
    dp[0] = 1;
    for(int i = 1; i < M; i++){
        long long ways = 0;
        for(int x : a)  if (i - x >= 0) ways = (ways + dp[i - x]) % MOD;
        dp[i] = ways;
    }
    if (N < M) {
        cout<<dp[N];
        return 0;
    }
    auto R = poly_pow(N, M, c);
    long long answer = 0;
    for(int i = 0; i < M; i++){
        answer = (answer + R[i] * dp[i]) % MOD;
    }
    cout<<answer;
    return 0;
}
