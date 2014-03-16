
#include "stdafx.h"
#include "bstree.h"
#include "rbtree.h"
#include "lest.hpp"

// algorithm
using std::shuffle;
using std::transform;
// vector
using std::vector;
// random
using std::mt19937;
using std::random_device;
// memory
using std::shared_ptr;
using std::make_shared;
// iostream
using std::cout;
// string
using std::string;
//functional
using std::for_each;
using std::ptr_fun;
using std::mem_fun_ref;
using std::mem_fun;

using algo::bstree;
using algo::generate_full_tree;

const lest::test spec[] =
{
    "algo::bstree constructed full tree satisfies binary search tree properties", []
    {
        EXPECT([]{
            bstree t;
            generate_full_tree(4, &t);
            return t.check();
        }())
    },
    "algo::bstree remove operation is correct", []
    {
        EXPECT([]{
            bstree bst;
            generate_full_tree(4, &bst);
            random_device rd;
            mt19937 g(rd());
            vector<int> v;
            shared_ptr<vector<bstree::btnode*>> sv = bst.bfs();
            transform(sv->begin(), sv->end(), back_inserter(v), mem_fun(&bstree::btnode::get_key));
            shuffle(v.begin(), v.end(), g);
            while (v.size() != 0) {
                bst.remove(v.back());
                assert(bst.check());
                v.pop_back();
            }
            return bst.size() == 0;
        }())
    }
};


int main(int argc, char* argv[])
{
    return lest::run(spec);
}
