OBJS = BF.o 
SRCS = BF.cpp 
CC = g++11
CFLAGS = -Wall -g -std=c++11

BF: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@


%.o: %.cc
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f *.o *~ *% *# .#*
clean-all:
	rm -f *.o *~ *% *# .#*