#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long cal_power(long long base, long long power) {
    long long result = 1;
    while (power > 0) {
        if (power % 2 == 1)
            result = (result * base) % MOD;
        base = (base * base) % MOD;
        power /= 2;
    }
    return result;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long inv100 = cal_power(100, MOD - 2);
    int n;
    long long k;
    cin >> n >> k;
    vector<vector<pair<int, int>>> adj(n);
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.emplace_back(u, v, w);
    }
    vector<bool> is_infected(n, false);
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        is_infected[x - 1] = true;
    }
    vector<long long> dp_down(n, 0), dp_up(n, 0);
    vector<vector<int>> children(n);
    vector<int> parent(n, -1);
    vector<int> order;
    vector<long long> p_no_transmit_up(n, 1);
    vector<int> child_idx_in_parent(n, -1);
    queue<int> q;
    vector<bool> visited(n, false);
    map<pair<int, int>, int> edge_weights;
    for (const auto& edge : edges) {
        int u = get<0>(edge);
        int v = get<1>(edge);
        int w = get<2>(edge);
        edge_weights[{u, v}] = w;
        edge_weights[{v, u}] = w;
    }
    q.push(0);
    visited[0] = true;
    order.push_back(0);
    int head = 0;
    while(head < order.size()){
        int u = order[head++];
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                children[u].push_back(v);
                child_idx_in_parent[v] = children[u].size() - 1;
                long long p_transmit = (1LL * w * inv100) % MOD;
                long long p_no_transmit_val = (1 - p_transmit + MOD) % MOD;
                p_no_transmit_up[v] = p_no_transmit_val;
                order.push_back(v);
            }
        }
    }
    vector<vector<long long>> sbling_stor(n);
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        if (is_infected[u]) {
            dp_down[u] = 0;
        } else {
            long long current_prob_healthy = 1;
            int num_children = children[u].size();
            if (num_children == 0) {
                dp_down[u] = 1;
                continue;
            }
            vector<long long> terms_vec(num_children);
            for (int j = 0; j < num_children; ++j) {
                int v = children[u][j];
                long long p_no_transmit = p_no_transmit_up[v];
                long long term = (dp_down[v] + (1 - dp_down[v] + MOD) * p_no_transmit) % MOD;
                terms_vec[j] = term;
                current_prob_healthy = (current_prob_healthy * term) % MOD;
            }
            dp_down[u] = current_prob_healthy;
            vector<long long> prefix(num_children + 1, 1);
            vector<long long> suffix(num_children + 1, 1);
            for (int j = 0; j < num_children; j++) {
                prefix[j + 1] = (prefix[j] * terms_vec[j]) % MOD;
            }
            for (int j = num_children - 1; j >= 0; j--) {
                suffix[j] = (suffix[j + 1] * terms_vec[j]) % MOD;
            }
            sbling_stor[u].resize(num_children);
            for (int j = 0; j < num_children; j++) {
                sbling_stor[u][j] = (prefix[j] * suffix[j + 1]) % MOD;
            }
        }
    }
    for (int u : order) {
        int p = parent[u];
        if (p == -1) {
            dp_up[u] = 1;
        } else {
            long long p_no_transmit = p_no_transmit_up[u];
            if (is_infected[p]) {
                dp_up[u] = p_no_transmit;
            } else {
                int u_idx_in_p = child_idx_in_parent[u];
                long long sibling_prod = 1;
                if (!sbling_stor[p].empty()) sibling_prod = sbling_stor[p][u_idx_in_p];
                long long h_p = (dp_up[p] * sibling_prod) % MOD;
                dp_up[u] = (h_p + (1 - h_p + MOD) * p_no_transmit) % MOD;
            }
        }
    }
    cout.precision(10);
    for (int i = 0; i < n; i++) {
        if (is_infected[i]) {
            cout << 1 << "\n";
        } else {
            long long prob_healthy = (dp_down[i] * dp_up[i]) % MOD;
            long long prob_infected = (1 - prob_healthy + MOD) % MOD;
            cout << prob_infected << "\n";
        }
    }
    return 0;
}
