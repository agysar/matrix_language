CXX = g++
CXX_FLAGS = -std=c++11 -g -Wall 

RM = rm
FILES = 


BINARIES = parser 
LIBS = sparse.o
#vector rational_number matrix 

src_dirs := .
SOURCES := $(addsuffix /*.cpp,$(src_dirs))
#lexeme_analyzer.cpp\
#		exceptions.cpp\
#		lexeme_declaration.cpp\
#		lexeme_parser.cpp\
#		./sparse_matrix/exceptions.cpp\
#		./sparse_matrix/rational_number.cpp\
#		./sparse_matrix/rational_map.cpp\
#		./sparse_matrix/rational_vector.cpp\
#	   	./sparse_matrix/random_access_iterator.cpp\
#	   	./sparse_matrix/rational_matrix.cpp


	
OBJS := $(patsubst %.cpp,%.o, $(wildcard $(SOURCES)))

all: $(BINARIES) $(LIBS)
#	./vector


parser: $(OBJS) $(LIBS)
	$(CXX) -o $@ $^

#rational_number: rational_number_main.o $(OBJS)
#	$(CXX) $(CXX_FLAGS) -o $@ $^

#vector: rational_vector_main.o $(OBJS)
#	$(CXX) $(CXX_FLAGS) -o $@ $^

#matrix: rational_matrix_main.o $(OBJS)
#	$(CXX) $(CXX_FLAGS) -o $@ $^

sparse.o: $(patsubst %.cpp,%.o, $(wildcard sparse_matrix/*.cpp))
	ld -o sparse.o -r $^


%.o: %.cpp
	$(CXX) $(addprefix -I , $(src_dirs)) $(CXX_FLAGS) -c $< -o $@

clean:
	$(RM) -f *.o  $(FILES) sparse_matrix/*.o

dist_clean: clean
	$(RM) -f $(BINARIES)

.PHONY: all clean dist_clean

