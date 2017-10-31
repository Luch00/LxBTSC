#include "bbcode_utils.h"
//#include <iterator>

namespace bbcode{

	//--------------------------------
	// upper case block
	string upper_case(string s){		
		transform(s.begin(), s.end(), s.begin(), capitalize);
		return s;
	}
	unsigned char capitalize(unsigned char c){		
		return toupper(c);
	}
	//--------------------------------
	// form_parcer, helper functions

	string get_module_msg(const string& str){
			return _THIS_MODULE_STR_IDENT + " " + str;
	}

	//--------------------------------
	// form_parcer, helper functions
	string random_string(size_t length){
		string res;
		string dictionary = _RND_GENERATOR_DICTIONARY;
		if(dictionary.empty()) throw runtime_error(get_module_msg("Empty _RND_GENERATOR_DICTIONARY"));
		for(size_t i = 0; i < length; i++){
			random_shuffle(dictionary.begin(), dictionary.end());
			//res.push_back(dictionary[0]);
			res.append(1, dictionary[0]);
		}
		return res;
	}

	// ------------------------------------------------------------------------------------------------------------------
	//! Templates specializations
	// ------------------------------------------------------------------------------------------------------------------

	// ------------------------------------------------------------------------------------------------------------------
	//! string to string spec (two arg)
	template<> string stream_cast(const string &value, cast_manip manip)
	{
		return value;
	}

	// ------------------------------------------------------------------------------------------------------------------
	//! char* to string spec (two arg)
	template<> string stream_cast(const char* value, cast_manip manip)
	{
		return string(value);
	}

	// ------------------------------------------------------------------------------------------------------------------
	//! char* to string spec (one arg)
	template<> string stream_cast(const string &value)
	{
		return value;
	}

	// ------------------------------------------------------------------------------------------------------------------
	//! char* to string spec (one arg)
	template<> string stream_cast(const char* value)
	{
		return string(value);
	}

	// ------------------------------------------------------------------------------------------------------------------
	//! Split string
	strings split_string(const string &str, const string &delimiter, const bool include_empty)
	{
		strings result;
		string sub = "";
		std::size_t dpos = 0, lastdpos = 0, dsize = delimiter.size();
		do {
			dpos = str.find(delimiter, lastdpos);
			sub = str.substr(lastdpos, dpos - lastdpos);
			if (!sub.empty() || include_empty) result.push_back(sub);
			lastdpos = dpos + dsize;
		} while (dpos != string::npos);
		return result;
	}

	// ------------------------------------------------------------------------------------------------------------------
	//! Splits string so that length of any substring is no more than max_sub_length
	strings split_string(const string &str, const string &delimiter, bool include_empty, size_t max_sub_length)
	{
		strings result = split_string(str, delimiter, include_empty);
		if (max_sub_length > 0) {
			strings new_res;
			for (strings::iterator it = result.begin(); it != result.end(); it++) {
				size_t len = it->length();
				if (len > max_sub_length) {
					size_t count = len / max_sub_length + 1;
					strings subsplit;
					for (size_t i = 0; i < count; i++) {
						subsplit.push_back(it->substr(i * max_sub_length, max_sub_length));
					}
					new_res.insert(new_res.end(), subsplit.begin(), subsplit.end());
				}
				else {
					new_res.push_back(*it);
				}
			}
			return new_res;
		}
		return result;
	}
	//----------------------------------------------------------
	//! functor for find_if algorithm
	//! trim_left, trim_right
	class trim_findfunct {
		const string _char_list;
	public:
		trim_findfunct(const string char_list):_char_list(char_list)  { }
		bool operator () ( const char ch) const {
			return string::npos == _char_list.find(ch);
		}
	};
	//----------------------------------------------------------
	//! erase head spaces
	string trim_left( const string &str, const string &char_list ) {
		string ret = "";
		string::const_iterator it = find_if(str.begin(), str.end(), trim_findfunct(char_list) );
		copy( it, str.end(), back_inserter(ret) );
		return ret;
	}

	//----------------------------------------------------------
	//! erase trail spaces
	string trim_right( const string &str, const string &char_list ) {
		string ret = "";
		string::const_reverse_iterator it = find_if(str.rbegin(), str.rend(), trim_findfunct(char_list) );
		copy(str.begin(), str.begin() + (str.rend() - it) , back_inserter(ret));
		return ret;
	}

	//----------------------------------------------------------
	//! erase head and trail spaces
	string trim( const string &str, const string &char_list ) {
		return trim_left(trim_right(str,char_list),char_list);
	}	

}
