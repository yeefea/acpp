CFLAGS=-O2
CPPFLAGS=-std=c++17

utils.o: utils.cpp
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch2_types.o: ch2_types.cpp 
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch2: utils.o ch2_types.o
	g++ $^ -o $@ $(CFLAGS) $(CPPFLAGS)

ch3_string.o: ch3_string.cpp 
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch3: utils.o ch3_string.o
	g++ $^ -o $@ $(CFLAGS) $(CPPFLAGS)

.PHONY: clean
clean:
	rm *.o