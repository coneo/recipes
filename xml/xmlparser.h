#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include <libxml/parser.h>
#include <string>

/*
 * XML节点类，用于对节点操作
 */
class XmlNode
{
public:
    XmlNode(xmlNodePtr node);
    ~XmlNode();

    bool valid() { return m_node != NULL; }

    XmlNode getChild(const char* nodename);

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
        getNum(const char* nodename)
    {
        char* tmp = NULL;
        tmp = (char*)xmlGetProp(m_node, (xmlChar*)nodename);
        if (tmp == NULL) return 0;
        T value = std::stoi(tmp);
        if (tmp) xmlFree(tmp);
        return value;
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
        getNum(const char* nodename)
    {
        char* tmp = NULL;
        tmp = (char*)xmlGetProp(m_node, (xmlChar*)nodename);
        if (tmp == NULL) return 0.0;
        //T value = std::stof(tmp);
        T value = std::stod(tmp);
        if (tmp) xmlFree(tmp);
        return value;
    }

    std::string getStr(const char* nodename);

    XmlNode& operator++();

private:
    void setToNext();

private:
    xmlNodePtr m_node;
};

/*
 * XML解析器，用于对xml进行解析,dump等操作
 */
class XmlParser
{
public:
    XmlParser();
    ~XmlParser();

    bool initFile(const char* filename);

    XmlNode getRootNode(const char* nodename);

private:
    void end();

private:
    xmlDocPtr m_doc;
};

#endif
