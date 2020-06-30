#include "graph.h"
#include "global.h"
#include "netlist.h"
#include <iostream>
#include <boost/format.hpp>
#define DEBUG

using namespace PowerOpt;




void Vertex::addInHyperEdge(HyperEdge* h)
{
    vector<HyperEdge*>::iterator it = find(inHyperEdges.begin(), inHyperEdges.end(), h);
    if(it != inHyperEdges.end())
    {
        printWarnMsg("hyper edge already exists in the current vertex");
    }
    else
    {
        inHyperEdges.push_back(h);
    }
}

void Vertex::addOutHyperEdge(HyperEdge* h)
{
    vector<HyperEdge*>::iterator it = find(outHyperEdges.begin(), outHyperEdges.end(), h);
    if(it != outHyperEdges.end())
    {
        printWarnMsg("hyper edge already exists in the current vertex");
    }
    else
    {
        outHyperEdges.push_back(h);
    }
}

void Vertex::addInEdge(Edge* e)
{
    vector<Edge*>::iterator it = find(inEdges.begin(), inEdges.end(), e);
    if(it != inEdges.end())
    {
        printWarnMsg("edge already exists in the current vertex");
    }
    else
    {
        inEdges.push_back(e);
    }
}

void Vertex::addOutEdge(Edge* e)
{
    vector<Edge*>::iterator it = find(outEdges.begin(), outEdges.end(), e);
    if(it != outEdges.end())
    {
        printWarnMsg("edge already exists in the current vertex");
    }
    else
    {
        outEdges.push_back(e);
    }
}



void HyperEdge::addEdge(Edge* e)
{

#ifdef DEBUG
    if( e->getSource()->getId() == e->getSink()->getId() )
    {
        string msg = "source and sink are same " + to_string(e->getSource()->getId()) + " " + to_string(e->getSink()->getId());
        printErrMsg(msg, true);
    }

    if( source->getId() != e->getSource()->getId() )
    {
        string msg = "hyperEdge's source and Edge's source are different " 
            + to_string(source->getId()) + " " + to_string(e->getSource()->getId());
        printErrMsg(msg, true);
    }
#endif

    //source = e->getSource();
    Vertex* sink = e->getSink();
#ifdef DEBUG
    vector<Edge*>::iterator it = find(edges.begin(), edges.end(), e);
    if(it != edges.end())
    {
        string msg = "Edge " + to_string(e->getId()) + " already exists";
        printWarnMsg(msg);
    }
#endif

    
    edges.push_back(e);
    sinks.push_back(e->getSink());
}

Vertex* Graph::createVertex(int instId, InstType type)
{
    int id = vertices.size();

    Vertex* v = new Vertex();
    v->setId(id);

    vertex2inst[id] = instId;
    vertex2type[id] = type;

    inst2vertex[pair_t(instId, type)] = id;

    vertices.push_back(v);
    return v;
}


Edge* Graph::createEdge(int v1, int v2)
{
    pair_t key(v1, v2);

#ifdef DEBUG
    if(v1 == v2)
    {
        printErrMsg("source and sink id are same", true);
    }

#endif
    if(pair2edge.find(key) != pair2edge.end())
    {
        printWarnMsg("edge already exists");
        return getEdge(v1, v2);
    }
    else
    {
        int id = edges.size();
        pair2edge.insert( { key, id } );

        Edge* e = new Edge();
        e->setId(id);
        e->setSource(getVertex(v1));
        e->setSink(getVertex(v2));

        edges.push_back(e);
        return e;
    }
}

Edge* Graph::createEdge(Vertex* v1, Vertex* v2)
{
    return createEdge(v1->getId(), v2->getId());
}

HyperEdge* Graph::createHyperEdge(vector<int> terms, vector<InstType> types)
{
    int id = hyperEdges.size();
    int sourceId = getVertexId(terms[0], types[0]);
    Vertex* source = getVertex(sourceId);

    HyperEdge* h = new HyperEdge();
    h->setId(id);
    h->setSource(source);
    hyperEdges.push_back(h);


    
    source->addOutHyperEdge(h);

    for(int i=1; i < terms.size(); i++)
    {
        int sinkId = getVertexId(terms[i], types[i]);
        Vertex* sink = getVertex(sinkId);

        Edge* e = createEdge(source, sink);
        h->addEdge(e);

        source->addOutEdge(e);
        sink->addInEdge(e);
        
        sink->addInHyperEdge(h);
    }

    return h;
}



Graph* PowerOpt::createGlobalGraph()
{
    Graph* g = new Graph();

    // set id
     
    // create vertices
    for(vector<Gate*>::iterator it = netlist()->gateBegin(); it != netlist()->gateEnd(); it++)
    {
        Gate* gate = *it;

        g->createVertex(gate->getId(), InstType::GATE);
    }

    for(vector<Pad*>::iterator it = netlist()->padBegin(); it != netlist()->padEnd(); it++)
    {
        Pad* pad = *it;

        g->createVertex(pad->getId(), InstType::PAD);
    }

    for(vector<Net*>::iterator it = netlist()->netBegin(); it != netlist()->netEnd(); it++)
    {
        Net* net = *it;

        vector<int> terms;
        vector<InstType> types;
        for(auto& pin : net->getTerms())
        {
            types.push_back(pin->getMasterType());
            switch(pin->getMasterType())
            {
                case InstType::GATE : terms.push_back(pin->getMasterGate()->getId()); break;
                case InstType::PAD  : terms.push_back(pin->getMasterPad()->getId()); break;
            }
        }

        g->createHyperEdge(terms, types);
    }

    return g;
}

string toStr(InstType type)
{
    switch(type)
    {
        case InstType::GATE: return "GATE";
        case InstType::PAD: return "PAD";
        case InstType::NET: return "NET";
        case InstType::PIN: return "PIN";
        default: return "";
    }
}

void Graph::print()
{

    cout << "<print all vertices>" << endl;
    HashMap<int,string> typeName;
    HashMap<int,string> instName;
    typeName.set_empty_key(INT_MAX);
    instName.set_empty_key(INT_MAX);

    for(auto& v : vertices)
    {   
        int vertexId = v->getId();
        int instId = getInstId(vertexId);
        InstType instType = getInstType(vertexId);
        switch(instType)
        {
            case InstType::GATE: 
                instName[vertexId] = netlist()->getGate(instId)->getGateName();
                typeName[vertexId] = netlist()->getGate(instId)->getMacroName();
                break;
            case InstType::PAD:
                instName[vertexId] = netlist()->getPad(instId)->getName();
                typeName[vertexId] = "PAD";
                break;
        }

        cout << boost::format("   - %d-th vertex (%s: %s)\n") % vertexId % typeName[vertexId] % instName[vertexId];
    }

    cout << endl;

    cout << "<print all hyper-edges>" << endl;

    for(auto& h : hyperEdges)
    {
        int hyperEdgeId = h->getId();
        int sourceId = h->getSource()->getId();

        cout << boost::format("%d-th hyper-edge (%s: %s)\n") % hyperEdgeId % typeName[sourceId] % instName[sourceId];

        int i=1;
        for(auto& sink : h->getSinks())
        {
            int sinkId = sink->getId();
            cout << boost::format("     - %d-th sink (%s: %s)\n") % i++ % typeName[sinkId] % instName[sinkId];
        }

        cout << endl;
    }
}







