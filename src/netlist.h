#ifndef __NETLIST__
#define __NETLIST__ 0
#include "global.h"
#include "stdlib.h"

namespace PowerOpt {

    class Net;
    class Pin;
    class Gate;
    class Pad;
    
    class Pin {
      private:
        int id;
        string name;
        string portName;
        InstType mtype;
        DirecType direction;
        UseType use;
        Net* net;       // if unconnected, then net == nullptr
        Gate* gate;     // if type of master isn't gate, gate == nullptr
        Pad* pad;       // if type of master isn't pad, pad == nullptr

      public:

        int getId() { return id; }
        string getFullName() { return name; }
        string getPortName() { return portName; }
        InstType getMasterType() { return mtype; }
        DirecType getDirection() { return direction; }
        UseType getUseType() { return use; }


        Net* getNet() { return net; }
        Gate* getMasterGate() { return gate; }
        Pad* getMasterPad() { return pad; }

        // setter
        void setId(int i) { id = i; }
       
        void setName(const char* n) { name = n; }
        void setName(string n) { name = n; }
        void setPortName(const char* n) { portName = n; }
        void setPortName(string n) { portName = n; }
        void setMasterType(InstType t) { mtype = t; }
        void setDirection(DirecType d) { direction = d; }
        void setNet(Net* n) { net = n; }
        void setMasterGate(Gate* g) { gate = g; }
        void setMasterPad(Pad* p) { pad = p; }
        void setUseType(UseType u) { use = u; }
    };


    class Net {
      private:
        int id;
        string name;
        UseType use;
        vector<Pin*> terms;
    
      public:
        void setId(int i) { id = i; }
        void setName(const char* n) { name = n; }
        void addTerm(Pin* p) { terms.push_back(p); }
        void setUseType(UseType u) { use = u; }

        UseType getUseType() { return use; }

        int getId() { return id; }
        string getName() { return name; }
        
        Pin* getSource();
        vector<Pin*> getSinks();
        vector<Pin*> getTerms();
    };

    class Pad {
      private:
        int id;
        string name;
        
        Pin* pin;
      
      public:
        int getId() { return id; }
        string getName() { return name; }
        Pin* getPin() { return pin; }
        DirecType getDirection() { return pin->getDirection(); }

        void setId(int i) { id = i; }
        void setName(string n) { name = n; }
        void setPin(Pin* p) { pin = p; }
    };

    class Gate {
      private:
        int id;
        string name;
        Macro* macro;
       
        LogicType logic;
        
        vector<Pin*> pins;


      public:
        int getId() { return id; }
        string getGateName() { return name; }
        string getMacroName() { return macro->getName(); }
        Macro* getMacro() { return macro; }
        LogicType getLogicType(){ return logic; }

        vector<Pin*> getInputPins();
        vector<Pin*> getOutputPins();

        void setId(int i) { id = i; }
        void setName(const char* n) { name = n; }
        void setName(string n) { name = n; }
        void addPin(Pin* p) { pins.push_back(p); }
        void setMacro(Macro* m) { macro = m; }        
    };


    class Netlist {
      private:
        static Netlist* inst;

        string designName;
        vector<Gate*> gates;
        vector<Pad*> pads;
        vector<Pin*> pins;
        vector<Net*> nets;

        HashMap<string,int> gate2id;
        HashMap<string,int> pad2id;
        HashMap<string,int> pin2id;
        HashMap<string,int> net2id;

      public:
        static Netlist* instance();

        Netlist()
        {
            gate2id.set_empty_key(INITSTR);
            pad2id.set_empty_key(INITSTR);
            pin2id.set_empty_key(INITSTR);
            net2id.set_empty_key(INITSTR);
        }



        // iterator
        vector<Gate*>::iterator gateBegin() { return gates.begin(); }
        vector<Gate*>::iterator gateEnd() { return gates.end(); }
        vector<Pad*>::iterator padBegin() { return pads.begin(); }
        vector<Pad*>::iterator padEnd() { return pads.end(); }
        vector<Net*>::iterator netBegin() { return nets.begin(); }
        vector<Net*>::iterator netEnd() { return nets.end(); }
        vector<Pin*>::iterator pinBegin() { return pins.begin(); }
        vector<Pin*>::iterator pinEnd() { return pins.end(); }


        Gate* createGate(const char* name);
        Pad* createPad(const char* name);
        Pin* createPin(const char* name);
        Net* createNet(const char* name);       
        Gate* createGate(string name);
        Pad* createPad(string name);
        Pin* createPin(string name);
        Net* createNet(string name);       

        // getter
        Pin* getPin(const char* name) { return pins[pin2id[name]]; }
        Pin* getPin(string name) { return pins[pin2id[name]]; } 
        Pin* getPin(int i) { return pins[i]; }
        Gate* getGate(int i) { return gates[i]; }
        Gate* getGate(const char* n) { return gates[gate2id[n]]; }
        Gate* getGate(string n) { return gates[gate2id[n]]; }
        Pad* getPad(int i) { return pads[i]; }
        Pad* getPad(const char* n) { return pads[pad2id[n]]; }
        Pad* getPad(string n) { return pads[pad2id[n]]; }
        Net* getNet(int i) { return nets[i]; }
        Net* getNet(const char* n) { return nets[net2id[n]]; }
        Net* getNet(string n) { return nets[net2id[n]]; }

        void setDesignName(const char* n) { designName = n; }
        string getDesignName() { return designName; }
    };

};

#endif
