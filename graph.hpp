#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

#include "vertex.hpp"

class Graph
{
private:
    unsigned int numVertices;
    unsigned int numEdges;
    std::unordered_map<std::string, Vertex> vertices;
    void addEdge(std::string&, std::string&, double);
    bool edgeExists(std::string&, std::string&);
    bool vertexExists(std::string&);

public:
    Graph(std::ifstream&);
    ~Graph();
    void showEdgeListRepresentation() const;
    void resetMSTSpecificInfo();
    void getJarnikPrimMST(int&, std::vector<std::string>&);
    void getKruskalMST(int&, std::vector<std::string>&);
};
