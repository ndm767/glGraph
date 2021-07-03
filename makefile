PNAME := glGraph

PCXXSRC := $(wildcard src/*.cpp)
PCXXSRC += $(wildcard src/parser/*.cpp)
PCXXSRC += $(wildcard src/renderer/*.cpp)
PCXXSRC += $(wildcard src/renderer/imgui/*.cpp)

POBJS := $(PCXXSRC:.cpp=.o)

CXXFLAGS += -std=c++17

LDLIBS += -lSDL2 -lGLEW -lGL

.SILENT: all $(POBJS)
.PHONY: all

all: $(PNAME)

$(PNAME): $(POBJS)
	@-$(LINK.cc) $(POBJS) -o $(PNAME) $(LDLIBS)
	@-$(RM) $(POBJS)

clean:
	@- $(RM) $(PNAME)
	@- $(RM) $(POBJS)
