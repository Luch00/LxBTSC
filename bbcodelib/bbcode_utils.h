/*!
	Abstract:
		this file is a part of bbcode library

	Author:
		Igor Franchuk (sprog@online.ru)

	Last Update:
		$Id: bbcode_utils.h,v 1.1 2007/12/19 19:13:30 lanthruster Exp $
		Version: 0.01
*/

#ifndef BBCODE_UTILS_H
#define BBCODE_UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <time.h>
#include <stdexcept>
#include "bbcode_config.h"

namespace{
	using std::string;
	using std::istream;
	using std::transform;
	using std::uppercase;
	using std::cin;
	using std::cout;
	using std::stringstream;
	using std::random_shuffle;
	using std::runtime_error;	
	using std::vector;
	using std::find_if;
}

namespace bbcode{	
	typedef vector<string> strings;
//--------------------------------
// helper functions
	unsigned char capitalize(unsigned char c);
	string upper_case(string s); /* only for Latin-1, locale is not used */
	string random_string(size_t length); /* returns random string sequence */

//--------------------------------
// helper templates

		template<class T, class C>
		T myswap(T& p1, C& p2){
			T old = p1;
			p1 = p2;
			return old;
		};

	//! Type T to Q std stream conversion
	enum cast_manip { cm_none, cm_dec, cm_hex, cm_oct, cm_boolalpha };

	//! Cast implementation
	template<class T, class Q>
		inline T stream_cast_impl(const Q &value, cast_manip manip)
	{
		std::stringstream buf;
		T res;
		switch (manip)
		{
		case cm_dec: buf << std::dec; break;
		case cm_hex: buf << std::hex; break;
		case cm_oct: buf << std::oct; break;
		case cm_boolalpha: buf << std::boolalpha; break;
		}
		buf << value;
		buf >> res;
		return res;
	}

	//! For cast with two arguments
	template<class T, class Q>
		T stream_cast(const Q &value, cast_manip manip)
	{
		return stream_cast_impl<T>(value, manip);
	}

	//! char* spec (two arg)
	template<class T> T stream_cast(const char* value, cast_manip manip)
	{
		return stream_cast_impl<T>(string(value), manip);
	}
	//! For one argument casting
	template<class T, class Q> T stream_cast(const Q &value)
	{
		return stream_cast_impl<T>(value, cm_none);
	}
	//! char* spec (one arg)
	template<class T> T stream_cast(const char* value)
	{
		return stream_cast_impl<T>(string(value));
	}

	//! size_t hack for WIN32
#ifdef WIN32
	//! size_t spec (one arg)
	template<class T> T stream_cast(const size_t value)
	{
		return stream_cast_impl<T>(static_cast<unsigned int>(value), cm_none);
	}
	//! size_t spec (one arg)
	template<class T> T stream_cast(const size_t value, cast_manip manip)
	{
		return stream_cast_impl<T>(static_cast<unsigned int>(value), manip);
	}
#endif

	//! string to string spec (two arg)
	template<> string stream_cast(const string &value, cast_manip manip);
	//! string to string spec (one arg)
	template<> string stream_cast(const string &value);
	//! char* to string spec (two arg)
	template<> string stream_cast(const char* value, cast_manip manip);
	//! char* to string spec (one arg)
	template<> string stream_cast(const char* value);

//--------------------------------
// helper functions

	string get_module_msg(const string& str);

	//! Splits string
	strings split_string(const string &str, const string &delimiter, const bool include_empty = true);
	//! Splits string so that length of any substring is no more than max_sub_length
	strings split_string(const string &str, const string &delimiter, bool include_empty, size_t max_sub_length);
	//! erase head spaces
	string trim_left( const string &str, const string &char_list=" \t\n\r\0\x0B");
	//! erase trail spaces
	string trim_right( const string &str, const string &char_list=" \t\n\r\0\x0B" );
	//! erase head and trail spaces
	string trim( const string &str, const string &char_list=" \t\n\r\0\x0B" );


}
#endif 
