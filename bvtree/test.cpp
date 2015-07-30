#include "bvtree.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
using namespace bvtree;

void test_create()
{
    BvNode* root = new BvNode(NULL);
    for (int i = 0; i < 5; ++i)
    {
        std::stringstream ss;
        ss << "node" << i;
        BvNode& node = BvNodeFactory::onCreateSequenceNode(root, ss.str());
        for (int j = 0; j < 3; ++j)
        {
            std::stringstream mm;
            mm << "child" << j;
            BvNodeFactory::onCreateSequenceNode(&node, mm.str());
        }
    }

    root->printOut();
}

class Node_MoveTo : public BvNodeTerminal
{
public:
    Node_MoveTo(BvNode* parnet)
        : BvNodeTerminal(parnet)
    {}
protected:
    virtual BvRunningState _doExecute(/*input,output*/) override
    {
        cout << "move to action" << endl;
        return BRS_Finish;
    }
};
class Node_Idle : public BvNodeTerminal
{
public:
    Node_Idle(BvNode* parnet)
        : BvNodeTerminal(parnet)
    {}
protected:
    virtual BvRunningState _doExecute() override
    {
        cout << "idle action" << endl;
        return BRS_Finish;
    }
};

class tree_obj
{
public:
    void create()
    {
        BvNode& root = BvNodeFactory::onCreateSequenceNode(NULL, "root");
        BvNodeFactory::onCreateTerminalNode<Node_MoveTo>(&root, "movenode");
        BvNodeFactory::onCreateTerminalNode<Node_Idle>(&root, "idlenode");
        root.printOut();
        m_root = &root;
    }

    void tick()
    {
        if (m_root->evaluate())
        {
            m_root->tick();
        }
    }
private:
    BvNode* m_root;
};

void tree_tick()
{
    tree_obj obj;
    obj.create();
    obj.tick();
    obj.tick();
    obj.tick();
}

int main()
{
    //test_create();
    tree_tick();
    return 0;
}
