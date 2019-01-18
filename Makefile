AR=ar

CXX=g++
CXXFLAGS_BASE=-Wall -Wextra -I.

CXXFLAGS_OPT=-O3 $(CXXFLAGS_BASE) $(CXXFLAGS)
CXXFLAGS_DBG=-g $(CXXFLAGS_BASE) $(CXXFLAGS)

SOURCES_BIN:=$(wildcard test/*.cpp)
SOURCES_LIB:=$(wildcard crysp/*.cpp)
SOURCES_COLLATZ:=$(wildcard example/collatz/*.cpp)

OBJS_LIB_OPT:=$(patsubst %.cpp,%.opt.o,$(SOURCES_LIB))
OBJS_LIB_DBG:=$(patsubst %.cpp,%.dbg.o,$(SOURCES_LIB))

LIB_OPT:=libcrysp.opt.a
LIB_DBG:=libcrysp.dbg.a

BIN_OPT:=main
BIN_DBG:=main.debug

COLLATZ_OPT=collatz
COLLATZ_DBG=collatz.debug

all: bin collatz

lib: lib_opt lib_dbg
bin: bin_opt bin_dbg

lib_opt: $(LIB_OPT)
lib_dbg: $(LIB_DBG)
bin_opt: $(BIN_OPT)
bin_dbg: $(BIN_DBG)

$(LIB_OPT): $(OBJS_LIB_OPT)
	$(AR) rcs $@ $+

$(LIB_DBG): $(OBJS_LIB_DBG)
	$(AR) rcs $@ $+

$(BIN_OPT): $(SOURCES_BIN) $(LIB_OPT)
	$(CXX) $(CXXFLAGS_OPT) $+ -o $@

$(BIN_DBG): $(SOURCES_BIN) $(LIB_DBG)
	$(CXX) $(CXXFLAGS_DBG) $+ -o $@

$(COLLATZ_OPT): $(SOURCES_COLLATZ) $(LIB_OPT)
	$(CXX) $(CXXFLAGS_OPT) $+ -o $@

$(COLLATZ_DBG): $(SOURCES_COLLATZ) $(LIB_DBG)
	$(CXX) $(CXXFLAGS_DBG) $+ -o $@

%.opt.o: %.cpp
	$(CXX) $(CXXFLAGS_OPT) $< -c -o $@

%.dbg.o: %.cpp
	$(CXX) $(CXXFLAGS_DBG) $< -c -o $@

clean:
	rm -f $(BIN_OPT) $(BIN_DBG) *.a *.o crysp/*.o test/*.o core.* *~
