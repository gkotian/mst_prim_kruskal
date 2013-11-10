#include <iostream>

#include "edge.hpp"

Edge::Edge(const std::string& v1, const std::string& v2, const double c) : vertex1(v1),
                                                                           vertex2(v2),
                                                                           cost(c)
{
}

#if 0
const std::string& getVertex1() const
{
}

const std::string& getVertex2() const
{
}
#endif

double Edge::getCost() const
{
    return cost;
}

std::ostream& operator<<(std::ostream& out, const Edge& e)
{
    out << e.getVertex1() << " <--- " << e.getCost() << " ---> " << e.getVertex2() << std::endl;

    return out;
}

std::string OutgoingEdge::getRemoteVertexName() const
{
    return remoteVertexName;
}

double OutgoingEdge::getCost() const
{
    return cost;
}

void OutgoingEdge::setCost(double c)
{
    cost = c;
}
