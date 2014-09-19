OBJETS=src/banker.o lib/processes.o
CXXFLAGS=-Ilib

banker: $(OBJETS)
				g++ $(OBJETS) -o banker

lib/processes.o: lib/processes.cpp

src/banker.o: src/banker.cpp lib/processes.h
