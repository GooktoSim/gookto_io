#include <iostream>
#include <sstream>
#include <string>

#include <gookto_io/Scenario.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

Scenario::Scenario()
{
    TiXmlDocument doc;

    doc.LoadFile(STSIO::ScenarioXMLPath.string().c_str());
    std::cout << "Loading ODScenario" << std::endl;

    if (!doc.LoadFile("./network_xml/odscenario.xml"))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "Scenario")
        {
            const char *id = elem->Attribute("id");
            const char *od_id = elem->Attribute("od_matrix_id");

            if (!id)
                throw std::runtime_error("Element should have 'id' attribute");
            if (!od_id)
                throw std::runtime_error("Element should have 'od_matrix_id' attribute");
            

            ODscenario.emplace_back(std::make_pair(atoi(id), atoi(od_id)));
        }
    };
    doc.Clear();
}