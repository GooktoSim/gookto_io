/**
 * STS19 Captain
 * @file : InputAgents.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef INPUTAGENTS_H
#define INPUTAGENTS_H

#include <iostream>
#include <string>
#include <vector>

class InputAgents
{
private:
    int id;

    int typeId;
    double dpt_time;

    std::vector<int> link_seq;
    std::vector<int> node_seq;

    // unique to PublicVeh -- pax information
    std::vector<int> pax_list;
    std::vector<int> pax_origin;
    std::vector<int> pax_dest;

    // unique to PublicVeh -- station information
    std::vector<int> station_seq;
    std::vector<double> station_dwell_time;
    std::vector<int> station_in;
    std::vector<int> station_out;

public:
    InputAgents(int id, int typeId, double dpt_time);

    // adding new links/nodes to the link_seq / node_seq
    void addLink(int val);
    void addNode(int val);

    // adding to SAV, BAV attributes
    void addPaxList(int val);
    void addPaxOrigin(int val);
    void addPaxDest(int val);

    void addStation(int val);
    void addStationDwellTime(double val);
    void addStationIn(int val);
    void addStationOut(int val);

    // access functions
    int getId()
    {
        return id;
    }
    int getTypeId()
    {
        return typeId;
    }
    double getDepTime()
    {
        return dpt_time;
    }

    std::vector<int> getLinkSeq()
    {
        return link_seq;
    }
    std::vector<int> getNodeSeq()
    {
        return node_seq;
    }

    std::vector<int> getPaxList()
    {
        return pax_list;
    }
    std::vector<int> getPaxOrigin()
    {
        return pax_origin;
    }
    std::vector<int> getPaxDest()
    {
        return pax_dest;
    }

    std::vector<int> getStationSeq()
    {
        return station_seq;
    }

    std::vector<double> getStationDwellTime()
    {
        return station_dwell_time;
    }

    std::vector<int> getStationIn()
    {
        return station_in;
    }

    std::vector<int> getStationOut()
    {
        return station_out;
    }
};

#endif