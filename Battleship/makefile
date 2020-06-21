CXX = g++
CXXFLAGS = -Wall

proj4: Computer.o Grid.o User.o Player.o main.cpp
	$(CXX) $(CXXFLAGS) Computer.o Grid.o User.o Player.o main.cpp -o proj4

Computer.o: Grid.o Player.o Computer.cpp Computer.h
	$(CXX) $(CXXFLAGS) -c Computer.cpp

Grid.o: Grid.cpp Grid.h
	$(CXX) $(CXXFLAGS) -c Grid.cpp

User.o: Grid.o Player.o User.cpp User.h
	$(CXX) $(CXXFLAGS) -c User.cpp

Player.o: Grid.o Player.cpp Player.h 
	$(CXX) $(CXXFLAGS) -c Player.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj4

run1:
	./proj4 p4_comp1.txt p4_user1.txt

run2:
	./proj4 p4_comp2.txt p4_user2.txt

run3:
	./proj4 p4_comp3.txt p4_user3.txt
