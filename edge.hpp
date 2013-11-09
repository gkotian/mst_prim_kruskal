#pragma once

#include <string>

class Edge
{
private:
    std::string remoteVertexName;
    double cost;

public:
    std::string getRemoteVertexName() const;
    double getCost() const;
    void setCost(double);
};
