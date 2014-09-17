#include "xmlparser.h"

XmlNode::XmlNode(xmlNodePtr node)
    : m_node(node)
{
}

XmlNode::~XmlNode()
{
}

XmlNode XmlNode::getChild(const char* nodename)
{
    xmlNodePtr nextNode = m_node->xmlChildrenNode;
    if (!nextNode) return XmlNode(NULL);

    while (xmlStrcmp(nextNode->name, (const xmlChar*)nodename))
    {
        nextNode = nextNode->next;
    }
    return XmlNode(nextNode);
}

void XmlNode::setToNext()
{
    xmlNodePtr nextNode = m_node->next;
    while (nextNode && xmlStrcmp(nextNode->name, (const xmlChar*)m_node->name))
    {
        nextNode = nextNode->next;
    }
    m_node = nextNode;
}

std::string XmlNode::getStr(const char* nodename)
{
    char* tmpstr = NULL;
    tmpstr = (char *)xmlGetProp(m_node, (xmlChar *)nodename);
    if (tmpstr == NULL) return "";
    std::string retstr = tmpstr;
    if (tmpstr) xmlFree(tmpstr);
    return retstr;
}

XmlNode& XmlNode::operator++()
{
    setToNext();
    return *this;
}

XmlParser::XmlParser()
{
    m_doc = NULL;
}

XmlParser::~XmlParser()
{
    end();
}

bool XmlParser::initFile(const char* filename)
{
    end();
    m_doc = xmlParseFile(filename);
    return (m_doc != NULL);
}

void XmlParser::end()
{
    if (m_doc)
    {
        xmlFreeDoc(m_doc);
        m_doc = NULL;
    }
}

XmlNode XmlParser::getRootNode(const char* nodename)
{
    xmlNodePtr rootNode = xmlDocGetRootElement(m_doc);
    if (!rootNode) return XmlNode(NULL);

    if (xmlStrcmp(rootNode->name, (const xmlChar*)nodename))
    {
        printf("wrong root node name %s\n", nodename);
    }
    return XmlNode(rootNode);
}
