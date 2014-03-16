
#ifndef BSTREE_H
#define BSTREE_H

using std::vector;
using std::shared_ptr;

class bstree {

public:
    struct btnode {
        int key;
        btnode *l;
        btnode *r;
        int get_key() const { return key; }
    };

    bstree();
    ~bstree();

    void clear_dfs();
    void clear_bfs();
    void insert(int n);
    void remove(int n);
    shared_ptr<vector<btnode*>> bfs();
    bool check();
    size_t size();
    void print(int indent = 0, btnode *n = nullptr);

private:
    btnode *_root;
    size_t _size;
    const int tabsize = 4;
};

void generate_full_tree(int h, bstree *t, int a = 0, int b = 0);

#endif
