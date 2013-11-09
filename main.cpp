#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "graph.hpp"

int main()
{
    std::string filename;
    int mstCost;
    std::vector<std::string> vMSTVertices;
    std::string rootVertex;

    while (1)
    {
        std::cout << "Enter graph file to use (q to quit): ";
        std::cin >> filename;

        if (filename == "q")
        {
            break;
        }

        filename = "graph_files/" + filename;

        std::ifstream fp(filename);

        if (!fp.is_open())
        {
            std::cout << "\"" << filename << "\" not found." << std::endl;
            continue;
        }

        // Generate a graph from the given input file
        Graph g(fp);

        fp.close();

        // Check if the graph was generated as expected
        g.showEdgeListRepresentation();

        std::cout << "Choose a root vertex for the minimum spanning tree : ";
        std::cin >> rootVertex;

        // Initiliase variables used for MST calculation
        mstCost = 0;
        vMSTVertices.clear();
        g.resetMSTSpecificInfo();

        // Get an MST using the Jarnik-Prim algorithm
        g.getJarnikPrimMST(mstCost, vMSTVertices);

        // Initiliase variables used for MST calculation
        mstCost = 0;
        vMSTVertices.clear();
        g.resetMSTSpecificInfo();

        g.getKruskalMST(mstCost, vMSTVertices);
    }
}
