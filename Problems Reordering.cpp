#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<int> A(N), B(M);
        for (int i = 0; i < N; ++i) cin >> A[i];
        for (int j = 0; j < M; ++j) cin >> B[j];
        int i = 0, j = 0;
        vector<int> merged;
        merged.reserve(N + M);
        while (i < N || j < M) {
            if (i == N) {
                merged.push_back(B[j++]);
            } else if (j == M) {
                merged.push_back(A[i++]);
            } else if (A[i] < B[j]) {
                merged.push_back(A[i++]);
            } else if (A[i] > B[j]) {
                merged.push_back(B[j++]);
            } else {
                (lexicographical_compare(A.begin() + i, A.end(), B.begin() + j, B.end()))?merged.push_back(A[i++]):merged.push_back(B[j++]);
            }
        }
        for (int k = 0; k < (int)merged.size(); ++k) {
            if (k > 0)cout<< ' ';
            cout<<merged[k];
        }
        cout<<'\n';
    }
    return 0;
}
