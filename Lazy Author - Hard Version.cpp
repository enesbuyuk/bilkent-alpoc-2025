#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000;
static const int MAXA = 10000;
int N, Q;
int A[MAXN + 5], CUR[MAXN + 5];

struct Query { int l, r, t, id; };

vector<Query> queries;
vector<pair<int, pair<int,int>>> updates;
int answer[MAXN + 5];
int freqArr[MAXA + 5];
int M;
int blkSize, blkCount;
int blkZero[/* will init later */ 105];

inline void addValue(int x) {
    if (++freqArr[x] == 1) {
        int b = x / blkSize;
        --blkZero[b];
    }
}

inline void removeValue(int x) {
    if (--freqArr[x] == 0) {
        int b = x / blkSize;
        ++blkZero[b];
    }
}

int getMex() {
    for (int b = 0; b < blkCount; ++b) {
        if (blkZero[b] > 0) {
            int start = b * blkSize;
            int end = min(M, start + blkSize - 1);
            for (int x = start; x <= end; ++x) {
                if (freqArr[x] == 0)
                    return x;
            }
        }
    }
    return M;
}

inline void applyUpdate(int idx, int L, int R) {
    auto &u = updates[idx];
    int pos = u.first;
    int oldVal = u.second.first;
    int newVal = u.second.second;
    if (L <= pos && pos <= R) {
        removeValue(CUR[pos]);
        addValue(newVal);
    }
    CUR[pos] = newVal;
}

inline void undoUpdate(int idx, int L, int R) {
    auto &u = updates[idx];
    int pos = u.first;
    int oldVal = u.second.first;
    int newVal = u.second.second;
    if (L <= pos && pos <= R) {
        removeValue(CUR[pos]);
        addValue(oldVal);
    }
    CUR[pos] = oldVal;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    int maxVal = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        CUR[i] = A[i];
        maxVal = max(maxVal, A[i]);
    }
    M = maxVal + 1;

    blkSize = sqrt(M) + 1;
    blkCount = (M + blkSize) / blkSize;
    memset(freqArr, 0, sizeof(freqArr));
    for (int b = 0; b < blkCount; ++b)
        blkZero[b] = blkSize;
    int lastBlockSize = M - (blkCount - 1) * blkSize + 1;
    blkZero[blkCount - 1] = lastBlockSize;

    int block = max(1, int(pow(N, 2.0 / 3.0)));
    for (int i = 0; i < Q; ++i) {
        int tp, l, r;
        cin >> tp >> l >> r;
        if (tp == 1) {
            queries.push_back({l, r, (int)updates.size(), (int)queries.size()});
        } else {
            updates.emplace_back(l, make_pair(CUR[l], r));
            CUR[l] = r;
        }
    }

    /////// resett
    for (int i = 1; i <= N; ++i) CUR[i] = A[i];
    memset(freqArr, 0, sizeof(freqArr));
    for (int b = 0; b < blkCount; ++b) blkZero[b] = blkSize;
    blkZero[blkCount - 1] = lastBlockSize;
    sort(queries.begin(), queries.end(), [&](auto &a, auto &b) {
        int ab = a.l / block, bb = b.l / block;
        if (ab != bb) return ab < bb;
        int ar = a.r / block, br = b.r / block;
        if (ar != br) return ar < br;
        return a.t < b.t;
    });
    int L = 1, R = 0, T = 0;
    for (auto &q : queries) {
        while (T < q.t) applyUpdate(T++, L, R);
        while (T > q.t) undoUpdate(--T, L, R);
        while (R < q.r) addValue(CUR[++R]);
        while (L > q.l) addValue(CUR[--L]);
        while (R > q.r) removeValue(CUR[R--]);
        while (L < q.l) removeValue(CUR[L++]);
        answer[q.id] = getMex();
    }
    for (int i = 0; i < (int)queries.size(); ++i) cout << answer[i] << endl;
    return 0;
}
