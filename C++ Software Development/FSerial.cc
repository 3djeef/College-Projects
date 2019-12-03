#include "FSerial.h"
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <cassert>

using namespace std;

//helper functions
string convertHex (string byte) {
//convert "00" to "\x00", etc using const string arrays
	const string nums[]= 
{"00","01","02","03","04","05","06","07","08","09","0a","0b","0c","0d","0e","0f",
"10","11","12","13","14","15","16","17","18","19","1a","1b","1c","1d","1e","1f",
"20","21","22","23","24","25","26","27","28","29","2a","2b","2c","2d","2e","2f",
"30","31","32","33","34","35","36","37","38","39","3a","3b","3c","3d","3e","3f",
"40","41","42","43","44","45","46","47","48","49","4a","4b","4c","4d","4e","4f",
"50","51","52","53","54","55","56","57","58","59","5a","5b","5c","5d","5e","5f",
"60","61","62","63","64","65","66","67","68","69","6a","6b","6c","6d","6e","6f",
"70","71","72","73","74","75","76","77","78","79","7a","7b","7c","7d","7e","7f",
"80","81","82","83","84","85","86","87","88","89","8a","8b","8c","8d","8e","8f",
"90","91","92","93","94","95","96","97","98","99","9a","9b","9c","9d","9e","9f",
"a0","a1","a2","a3","a4","a5","a6","a7","a8","a9","aa","ab","ac","ad","ae","af",
"b0","b1","b2","b3","b4","b5","b6","b7","b8","b9","ba","bb","bc","bd","be","bf",
"c0","c1","c2","c3","c4","c5","c6","c7","c8","c9","ca","cb","cc","cd","ce","cf",
"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","da","db","dc","dd","de","df",
"e0","e1","e2","e3","e4","e5","e6","e7","e8","e9","ea","eb","ec","ed","ee","ef",
"f0","f1","f2","f3","f4","f5","f6","f7","f8","f9","fa","fb","fc","fd","fe","ff"};

	const string hexs[]= 
{"\x00"s,"\x01","\x02","\x03","\x04","\x05","\x06","\x07","\x08","\x09","\x0a","\x0b","\x0c","\x0d","\x0e","\x0f",
"\x10","\x11","\x12","\x13","\x14","\x15","\x16","\x17","\x18","\x19","\x1a","\x1b","\x1c","\x1d","\x1e","\x1f",
"\x20","\x21","\x22","\x23","\x24","\x25","\x26","\x27","\x28","\x29","\x2a","\x2b","\x2c","\x2d","\x2e","\x2f",
"\x30","\x31","\x32","\x33","\x34","\x35","\x36","\x37","\x38","\x39","\x3a","\x3b","\x3c","\x3d","\x3e","\x3f",
"\x40","\x41","\x42","\x43","\x44","\x45","\x46","\x47","\x48","\x49","\x4a","\x4b","\x4c","\x4d","\x4e","\x4f",
"\x50","\x51","\x52","\x53","\x54","\x55","\x56","\x57","\x58","\x59","\x5a","\x5b","\x5c","\x5d","\x5e","\x5f",
"\x60","\x61","\x62","\x63","\x64","\x65","\x66","\x67","\x68","\x69","\x6a","\x6b","\x6c","\x6d","\x6e","\x6f",
"\x70","\x71","\x72","\x73","\x74","\x75","\x76","\x77","\x78","\x79","\x7a","\x7b","\x7c","\x7d","\x7e","\x7f",
"\x80","\x81","\x82","\x83","\x84","\x85","\x86","\x87","\x88","\x89","\x8a","\x8b","\x8c","\x8d","\x8e","\x8f",
"\x90","\x91","\x92","\x93","\x94","\x95","\x96","\x97","\x98","\x99","\x9a","\x9b","\x9c","\x9d","\x9e","\x9f",
"\xa0","\xa1","\xa2","\xa3","\xa4","\xa5","\xa6","\xa7","\xa8","\xa9","\xaa","\xab","\xac","\xad","\xae","\xaf",
"\xb0","\xb1","\xb2","\xb3","\xb4","\xb5","\xb6","\xb7","\xb8","\xb9","\xba","\xbb","\xbc","\xbd","\xbe","\xbf",
"\xc0","\xc1","\xc2","\xc3","\xc4","\xc5","\xc6","\xc7","\xc8","\xc9","\xca","\xcb","\xcc","\xcd","\xce","\xcf",
"\xd0","\xd1","\xd2","\xd3","\xd4","\xd5","\xd6","\xd7","\xd8","\xd9","\xda","\xdb","\xdc","\xdd","\xde","\xdf",
"\xe0","\xe1","\xe2","\xe3","\xe4","\xe5","\xe6","\xe7","\xe8","\xe9","\xea","\xeb","\xec","\xed","\xee","\xef",
"\xf0","\xf1","\xf2","\xf3","\xf4","\xf5","\xf6","\xf7","\xf8","\xf9","\xfa","\xfb","\xfc","\xfd","\xfe","\xff"};
	string hex("\0\0\0\0", 4);
	for (int i = 0; i < 256; i++) {
		if (nums[i]==byte) {
			hex = hexs[i];
			//inverse
		} else if (hexs[i]==byte) {
			hex = nums[i];
		}
	}
	return hex;
}
vector<string> Num2Vnum (int64_t n) {
	//convert any sizetype integer to strings of bytes in a vector
	int msb = 0;
	int64_t absval = llabs(n);
	//won't fit in llabs function
	if (n == -9223372036854775807 - 1) {
		absval = 9223372036854775807;
	}
	for(int64_t base2 = 1; base2 <= absval && msb < 64; base2<<=1){
		msb += 1;
	}
	msb+=1;
	int length = (int)ceil(((float)msb+4)/8)-1;
	int lengthBits = length << 4;
	int64_t temp = n;
	vector<string> result;
	for (int i=0; i<(length)+1; i++) {
		int byte = temp & 0xFF;
		if (i==length) {
			byte &= 0x0F;
			byte |= lengthBits;
		}
		stringstream stream;
		stream << hex << setw(2) << setfill('0') << byte;
		result.push_back(stream.str());
		temp >>= 8;
	}
	return result;
}
string makePositive(string s) {
//same thing as binary !(NOT), just with strings of hex
	for (unsigned int i=0; i<s.length(); i++) {
		char c = s.at(i);
		switch(c) {
			case '0' : {
				s.replace(i,1,1,'f');
			} break;
			case '1' : {
				s.replace(i,1,1,'e');
			} break;
			case '2' : {
				s.replace(i,1,1,'d');
			} break;
			case '3' : {
				s.replace(i,1,1,'c');
			} break;
			case '4' : {
				s.replace(i,1,1,'b');
			} break;
			case '5' : {
				s.replace(i,1,1,'a');
			} break;
			case '6' : {
				s.replace(i,1,1,'9');
			} break;
			case '7' : {
				s.replace(i,1,1,'8');
			} break;
			case '8' : {
				s.replace(i,1,1,'7');
			} break;
			case '9' : {
				s.replace(i,1,1,'6');
			} break;
			case 'a' : {
				s.replace(i,1,1,'5');
			} break;
			case 'b' : {
				s.replace(i,1,1,'4');
			} break;
			case 'c' : {
				s.replace(i,1,1,'3');
			} break;
			case 'd' : {
				s.replace(i,1,1,'2');
			} break;
			case 'e' : {
				s.replace(i,1,1,'1');
			} break;
			case 'f' : {
				s.replace(i,1,1,'0');
			} break;
		}
	}
   return s;
}
int64_t Vnum2Num (istream &in) {
	//convert stream of bytes into a number until the specified length(first 4 bits) is reached
	int length;
	int byte;
	string number;
	int64_t result;
	
	//grab length and first (half)byte
	byte = in.get();
	length = byte & 0xF0;
	byte = byte & 0x0F;
	length >>= 4;
	
	//process remaining bytes and create hex string
	stringstream stream;
	stream << hex << byte;
	number = stream.str();
	while (length > 0) {
		byte = in.get();
		stream << hex << setw(2) << setfill('0') << byte;
		length--;
	}
	number = stream.str();
	
	//check if hex number is negative
	string negativeSignBit = "89abcdef";
	char signBit = number.front();
	if (negativeSignBit.find(signBit) != string::npos) {
		//apply two's complement to identify correct negative number
		number = makePositive(number);
		result = stol(number,nullptr,16);
		result++;
		result = 0 - result;
	} else {
		//nothing special required for positive numbers
		result = stol(number,nullptr,16);
	}
	return result;
}

//serialization
void serialize(bool b, ostream &out) {
	if (b==true) {
		out << "t";
	} else {
		out << "f";
	}
}
void serialize(short s, ostream &out) {
	vector<string> result = Num2Vnum(s);
	out << "s";
	for (int i = result.size()-1; i>=0; i--) {
		out << convertHex(result[i]);
	}
}
void serialize(int n, ostream &out) {
	vector<string> result = Num2Vnum(n);
	out << "i";
	for (int i = result.size()-1; i>=0; i--) {
		out << convertHex(result[i]);
	}
}
void serialize(long l, ostream &out) {
	vector<string> result = Num2Vnum(l);
	out << "l";
	for (int i = result.size()-1; i>=0; i--) {
		out << convertHex(result[i]);
	}
}
void serialize(char c, ostream &out) {
	int id = c;
	stringstream stream;
	stream << hex << setw(2) << setfill('0') << id;
	string result = convertHex(stream.str());
	out << "c" << result;
}
void serialize(const string &s, ostream &out) {
	//vnum
	int length = s.length();
	vector<string> vnum = Num2Vnum(length);
	out << "S";
	for (int i = vnum.size()-1; i>=0; i--) {
		out << convertHex(vnum[i]);
	}
	//chars
	for (int i = 0; i < length; i++) {	
		int c = s.at(i);
		stringstream stream;
		stream << hex << setw(2) << setfill('0') << c;
		out << convertHex(stream.str());
	}
}

void unserialize(istream &in, bool &b) {
	char c = in.get();
	assert (c=='t'||c=='f');
	(c == 't') ? b = true : b = false;

}
void unserialize(istream &in, short &s) {
	char c = in.get();
	assert (c=='s');
	int64_t result = Vnum2Num(in);
	s = result;
}
void unserialize(istream &in, int &i) {
	char c = in.get();
	assert (c=='i');
	int64_t result = Vnum2Num(in);
	i = result;
}
void unserialize(istream &in, long &l) {
	char c = in.get();
	assert(c=='l');
	int64_t result = Vnum2Num(in);
	l = result;
}
void unserialize(istream &in, char &c) {
	string result;
	char ch = in.get();
	assert(ch=='c');
	c = in.get();
}
void unserialize(istream &in, string &s) {
	char c = in.get();
	assert(c=='S');
	int length = Vnum2Num(in);
	for (int i = 0; i < length; i++) {
		s += in.get();
	}
}

//class IFSerial
IFSerial::IFSerial(const std::string file) {
	vs.clear();
	ifstream in(file, ios::binary);
	while (in.is_open()) {
		char type = in.peek();
		switch (type) {
			case 't' : {
				bool data;
				unserialize(in, data);
				ostringstream oss;
				serialize(data, oss);
				vs.push_back(oss.str());
				break;
			} case 'f' : {
				bool data;
				unserialize(in, data);
				ostringstream oss;
				serialize(data, oss);
				vs.push_back(oss.str());
				break;
			} case 's' : {
				short data;
				unserialize(in, data);
				ostringstream oss;
				serialize(data, oss);
				vs.push_back(oss.str());
				break;
			} case 'i' : {
				int data;
				unserialize(in, data);
				ostringstream oss;
				serialize(data, oss);
				vs.push_back(oss.str());
				break;
			} case 'l' : {
				long data;
				unserialize(in, data);
				ostringstream oss;
				serialize(data, oss);
				vs.push_back(oss.str());
				break;
			} case 'c' : {
				char data;
				unserialize(in, data);
				ostringstream oss;
				serialize(data, oss);
				vs.push_back(oss.str());
				break;
			} case 'S' : {
				string data;
				unserialize(in, data);
				ostringstream oss;
				serialize(data, oss);
				vs.push_back(oss.str());
				break;
			} case char_traits<char>::eof() : {
				in.close();
				break;
			}
			default :
				f = true;
		}
	}
	e = false;
	f = false;
}
IFSerial::~IFSerial() {
	vs.clear();
}
bool IFSerial::eof() const {
	return e;
}
bool IFSerial::fail() const {
	return f;
}
IFSerial::operator bool() const {
	return !fail();
}

IFSerial &IFSerial::operator>>(bool &datum) {
	this->get(datum);
	return *this;
}
IFSerial &IFSerial::operator>>(short &datum) {
	this->get(datum);
	return *this;
}
IFSerial &IFSerial::operator>>(int &datum) {
	this->get(datum);
	return *this;
}
IFSerial &IFSerial::operator>>(long &datum) {
	this->get(datum);
	return *this;
}
IFSerial &IFSerial::operator>>(char &datum) {
	this->get(datum);
	return *this;
}
IFSerial &IFSerial::operator>>(std::string &datum) {
	this->get(datum);
	return *this;
}

void IFSerial::get(bool &datum) {
	if (size() < 1) {
		e = f = true;
	} else {
		unsigned int length = vs[0].size();
		if (length > 0) {
			if (vs[0].at(0) == 't') {
				vs.erase(vs.begin());
				datum = true;
			} else if (vs[0].at(0) == 'f') {
				vs.erase(vs.begin());
				datum = false;
			} else {
				f = true;
			}
		} else {
			f = true;
		}
	}
}
void IFSerial::get(short &datum) {
	//datum = 0;
	if (size() < 1) {
		e = f = true;
	} else {
		unsigned int length = vs[0].size();
		if (length > 1) {
			if (vs[0].at(0) == 's') {
				istringstream iss(vs[0]);
				unserialize(iss, datum);
				vs.erase(vs.begin());
			} else {
				f = true;
			}
		} else {
			f = true;
		}
	}
	
}
void IFSerial::get(int &datum) {
	//datum = 0;
	if (size() < 1) {
		e = f = true;
	} else {
		unsigned int length = vs[0].size();
		if (length > 1) {
			if (vs[0].at(0) == 'i') {
				istringstream iss(vs[0]);
				unserialize(iss, datum);
				vs.erase(vs.begin());
			} else {
				f = true;
			}
		} else {
			f = true;
		}
	}
}
void IFSerial::get(long &datum) {
	//datum = 0;
	if (size() < 1) {
		e = f = true;
	} else {
		unsigned int length = vs[0].size();
		if (length > 1) {
			if (vs[0].at(0) == 'l') {
				istringstream iss(vs[0]);
				unserialize(iss, datum);
				vs.erase(vs.begin());
			} else {
				f = true;
			}
		} else {
			f = true;
		}
	}
}
void IFSerial::get(char &datum) {
	if (size() < 1) {
		e = f = true;
	} else {
		unsigned int length = vs[0].length();
		if (length > 1) {
			if (vs[0].at(0) == 'c') {
				istringstream iss(vs[0]);
				unserialize(iss, datum);
				vs.erase(vs.begin());
			} else {
				f = true;
			}
		} else {
			f = true;
		}
	}
}
void IFSerial::get(std::string &datum) {
	if (size() < 1) {
		e = f = true;
	} else {
		unsigned int length = vs[0].size();
		if (length > 2) {
			if (vs[0].at(0) == 'S') {
				istringstream iss(vs[0]);
				unserialize(iss, datum);
				vs.erase(vs.begin());
			} else {
				f = true;
			}
		} else {
			f = true;
		}
	}
}
int IFSerial::size() const {
	return vs.size();
}

//class OFSerial
OFSerial::OFSerial(const std::string file) {
	out.open(file, ios::binary);
	if (out.good()) {
		f = false;
	} else {
		f = true;
	}
}
OFSerial::~OFSerial() {
	out.close();
}
bool OFSerial::fail() const {
	return f;
}
OFSerial::operator bool() const {
	return !fail();
}

OFSerial &OFSerial::operator<<(const bool &datum) {
	this->put(datum);
	return *this;
}
OFSerial &OFSerial::operator<<(const short &datum) {
	this->put(datum);
	return *this;
}
OFSerial &OFSerial::operator<<(const int &datum) {
	this->put(datum);
	return *this;
}
OFSerial &OFSerial::operator<<(const long &datum) {
	this->put(datum);
	return *this;
}
OFSerial &OFSerial::operator<<(const char &datum) {
	this->put(datum);
	return *this;
}
OFSerial &OFSerial::operator<<(const std::string &datum) {
	this->put(datum);
	return *this;
}

void OFSerial::put(const bool datum) {
	serialize(datum, out);
}
void OFSerial::put(const short datum) {
	serialize(datum, out);
}
void OFSerial::put(const int datum) {
	serialize(datum, out);
}
void OFSerial::put(const long datum) {
	serialize(datum, out);
}
void OFSerial::put(const char datum) {
	serialize(datum, out);
}
void OFSerial::put(const std::string datum) {
	serialize(datum, out);
}

