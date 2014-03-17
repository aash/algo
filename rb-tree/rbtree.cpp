
#include "stdafx.h"
#include "rbtree.h"

namespace algo {

    //   (x)   rotate_left  (y)
    //   / \                / \
    //  a   (y)    ==>    (x)  c
    //      / \           / \
    //     b   c         a   b
    void rbtree::rotate_left(btnode* x, btnode* p) {
        assert(x != nullptr && p != nullptr);
        if (x->r != nullptr) {
            btnode* y = x->r;
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
    void rbtree::rotate_right(btnode* y, btnode* p) {
        assert(y != nullptr && p != nullptr);
        if (y->l != nullptr) {
            btnode* x = y->l;
            p->resolve(y) = x;
            y->l = x->r;
            x->r = y;
        }
    }

}