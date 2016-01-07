#include<iostream>
#include<fstream>
#include<map>
#include"AdjacencyMatrix.h"
#include"distance_between_hexes.h"
#include<limits>
#include<set>
#include<string>
#include<algorithm>
#include"HexMap.h"
using namespace std;

map<unsigned int, unsigned int> hexToVertex;
map<unsigned int, unsigned int> vertexToHex;
vector<unsigned int> total_est_dist;
bool which_is_closer(unsigned int a, unsigned int b);
map<unsigned int, unsigned int> astar(unsigned int s, unsigned int f, AdjacencyMatrix& am);
int main()
{
        map<char,int> costs;
        ifstream in;
        int b;
        char a;
        in.open("terrain_costs.data",ifstream::in);
        while(in.eof()==0)
        {
                in>>a;
                in>>b;
                costs[a]=b;
        }
        in.close();
        AdjacencyMatrix *g;
        g= new AdjacencyMatrix;
        int num1;
        int num2;
        string weight;
        in.open("mapedges.data",ifstream::in);
        while(in.eof()==0)
        {
                in>>num1;
                in>>num2;
                in>>weight;
                if(hexToVertex.count(num1)==0)
                {
                        unsigned int v1=g->add_vertex(); //x will be ??
                        hexToVertex[num1]=v1;
                        vertexToHex[v1]=num1;
                }
                if(hexToVertex.count(num2)==0)
                {
                        unsigned int v2=g->add_vertex(); //x will be ??
                        hexToVertex[num2]=v2;
                        vertexToHex[v2]=num2;
                }
                //do the exact same thing with hex2

                int w=0;
                for(string::iterator it=weight.begin(); it!=weight.end(); ++it)
                {
                        w = costs[*it] + w;
                }
                g->add_edge(hexToVertex[num1], hexToVertex[num2],w);

        }
        in.close();
        unsigned int start=hexToVertex[309];
        unsigned int end=hexToVertex[1605];
        HexMap h(1605);
        map<unsigned int, unsigned int> route= astar(start,end,*g);
        while(end!=start)
        {
                h.add(vertexToHex[route[end]]);
                end= route[end];
        }
        return 0;
}

bool which_is_closer(unsigned int a, unsigned int b)
{
        return total_est_dist[a] > total_est_dist[b];
}
//A-STAR ALGOROITHM
map<unsigned int, unsigned int> astar(unsigned int s, unsigned int f, AdjacencyMatrix& am)
{
        const unsigned int infinity=std::numeric_limits<unsigned int>::max();
        set<unsigned int> closed; //holds vertices we no longer process
        vector<unsigned int> open; //holds vertices we still need to process

        map<unsigned int, unsigned int> parent;//what is returned
        //should be number of vertices
        //holds the distance already traveled for each vertex
        unsigned int size = am.order();
        vector<int> distance_traveled(size);
        total_est_dist.resize(size);
        //recall, total_est_dist is a global variable
        //Here, initialize it to infinity for all entries. # entries equals number of verticestotal_est_dist...
        for(int i=0; i<size;i++)
        {
                total_est_dist[i]= infinity;
        }
        //also, initialize to infinity: XXX
        //distance_traveled...
        for(int i=0; i<size;i++)
        {
                distance_traveled[i]= infinity;
        }
        for(int i=0;i<size;i++)
        {
                int d = distance_between_hexes(s,i);
                total_est_dist[i]= distance_traveled[i]+d;
        }
        open.push_back(s); //add our starting point to
        make_heap(open.begin(), open.end(), which_is_closer);
        //start the loop
        while(!open.empty())
        {
                //XXX
                //use pop_heap on open vector. then current=open.back(), then pop_back to remove it
                unsigned int current;
                pop_heap(open.begin(), open.end());
                current=open.back();
                open.pop_back();
                if(current==f)//stopping condition
                        return parent;
                //now don't forget to pop it off of open
                closed.insert(current);
                //make sure that we don't see this vertex again.
                set<unsigned int> nbor = am.out_neighbors(current);
                set<unsigned int>::iterator i;
                for(i= nbor.begin(); i!=nbor.end();++i)
                {
                        unsigned int cur_n = *i;
                        if(closed.count(cur_n)==1)
                        {
                                continue;
                        }
                        int temp_dist= distance_traveled[current] + am.weight(current, cur_n);
                        int x=0;
                        for(int j=0;j<open.size();j++)
                        {
                                if(open[j]==cur_n)
                                {
                                        x=1;
                                }
                        }
                        if(x!=1)
                        {
                                open.push_back(cur_n);
                                make_heap(open.begin(), open.end(), which_is_closer);
                        }
                        else if(temp_dist >= distance_traveled[cur_n])
{
                                continue;
                        }
                        parent[cur_n]=current; //best predecessor for this neighbor
                        distance_traveled[cur_n]= temp_dist;
                        int a = vertexToHex[cur_n];
                        int b = vertexToHex[f];
                        int c= distance_between_hexes(a,b);
                        total_est_dist[cur_n]=distance_traveled[cur_n]+c;
                        make_heap(open.begin(), open.end(), which_is_closer);
                }
        }
        return parent;
}
