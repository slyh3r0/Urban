CC=gcc
CCFLAGS=



HEADERS=
OBJECTS:=$(patsubst %.c, %.o, $(wildcard *.c))

.PHONY: all test clean
default: urban


urban: $(filter-out test.o, $(OBJECTS))
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJECTS): %.o: %.c $(HEADERS)
	$(CC) $(CCFLAGS) -c -o $@ $<

test: test.o regex.o
	$(CC) $(CCFLAGS) -o $@ $^


clean:
	rm -rf $(OBJECTS) urban test
