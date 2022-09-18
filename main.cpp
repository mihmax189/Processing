#include <iostream>

#include "settings.h"

int main(int argc, char const *argv[])
{
	Settings settings;	
	Settings::Parameters params;

	if (!settings.getSettings(params)) {
		cerr << "Bad settings!" << endl;
		return -1;
	}
	
	return 0;
}