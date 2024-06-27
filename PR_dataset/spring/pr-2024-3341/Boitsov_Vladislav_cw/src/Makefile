CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCDIR = .
BUILDDIR = ./build
TARGET = ./cw

SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

INCLUDEDIRS = $(shell find $(SRCDIR) -type d)
INCLUDEFLAGS = $(addprefix -I, $(INCLUDEDIRS))

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all
all: $(TARGET)

-include $(OBJECTS:.o=.d)

$(BUILDDIR)/%.d: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) -MM -MT $(patsubst %.d,%.o,$@) $< > $@
