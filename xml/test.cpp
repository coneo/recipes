#include "xmlparser.h"
#include <string>
#include <iostream>

using namespace std;

bool loadConfig()
{
    XmlParser xml;
    if (!xml.initFile("test.xml")) return false;

    XmlNode root = xml.getRootNode("config");
    if (!root.valid())
    {
        printf("parse config failed\n");
        return false;
    }

    std::string configname = root.getStr("name");
    cout << configname << endl;

    //parse node_a
    XmlNode nodeA = root.getChild("node_a");
    if (!nodeA.valid())
        return false;

    int index = nodeA.getNum<int>("index");
    cout << "node_a index=" << index << endl;

    float index2 = nodeA.getNum<float>("index2");
    cout << "node_a index2=" << index2 << endl;

    for (XmlNode item = nodeA.getChild("item"); item.valid(); ++item)
    {
        int id = item.getNum<int>("id");
        std::string name = item.getStr("name");
        cout << "item id=" << id << " name=" << name << endl;
    }
    cout << endl;

    //parse node_b
    XmlNode nodeB = root.getChild("node_b");
    if (!nodeB.valid())
        return false;

    cout << "node_b float=" << nodeB.getNum<float>("float") << endl;
    cout << "node_b int=" << nodeB.getNum<int>("int") << endl;
    for (XmlNode item = nodeB.getChild("item"); item.valid(); ++item)
    {
        int id = item.getNum<int>("id");
        std::string name = item.getStr("name");
        cout << "item id=" << id << " name=" << name << endl;
    }
    return true;
}

int main()
{
    loadConfig();
}
