TARGET   = application.out
CC       = gcc
RM       = rm -rf
SRCDIR   = ./src
SRC      = $(wildcard $(SRCDIR)/*.c)
INCDIR   = ./inc
CFLAGS   = `pkg-config --cflags --libs gtk+-3.0`
CFLAGS  += `pkg-config --cflags --libs gstreamer-1.0`
CFLAGS  += -I$(INCDIR)
CFLAGS  += -Wall -g
OBJS     = $(SRC:.c=.o)
RESOURCE = gui_res

all: $(OBJS) $(TARGET)

%.o: %.c $(RESOURCE).c
	$(CC) $(SRC) $(RESOURCE).c $(CFLAGS) -o $(TARGET)

$(RESOURCE).c: $(RESOURCE).gresource.xml
	glib-compile-resources --sourcedir=. $(RESOURCE).gresource.xml --generate-source

clean:
	$(RM) $(OBJS) $(TARGET) $(RESOURCE).c core *~
