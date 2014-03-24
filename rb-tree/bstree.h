#ifndef BSTREE_H
#define BSTREE_H

using std::vector;
using std::shared_ptr;

namespace algo {

    struct bstnode {
        typedef bstnode node;
        int key;
        node* l;
        node* r;
        int get_key() const { return key; }
        node*& resolve(node* x) {
            assert(l == x || r == x);
            return l == x ? l : r;
        }
    };

    template<typename T>
    class bstree {

    public:

        typedef typename T tree_node;

        bstree() : _root(nullptr) {}
        ~bstree() { clear_bfs(); }

        size_t size() { return _size; }
        tree_node* root() { return _root; }

        void clear_dfs();
        void clear_bfs();
        tree_node* search(int n);
        virtual tree_node* insert(int n);
        void remove(int n);
        //shared_ptr<vector<tree_node*>> bfs();
        const vector<tree_node*>& bfs();
        bool check_bst();
        void print(int indent = 0, tree_node* n = nullptr);
        static void generate_full_tree(int h, bstree<tree_node>* t, int a = 0, int b = 0);

    private:
        tree_node* _root;
        size_t _size;
        const int _tabsize = 4;
    };

    //
    // deallocate tree using depth first search
    // 
    template<typename T>
    void bstree<T>::clear_dfs() {
        using std::stack;
        using std::pair;
        using std::make_pair;
        if (_root == nullptr) {
            assert(size() == 0);
            return;
        }
        stack<pair<tree_node*, tree_node*>> s;
        s.push(make_pair(nullptr, _root));
        while (!s.empty()) {
            bool del = true;
            tree_node* p = s.top().first;
            tree_node* c = s.top().second;
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
    template<typename T>
    void bstree<T>::clear_bfs() {
        using std::queue;
        if (_root == nullptr)
            return;
        queue<tree_node*> q;
        q.push(_root);
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                tree_node* c = q.front();
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
    template<typename T>
    T* bstree<T>::insert(int n) {
        tree_node* c = nullptr;
        if (_root != nullptr) {
            c = _root;
            assert(_size != 0);
            while (
                (n <= c->key && c->l != nullptr) ||
                (n > c->key && c->r != nullptr)) {
                c = (n <= c->key) ? c->l : c->r;
            }
            if (n <= c->key) {
                assert(c->l == nullptr);
                c->l = new tree_node;
                c = c->l;
                c->l = c->r = nullptr;
                c->key = n;
            }
            else {
                assert(c->r == nullptr);
                c->r = new tree_node;
                c = c->r;
                c->l = c->r = nullptr;
                c->key = n;
            }
        }
        else {
            assert(_size == 0);
            c = new tree_node;
            c->l = c->r = nullptr;
            c->key = n;
            _root = c;
        }
        _size += 1;
        assert(c != nullptr);
        return c;
    }

    template<typename T>
    bool bstree<T>::check_bst() {
        using std::queue;
        queue<tree_node*> q;
        if (_root != nullptr)
            q.push(_root);
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                tree_node* c = q.back();
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

    template<typename T>
    const typename vector<T*>& bstree<T>::bfs() {
        using std::queue;
        using std::shared_ptr;
        using std::make_shared;
        if (_root == nullptr)
            return shared_ptr<vector<tree_node*>>();
        vector<tree_node*> v;
        queue<tree_node*> q;
        q.push(_root);
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                tree_node* c = q.front();
                q.pop();
                v.push_back(c);
                if (c->l != nullptr)
                    q.push(c->l);
                if (c->r != nullptr)
                    q.push(c->r);
            }
        }
        return make_shared<vector<tree_node*>>(v);
    }

    //
    // O(h)
    // 
    template<typename T>
    void bstree<T>::remove(int n) {
        if (_root != nullptr) {
            assert(_size != 0);
            tree_node* c = _root;
            tree_node* p = nullptr;
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
                    tree_node* cl = c->r;
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

    template<typename T>
    typename bstree<T>::tree_node* bstree<T>::search(int n) {
        if (_root != nullptr) {
            assert(_size != 0);
            tree_node* c = _root;
            while (
                (n < c->key && c->l != nullptr) ||
                (n > c->key && c->r != nullptr)) {
                c = (n <= c->key) ? c->l : c->r;
            }
            return c->key == n ? c : nullptr;
        }
        else
            return nullptr;
    }

    template<typename T>
    void bstree<T>::print(int indent, tree_node* n) {
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
            print(indent + _tabsize, n->l);
        if (n->r != nullptr)
            print(indent + _tabsize, n->r);
    }

    template<typename T>
    void bstree<T>::generate_full_tree(int h, bstree<tree_node>* t, int a, int b) {
        assert(h < 16);
        if (h == 0 || a > b)
            return;
        if (b == 0) {
            assert(t->size() == 0);
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


}

#endif // #ifndef BSTREE_H
