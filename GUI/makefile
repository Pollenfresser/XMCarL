TARGET   = myapplication
CC       = gcc
RM       = rm -rf
SRCDIR   = ./src
SRC      = $(wildcard $(SRCDIR)/*.c)
INCDIR   = ./inc
CFLAGS   = `pkg-config --cflags --libs gtk+-3.0`
CFLAGS   = `pkg-config --cflags --libs gstreamer-1.0`
CFLAGS  += -I$(INCDIR)
CFLAGS  += -Wall -g
OBJS     = $(SRC:.c=.o)

all: $(OBJS) $(TARGET)

%.o: %.c
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	$(RM) $(OBJS) $(TARGET) core *~
