# Makefile for C/C++

# target binary
BIN := none
BIN_DIR := bin
TESTS_DIR := tests

# PREFIX ?= arm-none-eabi

# select compiler
CXX := gcc
CXXFLAGS = -g -Wall -O0 -fno-omit-frame-pointer # debug
# CXXFLAGS = -Wall -O3  # benchmarking
CSTD ?= -std=c99   # c18

# sources
SRC_DIR := emu
SRC_SUBDIRS := 

# include paths (space separated)
INC_DIRS = . 

# library paths (space separated)
LIB_DIRS := # /usr/lib/x86_64-linux-gnu/openssl

# library names e.g. "pthread" or crypto"
LIB_NAMES := # crypto  # uncomment for SSL

# where to store the objects
OBJ_DIR := ./obj
OBJ_EXT := .o


# Do not etdit below this line
# ----------------------------------------------------
SRC_EXT_C := .c
SRC_EXT_CPP := .cpp

# find and collect sources
SRCS_C := $(wildcard $(SRC_DIR)/*$(SRC_EXT_C))
SRCS_C += $(foreach subdir,$(SRC_SUBDIRS),$(wildcard $(SRC_DIR)/$(subdir)/*$(SRC_EXT_C)))
SRCS_CPP := $(wildcard $(SRC_DIR)/*$(SRC_EXT_CPP))
SRCS_CPP += $(foreach subdir,$(SRC_SUBDIRS),$(wildcard $(SRC_DIR)/$(subdir)/*$(SRC_EXT_CPP)))

# collect includes
INCS += $(foreach idir,$(INC_DIRS),-I$(idir))

# collect libraries
LIBS += $(foreach ldir,$(LIB_DIRS),-L$(ldir))
LIBS += $(foreach lname,$(LIB_NAMES),-l$(lname))

# determine objects to build based on sources
OBJS_C += $(patsubst $(SRC_DIR)/%$(SRC_EXT_C), $(OBJ_DIR)/%.o, $(SRCS_C))
OBJS_CPP += $(patsubst $(SRC_DIR)/%$(SRC_EXT_CPP), $(OBJ_DIR)/%.o, $(SRCS_CPP))

OBJS += $(OBJS_C)
OBJS += $(OBJS_CPP)
OBJS := $(OBJS:$(SRC_EXT_C)=$(OBJ_EXT))  # double protection

# determine objects to link for binaries
LINKOBJ := $(filter-out $(OBJ_DIR)/main.o,$(OBJS))



TEST_SRCS += $(wildcard $(TESTS_DIR)/*$(SRC_EXT_C))
TEST_SRCS += $(wildcard $(TESTS_DIR)/*$(SRC_EXT_CPP))
TEST_BINS += $(basename $(notdir $(TEST_SRCS)))



# available targets
# ----------------------------------------------------
all: echo mkobjdirs tests

tests: mkobjdirs $(TEST_BINS)

clean:
	@rm -f $(BIN_DIR)/$(BIN) $(OBJS)
	$(foreach testbin, $(TEST_BINS), @rm -f  $(BIN_DIR)/$(testbin))
	@rm -d $(OBJ_DIR) $(BIN_DIR)


# Internal rules
# ----------------------------------------------------
echo:
	@echo "Compiling with $(CXX) $(CXXFLAGS)"
	@echo "Includes:  $(INCS)"
	@echo "Libraries: $(LIBS)"
	@echo "Sources:   $(SRCS_C) $(SRCS_CPP)"
	@echo "Objects:   $(OBJS)"
	@echo ""	


mkobjdirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	$(foreach subdir, $(SRC_SUBDIRS), @mkdir -p  $(OBJ_DIR)/$(subdir))

# link objects
main: $(OBJS)
	@echo "Linking $@..."	
	$(CXX) $^ -o $(BIN_DIR)/$(BIN) $(CXXFLAGS) $(INCS) $(LIBS)


# link objects to test binaries
$(TEST_BINS): $(OBJS)
	@echo "\nLinking $@:"
	$(CXX) $(LINKOBJ) $(TESTS_DIR)/$@.c* -o $(BIN_DIR)/$@ $(CXXFLAGS) $(INCS) $(LIBS)


# compile sources to objects	
$(OBJ_DIR)/%$(OBJ_EXT):$(SRC_DIR)/%$(SRC_EXT_C)
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

# compile sources to objects	
$(OBJ_DIR)/%$(OBJ_EXT):$(SRC_DIR)/%$(SRC_EXT_CPP)
	$(CXX) -c -o $@ $< $(CXXFLAGS) 


# will be called even if newest files exists
.PHONY: clean


# References
# https://ubuntuforums.org/showthread.php?t=1204739
