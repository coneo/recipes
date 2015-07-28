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
#define InvalidBvChildNodeIndex BvChildNodeCnt

    enum BvRunningState
    {
        BRS_Execut = 0,
        BRS_Finish = 1,
        BRS_Error  = -1,
    };

    class BvNodePrecondition
    {
    public:
        virtual bool externalCondition(/*input*/) const = 0;
    };
    class BvNodePreconditionTRUE : public BvNodePrecondition
    {
    public:
        virtual bool externalCondition() const override
        {
            return true;
        }
    };
    class BvNodePreconditionFALSE : public BvNodePrecondition
    {
    public:
        virtual bool externalCondition() const override
        {
            return false;
        }
    };
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


    class BvNode
    {
    public:
        BvNode(BvNode* parent)
            : m_childCnt(0),
              m_parent(parent),
              m_name("nonename"),
              m_preCondition(NULL)
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

    private:
        BvNode* m_childs[MaxBvChildNodeCnt];
        int     m_childCnt;
        BvNode* m_parent;
        std::string m_name;
        BvNodePrecondition* m_preCondition;
    };


    class BvNodeFactory
    {
    public:
        static BvNode& onCreateSequenceNode(BvNode* parent, std::string nodeName)
        {
            BvNode* node = new BvNode(parent);
            onCreateCommon(node, parent, nodeName);
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
