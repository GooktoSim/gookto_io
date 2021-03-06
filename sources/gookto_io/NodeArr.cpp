#include <iostream>
#include <sstream>
#include <string>

#include <gookto_io/IntersectionNode.hpp>
#include <gookto_io/NodeArr.hpp>

#include <gookto_io/intersection/connection.hpp>
#include <gookto_io/intersection/intersectionPhase.hpp>
#include <gookto_io/intersection/port.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

NodeArr::NodeArr()
{
    TiXmlDocument doc;

    doc.LoadFile(STSIO::NetworkXMLPath.string().c_str());
    std::cout << "Loading NodeArr" << std::endl;

    if (!doc.LoadFile(STSIO::NetworkXMLPath.string().c_str()))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *e = root->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement())
    {
        std::string elemName2 = e->Value();

        if (elemName2 == "nodes")
        {
            std::cout << "Got nodes" << std::endl;

            for (TiXmlElement *e2 = e->FirstChildElement(); e2 != NULL;
                 e2 = e2->NextSiblingElement())
            {
                std::string att1 = e2->Attribute("type");

                // TYPES OF NODES --> intersection, normal, terminal
                if (att1 == "intersection")
                {
                    // std::cout << "got intersection" << std::endl;
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        0, atol(e2->Attribute("id")),
                        atoi(e2->Attribute("num_connection")),
                        atoi(e2->Attribute("num_port")));

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // IntersectionNode
                            int temp = -1;
                            std::string att2 = e3->Attribute("type");
                            if (att2 == "in")
                            {
                                temp = 1;
                            }
                            port single_link(atol(e3->Attribute("link_id")),
                                             atoi(e3->Attribute("direction")),
                                             temp);
                            single_node.pushLink(single_link);
                        }

                        else if (val1 == "connection")
                        {
                            connection single_connection(
                                atol(e3->Attribute("id")),
                                atol(e3->Attribute("from_link")),
                                atol(e3->Attribute("from_lane")),
                                atol(e3->Attribute("to_link")),
                                atol(e3->Attribute("to_lane")), 1,
                                atof(e3->Attribute("length")));
                            single_node.pushConnection(single_connection);
                        }

                        else if (val1 == "phase")
                        {
                            intersectionPhase single_phase(
                                atol(e3->Attribute("id")));
                            for (TiXmlElement *e4 = e3->FirstChildElement();
                                 e4 != NULL; e4 = e4->NextSiblingElement())
                            {
                                std::string val2 = e4->Value();
                                if (val2 == "connection")
                                {
                                    single_phase.pushConnectionRef(
                                        atol(e4->Attribute("id_ref")));
                                    single_phase.pushPriority(
                                        atof(e4->Attribute("priority")));
                                }
                            }
                            single_node.pushPhase(single_phase);
                        }

                        else if (val1 == "signal_plan")
                        {
                            // std::string phase_string =
                            // e3->Attribute("phase"); std::string tmp1 =
                            // e3->Attribute("phase");

                            auto iss1 = std::istringstream{ e3->Attribute(
                                "phase_length") };
                            auto str1 = std::string{};
                            while (iss1 >> str1)
                            {
                                single_node.pushPhaseLength(atoi(str1.c_str()));
                            }

                            auto iss2 =
                                std::istringstream{ e3->Attribute("order") };
                            auto str2 = std::string{};
                            while (iss2 >> str2)
                            {
                                single_node.pushPhaseOrder(atoi(str2.c_str()));
                            }

                            single_node.setPhaseOffset(
                                atoi(e3->Attribute("offset")));
                        }
                    }
                    Nodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                    single_node.freeConnectedTable();
                    single_node.freePhaseTable();
                }

                else if (att1 == "normal")
                {
                    // std::cout << "got normal" << std::endl;
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        1, atol(e2->Attribute("id")), -1,
                        atoi(e2->Attribute("num_port")));

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for normal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // IntersectionNode
                            int temp = -1;
                            std::string att2 = e3->Attribute("type");
                            if (att2 == "in")
                            {
                                temp = 1;
                            }
                            port single_link(atol(e3->Attribute("link_id")),
                                             atoi(e3->Attribute("direction")),
                                             temp);
                            single_node.pushLink(single_link);
                        }
                        else if (val1 == "connection")
                        {
                            connection single_connection(
                                atol(e3->Attribute("id")),
                                atol(e3->Attribute("from_link")),
                                atol(e3->Attribute("from_lane")),
                                atol(e3->Attribute("to_link")),
                                atol(e3->Attribute("to_lane")),
                                atof(e3->Attribute("priority")),
                                atof(e3->Attribute("length")));
                            single_node.pushConnection(single_connection);
                        }
                    }
                    Nodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                }

                else if (att1 == "terminal")
                {
                    // std::cout << "got terminal" << std::endl;
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        2, atol(e2->Attribute("id")), -1,
                        atoi(e2->Attribute("num_port")));

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for terminal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // IntersectionNode
                            int temp = -1;
                            std::string att2 = e3->Attribute("type");
                            if (att2 == "in")
                            {
                                temp = 1;
                            }
                            port single_link(atol(e3->Attribute("link_id")),
                                             atoi(e3->Attribute("direction")),
                                             temp);
                            single_node.pushLink(single_link);
                        }
                    }
                    Nodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                }
            }
        }
    }
    doc.Clear();
};

void NodeArr::showArr()
{
    if (Nodes.size() == 0)
    {
        std::cout << "ITS EMPTY" << std::endl;
    }

    for (size_t i = 0; i < Nodes.size(); i++)
    {
        std::cout << Nodes[i].getId() << " " << Nodes[i].getNumConn() << " "
                  << Nodes[i].getNumLink() << std::endl;

        // Example:: getting the first connection ID of each intersection
        std::cout << "connID :" << Nodes[i].getConnections()[0].getConnId()
                  << std::endl;
    }
}