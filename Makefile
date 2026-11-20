CC ?= gcc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wpedantic
CPPFLAGS ?= -Iinclude
CORE = src/core.c src/algorithms.c
all: portfolio_lab portfolio_tests benchmark_runner
portfolio_lab: src/main.c $(CORE)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -lm
portfolio_tests: tests/tests.c $(CORE)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -lm
benchmark_runner: src/benchmark.c $(CORE)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -lm
test: portfolio_tests
	./portfolio_tests
clean:
	rm -f portfolio_lab portfolio_tests benchmark_runner
