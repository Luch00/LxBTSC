/*!

	Abstract:
		this file is a part of bbcode library

	Author:
		Igor Franchuk (sprog@online.ru)

	Last Update:
		$Id: bbcode_parser.h,v 1.1 2007/12/19 19:13:30 lanthruster Exp $
		Version: 0.01
*/

#ifndef BBCODE_parseR_H
#define BBCODE_parseR_H
#pragma once

#include <string>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <stack>
#include <vector>
#include <map>

#include "bbcode_config.h"
#include "bbcode_lexer.h"
#include "bbcode_utils.h"

#pragma warning(disable: 4290) //VS doesn't support exception specifications

namespace{

	using std::string;
	using std::istream;
	using std::cin;
	using std::out_of_range;
	using std::runtime_error;
	using std::stack;
	using std::vector;
	using std::map;
	using std::make_pair;
}

namespace bbcode{

//--------------------------------
// tag struct
	struct tag{
		enum tag_type{opening, closing};
		typedef map<string, string> attribs;		

		string name;		
		tag_type type;
		size_t left_bracket_pos;
		size_t right_bracket_pos;
		attribs attr;
		bool has_closing_tag;

		void clear(void){name = "", type = opening, left_bracket_pos = right_bracket_pos = 0; attr.clear();has_closing_tag = true;}
		template<class T>
			bool operator ==(T _t){if(name == _t.name && type == _t.type && left_bracket_pos == _t.left_bracket_pos && 
									  right_bracket_pos == _t.right_bracket_pos && attr == _t.attr && has_closing_tag == _t.has_closing_tag) return true;
								   return false;
								  }

		tag(void):
			name(""),
			type(opening),
			left_bracket_pos(0),
			right_bracket_pos(0),
			has_closing_tag(true)
			{}
	};
//--------------------------------
// this is multipart form data parser class

	class parser{

		typedef vector<tag> tags;
		typedef map<string, string> supported_tag_storage;

		parser_config _pconf; /* we keep all our configuration in this structure */
		lexer  _lexer;		  /* lexer, the source of lexems */
		conds  _current_state;/* parser's current state, defined by cond table */
		stack<lexeme> _lexems;
		string _parsed_data; /* used to keep immediate parsed data */	
		lexeme l;
		string _im_data;

		supported_tag_storage _supported_tag_storage; //preloaded tags that we support in BBcode library
		
		tags  _parsed_tags;
		tag   _tmp_tag;

		void _bbcode_replacements(void);	//here we're replacing bbcode tags
		string _tag_replacement(tag& t);	//replace bb tag with HTML tag
		tags _discarded_tags;//an internal unclosed|overlapped|sentencedtodleletion tag storage, required for U|O recovery
		void _discarded_tags_cleanup(void);

		string _js_guard(string str); //this is a simple javascript: insert protection

	public:		
		enum flag{store_data_in_memory=0, store_data_in_file=1};

		//tag schem loader

		void load_supported_tag_schema(const string& schema);

		string current_tag_schema(void) const;

 		/* class configuration block */

		size_t setf(size_t mode){	size_t old_conf = _pconf._config; _pconf._config |= mode; return old_conf;	}

		void   source_stream(istream& source_stream){	_pconf._source_stream = &source_stream;	}
		istream*  source_stream(void) const{	return _pconf._source_stream; }

		size_t read_buffer_size(size_t buffer_size)			 throw(out_of_range);

		size_t read_buffer_size( void )	  const	   {	return _pconf._read_buffer_size;	}

		parser_config pconf(parser_config& pconf){ parser_config tconf = _pconf; _pconf = pconf; return tconf;}
		parser_config pconf(void) const { return _pconf;}	
		

		/* end of class configuration block */

		/* class functinality */
		
		void parse(void);
		/* return alternative multipart form content */
		string content(void) const {	return _parsed_data;	}

		/* class configuration block */

		/* constructors */

		parser(void) : _pconf(cin, _DEFAULT_BUFFER_SIZE),
					   _current_state(C1),
					   l(TERM),
					   _im_data(""),
					   _parsed_data("")
						{load_supported_tag_schema(_SUPPORTED_BBTAGS);}

		parser(const string& schema) : _pconf(cin, _DEFAULT_BUFFER_SIZE),
					   _current_state(C1),
					   l(TERM),
					   _im_data(""),
					   _parsed_data("")
						{load_supported_tag_schema(schema);}
		/* end of constructors */

		virtual ~parser(){};
	};

}

#endif
