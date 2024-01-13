# # # to build the game:
# # #	$ cd game_dir
# # #	$ make
# # # executable binaries should be put in game_dir/bin to run the game,
# # # you need to cd bin , and type ./sfmlgame
# # # but it's a nnoying to chane director each time
# # # to compile and run in one command 
# # # make run
# # # define which conpiler to use
# CXX		:= g++
# OUTPUT	:= sfmlgame
# #if you need to manually specify yyour SFML install dir, do so here
# SFML_DIR := .
# INCLUDES_OBJECT := -I./include
# # complier and linker flags
# CXX_FLAGS	:= -O3 -std=c++17
# # INCLUDES	:= -I./src -I$(SFML_DIR)/include
# INCLUDES	:= -I./src -I$(SFML_DIR)/include
# # LDFLAGS		:= -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(SFML_DIR)/lib
LDFLAGS		:= -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
# # the source files for the ECS game engine
# SRC_FILES	:= $(wildcard src/*.cpp)
# OBJ_FILES	:= $(SRC_FILES:.cpp=.o)
# all: $(OUTPUT)
# # all of the main executable requirements / command
# $(OUTPUT) : $(OBJ_FILES) Makefile
# 	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@
# # specifies how the object files are complied from cpp files
# .cpp.o:
# 	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@
# #typing 'make clean' will remove all intermadiate build files
# clean : 
# 	rm -f $(OBJ_FILES) ./bin/sfmlgame
# # typing 'make run' will compile and run the program
# run : $(OUTPUT)
# 	cd bin && ./sfmlgame && cd ..
# # build:
# # 	 $(CXX) -c ./src/main.cpp 
	
# # run :
# # 	 $(CXX) main.o -o ./bin/sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	
# # 	 ./bin/sfml-app
# # clean :
# # 	rm -f main.o ./bin/sfml-app


# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := final_program

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)


run:
	cd build && ./final_program && cd ..

