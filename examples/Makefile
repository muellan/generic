.PHONY: clean 

INCLUDE  = ../include
CXX      = g++
FILTER   = *
SOURCES  = $(wildcard $(FILTER).cpp)
EXECS    = $(notdir $(SOURCES:.cpp=))
FLAGS    = -I $(INCLUDE) -std=c++14 -O3 -Wall 

.PHONY: all clean

all: $(EXECS)

clean:
	find -type f -not -name "*.cpp" -not -name "*.h" -not -name "Makefile" -not -name "runall" | xargs rm

cached_fn : cached_fn.cpp $(INCLUDE)/cached_fn.h timer.h
	$(CXX) $(FLAGS) -o $@ $<

tuple_map : tuple_map.cpp $(INCLUDE)/tuple_map.h
	$(CXX) $(FLAGS) -o $@ $<
