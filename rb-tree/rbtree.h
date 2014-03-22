#ifndef RBTREE_H
#define RBTREE_H

#include "bstree.h"

namespace algo {

    struct rbtnode {
        typedef rbtnode node;
        int key;
        bool red;
        node* l;
        node* r;
        int get_key() const { return key; }
        node*& resolve(node* x) {
            assert(l == x || r == x);
            return l == x ? l : r;
        }
    };

    template<typename T>
    class rbtree : public bstree<T> {

    public:

        void rotate_left(tree_node* x, tree_node* p);
        void rotate_right(tree_node* y, tree_node* p);

    };

    //   (x)   rotate_left  (y)
    //   / \                / \
    //  a   (y)    ==>    (x)  c
    //      / \           / \
    //     b   c         a   b
    template<typename T>
    void rbtree<T>::rotate_left(tree_node* x, tree_node* p) {
        assert(x != nullptr && p != nullptr);
        if (x->r != nullptr) {
            T* y = x->r;
            p->resolve(x) = y;
            x->r = y->l;
            y->l = x;
        }
    }

    //   (x)  rotate_right  (y)
    //   / \                / \
    //  a   (y)    <==    (x)  c
    //      / \           / \
    //     b   c         a   b
    template<typename T>
    void rbtree<T>::rotate_right(tree_node* y, tree_node* p) {
        assert(y != nullptr && p != nullptr);
        if (y->l != nullptr) {
            T* x = y->l;
            p->resolve(y) = x;
            y->l = x->r;
            x->r = y;
        }
    }

}

#endif // #ifndef RBTREE_H
