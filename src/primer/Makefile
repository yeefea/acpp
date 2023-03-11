CFLAGS=-Wall -O2
CPPFLAGS=-std=c++17

utils.o: utils.cpp
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

sales_data.o: sales_data.cpp
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch2_types.o: ch2_types.cpp 
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch2: utils.o ch2_types.o
	g++ $^ -o $@ $(CFLAGS) $(CPPFLAGS)

ch3_string.o: ch3_string.cpp 
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch4_expression.o: ch4_expression.cpp
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch5_statement.o: ch5_statement.cpp
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch6_function.o: ch6_function.cpp
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch7_class.o: ch7_class.cpp
	g++ -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

ch3: utils.o ch3_string.o
	g++ $^ -o $@ $(CFLAGS) $(CPPFLAGS)

ch4: utils.o ch4_expression.o
	g++ $^ -o $@ $(CFLAGS) $(CPPFLAGS)

ch5: utils.o ch5_statement.o
	g++ $^ -o $@ $(CFLAGS) $(CPPFLAGS)

ch6: utils.o ch6_function.o
	g++ $^ -o $@ $(CFLAGS) $(CPPFLAGS)

ch7: sales_data.o utils.o ch7_class.o
	g++ $^ -o $@ $(CFLAGS) $(CPPFLAGS)

.PHONY: clean
clean:
	rm *.o
