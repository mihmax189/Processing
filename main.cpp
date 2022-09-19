#include <iostream>
#include <string>

#include "settings.h"
#include "processing.h"

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		std::cerr << "Invalid arguents! use: ./process infile outfile" << std::endl;
		return 0;
	}

	std::string inFile(argv[1]);
	std::string outFile(argv[2]);

	Settings settings;	
	Settings::Parameters params;

	if (!settings.getSettings(params)) {
		cerr << "Bad settings!" << endl;
		return -1;
	}

	Processing *process;
	if (params.inType == Settings::Types::INT && params.outType == Settings::Types::INT)
		process = new ProcessingWork<int, int>();
	if (params.inType == Settings::Types::INT && params.outType == Settings::Types::FLOAT)
		process = new ProcessingWork<int, float>();
	if (params.inType == Settings::Types::FLOAT && params.outType == Settings::Types::INT)
		process = new ProcessingWork<float, int>();
	if (params.inType == Settings::Types::FLOAT && params.outType == Settings::Types::FLOAT)
		process = new ProcessingWork<float, float>();

	if (!process->readData(inFile))
		return -2;

	bool res;
	switch(params.process) {
		case Settings::Processing::MULTIPLICATION:			
			res = process->multiplication(3.14);
			if (!res) return -3;
			break;

		case Settings::Processing::LOG:			
			res = process->log10();
			if (!res) return -4;
			break;

		case Settings::Processing::POW:
			res = process->pow(2);
			if (!res) return -5;
			break;

		case Settings::Processing::AVERAGE:
			res = process->average();
			if (!res) return -6;
			break;

		default:
			;
	}

	process->writeData(outFile);
	
	return 0;
}