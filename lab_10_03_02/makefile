CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -I ../lab_10_03_common --coverage
LDFLAGS := -lm -lgcov
UNIT_LDFLAGS := -lgcov -lcheck -lm -lpthread -lrt
#UNIT_LDFLAGS := -lgcov -lcheck -lsubunit -lm -lpthread -lrt

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))

UNIT_SRCS := $(wildcard check_*.c)
UNIT_OBJS := $(OBJS)

unit_tests.exe : $(UNIT_OBJS)
	$(CC) $^ -o $@ $(UNIT_LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.d : %.c
	$(CC) -MM $< > $@

.PHONY : clean unit

unit : unit_tests.exe
	./$<

clean :
	$(RM) -rf -- *.exe *.o *.gcno *.gcda
