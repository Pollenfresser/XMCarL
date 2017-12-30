SOURCES = rs232.c

TARGET = main

CXX = gcc
#json-glib-1.0
CXXFLAGS = -Wall -g
#CXXFLAGS += -I.
#LDFLAGS = -lm


$(TARGET): $(SOURCES) $(RESOURCE).c
	$(CXX) $(SOURCES) $(RESOURCE).c $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)

.PHONY: clean
clean:
	@rm -rf $(OBJECT) $(TARGET) core *~
	@rm -rf $(RESOURCE).c
