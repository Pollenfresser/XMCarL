SRCDIR = ./src
INCDIR = ./inc
SRC = $(wildcard src/*.c)
RESOURCE = gui_res



TARGET = main

CXX = gcc
#json-glib-1.0
CXXFLAGS = -Wall -g
CXXFLAGS += -I$(SRCDIR)
CXXFLAGS += -I$(INCDIR)
#LDFLAGS = -lm


OBJS = $(SRC:.c=.o)


%.o: %.c
	$(CXX) $(CXXFLAGS) $(RESOURCE).c $< -o $@
	@echo ""


.PHONY: clean
clean:
	@rm -rf $(OBJECT) $(TARGET) core *~
	@rm -rf $(RESOURCE).c
