OPT= -g -Wall -Wextra -Werror

all: kmoyennes

kmoyennes: kmoyennes.o image.o
	gcc $(OPT) $^ -o $@

%.o: %.c
	gcc $(OPT) -c $<

clean:
	rm -f *.o kmoyennes out.ppm