CXX = g++
CXXFLAGS = -Wall

proj4: Carrier.o FedEx.o Letter.o Mail.o MailHouse.o Package.o Ups.o driver.cpp       
	$(CXX) $(CXXFLAGS) Carrier.o FedEx.o Letter.o Mail.o MailHouse.o Package.o Ups.o driver.cpp -o proj4

MailHouse.o: MailHouse.cpp MailHouse.h
	$(CXX) $(CXXFLAGS) -c MailHouse.cpp

Carrier.o: MailHouse.o Carrier.cpp Carrier.h
	$(CXX) $(CXXFLAGS) -c Carrier.cpp

Mail.o:  MailHouse.o Mail.cpp Mail.h
	$(CXX) $(CXXFLAGS) -c Mail.cpp

FedEx.o: MailHouse.o Carrier.o FedEx.cpp FedEx.h
	$(CXX) $(CXXFLAGS) -c FedEx.cpp

Ups.o: MailHouse.o Carrier.o Ups.cpp Ups.h
	$(CXX) $(CXXFLAGS) -c Ups.cpp

Letter.o: MailHouse.o Mail.o Letter.cpp Letter.h
	$(CXX) $(CXXFLAGS) -c Letter.cpp

Package.o: MailHouse.o Mail.o Package.cpp Package.h
	$(CXX) $(CXXXFLAGS) -c Package.cpp

clean:
	rm *.o*
	rm *~
run:
	./proj4

run1:
	./proj4 proj4_t1.txt

val1:
	valgrind ./proj4 proj4_t1.txt

run2:
	./proj4 proj4_t2.txt

val2:
	valgrind ./proj4 proj4_t2.txt

run3:
	./proj4 proj4_t3.txt

val3:
	valgrind ./proj4 proj4_t3.txt

run4:
	./proj4 proj4_t4.txt

val4:
	valgrind ./proj4 proj4_t4.txt
