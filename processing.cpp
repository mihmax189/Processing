#include "processing.h"

Processing::Processing(const Settings::Parameters & params) : params(params) {}

template <typename inType, typename outType>
outType Processing::multiplication(inType a, double b) {
	return (outType)(a * b);
}