
#ifndef RBTREE_H
#define RBTREE_H

using std::set;

class bstree {


    struct btnode {
        btnode *l;
        btnode *r;
        int key;
    };

public:
    bstree();
    ~bstree();

    void clear_dfs();
    void clear_bfs();
    void insert(int n);
    void remove(int n);
    bool check();
    size_t size();
    const set<int>& values() { return _values; }

private:
    btnode *_root;
    size_t _size;
    set<int> _values;
};

class rb_tree {
public:
    rb_tree();
    ~rb_tree();
};

#endif