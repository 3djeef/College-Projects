CXXFLAGS:=-Wall -Wextra -Wpedantic

assignment=hw7

$(assignment).a: FSerial.o
	ar rcs $@ $^

Serial.o:: FSerial.h
testprog.o:: FSerial.h

test: testprog
	./testprog

testprog: testprog.o $(assignment).a
	$(CXX) $(CXXFLAGS) -o $@ $^

tar:
	tar -cv $(MAKEFILE_LIST) FSerial.cc FSerial.h >$(assignment).tar

clean:
	rm -f a.out testprog *.a *.tar *.o