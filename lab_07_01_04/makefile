CC := gcc
OUT_DIR := ./out
SRC_DIR := ./src
INC_DIR := ./inc
UNIT_DIR := ./unit_tests

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -I $(INC_DIR) --coverage
LDFLAGS := -lm -lgcov
UNIT_LDFLAGS := -lgcov -lcheck -lm -lpthread -lrt

SRCS := $(wildcard $(SRC_DIR)/*.c)
UNIT_SRCS := $(wildcard $(UNIT_DIR)/check_*.c)

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(SRCS))
UNIT_OBJS := $(patsubst $(UNIT_DIR)/check_%.c,$(OUT_DIR)/check_%.o,$(UNIT_SRCS))

all: app.exe

app.exe: $(OBJS)
	mkdir -p $(OUT_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

unit_tests.exe : $(UNIT_OBJS) $(OUT_DIR)/array.o
	mkdir -p $(OUT_DIR)
	$(CC) $^ -o $@ $(UNIT_LDFLAGS)

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_%.o : $(UNIT_DIR)/check_%.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean coverage func release unit debug sanitized

func : app.exe
	./func_tests/scripts/func_tests.sh

release: CFLAGS += -O2
release: app.exe

debug: CC := clang
debug: CFLAGS += -DDEBUG=1 -glldb -fdebug-macro
debug: app.exe

sanitized: CC := clang
sanitized: CFLAGS += -fsanitize=address -fsanitize=undefined
sanitized: LDFLAGS += -fsanitize=address -fsanitize=undefined
sanitized: debug

unit : unit_tests.exe
	./$<

clean :
	$(RM) -rf ./*.exe $(OUT_DIR)/* *.out ./func_tests/scripts/*.temp ./func_tests/data/*.tmp

coverage :
	lcov --directory $(OUT_DIR) --capture --output-file $(OUT_DIR)/coverage.info
	genhtml $(OUT_DIR)/coverage.info --output-directory $(OUT_DIR)/html
	xdg-open $(OUT_DIR)/html/index.html
