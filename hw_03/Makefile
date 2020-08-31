CXX = g++
CXXFLAGS = -O3 -std=c++17 -Iinclude  -Werror -Wextra -Wunused-variable #-fsanitize=address
LDFLAGS = #-lasan -lncurses

EXE = hw_03
TEST = test_hw_03
SRCDIR = src
TESTDIR = test
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
TESTOBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(TESTDIR)/*.cpp))

all: $(TEST) $(EXE) 

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(TEST): $(OBJECTS) $(EXE) $(TESTOBJECTS)
	$(CXX) $(TESTOBJECTS)  obj/HuffmanException.o obj/BitReader.o obj/BitWriter.o obj/TreeNode.o obj/Tree.o obj/HuffmanNode.o obj/HuffmanTree.o obj/HuffmanArchiver.o obj/CLI.o -o $(TEST) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)


$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TEST)

.PHONY: clean all
