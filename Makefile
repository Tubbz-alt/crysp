AR=ar

CXX=g++
CXXFLAGS_BASE=-Wall -Wextra -I.

CXXFLAGS_OPT=-O3 $(CXXFLAGS_BASE) $(CXXFLAGS)
CXXFLAGS_DBG=-g $(CXXFLAGS_BASE) $(CXXFLAGS)

SOURCES_BIN:=$(wildcard test/*.cpp)
SOURCES_LIB:=$(wildcard crysp/*.cpp)

OBJS_LIB_OPT:=$(patsubst %.cpp,%.opt.o,$(SOURCES_LIB))
OBJS_LIB_DBG:=$(patsubst %.cpp,%.dbg.o,$(SOURCES_LIB))

BIN_OPT:=main
BIN_DBG:=main.debug

LIB_OPT:=libcrysp.opt.a
LIB_DBG:=libcrysp.dbg.a


all: bin

bin: bin_opt bin_dbg
lib: lib_opt lib_dbg

bin_opt: $(BIN_OPT)
bin_dbg: $(BIN_DBG)
lib_opt: $(LIB_OPT)
lib_dbg: $(LIB_DBG)

$(BIN_OPT): $(SOURCES_BIN) $(LIB_OPT)
	$(CXX) $(CXXFLAGS_OPT) $+ -o $@

$(BIN_DBG): $(SOURCES_BIN) $(LIB_DBG)
	$(CXX) $(CXXFLAGS_DBG) $+ -o $@

$(LIB_OPT): $(OBJS_LIB_OPT)
	$(AR) rcs $@ $+

$(LIB_DBG): $(OBJS_LIB_DBG)
	$(AR) rcs $@ $+

%.opt.o: %.cpp
	$(CXX) $(CXXFLAGS_OPT) $< -c -o $@

%.dbg.o: %.cpp
	$(CXX) $(CXXFLAGS_DBG) $< -c -o $@


clean:
	rm -f $(BIN_OPT) $(BIN_DBG) *.a *.o crysp/*.o test/*.o core.* *~
