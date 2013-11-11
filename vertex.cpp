#include <iostream>
#include <limits>

#include "vertex.hpp"
#include "edge.hpp"

// Default constructor
Vertex::Vertex()
{
}

// Constructor for the Vertex class. Initialises a vertex object to it's default state.
Vertex::Vertex(std::string& vertexName) : name(vertexName),
                                          inClosedSet(false),
                                          inOpenSet(false),
                                          associatedCost(std::numeric_limits<double>::max()),
                                          forestId(-1)
{
}

// Function to get the name of the vertex.
std::string Vertex::getName() const
{
    return name;
}

// Function to get the edge cost to the given remote vertex.
double Vertex::getOutgoingEdgeCost(const std::string& remoteVertexName)
{
    return outgoingEdges[remoteVertexName].getCost();
}

// Function to set the edge cost to the given remote vertex.
void Vertex::setOutgoingEdgeCost(const std::string& remoteVertexName, const double cost)
{
    outgoingEdges[remoteVertexName].setCost(cost);
}

// Function to check whether an edge exists or not to the given remote vertex.
bool Vertex::outgoingEdgeExists(const std::string& remoteVertexName)
{
    return outgoingEdges.count(remoteVertexName);
}

// Function to show edges connected to the vertex along with their associated costs.
void Vertex::showOutgoingEdges() const
{
    for (const auto i : outgoingEdges)
    {
        std::cout << i.first << "(" << i.second.getCost() << "), ";
    }
}

// Function to check whether the vertex is in the closed set or not.
bool Vertex::isInClosedSet() const
{
    return inClosedSet;
}

// Function to add the vertex to the closed set.
void Vertex::addToClosedSet()
{
    inClosedSet = true;
}

// Function to check whether the vertex is in the open set or not.
bool Vertex::isInOpenSet() const
{
    return inOpenSet;
}

// Function to add the vertex to the open set.
void Vertex::addToOpenSet()
{
    inOpenSet = true;
}

// Function to get the cost associated with the vertex.
// (applicable only to the Jarnik-Prim algorithm)
double Vertex::getAssocCost() const
{
    return associatedCost;
}

// Function to set the cost associated with the vertex.
// (applicable only to the Jarnik-Prim algorithm)
void Vertex::setAssocCost(double cost)
{
    associatedCost = cost;
}

// Function to get the forest ID of the vertex.
// (applicable only to Kruskal's algorithm)
int Vertex::getForestId() const
{
    return forestId;
}

// Function to set the forest ID of the vertex.
// (applicable only to Kruskal's algorithm)
void Vertex::addToForest(int f)
{
    forestId = f;
}

#if 0
// Function to get the map of edges connected to the vertex.
const Vertex::std::unordered_map<std::string, OutgoingEdge>& getOutgoingEdges()
{
    return outgoingEdges;
}
#endif

// Function to reset all information in the vertex object specific to MST computation.
void Vertex::resetMSTSpecificInfo()
{
    inClosedSet = false;
    inOpenSet = false;
    associatedCost = std::numeric_limits<double>::max();
}

// Associated cost comparison functor.
bool VertexAssocCostComparator::operator()(const Vertex& lhs, const Vertex& rhs) const
{
    return (lhs.getAssocCost() < rhs.getAssocCost());
}

// Vertex names comparison functor.
bool VertexComparator::operator()(const Vertex& lhs, const Vertex& rhs) const
{
    return (lhs.getName() == rhs.getName());
}
