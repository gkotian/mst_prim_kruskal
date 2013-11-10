#pragma once

#include <string>

class Edge
{
private:
    std::string vertex1;
    std::string vertex2;
    double cost;

public:
    Edge(const std::string&, const std::string&, const double);
    const std::string& getVertex1() const { return vertex1; }
    const std::string& getVertex2() const { return vertex2; }
    double getCost() const;
};

class OutgoingEdge
{
private:
    std::string remoteVertexName;
    double cost;

public:
    std::string getRemoteVertexName() const;
    double getCost() const;
    void setCost(double);
};

std::ostream& operator<<(std::ostream&, const Edge&);
