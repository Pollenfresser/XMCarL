TARGET   = myapplication
CC       = gcc
RM       = rm -rf
SRCDIR   = ./src
SRC      = $(wildcard $(SRCDIR)/*.c)
INCDIR   = ./inc
CFLAGS   = -Wall --pedantic -g
CFLAGS  += -I$(INCDIR)
OBJS     = $(SRC:.c=.o)

all: $(OBJS) $(TARGET)

%.o: %.c
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	$(RM) $(OBJS) $(TARGET) core *~
