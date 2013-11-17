#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "graph.hpp"
#include "vertex.hpp"
#include "priority_queue.hpp"

// The constructor reads the given input file and creates a graph accordingly.
Graph::Graph(std::ifstream& fp) : numEdges(0)
{
    // The first line contains the number of vertices in the graph.
    fp >> numVertices;

    unsigned int numVerticesNamedInFile = 0;
    unsigned int lineNum = 2;
    std::string vertex1, vertex2;
    double cost;

    while (!fp.eof())
    {
        fp >> vertex1 >> vertex2 >> cost;

        // Ensure that we haven't read past the end of file in reading the current line.
        if (fp.eof())
        {
            break;
        }

        // Add the first vertex to the graph if it hasn't been added already.
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

        // Add the second vertex to the graph if it hasn't been added already.
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

        // Add the edge to the graph if it hasn't been added already.
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

    // If the graph has more vertices than had been named in the file, then give some default
    // names to the unnamed vertices.
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
    vertices[vertex1].setOutgoingEdgeCost(vertex2, cost);
    vertices[vertex2].setOutgoingEdgeCost(vertex1, cost);

    edges.insert(std::pair<double, Edge>(cost, Edge(vertex1, vertex2, cost)));
}

bool Graph::edgeExists(std::string& vertex1, std::string& vertex2)
{
    return vertices[vertex1].outgoingEdgeExists(vertex2);
}

bool Graph::vertexExists(std::string& vertexName)
{
    return vertices.count(vertexName);
}

void Graph::showEdgeListRepresentation() const
{
    std::cout << "Number of vertices = " << numVertices << std::endl;
    std::cout << "Number of edges = " << numEdges << std::endl;

    for (const auto i : vertices)
    {
        std::cout << i.first << " : ";
        i.second.showOutgoingEdges();
        std::cout << std::endl;
    }
}

void Graph::resetMSTSpecificInfo()
{
    for (auto& i : vertices)
    {
        i.second.resetMSTSpecificInfo();
    }
}

void Graph::updateOpenSet(PriorityQueue<Vertex, VertexAssocCostComparator, VertexComparator>& openSet, std::string& newlyClosedVertex)
{
    for (auto i : vertices[newlyClosedVertex].getOutgoingEdges())
    {
        if (vertices[i.first].isInClosedSet())
        {
            continue;
        }
        else if (vertices[i.first].isInOpenSet())
        {
            if (i.second.getCost() < vertices[i.first].getAssocCost())
            {
                openSet.remove(vertices[i.first]);
                vertices[i.first].setAssocCost(i.second.getCost());
                openSet.push(vertices[i.first]);
            }
        }
        else
        {
            vertices[i.first].addToOpenSet();
            vertices[i.first].setAssocCost(i.second.getCost());
            openSet.push(vertices[i.first]);
        }
    }
}

void Graph::getJarnikPrimMST(double& mstCost, std::vector<std::string>& vMSTVertices)
{
    std::string rootVertexName;

    // Get the name of the first vertex, and take it as the root
    for (auto i : vertices)
    {
        rootVertexName = i.second.getName();
        break;
    }

    // Add the root vertex to the closed set right away.
    vMSTVertices.push_back(rootVertexName);
    vertices[rootVertexName].addToClosedSet();
    unsigned int numClosedVertices = 1;

    std::string newlyClosedVertex = rootVertexName;

    // The 'openSet' priority queue contains vertices currently under consideration for being
    // added to the closed set.
    PriorityQueue<Vertex, VertexAssocCostComparator, VertexComparator> openSet;

    while (numClosedVertices != numVertices)
    {
        updateOpenSet(openSet, newlyClosedVertex);

        // If the open set is empty at this point, then it means that no minimum spanning tree
        // exists for the graph.
        if (openSet.isEmpty())
        {
            mstCost = -1;
            vMSTVertices.clear();
            return;
        }

        Vertex tmp = openSet.top();
        openSet.pop();

        newlyClosedVertex = tmp.getName();
        mstCost += tmp.getAssocCost();
        vMSTVertices.push_back(newlyClosedVertex);

        vertices[newlyClosedVertex].addToClosedSet();
        ++numClosedVertices;
    }
}

void Graph::getKruskalMST(double& mstCost, std::vector<std::string>& vMSTVertices)
{
    // Initialise all elements of the forest IDs vector to false (i.e. all forest IDs are
    // available).
    for (unsigned int i = 0; i < numVertices; ++i)
    {
        forestIds.push_back(false);
    }

    unsigned int numClosedVertices = 0;

    for (auto i : edges)
    {
        bool isInClosedSetV1 = vertices[i.second.getVertex1()].isInClosedSet();
        bool isInClosedSetV2 = vertices[i.second.getVertex2()].isInClosedSet();

        if (isInClosedSetV1 && isInClosedSetV2)
        {
            unsigned int forestIdV1 = vertices[i.second.getVertex1()].getForestId();
            unsigned int forestIdV2 = vertices[i.second.getVertex2()].getForestId();

            if (forestIdV1 == forestIdV2)
            {
                // Adding this edge would form a loop. So this edge cannot be part of the MST.
                continue;
            }
            else
            {
                // Adding this edge will join two separate forests, so it can be part of the MST.
                mstCost += i.second.getCost();

                // Merge the two forests into a single larger forest (retain the smaller forest ID
                // and release the other).
                int retainedForestId;
                int forestIdToReturn;

                if (forestIdV1 < forestIdV2)
                {
                    retainedForestId = forestIdV1;
                    forestIdToReturn = forestIdV2;
                }
                else
                {
                    retainedForestId = forestIdV2;
                    forestIdToReturn = forestIdV1;
                }

                combineForests(retainedForestId, forestIdToReturn);

                releaseForestId(forestIdToReturn);
            }
        }
        else if (!isInClosedSetV1 && !isInClosedSetV2)
        {
            // Both vertices are not closed. This is the beginning of a new forest.
            mstCost += i.second.getCost();
            vertices[i.second.getVertex1()].addToClosedSet();
            vertices[i.second.getVertex2()].addToClosedSet();

            unsigned int newForestId = getNewForestId();
            if (newForestId < 0)
            {
                std::cout << "Forest IDs exhausted" << std::endl;
            }

            vertices[i.second.getVertex1()].addToForest(newForestId);
            vertices[i.second.getVertex2()].addToForest(newForestId);

            vMSTVertices.push_back(i.second.getVertex1());
            vMSTVertices.push_back(i.second.getVertex2());
            numClosedVertices += 2;

            if (numClosedVertices == numVertices)
            {
                break;
            }
        }
        else
        {
            // One of the vertices is closed, and the other is not. So grab the free floating
            // vertex into the forest, and make it closed.
            mstCost += i.second.getCost();

            if (isInClosedSetV1)
            {
                vertices[i.second.getVertex2()].addToClosedSet();
                vertices[i.second.getVertex2()].addToForest(vertices[i.second.getVertex1()].getForestId());
                vMSTVertices.push_back(i.second.getVertex2());
            }
            else
            {
                vertices[i.second.getVertex1()].addToClosedSet();
                vertices[i.second.getVertex1()].addToForest(vertices[i.second.getVertex2()].getForestId());
                vMSTVertices.push_back(i.second.getVertex1());
            }

            ++numClosedVertices;

            if (numClosedVertices == numVertices)
            {
                break;
            }
        }
    }

    // If all vertices were not closed, then no MST exists.
    if (numClosedVertices != numVertices)
    {
        mstCost = -1;
        vMSTVertices.clear();
    }
}

void Graph::combineForests(int newForestId, int oldForestId)
{
    for (auto& i : vertices)
    {
        if (i.second.getForestId() == oldForestId)
        {
            i.second.addToForest(newForestId);
        }
    }
}

int Graph::getNewForestId()
{
    unsigned int forestId = 0;

    for (auto i : forestIds)
    {
        if (i == false)
        {
            i = true;
            return forestId;
        }

        ++forestId;
    }

    return -1;
}

void Graph::releaseForestId(int f)
{
    if ((f >= 0) && (f < static_cast<int>(forestIds.size())))
    {
        forestIds[f] = false;
    }
}
