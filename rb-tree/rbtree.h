
#ifndef RBTREE_H
#define RBTREE_H

#include "bstree.h"

class rbtree: public bstree {
public:
    rbtree();
    ~rbtree();
};

void generate_full_tree(int h, bstree *t, int a = 0, int b = 0);

#endif