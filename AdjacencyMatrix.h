#ifndef ADJACENCY
#define ADJACENCY
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

class AdjacencyMatrix
{
        public:
                AdjacencyMatrix();
                AdjacencyMatrix(unsigned int num_vertices);
                void add_edge(unsigned int p, unsigned int q, int weight);
                unsigned int add_vertex();
                unsigned int order();
                set<unsigned int> out_neighbors(unsigned int p);
                int weight(unsigned int src, unsigned int dst);
                void display();
        private:
                unsigned int num_vert;
                vector< vector< unsigned int > > vertex;

};

#endif
