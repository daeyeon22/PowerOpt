#include "netlist.h"
#include "graph.h"

using namespace PowerOpt;

Netlist* Netlist::inst = nullptr;

Netlist* Netlist::instance()
{
    if(inst == nullptr)
        inst = new Netlist();
    return inst;
}



Pin* Net::getSource()
{
    Pin* frtPin = terms.front();

    if(frtPin->getDirection() != DirecType::OUTPUT)
    {
        printErrMsg("exception case in func getSource()", true);
    }
    
    return frtPin;
}

vector<Pin*> Net::getSinks()
{
    vector<Pin*> sinks;

    copy(terms.begin()+1, terms.end(), sinks.begin());
    return sinks;
}


vector<Pin*> Net::getTerms()
{
    return terms;
}





/********************/
/* create functions */
/********************/

Pad* Netlist::createPad(const char* n)
{
    if(pad2id.find(n) != pad2id.end())
    {
        string warnMsg = string(n) + " already exists!";
        printWarnMsg(warnMsg);
        return getPad(n);
    }
    else
    {
        int id = pads.size();
        pad2id[n] = id;

        Pad* pad = new Pad();
        pad->setId(id);
        pad->setName(n);

        pads.push_back(pad);
        return pad;
    }
}

Pad* Netlist::createPad(string n)
{
    return createPad(n.c_str());
}

Gate* Netlist::createGate(const char* n)
{
    if(gate2id.find(n) != gate2id.end())
    {
        string warnMsg = string(n) + " already exists!";
        printWarnMsg(warnMsg);
        return getGate(n);
    }
    else
    {
        int id = gates.size();
        gate2id[n] = id;

        Gate* gate = new Gate();
        gate->setId(id);
        gate->setName(n);

        gates.push_back(gate);
        return gate;
    }
}

Gate* Netlist::createGate(string n)
{
    return createGate(n.c_str());
}


Net* Netlist::createNet(const char* n)
{
    if(net2id.find(n) != net2id.end())
    {
        string warnMsg = string(n) + " already exists!";
        printWarnMsg(warnMsg);
        return getNet(n);
    }
    else
    {
        int id = nets.size();
        net2id[n] = id;

        Net* net = new Net();
        net->setId(id);
        net->setName(n);

        nets.push_back(net);
        return net;
    }
}

Net* Netlist::createNet(string n)
{
    return createNet(n.c_str());
}

Pin* Netlist::createPin(const char* n)
{
    if(pin2id.find(n) != pin2id.end())
    {
        string warnMsg = string(n) + " already exists!";
        printWarnMsg(warnMsg);
        return getPin(n);
    }
    else
    {
        int id = pins.size();
        pin2id[n] = id;

        Pin* pin = new Pin();
        pin->setId(id);
        pin->setName(n);

        pins.push_back(pin);
        return pin;
    }
}

Pin* Netlist::createPin(string n)
{
    return createPin(n.c_str());
}




