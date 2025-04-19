#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--){
        int N;
        long long K;
        cin >> N >> K;
        vector<long long> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        auto kAlgorithm = [&]() {
            long long best = A[0], cur = A[0];
            for (int i = 1; i < N; i++){
                cur = max(A[i], cur + A[i]);
                best = max(best, cur);
            }
            return best;
        };
        if (K == 0){
            cout<<kAlgorithm()<<endl;
            continue;
        }
        long long sumPos = 0, maxA = A[0];
        for (long long x : A){
            if (x > 0) sumPos += x;
            maxA = max(maxA, x);
        }
        cout<<(sumPos > 0 ? sumPos : maxA)<<endl;
    }
    return 0;
}
