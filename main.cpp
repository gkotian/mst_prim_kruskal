#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "graph.hpp"

int main()
{
    std::string filename;
    double mstCost;
    std::vector<std::string> vMSTVertices;

    while (1)
    {
        std::cout << "Enter graph file to use (q to quit): ";
        std::cin >> filename;

        if (filename == "q")
        {
            break;
        }

        // All graph files are kept in a directory called 'graph_files'
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
        //g.showEdgeListRepresentation();

        // Initialise variables used for MST calculation
        mstCost = 0;
        vMSTVertices.clear();
        g.resetMSTSpecificInfo();

        // Get an MST using the Jarnik-Prim algorithm
        g.getJarnikPrimMST(mstCost, vMSTVertices);

        std::cout << "Using Jarnik-Prim algorithm" << std::endl;
        std::cout << "---------------------------" << std::endl;
        if (mstCost == -1)
        {
            std::cout << "    no minimum spanning tree exists for this graph." << std::endl;
        }
        else
        {
            std::cout << "    MST cost = " << mstCost << std::endl;

            std::cout << "    ";
            for (auto i : vMSTVertices)
            {
                std::cout << i << ", ";
            }
            std::cout << std::endl;
        }

        // Initialise variables used for MST calculation
        mstCost = 0;
        vMSTVertices.clear();
        g.resetMSTSpecificInfo();

        // Get an MST using Kruskal's algorithm
        g.getKruskalMST(mstCost, vMSTVertices);
    }
}
