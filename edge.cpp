#include "edge.hpp"

std::string Edge::getRemoteVertexName() const
{
    return remoteVertexName;
}

double Edge::getCost() const
{
    return cost;
}

void Edge::setCost(double c)
{
    cost = c;
}
