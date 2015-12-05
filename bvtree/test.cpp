#include "bvtree.h"
#include <sstream>
#include <string>
#include <iostream>
#include <unistd.h>

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


struct stMoveInput
{
    int x;
    int y;
};
struct stMoveOutput
{
    int x;
    int y;
};

class Node_MoveTo : public BvNodeTerminal
{
public:
    Node_MoveTo(BvNode* parnet)
        : BvNodeTerminal(parnet)
    {}
protected:
    virtual BvRunningState _doExecute(const BvInputParam& input, BvOutputParam& output) override
    {
        const stMoveInput& inputData = input.getRealData<stMoveInput>();
        cout << "move to action x:" << inputData.x << " y:" << inputData.y << endl;
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
    virtual BvRunningState _doExecute(const BvInputParam& input, BvOutputParam& output) override
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
        static int tx=0,ty=0;
        tx++; ty++;
        m_input.x = tx;
        m_input.y = ty;
        BvInputParam input(&m_input);
        BvOutputParam output(&m_output);
        if (m_root->evaluate(input))
        {
            m_root->tick(input,output);
        }
    }
private:
    BvNode* m_root;
    stMoveInput m_input;
    stMoveOutput m_output;
};

void tree_tick()
{
    tree_obj obj;
    obj.create();
    while (true)
    {
        sleep(1);
        obj.tick();
    }
}

int main()
{
    //test_create();
    tree_tick();
    return 0;
}
