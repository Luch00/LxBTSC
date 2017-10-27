#include "bbcode_lexer.h"

namespace bbcode{
  //                                0	  1		  2		   3	  4		     5		6	 7		8	  9     10        11    12   13   14
  //					           CHAR  ENTER   CR_RET   COL    SEMICOL	QUOTE	SP  EQAL       PUBACK   EQUALITY  [     ]     /   *
  enum conds Lexer[][17]={/*C1*/   {C2,	  C4,    C1,  	  C6,	  C7,		C8,	   C10,  C1,	NT, NO,		C12,	  C13, C14, C15,  C16	 },  //-
						  /*C2*/   {C2,	  C3,    C3,	  C3,	  C3,	    C3,		C3,  C1,	NT, NO,		C3,		  C3,   C3,	 C3,  C3	 },  //---263422640625425\r
						  /*C3*/   {C1,	  C1,    C1,	  C1,	  C1,		C1,		C1,  C1,	T,  YES,	C1,		  C1,   C1,	 C1,  C1	 },  //we found WORD, pushback
						  /*C4*/   {C2,	  C1,    C1,	  C6,	  C7,		C8,		C1,  C1,	NT, NO,		C12,	  C1,   C1,	 C1,  C1	 },  //\r\n
						  /*C5*/   {C1,	  C1,    C1,	  C1,	  C1,		C1,		C1,  C1,	T,  NO,		C1,		  C1,   C1,	 C1,  C1	 },  //EMPTY
						  /*C6*/   {C1,	  C1,    C1,	  C1,	  C1,		C1,		C1,  C1,	T,  NO,		C1,		  C1,   C1,	 C1,  C1	 },  //we found COLON
						  /*C7*/   {C1,	  C1,    C1,	  C1,	  C1,		C1,		C1,  C1,	T,  NO,		C1,		  C1,   C1,	 C1,  C1	 },  //we found SEMICOLON
						  /*C8*/   {C1,	  C1,    C1,	  C1,	  C1,		C1,		C1,  C1,	T,  NO,		C1,		  C1,   C1,  C1,  C1	 },  //we found QUOTE						  
						  /*C9*/   {C1,	  C1,    C1,	  C1,	  C1,		C1,		C1,  C1,	T,  NO,		C1,		  C1,   C1,  C1,  C1	 },  //NOT USED
						  /*C10*/  {C11, C11,   C11,	 C11,	 C11,	   C11,	   C10,  C11,	NT, NO,		C11,	  C11,  C11, C11, C1	 },  //we're missing spaces
						  /*C11*/  {C1,   C1,    C1,	  C1,	  C1,	    C1,	    C1,  C1,	T,  YES,	C1,		  C1,   C1,	 C1,  C11    },  //we found SPACE
						  /*C12*/  {C1,   C1,    C1,	  C1,	  C1,	    C1,	    C1,  C1,	T,  NO,		C1,		  C1,   C1,	 C1,  C1	 },  //we found SPACE
						  /*C13*/  {C1,   C1,    C1,	  C1,	  C1,	    C1,	    C1,  C1,	T,  NO,		C1,		  C1,   C1,	 C1,  C1	 },  //we found LEFT_SQUARE_BRACKET
						  /*C14*/  {C1,   C1,    C1,	  C1,	  C1,	    C1,	    C1,  C1,	T,  NO,		C1,		  C1,   C1,	 C1,  C1	 },  //we found RIGHT_SQUARE_BRACKET
						  /*C15*/  {C1,   C1,    C1,	  C1,	  C1,	    C1,	    C1,  C1,	T,  NO,		C1,		  C1,   C1,	 C1,  C1	 },  //we found SLASH
						  /*C16*/  {C1,   C1,    C1,	  C1,	  C1,	    C1,	    C1,  C1,	T,  NO,		C1,		  C1,   C1,	 C1,  C1	 }   //we found MULTIPLIER
					 	  };
//--------------------------------
// lexer::get_lexeme_str, return current lexeme
  string lexer::get_lexeme_str(void){	  
	  return _strbuf_copy;	
  }
//--------------------------------
// lexer::init, perform initialization
	void lexer::init(const parser_config& pconf){
		_pconf=pconf;
		//makº sure the buffer is empty
		if(_buffer != NULL){
			delete [] _buffer;
			_buffer = NULL;
		}
	    _buffer = new char[_pconf._read_buffer_size]; /* allocating memory for buffer */
		_tot_characters_read = 0;		
		_read_chars_num  = 0;
		_current_state = C1; /* setting machine to initial state C1 */
		_strbuf.clear();
		_strbuf_copy.clear();
		_upper_str.clear();
		/* we need this to make sure the trigger won't work in case _DEFAULT_MAX_MULTIPART_FORM_INTERNAL_PARAM_LEN < _pconf._read_buffer_size*/		
		_i = 0;
}

//--------------------------------
// lexer::get_lexeme 

	lexeme lexer::get_lexeme(void){

	do{ /* we will roatate here till CIN isn't over */

		if(_i == _read_chars_num){
			_pconf._source_stream->read(_buffer, static_cast<streamsize>(_pconf._read_buffer_size));
			_read_chars_num = static_cast<size_t>(_pconf._source_stream->gcount());
			if(!_read_chars_num){		

				if(_current_state == C2){ 
					_strbuf_copy = _strbuf;						
					_strbuf.clear();
					_current_state = C1;
					_i = 0; //in case we have just one word, and there is nothing more, we return word and preparing for the next TERM
					return WORD;
				}

				return TERM;								  /* end of stream reached*/
			}
			//if(_tot_characters_read + _read_chars_num > _pconf._max_content_length) /* we have reached max_content_length limitation */
			//	throw out_of_range(get_module_msg("max content length reached (") + stream_cast<string>(_pconf._max_content_length) + ")");
			_tot_characters_read += _read_chars_num; /* increment read character counter */
			_i = 0;
		}	

		for(;  _i < _read_chars_num; _i++){
						
			//_strbuf.push_back(_buffer[_i]);
			_strbuf.append(1, _buffer[_i]);
			
			switch(_buffer[_i]){
				 
				case COLON :
							 _current_state = Lexer[_current_state][3];
							 break;	
				//case SEMICOLON :
				//			 _current_state = Lexer[_current_state][4];
				//			 break;
				case QUOTE :
							 _current_state = Lexer[_current_state][5];
							 break;
				case ENTER :
							 _current_state = Lexer[_current_state][1];
							 break;
				case CR_RETURN :
							 _current_state = Lexer[_current_state][2];
							 break;
			    case SPACEBAR :
							 _current_state = Lexer[_current_state][6];
							 break;
				case EQUALITY :
							 _current_state = Lexer[_current_state][10];
							 break;
				case  LEFT_SQUARE_BRACKET:
							 _current_state = Lexer[_current_state][11];
							 break;
				case  RIGHT_SQUARE_BRACKET:
							 _current_state = Lexer[_current_state][12];
							 break;
				case  SLASH:
							 _current_state = Lexer[_current_state][13];
							 break;
 				case  MULT:
							 _current_state = Lexer[_current_state][14];
							 break;

				default: 
							 _current_state = Lexer[_current_state][0];
							break;
			}
			bool _was_erased = false;
			/* now, check out if we're in Terminate state */
			if(Lexer[_current_state][8] == T && Lexer[_current_state][9] == YES){
				//pushing back one symbol
				//take you attention that we just not have to decrese _i, (due to implementation)
				if(int(_strbuf.length()-1) >= 0){
					_strbuf.erase(_strbuf.length()-1);
					_was_erased = true;
				}
			}



			if(Lexer[_current_state][8] == T && Lexer[_current_state][9] == NO && _i + 1 <= _read_chars_num){
				_i++;
			}

			switch(_current_state){	
				case C3: /* we found WORD */
						// That it is not the proper place for this hack 
						// but it make parser simplier
						_strbuf_copy = _strbuf;						
						_strbuf.clear();
						_current_state = C1;						
						switch(_strbuf_copy.length()){
							case 1:
									_upper_str = upper_case(_strbuf_copy);
									if(_upper_str == _BOLD)
										return BOLD;
									if(_upper_str == _ITALIC)
										return ITALIC;
									if(_upper_str == _UNDERLINE)
										return UNDERLINE;
									if(_upper_str == _HEADER)
										return HEADER;
									if(_upper_str == _SMALL)
										return SMALL;
									if(_upper_str == _OFFTOPIC)
										return OFFTOPIC;
									if(_upper_str == _Q)
										return QQUOTE;
									if(_upper_str == _MULT)
										return MULT;
								  	 break;
							case 2:
								   _upper_str = upper_case(_strbuf_copy);
									if(_upper_str == _HR)
										return HR;			
								   break;

							case 3:
								   _upper_str = upper_case(_strbuf_copy);
								   if(_upper_str == _SUP)
										return SUP;			
								   if(_upper_str == _SUB)
										return SUB;		
								   if(_upper_str == _RED)
										return RED;		
								   if(_upper_str == _URL)
										return URL;
								   if(_upper_str == _IMG)
										return IMG;
								   if(_upper_str == _PRE)
										return PRE;
								   if(_upper_str == _RED)
										return RED;
								   break;
							case 4:
								   _upper_str = upper_case(_strbuf_copy);								   
								   if(_upper_str == _SIZE)
										return SIZE;			
								   if(_upper_str == _FACE)
										return FACE;		
								   if(_upper_str == _LIST)
										return LIST;		
								   if(_upper_str == _CODE)
										return CODE;
								   if(_upper_str == _QUOTE)
										return QQUOTE;								   								   
								   if(_upper_str == _BLUE)
										return BLUE;
								   break;
							case 5:
									_upper_str = upper_case(_strbuf_copy);
									if(_upper_str == _EMAIL)
										return EMAIL;								   
									if(_upper_str == _QUOTE)
										return QQUOTE;								   
								   if(_upper_str == _COLOR)
										return COLOR;	
								   if(_upper_str == _GREEN)
										return GREEN;	
								   if(_upper_str == _WHITE)
										return WHITE;	
								   if(_upper_str == _BLACK)
										return BLACK;	
								   if(_upper_str == _OLIST)
										return OLIST;		
						    case 6:
									_upper_str = upper_case(_strbuf_copy);
								   if(_upper_str == _ORANGE)													 
										return ORANGE;	
								   if(_upper_str == _PURPLE)													 
										return PURPLE;	
								   if(_upper_str == _YELLOW)													 
										return YELLOW;	
									
						};
						return WORD;
			

				case C6: /* we found COLON */
						_strbuf_copy = _strbuf;						
						_strbuf.clear();						
						_current_state = C1;
						return COLON;	

				case C7: /* we found SEMICOLON */
						_strbuf_copy = _strbuf;						
						_strbuf.clear();						
						_current_state = C1;
						return SEMICOLON;	

				case C8: /* we found QUOTE */
						_strbuf_copy = _strbuf;						
						_strbuf.clear();						
						_current_state = C1;
						return QUOTE;	

				case C11: /* we found SPACE */
						_strbuf_copy = _strbuf;						
						_strbuf.clear();						
						_current_state = C1;
						return SPACE;	
				
				case C12: /* we found EQUALITY */
						_strbuf_copy = _strbuf;						
						_strbuf.clear();						
						_current_state = C1;
						return EQUALITY;	

				case C13: /* we found LEFT_SQUARE_BRACKET */
						_strbuf_copy = _strbuf;						
						_strbuf.clear();						
						_current_state = C1;
						return LEFT_SQUARE_BRACKET;	

				case C14: /* we found RIGHT_SQUARE_BRACKET */
						_strbuf_copy = _strbuf;						
						_strbuf.clear();						
						_current_state = C1;
						return RIGHT_SQUARE_BRACKET;	

				case C15: /* we found SLASH */
						_strbuf_copy = _strbuf;						
						_strbuf.clear();						
						_current_state = C1;
						return SLASH;	

				case C16: /* we found MULT */
						_strbuf_copy = _strbuf;						
						_strbuf.clear();						
						_current_state = C1;
						return MULT;	

				default :
					      break;
			}
			
		}

	  }while(_read_chars_num <= _pconf._read_buffer_size);
		
      return TERM;	
	}

}
