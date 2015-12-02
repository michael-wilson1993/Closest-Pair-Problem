OBJS = create.o
SRCS = create.cpp 
CC = g++11
CFLAGS = -Wall -g -std=c++11

create: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@


%.o: %.cc
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f *.o *~ *% *# .#*
clean-all:
	rm -f *.o *~ *% *# .#*