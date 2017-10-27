/*!
	Abstract:
		this file is a part of bbcode library

	Author:
		Igor Franchuk (sprog@online.ru)

	Last Update:
		$Id: bbcode_lexer.h,v 1.1 2007/12/19 19:13:30 lanthruster Exp $
		Version: 0.01
*/

#ifndef BBCODE_LEXER_H
#define BBCODE_LEXER_H
#pragma once

#include <string>
#include <iostream>
#include <istream>
#include <stdexcept>

#include "bbcode_config.h"
#include "bbcode_utils.h"

#pragma warning(disable: 4290) //VS doesn't support exception specifications

namespace{

	using std::string;
	using std::istream;
	using std::cin;
	using std::out_of_range;
	using std::length_error;
	using std::streamsize;
	
}

namespace bbcode{

	//symbols
	// T is TERMINATOR, NT = NOT TERMINATOR
	// CHAR = anyting but (COLON, SEMICOLON, QUOTE, ENTER, CR_RETURN, SPACE, EQUALITY)
//	enum  symbols{CHAR, COLON = ':', SEMICOLON = ';',  QUOTE = '"', ENTER = '\r', SPACEBAR = ' ', CR_RETURN = '\n'};

	//EM states
	enum  conds{C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19, 
				C20, C21, C22, C23, C24, C25, C26, C27, C28, C29, C30, 
				C31, C32, C33, C34, C35, C36, C37, C38, C39, C40, C41, 
				C42, C43, C44, C45, C46, C47, C48, C49, C50, C51, C52, 
				C53, C54, C55, C56, C57, C58, C59, C60, C61, C62, C63, 
				C64, C65, C66, C67, C68, C69, C70, C71, C72, C73, C74, 
				C75, C76, C77, C78, C79, C80, C81, C82, C83, C84, C85, 
				C86, C87, C88, C89, C90, C91, C92, C93, C94, C95, C96, 
				C97, C98, C99,C100,C101,C102,C103,C104,C105,C106,C107,
			   C108,C109,C110,C111,C112,C113,C114,C115,C116,C117,C118,
			   C119,C120,C121,C122,C123,C124,C125,C126,C127,C129,C130,
				END, T=1, NT=0, PB=2, YES=1, NO=0};


	class lexer{
	public:
			enum flag{ON=1, OFF=0};
	private:		
		parser_config _pconf;		
		char* _buffer;
		size_t _tot_characters_read;
		conds  _current_state;
		string _strbuf;
		string _strbuf_copy;
		
		string _upper_str;

		size_t _i;
		size_t _read_chars_num;
				
	public:	

		

		/* class initializer */
		void init(const parser_config& pconf);
		
		lexeme get_lexeme(void);
		string get_lexeme_str(void);		
	
		/* constructor section */
		lexer() : 
						_tot_characters_read(0),
						_buffer(NULL)						
						{}
		
		~lexer() { if(_buffer != NULL){ delete[] _buffer; _buffer = NULL;	} }

	};


}

#endif 
