CFLAGS=-O2 -I../../include -lzmq
CPPFLAGS=-std=c++17


hwclient: hwclient.cpp
	g++ $< -o $@ $(CFLAGS) $(CPPFLAGS)

hwserver: hwserver.cpp
	g++ $< -o $@ $(CFLAGS) $(CPPFLAGS)


.PHONY: clean
clean:
	rm *.o