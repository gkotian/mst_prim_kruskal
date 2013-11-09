#include <iostream>
#include <limits>

#include "vertex.hpp"
#include "edge.hpp"

Vertex::Vertex()
{
}

Vertex::Vertex(std::string& vertexName) : name(vertexName),
                                          inClosedSet(false),
                                          inOpenSet(false),
                                          associatedCost(std::numeric_limits<double>::max())
{
}

std::string Vertex::getName() const
{
    return name;
}

double Vertex::getEdgeCost(const std::string& remoteVertexName)
{
    return edges[remoteVertexName].getCost();
}

void Vertex::setEdgeCost(const std::string& remoteVertexName, const double cost)
{
    edges[remoteVertexName].setCost(cost);
}

bool Vertex::edgeExists(const std::string& remoteVertexName)
{
    return edges.count(remoteVertexName);
}

void Vertex::showEdges() const
{
    for (auto i = edges.cbegin(); i != edges.cend(); ++i)
    {
        std::cout << i->first << "(" << i->second.getCost() << "), ";
    }
}

bool Vertex::isInClosedSet() const
{
    return inClosedSet;
}

void Vertex::addToClosedSet()
{
    inClosedSet = true;
}

bool Vertex::isInOpenSet() const
{
    return inOpenSet;
}

void Vertex::addToOpenSet()
{
    inOpenSet = true;
}

double Vertex::getAssocCost() const
{
    return associatedCost;
}

void Vertex::setAssocCost(double cost)
{
    associatedCost = cost;
}

#if 0
const Vertex::std::unordered_map<std::string, Edge>& getEdges()
{
    return edges;
}
#endif

bool VertexAssocCostComparator::operator()(const Vertex& lhs, const Vertex& rhs) const
{
    return (lhs.getAssocCost() < rhs.getAssocCost());
}
