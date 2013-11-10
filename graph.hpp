#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <map>

#include "vertex.hpp"
#include "priority_queue.hpp"
#include "edge.hpp"

class Graph
{
private:
    unsigned int numVertices;
    unsigned int numEdges;
    std::unordered_map<std::string, Vertex> vertices;
    std::multimap<double, Edge> edges;
    void addEdge(std::string&, std::string&, double);
    bool edgeExists(std::string&, std::string&);
    bool vertexExists(std::string&);
    std::vector<bool> forestIds; // true => forest ID taken, false => forest ID available

public:
    explicit Graph(std::ifstream&);
    ~Graph();
    void showEdgeListRepresentation() const;
    void resetMSTSpecificInfo();
    void updateOpenSet(PriorityQueue<Vertex, VertexAssocCostComparator, VertexComparator>&, std::string&);
    void getJarnikPrimMST(double&, std::vector<std::string>&);
    void getKruskalMST(double&, std::vector<std::string>&);
    void combineForests(int, int);
    int getNewForestId();
    void releaseForestId(int);
};
