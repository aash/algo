
#include "stdafx.h"
#include "rbtree.h"

bstree::bstree() : _root(nullptr) {}

bstree::~bstree() {
    clear_dfs();
}

//
// deallocate tree using depth first search
// 
void bstree::clear_dfs() {
    using std::stack;
    using std::pair;
    using std::make_pair;
    if (_root == nullptr) {
        assert(size() == 0);
        return;
    }
    stack<pair<btnode*, btnode*>> s;
    s.push(make_pair(nullptr, _root));
    while (!s.empty()) {
        bool del = true;
        btnode *p = s.top().first;
        btnode *c = s.top().second;
        if (c->l != nullptr) {
            del = false;
            s.push(make_pair(c, c->l));
        }
        if (c->r != nullptr) {
            del = false;
            s.push(make_pair(c, c->r));
        }
        if (del) {
            if (p != nullptr) {
                ((p->l == c) ? p->l : p->r) = nullptr;
            }
            delete c;
            _size -= 1;
            s.pop();
        }
    }
    assert(size() == 0);
}

//
// deallocate tree using breadth first search
//
void bstree::clear_bfs() {
    using std::queue;
    if (_root == nullptr)
        return;
    queue<btnode*> q;
    q.push(_root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            btnode *c = q.front();
            q.pop();
            if (c->l != nullptr)
                q.push(c->l);
            if (c->r != nullptr)
                q.push(c->r);
            delete c;
            _size -= 1;
        }
    }
    assert(size() == 0);
}

//
// O(h)
//
void bstree::insert(int n) {
    if (_root != nullptr) {
        assert(_size != 0);
        btnode *c = _root;
        while (
            (n <= c->key && c->l != nullptr) ||
            (n > c->key && c->r != nullptr)) {
            c = (n <= c->key) ? c->l : c->r;
        }
        if (n <= c->key) {
            assert(c->l == nullptr);
            c->l = new btnode;
            c = c->l;
            c->l = c->r = nullptr;
            c->key = n;
        }
        else {
            assert(c->r == nullptr);
            c->r = new btnode;
            c = c->r;
            c->l = c->r = nullptr;
            c->key = n;
        }
    }
    else {
        assert(_size == 0);
        _root = new btnode;
        _root->l = _root->r = nullptr;
        _root->key = n;
    }
    _size += 1;
}

//
// O(h)
// 
void bstree::remove(int n) {
    if (_root != nullptr) {
        assert(_size != 0);
        btnode *c = _root, *p = nullptr;
        while (
            (n < c->key && c->l != nullptr) ||
            (n > c->key && c->r != nullptr)) {
            p = c;
            c = (n < c->key) ? c->l : c->r;
        }
        if (n == c->key) {
            if (p != nullptr) {
                (n <= p->key ? p->l : p->r) = (c->r != nullptr) ? c->r : c->l;
            }
            else {
                _root = (c->r != nullptr) ? c->r : c->l;
            }
            if (c->l != nullptr && c->r != nullptr) {
                int m = c->l->key;
                btnode *cl = c->r;
                while (
                    (m <= cl->key && cl->l != nullptr) ||
                    (m > cl->key && cl->r != nullptr)) {
                    cl = (m <= cl->key) ? cl->l : cl->r;
                }
                if (m <= cl->key) {
                    assert(cl->l == nullptr);
                    cl->l = c->l;
                }
                else {
                    assert(cl->r == nullptr);
                    cl->r = c->l;
                }
            }
            _size -= 1;
            delete c;
        }
    }
}

bool bstree::check() {
    using std::queue;
    queue<btnode*> q;
    if (_root != nullptr)
        q.push(_root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            btnode *c = q.back();
            q.pop();
            if (c->l != nullptr) {
                if (c->l->key > c->key)
                    return false;
                q.push(c->l);
            }
            if (c->r != nullptr) {
                if (c->r->key <= c->key)
                    return false;
                q.push(c->r);
            }
        }
    }
    return true;
}

size_t bstree::size() {
    return _size;
}

shared_ptr<vector<bstree::btnode*>> bstree::bfs() {
    using std::queue;
    using std::shared_ptr;
    using std::make_shared;
    if (_root == nullptr)
        return shared_ptr<vector<bstree::btnode*>>();
    vector<bstree::btnode*> v;
    queue<btnode*> q;
    q.push(_root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            btnode *c = q.front();
            q.pop();
            v.push_back(c);
            if (c->l != nullptr)
                q.push(c->l);
            if (c->r != nullptr)
                q.push(c->r);
        }
    }
    return make_shared<vector<bstree::btnode*>>(v);
}

void bstree::print(int indent, btnode *n) {
    using std::cout;
    using std::setw;
    if (_root == nullptr)
        return;
    if (n == nullptr)
        n = _root;
    if (indent != 0)
        cout << setw(indent) << ' ';
    cout << n->key << '\n';
    if (n->l != nullptr)
        print(indent + tabsize, n->l);
    if (n->r != nullptr)
        print(indent + tabsize, n->r);
}

void generate_full_tree(int h, bstree *t, int a = 0, int b = 0) {
    assert(h < 16);
    if (h == 0 || a > b)
        return;
    if (b == 0) {
        b = (1 << h) - 1;
        a = 1;
    }
    int m = (b + a) / 2;
    t->insert(m);
    if (h > 1) {
        generate_full_tree(h - 1, t, a, m - 1);
        generate_full_tree(h - 1, t, m + 1, b);
    }
}
