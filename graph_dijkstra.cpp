/*
 * graph_dijkstra.cpp
 *
 * 概要:
 * - グラフ探索アルゴリズムの一つ「ダイクストラ法」を実装
 * - 最短経路問題を解くサンプル
 * - 標準ライブラリ(STL)のpriority_queueを活用
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int cost;
};

using Graph = vector<vector<Edge>>;

vector<int> dijkstra(const Graph& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : graph[u]) {
            if (dist[u] + edge.cost < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.cost;
                pq.emplace(dist[edge.to], edge.to);
            }
        }
    }

    return dist;
}

int main() {
    int n = 5; // 頂点数
    Graph graph(n);

    // グラフ構築 (無向グラフ)
    graph[0].push_back({1, 10});
    graph[0].push_back({3, 30});
    graph[0].push_back({4, 100});
    graph[1].push_back({2, 50});
    graph[2].push_back({4, 10});
    graph[3].push_back({2, 20});
    graph[3].push_back({4, 60});

    // ダイクストラ法の実行
    vector<int> dist = dijkstra(graph, 0);

    cout << "Start: 0" << endl;
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            cout << "Node " << i << ": INF" << endl;
        } else {
            cout << "Node " << i << ": " << dist[i] << endl;
        }
    }

    return 0;
}
