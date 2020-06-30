#include "global.h"
#include <iostream>
using namespace PowerOpt;
using namespace std;

MacroType PowerOpt::toMacroType(const char* type)
{
    if(type == "FF")
        return MacroType::FF;
    else if(type == "CC")
        return MacroType::CC;
    else 
        return MacroType::CC;
}

DirecType PowerOpt::toDirecType(const char* type)
{
    if(type == "INPUT")
        return DirecType::INPUT;
    else if(type == "OUTPUT")
        return DirecType::OUTPUT;
    else if(type == "INOUT")
        return DirecType::INOUT;
    else 
        return DirecType::UNKNOWN;
}

LogicType PowerOpt::toLogicType(const char* type)
{
    
    return LogicType::AND;
}

InstType PowerOpt::toInstType(const char* type)
{
    if(type == "GATE")
        return InstType::GATE;
    else if(type == "PAD")
        return InstType::PAD;
    else if(type == "PIN")
        return InstType::PIN;
    else 
        return InstType::GATE;

}

UseType PowerOpt::toUseType(const char* type)
{
    if(type == "SIGNAL")
        return UseType::SIGNAL;
    else if(type == "CLOCK")
        return UseType::CLOCK;
    else if(type == "POWER")
        return UseType::POWER;
    else if(type == "GROUND")
        return UseType::GROUND;
    else
        return UseType::SIGNAL;
}

void PowerOpt::printErrMsg(string msg, bool term)
{
    cout << "[Error] " << msg << endl;
    if(term)
        exit(0);
}


void PowerOpt::printWarnMsg(string msg)
{
    cout << "[Warn] " << msg << endl;
}


