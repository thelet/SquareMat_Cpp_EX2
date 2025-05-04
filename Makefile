#/*  Author: <Thelet.Shevach@gmail.com


CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -pedantic -Werror
INCLUDES  := -Iinclude

SRCDIR    := src
TESTDIR   := tests
OBJDIR    := obj
BINDIR    := bin

LIB_SRCS  := $(wildcard $(SRCDIR)/SquareMat_*.cpp)
MAIN_SRC  := $(SRCDIR)/Main.cpp
TEST_SRC  := $(TESTDIR)/tests.cpp

LIB_OBJS  := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(LIB_SRCS))
MAIN_OBJ  := $(OBJDIR)/Main.o
TEST_OBJ  := $(OBJDIR)/tests.o

MAIN_BIN  := $(BINDIR)/Main
TEST_BIN  := $(BINDIR)/test

all: Main test

# ── Build & RUN the demo ───────────────────────────────
.PHONY: Main
Main: $(MAIN_BIN)
	@echo "Running Main demo:"
	@./$(MAIN_BIN)

# ── Build & RUN tests ───────────────────────────────────
.PHONY: test
test: $(TEST_BIN)

$(TEST_BIN): $(LIB_OBJS) $(TEST_OBJ) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Running unit tests:"
	@./$(TEST_BIN)

# ── Run tests under Valgrind for leak checks ────────────
.PHONY: valgrind
valgrind: $(TEST_BIN)
	@echo "Checking for memory leaks with Valgrind:"
	valgrind --leak-check=full --error-exitcode=1 ./$(TEST_BIN)

# ── Link demo ───────────────────────────────────────────
$(MAIN_BIN): $(LIB_OBJS) $(MAIN_OBJ) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ── Compile .cpp → .o ───────────────────────────────────
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ── Ensure directories exist ────────────────────────────
$(OBJDIR) $(BINDIR):
	mkdir -p $@

# ── Clean up ────────────────────────────────────────────
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
