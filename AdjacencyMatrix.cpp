#include"AdjacencyMatrix.h"
using namespace std;

AdjacencyMatrix::AdjacencyMatrix()
{
        num_vert=0;
        vertex.resize(num_vert);
}
AdjacencyMatrix::AdjacencyMatrix(unsigned int num_vertices)
{
        //Initializes the graph to have num_vertices vertices.
        num_vert=num_vertices;
        vertex.resize(num_vert);
        for(unsigned int i=0; i<num_vert; i++)
        {
                vertex[i].resize(num_vert);
        }
}
void AdjacencyMatrix::display()
{
        int a=0;
        int b=0;
        int c=0;
        for(unsigned int i=a;i<vertex.size();i++)
        {
                for(unsigned int j=b;j<vertex[i].size();j++)
                {
                        if(vertex[i][j]!=0)
                        {
                                cout<<"("<<i<<", " <<j <<") "<<c <<" " <<vertex[i][j] <<endl;
                                c++;
                        }
                }
        }

}
set<unsigned int> AdjacencyMatrix::out_neighbors(unsigned int p)
{
        set<unsigned int> neighbor;
        for(int i=0;i<vertex[p].size();i++)
        {
                if(vertex[p][i])
                {
                        neighbor.insert(i);
                }
        }
        return neighbor;
}

int AdjacencyMatrix::weight(unsigned int src, unsigned int dst)
{
   int w = vertex[src][dst];
   return w;
}
void AdjacencyMatrix::add_edge(unsigned int p, unsigned int q,int weight)
{
        if(vertex[p][q]==0)
        {
                vertex[p][q]=weight;
        }

}
unsigned int AdjacencyMatrix::add_vertex()
{
        vertex.resize(num_vert+1);
        num_vert++;
        for(unsigned int i=0;i<num_vert;i++)
        {
                vertex[i].resize(num_vert);
        }
        return num_vert-1;
}
unsigned int AdjacencyMatrix::order()
{
 return vertex.size();
}

           
