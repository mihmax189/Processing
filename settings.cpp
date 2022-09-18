#include "settings.h"

Settings::Settings() : file("./settings.md") {
	stream.open(file, std::ios::in);

	if (!stream.is_open()) {
		cerr << "file \'" << file << "\' don't found!" << endl;
		return;
	}

	read();
}

Settings::~Settings() {
	if (stream.is_open())
		stream.close();
}

bool Settings::isOpen() {
	return stream.is_open();
}

void Settings::read() {
	string line;
	string name;
	string value;

	do {
		std::getline(stream, line);
		if (line[0] == '#' || line.empty())
			continue;

		line = deleteWhitespaces(line);
		std::istringstream ss(line);
		std::getline(ss, name, ':');
		std::getline(ss, value, ':');

		name = deleteWhitespaces(name);
		value = deleteWhitespaces(value);

		if (!name.compare("in_type"))
			inType = value;
		else if (!name.compare("out_type"))
			outType = value;
		else			
			process = (Processing)(std::stoi(value));
		
	} while (!stream.eof());
}

string Settings::deleteWhitespaces(const string & line) {
	const char whitespaces[] {" \t\n"};

	const size_t first (line.find_first_not_of(whitespaces));
	const size_t last (line.find_last_not_of(whitespaces));

	return line.substr(first, (last - first) + 1);
}

bool Settings::getSettings(Settings::Parameters & params) {
	bool inTypeIsGood = true, outTypeIsGood = true, processIsGood = true;

 	if (!inType.compare("int"))
 		params.inType = Types::INT;
 	else if (!inType.compare("float"))
 		params.inType = Types::FLOAT;
 	else
 		inTypeIsGood= false;

 	if (!outType.compare("int"))
 		params.outType = Types::INT;
 	else if (!outType.compare("float"))
 		params.outType = Types::FLOAT;
 	else
 		outTypeIsGood = false;
	
 	switch (process) {
 		case Processing::MULTIPLICATION:
 			params.process = MULTIPLICATION;
 			break;
 		case Processing::LOG:
 			params.process = LOG;
 			break;
 		case Processing::POW:
 			params.process = POW;
 			break;
 		case Processing::AVERAGE:
 			params.process = AVERAGE;
 			break;
 		default:
 			processIsGood = false;
 	}
	
 	return (inTypeIsGood && outTypeIsGood && processIsGood) ? true : false;
 }