#include <string>
#include <iostream>
#include <vector>

#include "intersection/intersectionPhase.hpp"
#pragma once


class Signalplans 
{
private:
    /*
    Node Types:
        Intersection = 0
        Normal = 1
        Terminal = 2
     */
    int id;

    double end; //end time
    
    double start; // start time  
    /**
     * numConnections: Applicable only for IntersectionNode
     */
    // std::vector<intersectionSignal> signalTable; //intersectionPhase:  ID, connectionId (list), priority(list)

    std::vector<intersectionPhase> phaseTable; //intersectionPhase:  ID, connectionId (list), priority(list)
    /**
     * intersectionPhase: Intersection
     */

    std::vector<int> phaseLength;
    std::vector<int> phaseOrder;
    int phaseOffset;
    
    
    //signalSequence: order(list), phase_length
    //may have to make this into a Pointer Loop

public:
    Signalplans(int id, double end, double start);

    void initPhase(); //set all priority to 0 for all connections;
    void setPhase( int phase ); //set priority according to chosen phase number
    void setPhaseOffset ( int offset );

    void pushPhase ( intersectionPhase phase );
    void pushPhaseLength ( int length );
    void pushPhaseOrder ( int order );

    //Check Functions
    int getId() const { return id; }
    // int getNode() const { return node; }

    int getPhaseOffset() { return phaseOffset; }

    std::vector<intersectionPhase> getPhaseTable() { return phaseTable; }
    std::vector<int> getPhaseLength() { return phaseLength; }
    std::vector<int> getPhaseOrder() { return phaseOrder; }

    void freePhaseTable() { std::vector<intersectionPhase>().swap(phaseTable); }
    void freePhaseLength() { std::vector<int>().swap(phaseLength); }
    void freePhaseOrder() { std::vector<int>().swap(phaseOrder); }
};