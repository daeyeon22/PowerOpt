/*-----------------------------------------------------------*/
/*                                                           */
/*                                                           */
/*                                                           */
/*-----------------------------------------------------------*/


#ifndef __LEFDEFIO__
#define __LEFDEFIO__ 0

#include "global.h"

namespace PowerOpt
{
    class MacroPin
    {
      private:
        int id;
        string name;
        DirecType direction;
        UseType use;

      public:
        int getId() { return id; }
        string getName() { return name; }

        void setId(int i) { id = i; }
        void setName(string n) { name = n; }
        void setName(const char* n) { name = n; }
        void setDirection(DirecType d) { direction = d; }
        void setUseType(UseType u) { use = u; }
   
        UseType getUseType() { return use; }
        DirecType getDirection() { return direction; }
    };

    class Macro {
      private:
        int id;
        string name ;
        MacroType type ;
        
        HashMap<string,int> pin2id;
        vector<MacroPin*> pins;

      public:
        Macro()
        {
            pin2id.set_empty_key(INITSTR);
        }
          
        int getId() { return id; }
        string getName() { return name; }
        MacroType getType() { return type; };
        bool getIsFF(){ return type == MacroType::FF; }

        void setId(int i) { id = i; }
        void setMacroType(MacroType t) { type = t; }
        void setName(string n) { name = n; }
        void setName(const char* n) { name = n; }
        void addMacroPin(MacroPin* p){ pins.push_back(p); }

        MacroPin* createMacroPin(const char* n);
        MacroPin* createMacroPin(string n);

        MacroPin* getMacroPin(const char* n) { return pins[pin2id[n]]; }
        MacroPin* getMacroPin(string n) { return pins[pin2id[n]]; }

    };
    
    class StdCellLib {
      private:
        static StdCellLib* inst;
        vector<Macro*> macros;

        HashMap<string,int> macro2id;

      public:
        static StdCellLib* instance();

        StdCellLib()
        {
            macro2id.set_empty_key(INITSTR);
        }


        void addMacro(Macro* m);

        Macro* getMacro(int i) { return macros[i]; }
        Macro* getMacro(string n) { return macros[macro2id[n]]; }
        Macro* getMacro(const char* n) { return macros[macro2id[n]]; } 
        Macro* createMacro(const char* name);
        Macro* createMacro(string name);

    };
};  
    

#endif
