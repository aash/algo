
#include "stdafx.h"
#include "rbtree.h"

void generate_full_tree(int h, bstree &t, int a = 0, int b = 0) {
    assert(h < 16);
    assert(a <= b && b - a <= 1 << h);
    if (h == 0)
        return;
    if (b == 0) {
        b = 1 << h;
        a = 0;
    }
    int m = (b + a) / 2;
    t.insert(m);
    generate_full_tree(h - 1, t, a, m);
    generate_full_tree(h - 1, t, m, b);
}

int main(int argc, char* argv[])
{
    const int n = 10;
    bstree bst;

    generate_full_tree(3, bst);
    assert(bst.check());

    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<int> v;
    std::copy(bst.values().begin(), bst.values().end(), std::back_inserter(v));
    std::shuffle(v.begin(), v.end(), g);

    while (v.size() != 0) {
        bst.remove(v.back());
        assert(bst.check());
        std::cout << v.back() << "\n";
        v.pop_back();
    }
    //for (int i = 0; i < n; i++) {
    //    bst.insert(i);
    //}

	return 0;
}
