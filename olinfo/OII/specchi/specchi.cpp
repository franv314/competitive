#include <bits/stdc++.h>
using namespace std;

#define MAXR 250'000
#define MAXC 250'000

#define LAYERS 20

typedef enum { SOPRA, DESTRA, SOTTO, SINISTRA } parete_t;

typedef struct {
    parete_t lato;
    int posizione;
} foro_t;

struct RNG {
    mt19937 mt;

    int operator()() {
        int x = LAYERS - 32 + __builtin_clz(mt() & ((1 << (LAYERS - 1)) - 1));
        return x;
    }

    RNG() : mt(random_device()()) { }
} rng;

struct Node {
    variant<foro_t, tuple<int, int, int>, tuple<>> pos;
    vector<pair<Node*, Node*>> adj;

    Node(foro_t foro) : pos(foro), adj(LAYERS, {NULL, NULL}) { }
    Node(int r, int c, int dir) : pos(tie(r, c, dir)), adj(rng(), {NULL, NULL}) { }
    Node() : pos(tie()), adj(LAYERS, {NULL, NULL}) { }
};

map<int, array<Node*, 4>> rows[MAXR];
map<int, array<Node*, 4>> cols[MAXC];
Node* fori[4][MAXR];

void link_ends(Node* end1, Node* end2) {
    for (int i = 0; i < LAYERS; i++) {
        end1->adj[i].first = end2;
        end2->adj[i].first = end1;
    }
}

void insert_after_end(Node* end, Node* to_insert) {
    for (int i = 0; i < to_insert->adj.size(); i++) {
        to_insert->adj[i].first = end;
        to_insert->adj[i].second = end->adj[i].first ?: end->adj[i].second;

        if ((to_insert->adj[i].second)->adj[i].first == end) {
            (to_insert->adj[i].second)->adj[i].first = to_insert;
        } else {
            (to_insert->adj[i].second)->adj[i].second = to_insert;
        }

        if (end->adj[i].first == to_insert->adj[i].second) {
            end->adj[i].first = to_insert;
        } else {
            end->adj[i].second = to_insert;
        }
    }
}

void inizia(int R, int C) {
    for (int r = 0; r < R; r++) {
        fori[SINISTRA][r] = new Node((foro_t){SINISTRA, r});
        fori[  DESTRA][r] = new Node((foro_t){  DESTRA, r});
        link_ends(fori[SINISTRA][r], fori[DESTRA][r]);

        rows[r][-1][  DESTRA] = new Node(r, -1,   DESTRA);
        rows[r][ C][SINISTRA] = new Node(r,  C, SINISTRA);

        insert_after_end(fori[SINISTRA][r], rows[r][-1][DESTRA]);
        insert_after_end(fori[DESTRA][r], rows[r][C][SINISTRA]);
    }
    for (int c = 0; c < C; c++) {
        fori[SOPRA][c] = new Node((foro_t){SOPRA, c});
        fori[SOTTO][c] = new Node((foro_t){SOTTO, c});
        link_ends(fori[SOPRA][c], fori[SOTTO][c]);

        cols[c][-1][SOTTO] = new Node(-1, c, SOTTO);
        cols[c][ R][SOPRA] = new Node( R, c, SOPRA);

        insert_after_end(fori[SOPRA][c], cols[c][-1][SOTTO]);
        insert_after_end(fori[SOTTO][c], cols[c][ R][SOPRA]);
    }
}

pair<Node*, Node*> split(Node* u, Node* v) {
    Node *old_u = v, *old_v = u;
    Node *end_u = new Node, *end_v = new Node;

    bool came_from_u, came_from_v; // true se dal first
    came_from_u = u->adj[0].first == old_u;
    came_from_v = v->adj[0].first == old_v;

    for (int i = 0; i < LAYERS; i++) {
        Node* start_u = u;
        while (u->adj.size() <= i) {
            old_u = u;

            if (came_from_u) {
                u = u->adj.back().second;
            } else {
                u = u->adj.back().first;
            }

            if (start_u == u) {
                return {end_u, end_v};
            }

            came_from_u = u->adj[old_u->adj.size() - 1].first == old_u;
        }

        Node* start_v = v;
        while (v->adj.size() <= i) {
            old_v = v;

            if (came_from_v) {
                v = v->adj.back().second;
            } else {
                v = v->adj.back().first;
            }

            if (start_v == v) {
                return {end_u, end_v};
            }

            came_from_v = v->adj[old_v->adj.size() - 1].first == old_v;
        }

        end_u->adj[i].first = u;
        if (came_from_u) {
            u->adj[i].first = end_u;
        } else {
            u->adj[i].second = end_u;
        }

        end_v->adj[i].first = v;
        if (came_from_v) {
            v->adj[i].first = end_v;
        } else {
            v->adj[i].second = end_v;
        }
    }
    return {end_u, end_v};
}

void merge(Node* end_u, Node* end_v) {
    for (int i = 0; i < LAYERS; i++) {
        Node *merge_u = end_u->adj[i].first;
        Node *merge_v = end_v->adj[i].first;

        if (merge_u->adj[i].first == end_u) {
            merge_u->adj[i].first = merge_v;
        } else {
            merge_u->adj[i].second = merge_v;
        }

        if (merge_v->adj[i].first == end_v) {
            merge_v->adj[i].first = merge_u;
        } else {
            merge_v->adj[i].second = merge_u;
        }
    }

    delete end_u;
    delete end_v;
}

void aggiungi(int row, int col, char orientamento) {
    Node *r = rows[row].upper_bound(col)->second[SINISTRA];
    Node *b = cols[col].upper_bound(row)->second[SOPRA];
    Node *l = prev(rows[row].upper_bound(col))->second[DESTRA];
    Node *t = prev(cols[col].upper_bound(row))->second[SOTTO];

    auto [l_list, r_list] = split(l, r);
    auto [t_list, b_list] = split(t, b);

    rows[row][col][SINISTRA] = new Node(row, col, SINISTRA);
    rows[row][col][  DESTRA] = new Node(row, col,   DESTRA);
    cols[col][row][   SOTTO] = new Node(row, col,    SOTTO);
    cols[col][row][   SOPRA] = new Node(row, col,    SOPRA);

    insert_after_end(l_list, rows[row][col][SINISTRA]);
    insert_after_end(r_list, rows[row][col][  DESTRA]);
    insert_after_end(t_list, cols[col][row][   SOPRA]);
    insert_after_end(b_list, cols[col][row][   SOTTO]);

    if (orientamento == '/') {
        merge(l_list, t_list);
        merge(r_list, b_list);
    } else {
        merge(l_list, b_list);
        merge(r_list, t_list);
    }
}

foro_t calcola(foro_t ingresso) {
    Node *old = NULL, *curr = fori[ingresso.lato][ingresso.posizione];
    do {
        if (curr->adj.back().first != old) {
            old = curr;
            curr = curr->adj.back().first;
        } else {
            old = curr;
            curr = curr->adj.back().second;
        }
    } while (curr != NULL);
    return get<foro_t>(old->pos);
}