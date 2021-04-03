/**
 * ______________________________________________________
 * This file is part of ko-tbl-shell project.
 * 
 * @author       Mustafa Kemal Gılor <mustafagilor@gmail.com> (2016)
 * .
 * SPDX-License-Identifier:	MIT
 * ______________________________________________________
 */

#pragma once

#include <string>
#include <cctype>
#include <boost\functional\hash.hpp>

namespace strop
{
	struct ci_char_traits : public std::char_traits<char> {
		static char to_upper(char ch) {
			return std::toupper((unsigned char) ch);
		}
		static bool eq(char c1, char c2) {
			return to_upper(c1) == to_upper(c2);
		}
		static bool lt(char c1, char c2) {
			return to_upper(c1) < to_upper(c2);
		}
		static int compare(const char* s1, const char* s2, size_t n) {
			while (n-- != 0) {
				if (to_upper(*s1) < to_upper(*s2)) return -1;
				if (to_upper(*s1) > to_upper(*s2)) return 1;
				++s1; ++s2;
			}
			return 0;
		}
		static const char* find(const char* s, int n, char a) {
			auto const ua(to_upper(a));
			while (n-- != 0) {
				if (to_upper(*s) == ua)
					return s;
				s++;
			}
			return nullptr;
		}
	};
	using ci_string = std::basic_string<char, ci_char_traits>;



	std::size_t hash_value(ci_string const& b);

}



