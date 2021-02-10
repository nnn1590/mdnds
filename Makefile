SHELL  := /bin/sh
CXX    := g++
CFLAGS := -s -O3
LIBS   := -lboost_system -lboost_filesystem

.PHONY: all
all: bin/mdnds

bin/mdnds: main.cpp nds.cpp nds_fst.cpp nds.h nds_fst.h nds_header.h util.h
	$(CXX) $(CFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	$(RM) bin/mdnds
