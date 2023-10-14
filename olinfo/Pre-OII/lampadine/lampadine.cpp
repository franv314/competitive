#include <bits/stdc++.h>
using namespace std;

vector<int> disconnect(vector<int>);
void series(vector<int>);

void study(int N) {
    auto my_svita = [&N](vector<int> q) -> vector<int> {
        vector<int> query;
        for (int i = 0; i < N; i++) {
            if (q[i]) query.push_back(i);
        }
        return disconnect(query);
    };
    vector<pair<vector<int>, vector<int>>> subsets;

    vector<int> temp(N);
    iota(temp.begin(), temp.end(), 0);
    subsets.emplace_back(temp, vector<int>());

    while (!subsets.empty()) {
        vector<int> query(N);
        for (auto [head, tail]: subsets) {
            for (int i = 0; i < head.size() / 2; i++) {
                query[head[i]] = true;
            }
        }

        vector<int> ans = my_svita(query);

        vector<pair<vector<int>, vector<int>>> new_subsets;

        for (auto [head, tail]: subsets) {
            vector<int> new_head_1, new_tail_1, new_head_2, new_tail_2;

            for (int i = 0; i < head.size() / 2; i++) {
                new_head_1.push_back(head[i]);
            }
            for (int i = head.size() / 2; i < head.size(); i++) {
                if (ans[head[i]]) new_head_2.push_back(head[i]);
                else new_tail_1.push_back(head[i]);
            }
            for (auto elem: tail) {
                if (ans[elem]) new_tail_2.push_back(elem);
                else new_tail_1.push_back(elem);
            }

            if (new_head_1.size() == 1) {
                copy(new_tail_1.begin(), new_tail_1.end(), back_inserter(new_head_1));
                series(new_head_1);
            } else if (!new_head_1.empty() || !new_tail_1.empty()) {
                new_subsets.emplace_back(new_head_1, new_tail_1);
            }

            if (new_head_2.size() == 1) {
                copy(new_tail_2.begin(), new_tail_2.end(), back_inserter(new_head_2));
                series(new_head_2);
            } else if (!new_head_2.empty() || !new_tail_2.empty()) {
                new_subsets.emplace_back(new_head_2, new_tail_2);
            }
        }
        subsets = new_subsets;
    }
}
