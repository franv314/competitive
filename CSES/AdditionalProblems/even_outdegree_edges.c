#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List {
    int val;
    struct List *next;
};

void push_front(struct List **list, int val) {
    if (!*list) {
        *list = (struct List*)malloc(sizeof(struct List));
        (*list)->val = val;
        (*list)->next = NULL;
        return;
    }
    
    struct List *new_elem = (struct List*)malloc(sizeof(struct List));
    memcpy(new_elem, *list, sizeof(struct List));
    
    (*list)->val = val;
    (*list)->next = new_elem;
}

void free_list(struct List *list) {
    while (list) {
        struct List *next = list->next;
        free(list);
        list = next;
    }
}

struct List **adj;
int *visited, *out;

int pos = 0;
int *u, *v;

int dfs(int node, int par) {
    visited[node] = 1;

    struct List *curr = adj[node];
    while (curr) {
        struct List *next = curr->next;
        int child = curr->val;

        if (child == par || visited[child] == 2) {
        } else if (visited[child]) {
            u[pos] = node + 1;
            v[pos] = child + 1;
            pos++;
            out[node]++;
        } else {
            dfs(child, node);
        }

        curr = next;
    }

    visited[node] = 2;
    if (par != -1) {
        if (out[node] % 2) {
            u[pos] = node + 1;
            v[pos] = par + 1;
            pos++;
        } else {
            u[pos] = par + 1;
            v[pos] = node + 1;
            pos++;
            out[par]++;
        }
        return 1;
    } else if (out[node] % 2) {
        return 0;
    }
    return 1;
}

int main(void) {
    int n, m; scanf("%d%d", &n, &m);

    adj = (struct List**)calloc(n, sizeof(struct List*));
    visited = (int*)calloc(n, sizeof(int));
    out = (int*)calloc(n, sizeof(int));
    u = (int*)malloc(m * sizeof(int));
    v = (int*)malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        a--, b--;

        push_front(&adj[a], b);
        push_front(&adj[b], a);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && !dfs(i, -1)) {
            puts("IMPOSSIBLE");
            goto end;
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%d %d\n", u[i], v[i]);
    }

end:
    for (int i = 0; i < n; i++) {
        free_list(adj[i]);
    }

    free(adj);
    free(out);
    free(u);
    free(v);
}