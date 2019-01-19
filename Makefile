AR=ar

CXX=g++
CXXFLAGS_BASE=-Wall -Wextra -I.

CXXFLAGS_OPT=-O3 $(CXXFLAGS_BASE) $(CXXFLAGS)
CXXFLAGS_DBG=-g $(CXXFLAGS_BASE) $(CXXFLAGS)

SOURCES_LIB:=$(wildcard crysp/*.cpp)
SOURCES_MAIN:=$(wildcard test/*.cpp)
SOURCES_COLLATZ:=$(wildcard example/collatz/*.cpp)

OBJS_LIB_OPT:=$(patsubst %.cpp,%.opt.o,$(SOURCES_LIB))
OBJS_LIB_DBG:=$(patsubst %.cpp,%.dbg.o,$(SOURCES_LIB))

LIB_OPT:=libcrysp.opt.a
LIB_DBG:=libcrysp.dbg.a

MAIN_OPT:=main
MAIN_DBG:=main.debug

COLLATZ_OPT:=collatz
COLLATZ_DBG:=collatz.debug

BINS_OPT:=$(MAIN_OPT) $(COLLATZ_OPT)
BINS_DBG:=$(MAIN_DBG) $(COLLATZ_DBG)

all: bins

lib:  lib_opt lib_dbg
bins: bins_opt bins_dbg

lib_opt: $(LIB_OPT)
lib_dbg: $(LIB_DBG)
bins_opt: $(BINS_OPT)
bins_dbg: $(BINS_DBG)

$(LIB_OPT): $(OBJS_LIB_OPT)
	$(AR) rcs $@ $+

$(LIB_DBG): $(OBJS_LIB_DBG)
	$(AR) rcs $@ $+

$(MAIN_OPT): $(SOURCES_MAIN) $(LIB_OPT)
	$(CXX) $(CXXFLAGS_OPT) $+ -o $@

$(MAIN_DBG): $(SOURCES_MAIN) $(LIB_DBG)
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
	rm -f $(MAIN_OPT) $(MAIN_DBG) (COLLATZ_OPT) $(*.a *.o crysp/*.o test/*.o core.* *~
