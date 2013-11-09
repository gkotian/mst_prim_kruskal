#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream> // for std::stringstream

#include "graph.hpp"
#include "vertex.hpp"

Graph::Graph(std::ifstream& fp) : numEdges(0)
{
    // The first line contains the number of vertices in the graph
    fp >> numVertices;

    unsigned int numVerticesNamedInFile = 0;
    unsigned int lineNum = 2;
    std::string vertex1, vertex2;
    double cost;

    while (!fp.eof())
    {
        fp >> vertex1;
        fp >> vertex2;
        fp >> cost;

        // Ensure that we haven't read past the end of file in reading the current line
        if (fp.eof())
        {
            break;
        }

        if (!vertexExists(vertex1))
        {
            if (numVerticesNamedInFile < numVertices)
            {
                Vertex v(vertex1);
                vertices[vertex1] = v;
                ++numVerticesNamedInFile;
            }
            else
            {
                std::cout << "Cannot add vertex " << vertex1 << "as the vertices limit has been reached. skipping edge (" << vertex1 << ", " << vertex2 << ", " << cost << ") - line # " << lineNum << std::endl;
                ++lineNum;
                continue;
            }
        }

        if (!vertexExists(vertex2))
        {
            if (numVerticesNamedInFile < numVertices)
            {
                Vertex v(vertex2);
                vertices[vertex2] = v;
                ++numVerticesNamedInFile;
            }
            else
            {
                std::cout << "Cannot add vertex " << vertex2 << "as the vertices limit has been reached. skipping edge (" << vertex1 << ", " << vertex2 << ", " << cost << ") - line # " << lineNum << std::endl;
                ++lineNum;
                continue;
            }
        }

        if (edgeExists(vertex1, vertex2))
        {
            std::cout << "Request to add duplicate edge between " << vertex1 << " and " << vertex2 << " at line # " << lineNum << "... ignoring" << std::endl;
        }
        else
        {
            addEdge(vertex1, vertex2, cost);
            ++numEdges;
        }

        ++lineNum;
    }

    if (numVerticesNamedInFile < numVertices)
    {
        unsigned int numUnnamedVertices = numVertices - numVerticesNamedInFile;

        if (numUnnamedVertices == 1)
        {
            std::cout << "1 vertex was not named in the file, will call it 'Unnamed 1'" << std::endl;
        }
        else
        {
            std::cout << numUnnamedVertices << " vertices were not named in the file, will call them 'Unnamed 1' through 'Unnamed " << numUnnamedVertices << "'" << std::endl;
        }

        std::stringstream ss;
        std::string tmp;

        for (unsigned int i = numVerticesNamedInFile; i < numVertices; ++i)
        {
            // Create the desired vertex name.
            ss << "Unnamed " << (numVertices - numVerticesNamedInFile);

            // Add it to the graph.
            tmp = ss.str();
            Vertex v(tmp);
            vertices[tmp] = v;

            // Clear the stringstream variable.
            ss.str("");
            tmp.clear();
        }
    }
}

Graph::~Graph()
{
    vertices.erase(vertices.begin(), vertices.end());
}

void Graph::addEdge(std::string& vertex1, std::string& vertex2, double cost)
{
    vertices[vertex1].setEdgeCost(vertex2, cost);
    vertices[vertex2].setEdgeCost(vertex1, cost);
}

bool Graph::edgeExists(std::string& vertex1, std::string& vertex2)
{
    return vertices[vertex1].edgeExists(vertex2);
}

bool Graph::vertexExists(std::string& vertexName)
{
    return vertices.count(vertexName);
}

void Graph::showEdgeListRepresentation() const
{
    std::cout << "Number of vertices = " << numVertices << std::endl;
    std::cout << "Number of edges = " << numEdges << std::endl;

    for (auto i = vertices.cbegin(); i != vertices.cend(); ++i)
    {
        std::cout << i->first << " : ";
        i->second.showEdges();
        std::cout << std::endl;
    }
}

void Graph::resetMSTSpecificInfo()
{
}

void Graph::getJarnikPrimMST(int& mstCost, std::vector<std::string>& vMSTVertices)
{
}

void Graph::getKruskalMST(int& mstCost, std::vector<std::string>& vMSTVertices)
{
}
