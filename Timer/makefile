INC_FILES := timer.h
SRC_FILES := timer.c main.c
OBJ_FILES := $(SRC_FILES:.c=.o)
TARGET := main

RM := rm -rf

CC := gcc
CFLAGS := -g
LFLAGS := -lpthread

all : $(TARGET)

%.o : %.c $(INC_FILES)
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET) : $(OBJ_FILES)
	$(CC) $(LFLAGS) -o $(TARGET) $^

clean :
	$(RM) $(OBJ_FILES) $(TARGET)

rebuild :
	$(MAKE) clean
	$(MAKE) all
