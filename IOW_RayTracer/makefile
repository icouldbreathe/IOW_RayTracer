# Makefile

# Project files
EXE := ray
BUILD_DIR := build
BIN_DIR := bin
SRC_DIRS ?= src
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Debug build config
DB_DIR := debug
DB_BUILD_DIR := $(DB_DIR)/$(BUILD_DIR)
DB_BIN_DIR := $(DB_DIR)/$(BIN_DIR)
DB_EXE := $(DB_BIN_DIR)/$(EXE)_debug.out
DB_OBJS := $(SRCS:%=$(DB_BUILD_DIR)/%.o)
DB_DEPS := $(DB_OBJS:.o=.d)
DB_CPP_FLAGS := -g -O0 -DDEBUG

# Release build config
REL_DIR := release
REL_BUILD_DIR := $(REL_DIR)/$(BUILD_DIR)
REL_BIN_DIR := $(REL_DIR)/$(BIN_DIR)
REL_EXE := $(REL_BIN_DIR)/$(EXE)_release.out
REL_IMG_OUTPUT := $(REL_BIN_DIR)/render.ppm
REL_OBJS := $(SRCS:%=$(REL_BUILD_DIR)/%.o)
REL_DEPS := $(REL_OBJS:.o=.d)
REL_CPP_FLAGS := -O3 -DNDEBUG

# Compiler flags
CXX := clang++
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++11 -Wall -Werror -Wextra 

# Default build
all: render

# Debug rules
debug: $(DB_EXE)

$(DB_EXE): $(DB_OBJS)
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CPPFLAGS) $(DB_CPP_FLAGS) $(DB_OBJS) -o $@ $(LDFLAGS)
	@echo "Debug: Finished"

$(DB_BUILD_DIR)/%.cpp.o: %.cpp
	@echo "Debug: Building.."
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DB_CPP_FLAGS) -c $< -o $@

# Release rules
release: $(REL_EXE)

$(REL_EXE): $(REL_OBJS)
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CPPFLAGS) $(REL_CPP_FLAGS) $(REL_OBJS) -o $@ $(LDFLAGS)
	@echo "Release: Finished."

$(REL_BUILD_DIR)/%.cpp.o: %.cpp
	@echo "Release: Building.."
	@$(MKDIR_P) $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(REL_CPP_FLAGS) -c $< -o $@

# Render rules
render: $(REL_IMG_OUTPUT)

$(REL_IMG_OUTPUT): $(REL_EXE)
	@echo "Release: Executing.."
	@$(MKDIR_P) $(dir $@)
	@$< > $@
	@open $@

# Other rules
prep:
	$(MKDIR_P) $(DB_DIR) $(DB_BUILD_DIR) $(DB_BIN_DIR) $(REL_DIR) $(REL_BUILD_DIR) $(REL_BIN_DIR)

.PHONY: all clean debug prep release remake

remake: clean all

clean:
	@echo "Cleaning up.."
	@$(RM) -r $(DB_DIR) $(REL_DIR)

-include $(DEPS)
MKDIR_P ?= mkdir -p
