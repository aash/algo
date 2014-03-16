
#include "stdafx.h"
#include "rbtree.h"

using std::vector;
using std::transform;
using std::mt19937;
using std::random_device;
using std::shared_ptr;
using std::shuffle;
using std::mem_fun_ref;
using std::mem_fun;
using std::cout;
using std::for_each;
using std::ptr_fun;

struct deref {
    int operator() (bstree::btnode *n) {
        return n->key;
    }
};

int main(int argc, char* argv[])
{
    bstree bst;
    generate_full_tree(4, &bst);
    bst.print();
    assert(bst.check());

#define QWE
#ifdef QWE
    random_device rd;
    mt19937 g(rd());
    vector<int> v;
    shared_ptr<vector<bstree::btnode*>> sv = bst.bfs();
    transform(sv->begin(), sv->end(), back_inserter(v), mem_fun(&bstree::btnode::get_key));
    shuffle(v.begin(), v.end(), g);

    while (bst.size() != 0) {
        bst.remove(v.back());
        cout << "--------------------------------------\n";
        cout << "remove " << v.back() << "\n";
        bst.print();
        assert(bst.check());
        v.pop_back();
    }
#endif

    return 0;
}
