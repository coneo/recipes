#ifndef _BV_ANYDATA_H
#define _BV_ANYDATA_H

namespace bvtree
{
    class BvAnyData
    {
    public:
        template<typename RealDataType>
        BvAnyData(RealDataType* _data)
            : m_realData(_data)
        {}

        template<typename RealDataType>
        RealDataType& getRealData()
        {
            return *reinterpret_cast<RealDataType*>(m_realData);
        }

        template<typename RealDataType>
        const RealDataType& getRealData() const
        {
            return *reinterpret_cast<const RealDataType*>(m_realData);
        }

        template<typename RealDataType>
        BvAnyData& operator =(RealDataType* _data)
        {
            set<RealDataType>(_data);
            return *this;
        }

    private:
        template<typename RealDataType>
        void set(RealDataType* _data)
        {
            m_realData = reinterpret_cast<void*>(_data);
        }
        void* m_realData;
    };
}
#endif
