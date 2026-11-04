CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Wconversion -g
INCLUDES = -Ican_demo

SRCS = can_demo/Can.c \
       can_demo/CanIf.c \
       can_demo/PduR.c \
       can_demo/Com.c \
       can_demo/Rte.c \
       can_demo/Swc.c \
       can_demo/main.c

TARGET = can_demo/can_demo.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

run: all
	.\$(TARGET)

clean:
	del /Q can_demo\can_demo.exe