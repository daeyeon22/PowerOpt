EXE = powerOpt
CXX = g++
SYSTEM = x86-64_linux
LIBFORMAT = static_pic
OBJECT = ../build

CXXOPTS = -m64 -O1 -fopenmp -fPIC -fno-strict-aliasing -fexceptions -fpermissive -DNDEBUG -DIL_STD -Wno-ctor-dtor-privacy 

CFLAGS = -std=c++11 -static-libstdc++ -O1 -fopenmp -fpermissive -DNDEBUG -DIL_STD -Wno-ctor-dtor-privacy $(LIBINCLUDE)

# include library settings..
LIBINCLUDE = -I$(SRCHASH)/include -I$(SRCDEF)/include -I$(SRCLEF)/include -I$(BOOST)/include 

# linking flag settings
LINKCFLAGS = $(CFLAGS) -static-libstdc++ $(DEFLIBS) $(LEFLIBS) $(LIBGOMP)

# source settings.
SRCLEF 	= ../lib/lef/5.8-p027
SRCDEF 	= ../lib/def/5.8-p027
SRCHASH = /home/tool/cpplib/sparsehash/install/2.0.3
BOOST = /home/tool/cpplib/boost/install/1.67.0
LIBGOMP = -L../lib/libgomp/libgomp.a -static

DEFLIBS         = -L$(SRCDEF)/lib -ldef -ldefzlib -lcdef -lcdefzlib
LEFLIBS         = -L$(SRCLEF)/lib -llef -llefzlib -lclef -lclefzlib


DEBUG = -g -gstrict-dwarf -gdwarf-2

SRC = 	$(OBJECT)/defRead.o \
	  	$(OBJECT)/lefRead.o \
	  	$(OBJECT)/netlist.o \
	  	$(OBJECT)/stdlib.o \
	  	$(OBJECT)/global.o \
	  	$(OBJECT)/graph.o \
		$(OBJECT)/main.o

$(EXE): $(SRC)
	@echo " "
	@echo "Linking..."
	@echo " "
	$(CXX) $(CXXOPTS) $^ -o $@ $(LINKCFLAGS)
	@echo " "
	@echo "Linking is Completed !!"
	@echo " "
	@echo "Tagging..."
	@echo " "
	ctags -R
	@echo " "
	@echo "Finished..!"
	@echo " "
	@echo "GNU GCC/G++ compiler has been used as"
	@g++ --version

$(OBJECT)/defRead.o: defRead.cpp netlist.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJECT)/lefRead.o: lefRead.cpp stdlib.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJECT)/netlist.o: netlist.cpp netlist.h
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJECT)/stdlib.o: stdlib.cpp stdlib.h
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJECT)/global.o: global.cpp global.h
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJECT)/graph.o: graph.cpp graph.h
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJECT)/main.o: main.cpp stdlib.h  netlist.h 
	$(CXX) $(CFLAGS) -c -o $@ $<


.PHONY: clean
clean: 
	/bin/rm -f $(OBJECT)/*.o 2> /dev/null;  /bin/rm -f $(EXE) 2> /dev/null; /bin/rm -f defreader defwriter lefreader lefwriter 2> /dev/null; /bin/rm -f *.log;


