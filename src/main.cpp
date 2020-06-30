#include <iostream>
#include <string>
#include "global.h"
#include "graph.h"


using namespace std; 
using namespace PowerOpt;

char* get_cmd_option(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmd_option_exists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}


int main(int argc, char** argv)
{
    char* lefFileName;
    char* defFileName;

    if( cmd_option_exists(argv, argv+argc, "-lef") )
    {
        lefFileName = get_cmd_option(argv, argv+argc, "-lef");
        cout << "[Arg] -lef     : " << lefFileName << endl;
    }
    else
    {
        cout << "[Error] LEF file is missing, it is necessary!" << endl;
        cout << "Program Terminated" << endl;
        exit(0);
    }


    if( cmd_option_exists(argv, argv+argc, "-def") )
    {
        defFileName  = get_cmd_option(argv, argv+argc, "-def");
        cout << "[Arg] -def     : " << defFileName << endl;
    }
    else
    {
        cout << "[Error] DEF file is missing, it is necessary!" << endl;
        cout << "Program Terminated" << endl;
        exit(0);
    }


    cout << "start to read LEF - " << lefFileName << endl;
    readLEF(lefFileName);
    cout << "finished read LEF" << endl;

    cout << "start to read DEF - " << defFileName << endl;
    readDEF(defFileName);
    cout << "finished read DEF" << endl;

    Graph* g = createGlobalGraph();
    g->print();



    return 0;

}

