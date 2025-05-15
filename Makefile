# Directories
TOP_DIR := .
HDR_DIR := $(TOP_DIR)/hdr
TEST_DIR := $(TOP_DIR)/tests
BUILD_DIR := $(TOP_DIR)/build
TEST_BIN_DIR := $(BUILD_DIR)/bin

# Resources
HDRS := $(wildcard $(HDR_DIR)/*.hpp)
TEST_MAIN := $(TEST_DIR)/doctest.cpp
TEST_SRCS := $(filter-out $(TEST_MAIN),$(wildcard $(TEST_DIR)/*.cpp))
TEST_NAMES := $(subst .cpp,,$(subst $(TEST_DIR)/,,$(TEST_SRCS)))
RUN_TEST_NAMES := $(addsuffix .run,$(TEST_NAMES))

# Compiler definitions
CC := g++
CFLAGS := -std=c++17 
INCS := $(HDR_DIR) $(TEST_DIR)

# Formatting
SEP_STR := "---------------------------------------------------"

# Targets
.PHONY: all test $(TEST_NAMES) $(RUN_TEST_NAMES) clean

all: $(TEST_NAMES)

test: $(RUN_TEST_NAMES)

$(RUN_TEST_NAMES): %.run : %
	$(TEST_BIN_DIR)/$*

$(TEST_NAMES):% : $(TEST_BIN_DIR)/%

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo $(SEP_STR)
	@echo -n "Compiling test executable $* ..."
	$(CC) $(CFLAGS) $(addprefix -I ,$(INCS)) -o $@ $(TEST_MAIN) $<
	@echo -n " done."
	@echo $(SEP_STR)

clean:
	rm -rf $(BUILD_DIR)
