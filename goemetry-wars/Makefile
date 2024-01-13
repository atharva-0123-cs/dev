# # to build the game:
# #	$ cd game_dir
# #	$ make

# # executable binaries should be put in game_dir/bin to run the game,
# # you need to cd bin , and type ./sfmlgame
# # but it's a nnoying to chane director each time

# # to compile and run in one command 
# # make run

# # define which conpiler to use
CXX		:= g++
OUTPUT	:= sfmlgame

#if you need to manually specify yyour SFML install dir, do so here
SFML_DIR := .

# complier and linker flags
CXX_FLAGS	:= -O3 -std=c++17
# INCLUDES	:= -I./src -I$(SFML_DIR)/include
INCLUDES	:= -I./src 
# LDFLAGS		:= -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(SFML_DIR)/lib
LDFLAGS		:= -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

# the source files for the ECS game engine
SRC_FILES	:= $(wildcard src/*.cpp)
OBJ_FILES	:= $(SRC_FILES:.cpp=.o)

all: $(OUTPUT)

# all of the main executable requirements / command
$(OUTPUT) : $(OBJ_FILES) Makefile
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

# specifies how the object files are complied from cpp files
.cpp.o:
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

#typing 'make clean' will remove all intermadiate build files
clean : 
	rm -f $(OBJ_SFMLGAME) ./bin/sfmlgame

# typing 'make run' will compile and run the program
run : $(OUTPUT)
	cd bin && ./sfmlgame && cd ..

# build:
# 	 $(CXX) -c ./src/main.cpp 
	

# run :
# 	 $(CXX) main.o -o ./bin/sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	
# 	 ./bin/sfml-app
	
# clean :
# 	rm -f main.o ./bin/sfml-app

