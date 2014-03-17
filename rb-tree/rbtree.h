
#ifndef RBTREE_H
#define RBTREE_H

#include "bstree.h"

namespace algo {

    class rbtree : public bstree {
    public:

        struct btnode {
            int key;
            bool red;
            btnode* l;
            btnode* r;
            int get_key() const { return key; }
            btnode*& resolve(btnode* x) {
                assert(l == x || r == x);
                return l == x ? l : r;
            }
        };

        void rbtree::rotate_left(btnode* x, btnode* p);
        void rbtree::rotate_right(btnode* y, btnode* p);
    };
}

#endif