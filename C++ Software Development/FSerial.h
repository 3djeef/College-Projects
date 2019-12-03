#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class IFSerial {
  public:
  
	IFSerial(const std::string);
	~IFSerial();
	bool eof() const;
	bool fail() const;
	operator bool() const;

	IFSerial &operator>>(bool &);
	IFSerial &operator>>(short &);
	IFSerial &operator>>(int &);
	IFSerial &operator>>(long &);
	IFSerial &operator>>(char &);
	IFSerial &operator>>(std::string &);
  private:

	std::vector<std::string> vs;
	bool e;
	bool f;
	void get(bool &);
	void get(short &);
	void get(int &);
	void get(long &);
	void get(char &);
	void get(std::string &);
	int size() const;
};

class OFSerial {
  public:
	OFSerial(const std::string);
	~OFSerial();
	bool fail() const;
	operator bool() const;

	OFSerial &operator<<(const bool &);
	OFSerial &operator<<(const short &);
	OFSerial &operator<<(const int &);
	OFSerial &operator<<(const long &);
	OFSerial &operator<<(const char &);
	OFSerial &operator<<(const std::string &);
  private:

	std::ofstream out;
	bool f;
	std::string filename() const;
	void put(const bool);
	void put(const short);
	void put(const int);
	void put(const long);
	void put(const char);
	void put(const std::string);
};

#endif