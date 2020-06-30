#ifndef __GLOBAL__
#define __GLOBAL__

#include <cstring>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include <cfloat> 
#include <algorithm>
#include <limits>
#include <assert.h>
#include <sparsehash/dense_hash_map>
#include <omp.h>
#include <string>
#include <tuple>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/format.hpp>

#define netlist() PowerOpt::Netlist::instance()
#define stdCellLib() PowerOpt::StdCellLib::instance()

#define INITSTR "INITSTR"

using google::dense_hash_map;
using namespace std;

namespace PowerOpt
{
    template <typename A, typename B>
    using HashMap = dense_hash_map<A,B>;
   
    enum MacroType { FF, CC };
    enum DirecType { INPUT, OUTPUT, INOUT, UNKNOWN };
    enum LogicType { AND, AOI, BUFF, DFF, INV, LH, MUX, NAND, NOR, OAI, OR, XNOR, XOR };
    //enum MasterType { PAD, GATE };
    enum UseType { CLOCK, SIGNAL, POWER, GROUND };
    enum InstType { PIN, NET, PAD, GATE };


    extern MacroType toMacroType(const char* type);
    extern DirecType toDirecType(const char* type);
    extern LogicType toLogicType(const char* type);
    extern InstType toInstType(const char* type);
    extern UseType toUseType(const char* type);

    // read LEF/DEF
    extern int readLEF(const char* input);
    extern int readDEF(const char* input);

    extern void printErrMsg(string msg, bool terminate=true);
    extern void printWarnMsg(string msg);
};

#endif

