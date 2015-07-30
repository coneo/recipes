#ifndef _BVTREE_H
#define _BVTREE_H

#include <string>
#include <iostream>
#include <assert.h>

namespace bvtree
{
#define SAFE_DELETE(x)\
    if (x) \
        delete x;

#define MaxBvChildNodeCnt 16
#define InvalidBvChildNodeIndex MaxBvChildNodeCnt

    enum BvRunningState
    {
        BRS_Execut = 0,
        BRS_Finish = 1,
        BRS_Error  = -1,
    };

    enum BvTerminalState
    {
        BTS_Ready = 1,
        BTS_Running = 2,
        BTS_Finish = 3,
    };

    //条件类
    class BvNodePrecondition
    {
    public:
        virtual bool externalCondition(/*input*/) const = 0;
    };
    //条件 真
    class BvNodePreconditionTRUE : public BvNodePrecondition
    {
    public:
        virtual bool externalCondition() const override
        {
            return true;
        }
    };
    //条件 假
    class BvNodePreconditionFALSE : public BvNodePrecondition
    {
    public:
        virtual bool externalCondition() const override
        {
            return false;
        }
    };
    //条件否 一元运算
    class BvNodePreconditionNOT : public BvNodePrecondition
    {
    public:
        BvNodePreconditionNOT(BvNodePrecondition* lcondition)
            : m_lcondition(lcondition)
        {
        }
        ~BvNodePreconditionNOT()
        {
            SAFE_DELETE(m_lcondition);
        }
        virtual bool externalCondition() const override
        {
            return !m_lcondition->externalCondition();
        }

    private:
        BvNodePrecondition* m_lcondition;
    };


    //节点类
    class BvNode
    {
    public:
        BvNode(BvNode* parent, BvNodePrecondition* preCondition = NULL)
            : m_childCnt(0),
              m_parent(parent),
              m_name("nonename"),
              m_preCondition(preCondition)
        {
            for (int i = 0; i < MaxBvChildNodeCnt; ++i)
                m_childs[i] = NULL;
        }
        virtual ~BvNode()
        {
            for (int i = 0; i < MaxBvChildNodeCnt; ++i)
                SAFE_DELETE(m_childs[i]);
            SAFE_DELETE(m_preCondition);
        }

        BvNode& addChild(BvNode* child)
        {
            assert(child != NULL);
            if (m_childCnt >= MaxBvChildNodeCnt)
                return (*this);
            m_childs[m_childCnt++] = child;
            return (*this);
        }

        bool evaluate(/*input*/)
        {
            return (m_preCondition == NULL || m_preCondition->externalCondition()) && _doEvaluate();
        }

        BvRunningState tick()
        {
            return _doTick();
        }

        void setName(std::string name) { m_name = name; }
        std::string getName() const { return m_name; }

        void printOut()
        {
            for (int i = 0; i < m_childCnt; ++i)
            {
                std::cout << getName() << ": [" << i <<"] :" << m_childs[i]->getName() << std::endl;
                m_childs[i]->printOut();
            }
        }

    protected:
        virtual bool _doEvaluate(/*input*/)
        {
            return true;
        }

        virtual BvRunningState _doTick()
        {
            return BRS_Finish;
        }

        bool indexValid(int index) const
        {
            return index >= 0 && index < m_childCnt;
        }

    protected:
        BvNode* m_childs[MaxBvChildNodeCnt];
        int     m_childCnt;
        BvNode* m_parent;
        std::string m_name;
        BvNodePrecondition* m_preCondition;
    };

    //顺序节点
    class BvNodeSequence : public BvNode
    {
    public:
        BvNodeSequence(BvNode* parnet, BvNodePrecondition* preCondition = NULL)
            : BvNode(parnet, preCondition),
              m_curNodeIndex(InvalidBvChildNodeIndex)
        {
        }
        virtual bool _doEvaluate(/*input*/) override;
        virtual BvRunningState _doTick() override;

    private:
        int m_curNodeIndex;
    };

    //行为节点基类，需要用户去继承该类实现具体的行为节点
    class BvNodeTerminal : public BvNode
    {
    public:
        BvNodeTerminal(BvNode* parnet, BvNodePrecondition* preCondition = NULL)
            : BvNode(parnet, preCondition),
              m_state(BTS_Ready),
              m_needExit(false)
        {}

        virtual BvRunningState _doTick();
    protected:
        virtual void _doEnter(/*input*/){}
        virtual BvRunningState _doExecute(/*input,output*/){ return BRS_Finish; }
        virtual void _doExit(/*input,BvRunningState*/){}
    private:
        BvTerminalState m_state;
        bool m_needExit;
    };

    //节点工厂，用于生产各类节点
    class BvNodeFactory
    {
    public:
        static BvNode& onCreateSequenceNode(BvNode* parent, std::string nodeName)
        {
            BvNode* node = new BvNodeSequence(parent);
            onCreateCommon(node, parent, nodeName);
            return (*node);
        }

        template <typename T>
        static BvNode& onCreateTerminalNode(BvNode* parnet, std::string nodeName)
        {
            //FIXME check if T is subclass of BvNodeTerminal
            BvNodeTerminal* node = new T(parnet);
            onCreateCommon(node, parnet, nodeName);
            return (*node);
        }

    private:
        static void onCreateCommon(BvNode* me, BvNode* parent, std::string name)
        {
            assert(me != NULL);
            if (parent)
                parent->addChild(me);
            me->setName(name);
        }
    };
};
#endif
