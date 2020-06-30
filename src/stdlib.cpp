#include <iostream>
#include "stdlib.h"

using namespace std;
using namespace PowerOpt;


StdCellLib* StdCellLib::inst = nullptr;

StdCellLib* StdCellLib::instance()
{
    if(inst == nullptr)
        inst = new StdCellLib();
    return inst;
}


Macro* StdCellLib::createMacro(const char* name)
{
    if(macro2id.find(name) != macro2id.end())
    {
        string warnMsg = string(name) + " already exists!";
        printWarnMsg(warnMsg);
        return getMacro(name);
    }
    else
    {
        int id = macros.size();
        macro2id[name] = id;

        Macro* mac = new Macro();
        mac->setId(id);
        mac->setName(name);

        macros.push_back(mac);
        return mac;
    }
}


Macro* StdCellLib::createMacro(string name)
{
    return createMacro(name.c_str());
}

MacroPin* Macro::createMacroPin(const char* n)
{
    if(pin2id.find(n) != pin2id.end())
    {
        string warnMsg = string(n) + " already exists!";
        printWarnMsg(warnMsg);
        return getMacroPin(name);
    }
    else
    {
        int id = pins.size();
        pin2id[n] = id;
        MacroPin* m_pin = new MacroPin();
        m_pin->setId(id);
        m_pin->setName(n);
        
        pins.push_back(m_pin);
        return m_pin;
    }
}

MacroPin* Macro::createMacroPin(string n)
{
    return createMacroPin(n.c_str());
}









