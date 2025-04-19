#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--){
        long long N, M;
        cin >> N >> M;
        auto S = static_cast<long long>((__int128)N * (N + 1) % M);
        (S == 0 || S > N)?cout<<"Ahmet"<<"\n":cout<<"Alp"<<"\n";
    }
    return 0;
}
