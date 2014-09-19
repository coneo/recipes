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

    XmlNode getChild(const char* nodename = NULL);

    template <typename T,
             typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
    bool getNum(const char* nodename, T& value)
    {
        char* tmp = NULL;
        tmp = (char*)xmlGetProp(m_node, (xmlChar*)nodename);
        if (tmp == NULL) return false;
        value = std::stoll(tmp);
        if (tmp) xmlFree(tmp);
        return true;
    }

    template <typename T,
             typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    bool getNum(const char* nodename, T& value)
    {
        char* tmp = NULL;
        tmp = (char*)xmlGetProp(m_node, (xmlChar*)nodename);
        if (tmp == NULL) return false;
        value = std::stold(tmp);
        if (tmp) xmlFree(tmp);
        return true;
    }

    bool getStr(const char* nodename, std::string& str);

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
