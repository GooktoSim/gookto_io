//! NextSim Captain
//! Copyright (c) 2019 Justin Kim, Kaist
//! Copying, reproducing and commercial use is not allowed.
//! We are not conveying any rights to any intellectual property of any third
//! parties
//!
//! \file : InputLink.hpp
//! \version : 1.0
//! \author : Jae Hwan Jung, Justin Kim

#ifndef INPUTLINK_H
#define INPUTLINK_H


#include <vector>
#include <string>
#include "BaseClass.hpp"
#include "InputLane.hpp"
// #include "InputLane.hpp"
// #include "InputCell.hpp"


class InputLink : public MetaData
{
private:
    std::size_t m_toNode = 0, m_fromNode = 0;
    int m_numLane;
    std::string _type, _sim_type;

    std::vector<InputLane> LaneArr;
    std::vector<std::size_t> LaneIds;
    std::vector<int> m_laneNumCellVector;

public:
    //Constructors
    InputLink(std::size_t id, int lane, double length, double width, double stopline);
    ~InputLink() = default;
    InputLink(const InputLink& link) = default;
    InputLink& operator=(const InputLink& link) = default;


    //each cell might have different 4 params
    std::vector<std::vector<double>> Get2DFreeFlowSpeed();
    std::vector<std::vector<double>> Get2DMaxSpeed();
    std::vector<std::vector<double>> Get2DMinSpeed();
    std::vector<std::vector<double>> Get2DQmax2D();
    std::vector<std::vector<double>> Get2DWaveSpeed();
    std::vector<std::vector<size_t>> Get2DMaxVehicle();
    [[nodiscard]] const std::vector<std::size_t>& GetLaneIds() const { return LaneIds; }
    [[nodiscard]] const std::vector<InputLane>& GetLaneArr() const { return LaneArr; }

    [[nodiscard]] std::size_t GetID() const { return ID; }
    int GetNumSect() { return m_laneNumCellVector[0]; }
    int GetNumLane() { return m_numLane; }
    void setNumLane(int num);

    void pushLaneId(InputLane lane);

    void SetFromNode(std::size_t val);
    std::size_t GetFromNode() { return m_fromNode; }

    void SetToNode(std::size_t val);
    std::size_t GetToNode() { return m_toNode; }

    void SetSimType(const std::string& val) { _sim_type = val; }
    [[nodiscard]] const std::string& GetSimType() const { return _sim_type; }
    void SetType(const std::string& val) { _type = val; }
    [[nodiscard]] const std::string& GetType() const { return _type; }
    //Free 2d Vectors


    //Need to make helper functions for Designating cell-by-cell values
};

#endif
