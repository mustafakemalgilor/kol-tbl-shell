/**
 * ______________________________________________________
 * This file is part of ko-tbl-shell project.
 * 
 * @author       Mustafa Kemal Gılor <mustafagilor@gmail.com> (2016)
 * .
 * SPDX-License-Identifier:	MIT
 * ______________________________________________________
 */

#include "stdafx.h"
#include "ci_string.hpp"

std::size_t strop::hash_value(ci_string const & b) {
	boost::hash<std::string> hasher;
	return hasher(std::string(b.c_str()));
}
