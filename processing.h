#ifndef _PROCESSING_H_
#define _PROCESSING_H_

#include <any>
#include "settings.h"

using std::any;

class Processing {
public:
	Processing(const Settings::Parameters &);
	Processing(const Processing &) = delete;
	Processing & operator=(const Processing &) = delete;

	template <typename inType, typename outType>
	outType multiplication(inType a, double b);

private:
	const Settings::Parameters params;
};

#endif
