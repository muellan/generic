.PHONY: clean 

INCLUDE  = ../include
FILTER   = *
SOURCES  = $(wildcard $(FILTER).cpp)
EXECS    = $(notdir $(SOURCES:.cpp=))
FLAGS    = -I $(INCLUDE) -std=c++14 -O3 -Wall 

.PHONY: all clean

all: $(EXECS)

clean:
	find -type f -not -name "*.cpp" -not -name "*.h" -not -name "Makefile" -not -name "runall" | xargs rm

cached_fn : cached_fn.cpp $(INCLUDE)/cached_fn.h timer.h
	g++ $(FLAGS) -o $@ $<

tuple_map : tuple_map.cpp $(INCLUDE)/tuple_map.h
	g++ $(FLAGS) -o $@ $<
