#ifndef _PROCESSING_H_
#define _PROCESSING_H_

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "settings.h"

using std::vector;
using std::string;

class Processing {
public:
	virtual bool readData(const string & file) = 0;
	virtual bool writeData(const string & file) = 0;

	virtual bool multiplication(double) = 0;
	virtual bool log10() = 0;
	virtual bool pow(int) = 0;
	virtual bool average() = 0;
};

template <class inType, class outType>
class ProcessingWork : public Processing {
public:
	ProcessingWork() {}
	ProcessingWork(const ProcessingWork &) = delete;
	ProcessingWork & operator=(const ProcessingWork &) = delete;
	
	bool readData(const string & file);
	bool writeData(const string & file);

	bool multiplication(double);
	bool log10();
	bool pow(int);
	bool average();

private:
	vector<inType> inData;
	vector<outType> outData;

	std::fstream instream;
	std::fstream outstream;

	outType multiplication(inType a, double b);
	outType log10(inType);
	outType pow(inType, int);
};

template <class inType, class outType>
bool ProcessingWork<inType, outType>::readData(const string & file) {
	instream.open(file, std::ios::in);

	if (!instream.is_open()) {
		cerr << "file \'" << file << "\' don't found!" << endl;
		return false;
	}

	inType data;	
	while (instream >> data) {
		inData.push_back(data);
	}

	return true;
}

template <class inType, class outType>
bool ProcessingWork<inType, outType>::writeData(const string & file) {
	outstream.open(file, std::ios::out);

	if (!outstream.is_open()) {
		cerr << "file \'" << file << "\' don't found!" << endl;
		return false;
	}
	
	for (auto it = outData.begin(); it != outData.end(); it++)
		outstream << *it << std::endl;

	return true;
}

template <class inType, class outType>
bool ProcessingWork<inType, outType>::multiplication(double b) {
	for (auto it = inData.begin(); it != inData.end(); it++)
		outData.push_back(multiplication(*it, b));

	return true;
}

template <class inType, class outType>
outType ProcessingWork<inType, outType>::multiplication(inType a, double b) {
	return (outType)(a * b);
}

template <class inType, class outType>
bool ProcessingWork<inType, outType>::log10() {
	for (auto it = inData.begin(); it != inData.end(); it++)
		outData.push_back(log10(*it));

	return true;
}

template <class inType, class outType>
outType ProcessingWork<inType, outType>::log10(inType a) {
	return (outType)std::log10(a);
}

template <class inType, class outType>
bool ProcessingWork<inType, outType>::pow(int b) {
	for (auto it = inData.begin(); it != inData.end(); it++)
		outData.push_back(pow(*it, b));

	return true;
}

template <class inType, class outType>
outType ProcessingWork<inType, outType>::pow(inType a, int b) {
	return (outType)std::pow(a, b);
}

template <class inType, class outType>
bool ProcessingWork<inType, outType>::average() {
	int count = 0;
	inType val = 0;

	for (auto it = inData.begin(); it != inData.end(); it++) {
		val += *it;
		count++;
		
		if (count == 10 || (it + 1) == inData.end()) {
			outData.push_back((outType)(val / count));
			val = 0, count = 0;
		}
	}

	return true;
}

#endif
