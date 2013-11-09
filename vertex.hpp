#pragma once

#include <unordered_map>
#include <string>

#include "edge.hpp"

class Vertex
{
private:
    std::string name;
    std::unordered_map<std::string, Edge> edges;
    bool inClosedSet;
    bool inOpenSet;
    double associatedCost;

public:
    Vertex();
    explicit Vertex(std::string&);
    std::string getName() const;
    double getEdgeCost(const std::string&);
    void setEdgeCost(const std::string&, const double);
    bool edgeExists(const std::string&);
    void showEdges() const;
    bool isInClosedSet() const;
    void addToClosedSet();
    bool isInOpenSet() const;
    void addToOpenSet();
    double getAssocCost() const;
    void setAssocCost(double);
    const std::unordered_map<std::string, Edge>& getEdges() { return edges; }
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
