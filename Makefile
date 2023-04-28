#flag for starting compilation of the .c file
CC = gcc

#flag for accessing the geometry file/folder
APP_NAME = geometry
#The name of the flag by which we will access the folder with the files of the statistical library
LIB_NAME = libgeometry

#Flag for starting compiler warning output
CFLAGS = -Wall -Werror

#Adding the src folder to include path and changing the dependent sources from the header file(-MMD)
CPPFLAGS = -I src -MD -MMD

#flag for accessing the bin folder in the following Makefile code
BIN_DIR = bin
#flag for accessing the obj folder in the following Makefile code
OBJ_DIR = obj
#flag for accessing the src folder in the following Makefile code
SRC_DIR = src

#accessing the executable code file (bin/geometry)
APP_PATH = $(BIN_DIR)/$(APP_NAME)
#accessing executable files of additional files (statistical libraries) (obj/src/libgeometry/libgeometry.o)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).o

#extension of code files
SRC_EXT = c

#search for files with the extension .c in the folder src/geometry
APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
#Navigating to the object (.o) files of the executable
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

#find the files with the extension .c in the src/libgeometry folder
LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
#Navigating to the object (.o) files of the executable
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

#the path to the libraries .h which we connect
DEPS = $(APP_OBJECTS:.o=.h) $(LIB_OBJECTS:.o=.h)

all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	$(RM) $(APP_PATH) $(OBJ_DIR)/*/*/*.[od]

.PHONY: run

run:
	./bin/geometry