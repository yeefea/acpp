CFLAGS=-O2
CPPFLAGS=-std=c++17

utils.o: utils.cpp
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch2_types.o: ch2_types.cpp 
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch2: utils.o ch2_types.o
	g++ $^ -o $@ $(CFLAGS) $(CPPFLAGS)

.PHONY: clean
clean:
	rm *.o