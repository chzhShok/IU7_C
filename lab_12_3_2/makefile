CC := gcc
OUT_DIR := ./out
SRC_DIR := ./src
INC_DIR := ./inc
UNIT_DIR := ./unit_tests
LIB_SRC_DIR := ./libsrc
LIB_INC_DIR := ./libinc

CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -I $(INC_DIR) -I $(LIB_INC_DIR) -g -MMD
LDFLAGS := -lm -lgcov
#UNIT_LDFLAGS := -lgcov -lcheck -lm -lpthread -lrt
UNIT_LDFLAGS := -lgcov -lcheck -lsubunit -lm -lpthread -lrt

SRCS := $(wildcard $(SRC_DIR)/*.c)
LIB_SRCS := $(wildcard $(LIB_SRC_DIR)/*.c)
UNIT_SRCS := $(wildcard $(UNIT_DIR)/check_*.c)

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o) $(LIB_SRCS:$(LIB_SRC_DIR)/%.c=$(OUT_DIR)/%.o)
ALL_OBJS := $(OBJS) $(UNIT_SRCS:$(UNIT_DIR)/%.c=$(OUT_DIR)/%.o)
UNIT_OBJS := $(filter-out $(OUT_DIR)/main.o, $(ALL_OBJS))

DEPS := $(OBJS:.o=.d) $(UNIT_OBJS:.o=.d)

LIBRARY := libmylib.so

python: $(OUT_DIR)/$(LIBRARY)
	python3 main.py

$(OUT_DIR)/$(LIBRARY): $(LIB_SRCS:$(LIB_SRC_DIR)/%.c=$(OUT_DIR)/%.o)
	mkdir -p $(OUT_DIR)
	$(CC) -shared -o $@ $^

unit_tests.exe : $(UNIT_OBJS) $(OUT_DIR)/$(LIBRARY)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(UNIT_LDFLAGS) -L$(OUT_DIR) -lmylib

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(OUT_DIR)/%.o : $(LIB_SRC_DIR)/%.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(OUT_DIR)/check_%.o : $(UNIT_DIR)/check_%.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean unit run

unit: unit_tests.exe
	./$<

clean:
	$(RM) -- -rf ./*.exe $(OUT_DIR)/* *.out ./func_tests/scripts/*.temp ./func_tests/data/*.tmp output.txt

-include $(DEPS)
