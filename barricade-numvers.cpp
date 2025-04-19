#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using u128 = __uint128_t;
u128 pows[10][20];
u128 barricades(u128 X) {
    if (X < 10) return 0;
    vector<int> D;
    u128 t = X;
    while (t) {
        D.push_back((int)(t % 10));
        t /= 10;
    }
    reverse(D.begin(), D.end());
    int n = D.size();
    u128 ans = 0;
    for (int L = 2; L < n; ++L) for (int d = 1; d <= 9; ++d) ans += pows[d][L-1];
    int lead = D[0];
    for (int d = 1; d < lead; ++d) ans += pows[d][n-1];
    bool good = true;
    for (int i = 1; i < n && good; ++i) {
        int rem = n - 1 - i;
        int lim = min(lead - 1, D[i] - 1);
        if (lim >= 0) ans += (u128)(lim + 1) * pows[lead][rem];
        if (D[i] >= lead) good = false;
    }
    if (good) ans += 1;
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int d = 0; d <= 9; ++d) {
        pows[d][0] = 1;
        for (int e = 1; e < 20; ++e) pows[d][e] = pows[d][e-1] * (u128)d;
    }
    ull L, R;
    cin >> L >> R;
    u128 ansR = barricades((u128)R);
    u128 ansL = (L > 0 ? barricades((u128)L - 1) : 0);
    u128 res = ansR - ansL;
    cout << (ull)res;
    return 0;
}
