
CC = g++
CFLAGS = -Wall -g -I./include
CPP_FLAGS='-std=c++17'

ACPP=src/acpp
BINDIR=bin

.PHONY: all clean

all: bin/ch1 bin/ch2 bin/ch3 bin/ch4 bin/ch5 bin/ch6 bin/ch7

clean:
	rm -rf $(ACPP)/*.o
	rm -rf $(BINDIR)/*

$(ACPP)/grade.o: $(ACPP)/grade.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/Student_info.o: $(ACPP)/Student_info.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/median.o: $(ACPP)/median.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/util.o: $(ACPP)/util.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)


$(BINDIR)/ch1: $(ACPP)/ch1.cpp 
	$(CC) $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch2: $(ACPP)/ch2.cpp 
	$(CC) $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch3: $(ACPP)/ch3.cpp
	$(CC) $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/ch4.o: $(ACPP)/ch4.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch4: $(ACPP)/ch4.o $(ACPP)/median.o $(ACPP)/Student_info.o $(ACPP)/grade.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/ch5.o: $(ACPP)/ch5.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch5: $(ACPP)/ch5.o $(ACPP)/median.o $(ACPP)/Student_info.o $(ACPP)/grade.o $(ACPP)/util.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/ch6.o: $(ACPP)/ch6.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch6: $(ACPP)/ch6.o $(ACPP)/util.o $(ACPP)/Student_info.o $(ACPP)/median.o $(ACPP)/grade.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch7: $(ACPP)/ch7.cpp
	$(CC) $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch8: $(ACPP)/ch8.cpp
	$(CC) $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(ACPP)/ch9.o: $(ACPP)/ch9.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPP_FLAGS)

$(BINDIR)/ch9: $(ACPP)/ch9.o $(ACPP)/Student_info.o $(ACPP)/median.o $(ACPP)/grade.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPP_FLAGS)