#include <iostream>

#include "vertex.hpp"
#include "edge.hpp"

Vertex::Vertex()
{
}

Vertex::Vertex(std::string& vertexName) : name(vertexName),
                                          inClosedSet(false),
                                          inOpenSet(false)
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

void Vertex::putInClosedSet()
{
    inClosedSet = true;
}

bool Vertex::isInOpenSet() const
{
    return inOpenSet;
}

void Vertex::putInOpenSet()
{
    inOpenSet = true;
}
