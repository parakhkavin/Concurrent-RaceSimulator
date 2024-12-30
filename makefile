CXX = g++

CXXFLAGS = -std=c++17 -pthread

INCLUDES = -I./src

SRCDIR = src

OBJDIR = obj

BINDIR = bin


SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


EXECUTABLE = $(BINDIR)/race

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

run: $(EXECUTABLE)
	@./$(EXECUTABLE) 2
	@./$(EXECUTABLE) 4
	@./$(EXECUTABLE) 10

clean:
	rm -rf $(OBJDIR)
	rm -f -r $(BINDIR)
	rm -r -f html
	rm -r -f latex

doc:
	doxygen docConfig

