OUT_DIR=build
OUT_BIN=main

SRC_DIR=src
INC_DIR=inc
OBJ_DIR=obj

CFLAGS?= -O2 -std=c99 -I$(INC_DIR)
LDFLAGS+= -s
CC?=gcc

ifeq ($(OS),Windows_NT)
	LDFLAGS := -lmingw32 $(LDFLAGS) -Llib
	OUT_BIN := $(OUT_BIN).exe
endif

OUT := $(OUT_DIR)/$(OUT_BIN)

.PHONY: run all

all: $(OUT)

run: all
	cd build && $(OUT_BIN)

$(OUT): $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) -c $(CFLAGS) $< -o $@