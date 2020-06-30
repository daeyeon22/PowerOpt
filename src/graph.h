
#ifndef __GRAPH__
#define __GRAPH__

#include "global.h"


namespace PowerOpt
{

    class Vertex;
    class HyperEdge;
    class Edge;
    class Graph;

    typedef pair<int,int> pair_t;
    
    //
    Graph* createGlobalGraph();



    class Vertex
    {
      private:
        int id;

        vector<HyperEdge*> inHyperEdges;
        vector<HyperEdge*> outHyperEdges;
        vector<Edge*> inEdges;
        vector<Edge*> outEdges;

      public:
        void setId(int i) { id = i; }
        int getId() { return id; }

        void addInHyperEdge(HyperEdge* h);
        void addOutHyperEdge(HyperEdge* h);
        void addInEdge(Edge* e);
        void addOutEdge(Edge* e);

        // iterator
        vector<Edge*>::iterator inEdgeBegin() { return inEdges.begin(); }
        vector<Edge*>::iterator inEdgeEnd() { return inEdges.end(); }
        vector<Edge*>::iterator outEdgeBegin() { return outEdges.begin(); }
        vector<Edge*>::iterator outEdgeEnd() { return outEdges.end(); }
        vector<HyperEdge*>::iterator inHyperEdgeBegin() { return inHyperEdges.begin(); }
        vector<HyperEdge*>::iterator inHyperEdgeEnd() { return inHyperEdges.end(); }
        vector<HyperEdge*>::iterator outHyperEdgeBegin() { return outHyperEdges.begin(); }
        vector<HyperEdge*>::iterator outHyperEdgeEnd() { return outHyperEdges.end(); }

        
        // 
        bool operator == (Vertex* v) const { return id == v->getId(); }
    };

    class HyperEdge
    {
      private:
        int id;
        Vertex* source;
        vector<Vertex*> sinks;
        vector<Edge*> edges;

        

      public:
        void setId(int i) { id = i; }
        int getId() { return id; }

        void addEdge(Edge* e);
        void setSource(Vertex* v) { source = v; }
        Vertex* getSource() { return source; }
        vector<Vertex*> getSinks() { return sinks; }
        bool operator == (HyperEdge* h) const { return id == h->getId(); }
    };

    // directed edge
    class Edge
    {
      private:
        int id;
        Vertex* source;
        Vertex* sink;

      public:
        void setId(int i) { id = i; }
        int getId() { return id; }
        
        void setSink(Vertex* s) { sink = s; }
        void setSource(Vertex* s) { source = s; }
        Vertex* getSink() { return sink; }
        Vertex* getSource() { return source; }

        bool operator == (Edge* e) const { return id == e->getId(); }
    };

    // directed graph
    class Graph
    {
      private:
        int id;

        vector<Vertex*> vertices;
        vector<Edge*> edges;
        vector<HyperEdge*> hyperEdges;

        map<pair_t, int> pair2edge;
        map<pair_t, int> inst2vertex;

        HashMap<int,int> vertex2inst;
        HashMap<int,InstType> vertex2type;

      public:
        
        Graph()
        {
            vertex2inst.set_empty_key(INT_MAX);
            vertex2type.set_empty_key(INT_MAX);
        }
        
        void setId(int i) { id = i; }
        int getId() { return id; }

        int getVertexId(int instId, InstType type) { return inst2vertex[pair_t(instId, type)]; }
        int getInstId(int vertexId) { return vertex2inst[vertexId]; }
        InstType getInstType(int vertexId) { return vertex2type[vertexId]; }

        Vertex* createVertex(int instId, InstType type);
        Vertex* getVertex(int vertexId) { return vertices[vertexId]; }
        Edge* createEdge(int v1, int v2);
        Edge* createEdge(Vertex* v1, Vertex* v2);
        Edge* getEdge(int v1, int v2) { return edges[pair2edge[pair_t(v1,v2)]]; }
        HyperEdge* createHyperEdge(vector<int> terms, vector<InstType> types);



        void print(); 

    };


};



//bool operator == (PowerOpt::Vertex* v1, PowerOpt::Vertex* v2) { return v1->getId() == v2->getId(); }
//bool operator == (Edge* e1, Edge* e2) { return e1->getId() == e2->getId(); }
//bool operator == (HyperEdge* h1, HyperEdge* h2) { return h1->getId() == h2->getId(); }

#endif




