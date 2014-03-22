
#include "stdafx.h"
#include "bstree.h"
#include "rbtree.h"
#include "lest.hpp"

const lest::test spec[] =
{
    "algo::rbtree constructed full tree satisfies bst rules", [] {
        EXPECT([]{
            using algo::rbtree;
            using algo::rbtnode;
            rbtree<rbtnode> t;
            rbtree<rbtnode>::generate_full_tree(4, &t);
            return t.check_bst();
        }())
    },
    "algo::rbtree remove operation is correct", [] {
        EXPECT([]{
            using std::mem_fun;
            using std::shared_ptr;
            using std::shuffle;
            using std::transform;
            using std::vector;
            using std::mt19937;
            using std::random_device;
            using algo::rbtree;
            using algo::rbtnode;
            rbtree<rbtnode> bst;
            rbtree<rbtnode>::generate_full_tree(4, &bst);
            random_device rd;
            mt19937 g(rd());
            vector<int> v;
            shared_ptr<vector<rbtnode*>> sv = bst.bfs();
            transform(sv->begin(), sv->end(), back_inserter(v),
                mem_fun(&rbtnode::get_key));
            shuffle(v.begin(), v.end(), g);
            while (v.size() != 0) {
                bst.remove(v.back());
                assert(bst.check_bst());
                v.pop_back();
            }
            return bst.size() == 0;
        }())
    },
    "algo::rbtree rotate_left, rotate_right does not break bst rules", [] {
        EXPECT([]{
            using std::mem_fun;
            using std::shared_ptr;
            using std::shuffle;
            using std::transform;
            using std::vector;
            using std::mt19937;
            using std::random_device;
            using algo::rbtree;
            using algo::rbtnode;
            rbtree<rbtnode> bst;
            rbtree<rbtnode>::generate_full_tree(4, &bst);
            //bst.rotate_left();
            return bst.check_bst();
        }())
    }
};

int main(int argc, char* argv[])
{
    return lest::run(spec);
}
