#include "bvtree.h"

namespace bvtree
{
bool BvNodeSequence::_doEvaluate(const BvInputParam& input)
{
    unsigned int child_index = 0;
    if (m_curNodeIndex != InvalidBvChildNodeIndex)
        child_index = m_curNodeIndex;

    if (indexValid(child_index))
    {
        BvNode* child_node = m_childs[child_index];
        if (child_node->evaluate(input))
            return true;
    }
    return false;
}

BvRunningState BvNodeSequence::_doTick(const BvInputParam& input, BvOutputParam& output)
{
    BvRunningState isFinish = BRS_Finish;

    //first time
    if (m_curNodeIndex == InvalidBvChildNodeIndex)
        m_curNodeIndex = 0;

    //FIXME check index outbound
    BvNode* curNode = m_childs[m_curNodeIndex];
    isFinish = curNode->tick(input, output);
    if (isFinish == BRS_Finish)
    {
        ++m_curNodeIndex;
        if (m_curNodeIndex >= m_childCnt)
        {
            m_curNodeIndex = InvalidBvChildNodeIndex;
        }
        else
        {
            isFinish = BRS_Execut;
        }
    }
    if (isFinish < 0)
    {
        m_curNodeIndex = InvalidBvChildNodeIndex;
    }
    return isFinish;
}

BvRunningState BvNodeTerminal::_doTick(const BvInputParam& input, BvOutputParam& output)
{
    BvRunningState isFinish = BRS_Finish;

    if (m_state == BTS_Ready)
    {
        _doEnter(input);
        m_needExit = true;
        m_state = BTS_Running;
        //setActiveNode(this);
    }
    if (m_state == BTS_Running)
    {
        isFinish = _doExecute(input, output);
        //setActiveNode(this);
        if (isFinish == BRS_Finish || isFinish < 0)
            m_state = BTS_Finish;
    }
    if (m_state == BTS_Finish)
    {
        if (m_needExit)
            _doExit(input, isFinish);
        m_state = BTS_Ready;
        m_needExit = false;
        //setActiveNode(NULl);
    }
    return isFinish;
}

};
