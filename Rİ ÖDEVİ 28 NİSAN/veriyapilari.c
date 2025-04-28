#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_FRIENDS 100

typedef struct User {
    int id;
    int friends[MAX_FRIENDS];
    int friend_count;
} User;

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int id;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

User users[MAX_USERS];
int user_count = 0;

// Red-Black Tree kök düðüm
RBNode* root = NULL;

// Red-Black Tree iþlemleri
RBNode* create_rbt_node(int id) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->id = id;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void left_rotate(RBNode** root, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(RBNode** root, RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
}

void fix_rbt(RBNode** root, RBNode* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(root, z->parent->parent);
            }
        } else {
            RBNode* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insert_rbt(int id) {
    RBNode* z = create_rbt_node(id);
    RBNode* y = NULL;
    RBNode* x = root;
    while (x) {
        y = x;
        if (z->id < x->id)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (!y)
        root = z;
    else if (z->id < y->id)
        y->left = z;
    else
        y->right = z;
    fix_rbt(&root, z);
}

void inorder_rbt(RBNode* node) {
    if (!node) return;
    inorder_rbt(node->left);
    printf("%d ", node->id);
    inorder_rbt(node->right);
}

void free_rbt(RBNode* node) {
    if (!node) return;
    free_rbt(node->left);
    free_rbt(node->right);
    free(node);
}

// Kullanýcý iþlemleri
int find_user_index(int id) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == id) return i;
    }
    return -1;
}

void add_friendship(int id1, int id2) {
    int idx1 = find_user_index(id1);
    int idx2 = find_user_index(id2);
    if (idx1 != -1 && idx2 != -1) {
        users[idx1].friends[users[idx1].friend_count++] = id2;
        users[idx2].friends[users[idx2].friend_count++] = id1;
    }
}

void load_data(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    char type[100];
    int id1, id2;

    while (fscanf(file, "%s", type) != EOF) {
        if (type[0] == '#') {
            fgets(type, sizeof(type), file);
            continue;
        }
        if (strcmp(type, "USER") == 0) {
            fscanf(file, "%d", &id1);
            users[user_count].id = id1;
            users[user_count].friend_count = 0;
            insert_rbt(id1);
            user_count++;
        } else if (strcmp(type, "FRIEND") == 0) {
            fscanf(file, "%d %d", &id1, &id2);
            add_friendship(id1, id2);
        }
    }
    fclose(file);
}

// BFS ile mesafe hesaplama
typedef struct QueueNode {
    int idx;
    int level;
} QueueNode;

void find_friends_at_distance_bfs(int start_id, int distance) {
    printf("\n--- Kullanici %d mesafe %d arkadaslari ---\n", start_id, distance);

    bool visited[MAX_USERS] = {false};
    int start_idx = find_user_index(start_id);
    if (start_idx == -1) {
        printf("Kullanici bulunamadi!\n");
        return;
    }

    QueueNode queue[MAX_USERS];
    int front = 0, rear = 0;

    visited[start_idx] = true;
    queue[rear++] = (QueueNode){start_idx, 0};

    int found = 0;

    while (front < rear) {
        QueueNode current = queue[front++];
        if (current.level == distance) {
            printf("Arkadas: %d\n", users[current.idx].id);
            found = 1;
            continue;
        }
        for (int i = 0; i < users[current.idx].friend_count; i++) {
            int friend_idx = find_user_index(users[current.idx].friends[i]);
            if (friend_idx != -1 && !visited[friend_idx]) {
                visited[friend_idx] = true;
                queue[rear++] = (QueueNode){friend_idx, current.level + 1};
            }
        }
    }

    if (!found) {
        printf("Bu mesafede arkadas bulunamadi.\n");
    }
}

// Ortak arkadaþlar
void find_common_friends(int id1, int id2) {
    printf("\n--- Kullanici %d ve %d ortak arkadaslari ---\n", id1, id2);

    int idx1 = find_user_index(id1);
    int idx2 = find_user_index(id2);

    if (idx1 == -1 || idx2 == -1) {
        printf("Kullanici bulunamadi.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < users[idx1].friend_count; i++) {
        int friend_id = users[idx1].friends[i];
        for (int j = 0; j < users[idx2].friend_count; j++) {
            if (friend_id == users[idx2].friends[j]) {
                printf("Ortak arkadas: %d\n", friend_id);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Ortak arkadas bulunamadi.\n");
    }
}

// Topluluklar
void dfs_component(int idx, bool visited[]) {
    visited[idx] = true;
    printf("%d ", users[idx].id);

    for (int i = 0; i < users[idx].friend_count; i++) {
        int friend_idx = find_user_index(users[idx].friends[i]);
        if (friend_idx != -1 && !visited[friend_idx]) {
            dfs_component(friend_idx, visited);
        }
    }
}

void find_communities() {
    printf("\n--- Topluluklar ---\n");
    bool visited[MAX_USERS] = {false};
    for (int i = 0; i < user_count; i++) {
        if (!visited[i]) {
            printf("Topluluk: ");
            dfs_component(i, visited);
            printf("\n");
        }
    }
}

// Etki alaný
int dfs_reachability(int idx, bool visited[]) {
    visited[idx] = true;
    int count = 1;
    for (int i = 0; i < users[idx].friend_count; i++) {
        int friend_idx = find_user_index(users[idx].friends[i]);
        if (friend_idx != -1 && !visited[friend_idx]) {
            count += dfs_reachability(friend_idx, visited);
        }
    }
    return count;
}

void calculate_influence(int id) {
    printf("\n--- Kullanici %d etki alani ---\n", id);

    int idx = find_user_index(id);
    if (idx == -1) {
        printf("Kullanici bulunamadi.\n");
        return;
    }

    bool visited[MAX_USERS] = {false};
    int influence = dfs_reachability(idx, visited) - 1;

    printf("Toplam etki alani: %d kullanici\n", influence);
}

// Main fonksiyon
int main() {
    load_data("veriseti.txt");

    int users_list[] = {101, 102, 103, 104, 105};
    int n = 5;

    for (int i = 0; i < n; i++) {
        int user_id = users_list[i];
        find_friends_at_distance_bfs(user_id, 1);
        for (int j = 0; j < n; j++) {
            if (i != j) {
                find_common_friends(user_id, users_list[j]);
            }
        }
        calculate_influence(user_id);
    }

    find_communities();

    printf("\n--- Red-Black Tree inorder dolasimi (kimlik numaralarina gore) ---\n");
    inorder_rbt(root);
    printf("\n");

    free_rbt(root);
    return 0;
}

