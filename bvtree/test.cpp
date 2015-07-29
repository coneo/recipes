#include "bvtree.h"
#include <sstream>

void test_create()
{
    bvtree::BvNode* root = new bvtree::BvNode(NULL);
    for (int i = 0; i < 5; ++i)
    {
        std::stringstream ss;
        ss << "node" << i;
        bvtree::BvNode& node = bvtree::BvNodeFactory::onCreateSequenceNode(root, ss.str());
        for (int j = 0; j < 3; ++j)
        {
            std::stringstream mm;
            mm << "child" << j;
            bvtree::BvNodeFactory::onCreateSequenceNode(&node, mm.str());
        }
    }

    root->printOut();
}

void tree_tick()
{
}

int main()
{
    test_create();
    return 0;
}
