SRCDIR = ./src
INCDIR = ./inc
SRC = $(wildcard src/*.c)
RESOURCE = gui_res

TARGET = main

CXX = gcc
#json-glib-1.0
CXXFLAGS = 'pkg-config --cflags --libs gtk+-3.0'
CXXFLAGS += -Wall -g
CXXFLAGS += -I$(SRCDIR)
CXXFLAGS += -I$(INCDIR)


OBJS = $(SRC:.c=.o)

all: $(SRC) $(TARGET)

%.o: %.c
	$(CXX) $(CXXFLAGS) $(RESOURCE) $< -o $(TARGET)
	@echo ""


.PHONY: clean
clean:
	@rm -rf $(OBJECT) $(TARGET) core *~
	@rm -rf $(RESOURCE).c
