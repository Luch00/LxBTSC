/*!

	Abstract:
		this file is a part of bbcode library

	Author:
		Igor Franchuk (sprog@online.ru)

	Last Update:
		$Id: bbcode_config.h,v 1.1 2007/12/19 19:13:30 lanthruster Exp $
		Version: 0.01
*/

#ifndef BBCODE_CONFIG_H
#define BBCODE_CONFIG_H
#pragma once

#include <string>
#include <istream>
#include <iostream>

namespace{
	using std::string;
	using std::istream;
	using std::cin;
}

namespace bbcode{

	/* lexems */
	enum  lexeme{SPACE, WORD, OFFTOPIC, UNDERLINE, DELIMITER, TERM,
					  ITALIC, BOLD, HEADER, SMALL, HR, IMG, RED, SUB, SUP, URL, PRE, QQUOTE, CODE, FACE, LIST, SIZE,
					  COLOR, ORANGE, YELLOW, GREEN, BLUE, WHITE, PURPLE, BLACK, EMAIL, OLIST,
					  EQUALITY='=', COLON = ':', SEMICOLON = ';',  QUOTE = '"',
					  ENTER = '\r', SPACEBAR = ' ', CR_RETURN = '\n', LEFT_SQUARE_BRACKET = '[', RIGHT_SQUARE_BRACKET = ']',
					  SLASH = '/', MULT = '*'};


	const string _THIS_MODULE_STR_IDENT							= "bbcode library";
	const string _RND_GENERATOR_DICTIONARY						= "abcdefghijklmnopqrstuvwxyz0123456789";
	const size_t _DEFAULT_BUFFER_SIZE							= 8192;	 		/* we're using default buffer size of 8192 bytes */

	const string _HTML_LT										= "<";
	const string _HTML_GT										= ">";
	const string _HTML_BSLASH									= "/";
	
	const string _BOLD											= "B";
	const string _ITALIC										= "I";
	const string _UNDERLINE										= "U";
	const string _HEADER										= "H";
	const string _SMALL											= "S";
	const string _OFFTOPIC										= "O";
	const string _Q												= "Q";
	const string _MULT											= "*";
	const string _QUOTE											= "QUOTE";
	const string _AQUOTE										= "AQUOTE";
	const string _HR											= "HR";
	const string _IMG											= "IMG";
	const string _RED											= "RED";
	const string _SUB											= "SUB";
	const string _SUP											= "SUP";
	const string _URL											= "URL";
	const string _PRE											= "PRE";
	const string _CODE											= "CODE";
	const string _FACE											= "FACE";
	const string _LIST											= "LIST";
	const string _OLIST											= "OLIST";
	const string _SIZE											= "SIZE";
	const string _COLOR											= "COLOR";
	const string _ORANGE										= "ORANGE";
	const string _YELLOW										= "YELLOW";
	const string _GREEN											= "GREEN";
	const string _BLUE											= "BLUE";
	const string _PURPLE										= "PURPLE";
	const string _WHITE											= "WHITE";
	const string _BLACK											= "BLACK";
	const string _EMAIL											= "EMAIL";

	const string _TITLE											= "TITLE";


	const size_t	DEBUG_MODE_ON										= 1;
	const size_t  DUBUG_MODE_OFF										= 2396744;
			
/*URL  ! <a href=\"$URL\">|\
 /URL  ! </a>|\*/
	const string _SUPPORTED_BBTAGS = 
"B   !   <b>|\
 /B  ! </b>|\
 I   !  <i>|\
 /I  !  </i>|\
 U   !  <u>|\
 /U  ! </u>|\
 H   !  <h>|\
 /H  !  </h>|\
 S   ! <small>|\
 /S  ! </small>|\
 SUB   ! <sub>|\
 /SUB  ! </sub>|\
 SUP   ! <sup>|\
 /SUP  ! </sup>|\
 O  ! <font face=\"Verdana, Arial\" color=\"gray\" size=\"2\">|\
 /O  ! </font>|\
 COLOR  ! <font face=\"Verdana, Arial\" color=\"$COLOR\" size=\"2\">|\
 /COLOR  ! </font>|\
 RED  ! <font face=\"Verdana, Arial\" color=\"red\" size=\"2\">|\
 /RED  ! </font>|\
 ORANGE  ! <font face=\"Verdana, Arial\" color=\"orange\" size=\"2\">|\
 /ORANGE  ! </font>|\
 YELLOW  ! <font face=\"Verdana, Arial\" color=\"yellow\" size=\"2\">|\
 /YELLOW  ! </font>|\
 GREEN  ! <font face=\"Verdana, Arial\" color=\"green\" size=\"2\">|\
 /GREEN  ! </font>|\
 BLUE  ! <font face=\"Verdana, Arial\" color=\"blue\" size=\"2\">|\
 /BLUE  ! </font>|\
 PURPLE  ! <font face=\"Verdana, Arial\" color=\"purple\" size=\"2\">|\
 /PURPLE  ! </font>|\
 WHITE  ! <font face=\"Verdana, Arial\" color=\"white\" size=\"2\">|\
 /WHITE  ! </font>|\
 BLACK  ! <font face=\"Verdana, Arial\" color=\"black\" size=\"2\">|\
 /BLACK  ! </font>|\
 SIZE  ! <font face=\"Verdana, Arial\" color=\"#cc0000\" size=\"$SIZE\">|\
 /SIZE  ! </font>|\
 FACE  ! <font face=\"$FACE\">|\
 /FACE  ! </font>|\
 PRE  ! <pre>|\
 /PRE  ! </pre>|\
  CODE  ! <code>|\
 /CODE  ! </code>|\
  IMG  ! <a href=\"$IMG\" target=\"_blank\" title=\"$TITLE\">|\
 /IMG  ! </a>|\
  LIST  ! <ul>|\
 /LIST  ! </ul>|\
 OLIST  ! <ol>|\
 /OLIST  ! </ol>|\
  *  ! <li>|\
 /*  ! </li>|\
 EMAIL  ! <a href=\"mailto:$EMAIL\" target=\"_blank\">|\
 /EMAIL  ! </a>|\
 HR  ! <hr>|\
 QUOTE  ! <div style=\"margin:20px; margin-top:5px;\"><div style=\"margin-bottom:2px\">Quote:</div><table cellpadding=\"3\" cellspacing=\"0\" border=\"0\" width=\"100%\"><tr><td style=\"border:1px inset\"><div>Originally Posted by <strong>$QUOTE</strong></div><div style=\"font-style:italic\">|\
 /QUOTE  ! </div></td></tr></table></div>|";
	const string _SHEMA_DELIMITER								= "|";
	const string _SHEMA_TAG_DELIMITER							= "!";
	const string _COLON											= ":";

	const string _BBTAG_IS_UNAVAILABLE_RET					    = "";	
	const string _SCHEMA_MACRO_PREFIX							= "$";

	const size_t _MAXIMUM_PROTO_LENGTH							= 6;
		

	/* we store user setup in this structure */

struct parser_config{

	enum flag{store_data_in_memory=0, store_data_in_file=1};

	size_t					 _config;			//we keep our configuratin here			
	istream*				 _source_stream;	//source, from where we're going to read our files	
	size_t					 _read_buffer_size; // buffer we read data into

	parser_config(istream& source_stream, size_t read_buffer_size) :						
						_source_stream(&source_stream),
						_config(0),
						_read_buffer_size(read_buffer_size){}

  
	parser_config(void) :											
						_source_stream(&cin),							
						_config(0),
						_read_buffer_size(_DEFAULT_BUFFER_SIZE){}

};

}

#endif
