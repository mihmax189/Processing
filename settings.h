#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::cerr;
using std::endl;

class Settings {
public:
	Settings();
	~Settings();
	Settings &operator=(const Settings &) = delete;
	Settings(const Settings &) = delete;

	bool isOpen();

	enum Processing {
		MULTIPLICATION = 1,
		LOG,
		POW,
		AVERAGE
	};

	enum Types {
		INT, 
		FLOAT
	};

	struct Parameters {
		Processing process;
		Types inType;
		Types outType;
	};

	bool getSettings(Parameters &);

private:
	void read();
	string deleteWhitespaces(const string &);
	
	std::fstream stream;
	const string file;

	string inType;
	string outType;
	Processing process;
};

#endif