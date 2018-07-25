#include "stdafx.h"
#include "ci_string.hpp"

std::size_t strop::hash_value(ci_string const & b) {
	boost::hash<std::string> hasher;
	return hasher(std::string(b.c_str()));
}
