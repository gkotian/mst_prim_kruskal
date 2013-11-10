#pragma once

#include <unordered_map>
#include <string>

#include "edge.hpp"

class Vertex
{
private:
    std::string name;
    std::unordered_map<std::string, OutgoingEdge> outgoingEdges;
    bool inClosedSet;
    bool inOpenSet;
    double associatedCost;
    int forestId;

public:
    Vertex();
    explicit Vertex(std::string&);
    std::string getName() const;
    double getOutgoingEdgeCost(const std::string&);
    void setOutgoingEdgeCost(const std::string&, const double);
    bool outgoingEdgeExists(const std::string&);
    void showOutgoingEdges() const;
    bool isInClosedSet() const;
    void addToClosedSet();
    bool isInOpenSet() const;
    void addToOpenSet();
    double getAssocCost() const;
    void setAssocCost(double);
    int getForestId() const;
    void addToForest(int);
    const std::unordered_map<std::string, OutgoingEdge>& getOutgoingEdges() { return outgoingEdges; }
    void resetMSTSpecificInfo();
};

class VertexAssocCostComparator
{
public:
    bool operator()(const Vertex&, const Vertex&) const;
};

class VertexComparator
{
public:
    bool operator()(const Vertex&, const Vertex&) const;
};
