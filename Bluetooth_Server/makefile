SOURCES = blue_server.c blue_client.c
TARGET = main

CXX = gcc
#json-glib-1.0
CXXFLAGS = -lbluetooth -Wall -g
CXXFLAGS += -I.
LDFLAGS = -lm


$(TARGET): $(SOURCES)
	$(CXX) blue_server.c $(LDFLAGS) $(CXXFLAGS) -o server.o
	$(CXX) blue_client.c $(LDFLAGS) $(CXXFLAGS) -o client.o

.PHONY: clean
clean:
	@rm -rf $(OBJECT) $(TARGET) core *~
