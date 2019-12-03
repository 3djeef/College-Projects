#include "FSerial.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main() {
	cout << "Test begins.\n";
	
	/* ofstream foo;
	foo.open("data");
	foo << "f" "t" "s" "\x0"s "i" "\x4f\x80\x0\x0\x0"s "l" "\x8f\xf2\x1f\xae\x74\x50\x49\x11\xcc" "c" "\x7c" "S\x10\x10" "TESTING string1.";
	foo.close(); */
	
	try {
		OFSerial out("data");
		cout << out.fail() << out << endl;
		bool z = false;
		bool y = true;
		short x = 0;
		int w = -2147483648;
		long v = -999888777666555444;
		char u = '|';
		string t = "TESTING string1.";
		out << z;
		out << y;
		out << x;
		out << w;
		out << v;
		out << u;
		out << t;
	} catch (string msg) {
		cout << msg << endl;
	} try {
		IFSerial in("data");
		bool a, b;
		in >> a >> b;
		assert(!a);
		assert(b);

		cout << in.eof() << in.fail() << in << endl;
		
		short c;
		in >> c;
		assert(c == 0);
		
		int d;
		in >> d;
		assert(d == -2147483648);
		
		long e;
		in >> e;
		assert(e == -999888777666555444);
		
		char f;
		in >> f;
		assert(f == '|');
		
		string h;
		in >> h;
		assert(h == "TESTING string1.");
		cout << in.eof() << in.fail() << endl;
		
		
		int l;
		in >> l;
		cout << in.eof() << in.fail() << endl;
		
		const IFSerial p("simple");
		cout << "const: " << p.eof() << endl;
		
		cout << "const: " << p.eof() << endl;
		
		
	} catch (string msg) {
		
	}	

	try {
		OFSerial out("lock");
		cout << out.fail() << out << endl;
		bool z = false;
		bool y = true;
		short x = 0;
		int w = -2147483648;
		long v = -999888777666555444;
		char u = '|';
		string t = "TESTING string1.";
		out << z;
		out << y;
		out << x;
		out << w;
		out << v;
		out << u;
		out << t;
	} catch (string msg) {
		cout << msg << endl;
	} try {
		IFSerial in("lock");
		bool a, b;
		in >> a >> b;
		assert(!a);
		assert(b);

		cout << in.eof() << in.fail() << in << endl;
		
		short c;
		in >> c;
		assert(c == 0);
		
		int d;
		in >> d;
		assert(d == -2147483648);
		
		long e;
		in >> e;
		assert(e == -999888777666555444);
		
		char f;
		in >> f;
		assert(f == '|');
		
		string h;
		in >> h;
		assert(h == "TESTING string1.");
		cout << in.eof() << in.fail() << endl;
		
		
		int l;
		in >> l;
		cout << in.eof() << in.fail() << endl;
		
		
	} catch (string msg) {
		
	}




	{
	OFSerial out("data");
	out << true;
	out << 'x' << 42;
	}

	IFSerial in("data");
	bool b; char c; int i;
	in >> b >> c;
	in >> i;
	assert(b);
	assert(c == 'x');
	assert(i == 42);
	assert(in);
	assert(!in.fail());
	assert(!in.eof());
	in >> i;
	assert(!in);		// same as in.fail()
	assert(in.fail());	// a conversion (in >> i) failed
	assert(in.eof());	// we hit end-of-file


	// Read the raw datafile
	ifstream raw("data");
	string data;
	while (raw.get(c))
	data += c;
	assert(data == "t" "cx" "i\x10\x2a");   // true, 'x', 42

	// Try writing to a file that can’t be created.
	OFSerial o("/this/does/not/exist");
	assert(!o);
	assert(o.fail());
	o << 14225628;	    // Must not complain, throw, or exit.
	assert(!o);
	assert(o.fail());
	cout << "Test ends.\n";
	return 0;
}