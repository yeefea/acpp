
CC = g++
CFLAGS = -Wall -g -I./include
CPP_FLAGS='-std=c++11'

ACPP=src/acpp
BINDIR=bin

.PHONY: all clean

all: bin/ch4 bin/ch5

clean:
	rm -rf $(ACPP)/*.o

$(ACPP)/grade.o: $(ACPP)/grade.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/Student_info.o: $(ACPP)/Student_info.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/median.o: $(ACPP)/median.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/ch4.o: $(ACPP)/ch4.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch4: $(ACPP)/ch4.o $(ACPP)/median.o $(ACPP)/Student_info.o $(ACPP)/grade.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/ch5.o: $(ACPP)/ch5.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch5: $(ACPP)/ch5.o $(ACPP)/median.o $(ACPP)/Student_info.o $(ACPP)/grade.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPP_FLAGS)