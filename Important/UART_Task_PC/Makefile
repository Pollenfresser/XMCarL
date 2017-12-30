SOURCES = /src/rs232.c
RESOURCE = /src/main

TARGET = main

CXX = gcc
#json-glib-1.0
CXXFLAGS = -Wall -g
#CXXFLAGS += -I.
#LDFLAGS = -lm


$(TARGET): $(SOURCES) $(RESOURCE).c
	$(CXX) $(SOURCES) $(RESOURCE).c $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)

$(RESOURCE).c: $(RESOURCE).gresource.xml
	glib-compile-resources --sourcedir=. $(RESOURCE).gresource.xml --generate-source

.PHONY: clean
clean:
	@rm -rf $(OBJECT) $(TARGET) core *~
	@rm -rf $(RESOURCE).c
