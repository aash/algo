
#include "stdafx.h"
#include "bstree.h"
#include "rbtree.h"
#include "lest.hpp"

const lest::test spec[] =
{
    "algo::bstree constructed full tree satisfies bst rules", [] {
        EXPECT([]{
            using algo::bstree;
            using algo::generate_full_tree;
            bstree t;
            generate_full_tree(4, &t);
            return t.check();
        }())
    },
    "algo::bstree remove operation is correct", [] {
        EXPECT([]{
            using std::mem_fun;
            using std::shared_ptr;
            using std::shuffle;
            using std::transform;
            using std::vector;
            using std::mt19937;
            using std::random_device;
            using algo::bstree;
            using algo::generate_full_tree;
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
            using algo::bstree;
            using algo::generate_full_tree;
            rbtree bst;
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
            return bst.size() != 0;
        }())
    }
};

int main(int argc, char* argv[])
{
    return lest::run(spec);
}
