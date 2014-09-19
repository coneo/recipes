#include "xmlparser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class stFoo
{
public:
    stFoo()
    {
        itemList.clear();
    }
    std::string toStr()
    {
        std::ostringstream os;
        os << "index=" << index << std::endl;
        os << "index2=" << index2 << std::endl;
        for (const auto& item : itemList)
        {
            os << "item: id=" << item.first << " name=" << item.second << std::endl;
        }
        return os.str();
    }
    int32_t index {0};
    float index2 {0.0};
    std::map<int32_t,std::string> itemList;
};

bool loadConfig()
{
    stFoo foo;

    XmlParser xml;
    if (!xml.initFile("test.xml")) return false;

    XmlNode root = xml.getRootNode("config");
    if (!root.valid())
    {
        printf("parse config failed\n");
        return false;
    }

    std::string configname = "";
    root.getStr("name", configname);
    cout << configname << endl;

    //parse node_a
    XmlNode nodeA = root.getChild("node_a");
    if (!nodeA.valid())
        return false;

    nodeA.getNum("index", foo.index);
    nodeA.getNum("index2", foo.index2);
    for (XmlNode item = nodeA.getChild("item"); item.valid(); ++item)
    {
        int id = 0;
        item.getNum("id", id);
        std::string name = "";
        item.getStr("name", name);
        foo.itemList[id] = name;
    }
    cout << foo.toStr() << endl;

    return true;
}

int main()
{
    loadConfig();
}
