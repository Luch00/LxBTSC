#include "bbcode_parser.h"
//#include <QMessageBox>
//#include <QString>

namespace bbcode{

   //                               0      1	 2	   3	4	   5	 6   7	  8	   9	10     11      12      13       14   15  16  17   18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  
   //								[      ]    BOLD  WORD COLON QUOTE SP  EQAL   /	  ITAL UNDER HEADER  SMALL	  SUB	    TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE CDE  HR IMG EML  LST  MUL LS2
 enum conds Parser[][50]={/*C1*/   {C2,   C1,   C1,	  C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,		NT,  NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // INITIAL STATE
						  /*C2*/  {C25,  C25,  C26,  C25, C25,	  C25,  C25,C25,  C3, C28, C30,	  C32,	  C34,	  C36,	    NT,  NO, C1, NO, C38,C40,C42,C48,C50,C52,C54,C56,C58,C60,C62,C64,C70,C76,C85,C91,C93,C95,C97,C105,C114,C116,C118,C36,C36,C36,C36,C36,C36,C36,},  // opening tags distributor
						  /*C3*/  {C25,  C25,  C26,	 C25, C25,	  C25,  C25,C25, C25, C28, C30,	  C32,	  C34,	  C36,	    NT,  NO, C1, NO, C38,C40,C46,C48,C50,C52,C54,C56,C58,C60,C62,C68,C74,C80,C87,C91,C93,C25,C99,C107,C114,C25,C118,C36,C36,C36,C36,C36,C36,C36,},  // closing tags distributor
						  /*C4*/   {C4,   C4,  C18,	  C4,  C4,	   C4,   C4, C4,  C4,  C4,  C4,	   C4,	   C5,	   C4,	    NT,  NO, C1, NO,  C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4,  C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C4,},  //
						  /*C5*/   {C2,   C2,	C2,	  C6,  C2,	   C2,   C5, C2,  C2,  C2,  C2,    C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C6*/   {C2,  C12,  C18,	  C2,  C2,	   C2,   C6, C2,  C7,  C2, C14,	   C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C7*/   {C2,   C2,	C2,	  C2,  C2,	   C2,   C7, C8,  C2,  C2,  C2,	   C2,	   C2, 	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C8*/   {C2,  C11,	C2,	  C2,  C2,	   C9,   C8, C2,  C2,  C2,  C2,	   C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C9*/   {C9,   C9,	C2,	  C9,  C9,	   C10,  C9, C9,  C9,  C9,  C9,	   C9,	   C9,	   C9,	    NT,  NO, C1, NO,  C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9,  C9, C9, C9, C9, C9, C9, C9, C9, C9, C9, C9,},  //
						  /*C10*/  {C2,   C2,  C18,	  C2, C11,	   C2,  C10, C2,  C2,  C2,  C2,	   C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C11*/  {C6,   C6,   C6,	  C6,  C6,	   C6,   C6, C6,  C6,  C6,  C6,	   C6,	   C6,	   C6,	    T,   NO, C6, NO,  C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6,  C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6,},  //
						  /*C12*/  {C2,   C2,   C2,	  C2, C13,	   C2,  C12, C2,  C2,  C2,  C2,	   C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C13*/  {C6,   C6,   C6,	  C6,  C6,	   C6,   C6, C6,  C6,  C6,  C6,	   C6,	   C6,	   C6,	    T,   NO, C6, NO,  C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6,  C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6,},  //
						  /*C14*/  {C2,   C2,   C2,	  C2,  C2,	   C2,  C14,C15,  C2,  C2,  C2,	   C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C15*/  {C2,  C17,   C2,	  C2,  C2,	  C16,   C2, C2,  C2,  C2,  C2,	   C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C16*/ {C16,  C16,   C2,	 C16, C16,	  C17,  C16,C16, C16, C16, C16,	   C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C17*/  {C6,   C6,   C6,	  C6,  C6,	   C6,   C6, C6,  C6,  C6,  C6,	   C6,	   C6,	   C6,	    T,   NO, C6, NO,  C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6,  C6, C6, C6, C6, C6, C6, C6, C6, C6, C6, C6,},  //
						  /*C18*/ {C20,  C20,  C19,	 C20, C20,	  C20,  C20,C20, C20, C20, C20,	  C20,	  C20,	  C20,	    NT,  NO, C1, NO, C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20, C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,C20,},  //
						  /*C19*/  {C1,   C1,   C1,	  C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C23,NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  //
						  /*C20*/  {C2,   C2,   C2,	  C2,  C2,	   C2,   C2, C2,  C2,  C2,  C2,	   C2,	   C2,	   C2,	    T,   NO, C4, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C21*/  {C2,   C2,  C22,	  C2,  C2,	   C2,   C2, C2,  C2,  C2,  C2,	   C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C22*/  {C2,   C2,   C2,	  C2,  C2,	   C2,   C2, C2,  C2,  C2,  C2,	   C2,	   C2,	   C2,	    T,   NO, C4, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C23*/ {C21,  C23,  C23,	 C23, C23,	  C23,  C23,C23, C23, C23, C23,	  C23,	  C23,	  C23,	    NT,  NO, C1, NO, C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23, C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,C23,},  //
						  /*C24*/  {C2,   C2,   C2,	  C2,  C2,	   C2,   C2, C2,  C2,  C2,  C2,	   C2,	   C2,	   C2,	    NT,  NO, C1, NO,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,  C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,},  //
						  /*C25*/  {C1,   C1,   C1,	  C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,  YES, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // ERROR STATE
	 //[b]			  			    [     ]   BOLD  WORD  COLON  QUOTE SP  EQAL  /	  ITAL								    TER  PB  RET MEM 																																
						  /*C26*/ {C25,  C27,  C25,	  C25, C25,	  C25,  C26,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [b
						  /*C27*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [b]
	 //[i]			  			    [     ]   BOLD  WORD  COLON  QUOTE SP  EQAL  /	  ITAL								    TER  PB  RET MEM 																															
						  /*C28*/ {C25,  C29,  C25,	  C25, C25,	  C25,  C28,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [i
						  /*C29*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [i]
	 //[u]			  			    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER						    TER  PB  RET MEM 																																
						  /*C30*/ {C25,  C31,  C25,	  C25, C25,	  C25,  C30,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [u
						  /*C31*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [u]
	 //[h]			  			    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM 																																
						  /*C32*/ {C25,  C33,  C25,	  C25, C25,	  C25,  C32,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [h
						  /*C33*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO , C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [h]
	 //[small]		  			    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM 																																
						  /*C34*/ {C25,  C35,  C25,	  C25, C25,	  C25,  C34,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [small
						  /*C35*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [small]	  
	 //[sub]		  			    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM 																																
						  /*C36*/ {C25,  C37,  C25,	  C25, C25,	  C25,  C36,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [sub
						  /*C37*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [sub]	
	 //[sup]		  			    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C38*/{C25,  C39,  C25,	  C25, C25,	  C25,  C38,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [sup
						  /*C39*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [sup]	
	 //[offtopic]				    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C40*/{C25,  C41,  C25,	  C25, C25,	  C25,  C40,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [offtopic
						  /*C41*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [offtopic]	
	 //[color=WORD]				    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL
						  /*C42*/{C25,  C25,  C25,	  C25, C25,	  C25,  C40,C43, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [color
						  /*C43*/{C25,  C25,  C25,	  C44, C25,	  C25,  C43,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C44,C44,C44,C44,C44,C44,C44,C44,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [color=
						  /*C44*/{C25,  C45,  C25,	  C25, C25,	  C25,  C44,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [color=WORD
						  /*C45*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [color=WORD]
  	 //[/color]					    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C46*/{C25,  C47,  C25,	  C25, C25,	  C25,  C46,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [/color
						  /*C47*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [/color]
	//[red]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C48*/{C25,  C49,  C25,	  C25, C25,	  C25,  C48,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [red
						  /*C49*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [red]
	//[orange]					    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C50*/{C25,  C51,  C25,	  C25, C25,	  C25,  C50,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [orange
						  /*C51*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [orange]
//[yellow	]					    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C52*/{C25,  C53,  C25,	  C25, C25,	  C25,  C52,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [yellow
						  /*C53*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [yellow]
  //[green	]					    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C54*/{C25,  C55,  C25,	  C25, C25,	  C25,  C54,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [green
						  /*C55*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [green]
//[blue	]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C56*/{C25,  C57,  C25,	  C25, C25,	  C25,  C56,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [blue
						  /*C57*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [blue]
//[purple	]					    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C58*/{C25,  C59,  C25,	  C25, C25,	  C25,  C58,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [purple
						  /*C59*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [purple]
//[white]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C60*/{C25,  C61,  C25,	  C25, C25,	  C25,  C60,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [white
						  /*C61*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [white]
//[black]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C62*/{C25,  C63,  C25,	  C25, C25,	  C25,  C60,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [black
						  /*C63*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [black]
//[size=WORD]					    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ
						  /*C64*/{C25,  C25,  C25,	  C25, C25,	  C25,  C64,C65, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [size
						  /*C65*/{C25,  C25,  C25,	  C66, C25,	  C25,  C65,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [size=
						  /*C66*/{C25,  C67,  C25,	  C25, C25,	  C25,  C66,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [size=WORD
						  /*C67*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [size=WORD]
//[/size]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C68*/{C25,  C69,  C25,	  C25, C25,	  C25,  C68,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [/size
						  /*C69*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [/size]
//[face=WORD]					    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ
						  /*C70*/{C25,  C25,  C25,	  C25, C25,	  C25,  C70,C71, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [face
						  /*C71*/{C25,  C25,  C25,	  C72, C25,	  C25,  C71,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [face=
						  /*C72*/{C25,  C73,  C25,	  C25, C25,	  C25,  C72,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [face=WORD
						  /*C73*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [face=WORD]
//[/face]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C74*/{C25,  C75,  C25,	  C25, C25,	  C25,  C74,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [/face
						  /*C75*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [/face]
//[url]							    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE CDE HR  IMG  EML LST MUL LS2																															
						  /*C76*/{C25,  C77,  C25,	  C25, C25,	  C25,  C76,C82, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [url
						  /*C77*/{C25,  C25,  C25,	  C78, C25,	  C25,  C77,C25, C78, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [url]
						  /*C78*/{C79,  C25,  C78,	  C78, C78,	  C25,  C79,C78, C78, C78, C78,	  C78,	  C78,	  C78,	    NT,	 NO, C1, YES,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78,C78, C78,C78,C78,C78,C25,C25,C25,C25,C25,C25,C25,},  // found [url]WORD
						  /*C79*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C2, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [url]WORD[
//[/url]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE																																
						  /*C80*/{C25,  C81,  C25,	  C25, C25,	  C25,  C74,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [/url
						  /*C81*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [/url]

						  /*C82*/{C25,  C25,  C25,	  C83, C25,	  C25,  C82,C25, C83, C83, C83,	  C83,	  C83,	  C83,	    NT,	 NO, C1, YES,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [url=hello +
						  /*C83*/{C25,  C84,  C25,	  C83, C83,	  C25,  C83,C83, C83, C83, C83,	  C83,	  C83,	  C83,	    NT,	 NO, C1, YES,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C83,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [url=hello +
						  /*C84*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [url=hello w]
//[quote]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C85*/{C25,  C86,  C25,	  C25, C25,	  C25,  C85,C89, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [quote
						  /*C86*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [quote]
//[/quote]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C87*/{C25,  C88,  C25,	  C25, C25,	  C25,  C87,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [quote
						  /*C88*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [quote]
//[/quote=]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER					    TER  PB  RET MEM SUP 																																
						  /*C89*/{C25,  C25,  C25,	  C90, C25,	  C25,  C89,C25, C25, C90, C90,	  C90,	  C90,	  C90,	    NT,  NO, C1, YES,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90, C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,},  // found [quote=
						  /*C90*/{C25,  C86,  C25,	  C90, C25,	  C25,  C90,C25, C25, C90, C90,	  C90,	  C90,	  C90,	    NT,  NO, C1, YES,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90, C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,C90,},  // found [quote=.+	
//[pre]							    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
						  /*C91*/{C25,  C92,  C25,	  C25, C25,	  C25,  C91,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [pre
						  /*C92*/ {C1,	 C1,    C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [pre]
//[/pre]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
						  /*C93*/{C25,  C94,  C25,	  C25, C25,	  C25,  C94,C25, C25, C25, C25,	  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [code
						  /*C94*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [code]
//[hr]							    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
						  /*C95*/{C25,  C96,  C25,	  C25, C25,	  C25,  C95, C25, C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},  // found [hr
						  /*C96*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [hr]
//[img							    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
						  /*C97*/{C25,  C98,  C25,	  C25, C25,	  C25,  C97,C103,C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [img
						  /*C98*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO,C101, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [img]
//[/img							    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
						  /*C99*/{C25,C100,  C25,	  C25, C25,	  C25,  C99,C25, C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [/img
						 /*C100*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [/img]
//[img].+						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP  OFF  COL RED  ORG YEL  GRN BLU  PUR  WHT  BLK  SZ   FAC  URL  QUO  PRE   CDE  HR   IMG   EML  LST  MUL  LS2
					    /*C101*/{C102,  C25, C101,  C101, C101,	  C25,  C25,C25,C101,C101,C101,  C101,	 C101,   C101,	    NT,  NO, C1, YES,C101,C101,C25,C101,C101,C101,C25,C101,C101,C101,C101,C101,C101,C101,C101,C101, C101,C101,C101, C101,C101,C101,C101,C25,C25,C25,C25,C25,C25,C25,},// found [/img
						/*C102*/  {C1,	 C1,   C1,	  C1,   C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C2, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [/img]
//[img=]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP  OFF  COL  RED  ORG  YEL  GRN  BLU  PUR  WHT  BLK  SZ   FAC  URL  QUO  PRE
					     /*C103*/{C25,  C25,  C25,	C104, C104,	  C25, C104,C104,C104,C104,C104, C104,	 C104,	 C104,	    NT,  NO, C1, YES,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [img=
//[img=]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP  OFF   COL RED  ORG  YEL  GRN  BLU  PUR  WHT  BLK  SZ   FAC  URL  QUO  PRE
						 /*C104*/{C25,  C98,  C25,	C104, C104,	  C25, C104,C104,C104,C104,C104, C104,	 C104,	 C104,	    NT,  NO, C1, YES,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C104,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [img=.+
//[email						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
						 /*C105*/{C25, C106,  C25,	  C25, C25,	  C25, C105,C111,C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [email
						 /*C106*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO,C109, NO, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [email]
//[/email						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
						 /*C107*/{C25, C108,  C25,	  C25, C25,	  C25,  C99,C25, C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [/email
						 /*C108*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [/email]
//[email].+						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP  OFF  COL  RED  ORG  YEL  GRN  BLU  PUR  WHT  BLK  SZ   FAC  URL  QUO  PRE
					    /*C109*/{C110,  C25, C109, C109,  C109,	  C109,C109,C25, C25,C109, C109, C109,	 C109,   C109,	    NT,  NO, C1, YES,C109,C109,C109,C109,C109,C109,C109,C109,C109,C109,C109,C109,C109,C109,C109,C109,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [email].+
						/*C110*/  {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C2, NO,  C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [email].+[
//[email=]						    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
					     /*C111*/{C25,  C25,  C25,	C112, C25,	  C25, C112,C25, C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [email=
						 /*C112*/{C25, C113,  C25,  C112, C25,	  C25,C112,C25, C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [email=.+
						 /*C113*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [email]
//[list							    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
					  	 /*C114*/{C25, C115,  C25,	  C25, C25,	  C25, C114, C25,C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [list
						 /*C115*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO,C109, NO, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [list]
//[*							    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
					  	 /*C116*/{C25, C117,  C25,	  C25, C25,	  C25, C116, C25,C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [*
						 /*C117*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [*]
//[*							    [     ]   BOLD  WORD  COLON   QUOTE SP  EQAL  /	  ITAL UNDER HEADER						TER  PB  RET MEM SUP OFF COL RED ORG YEL GRN BLU PUR WHT BLK  SZ FAC URL QUO PRE
					  	 /*C118*/{C25, C119,  C25,	  C25, C25,	  C25, C118, C25,C25, C25, C25,  C25,	  C25,	  C25,	    NT,  NO, C1, YES,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25, C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,C25,},// found [*
						 /*C119*/ {C1,	 C1,   C1,	   C1,  C1,	   C1,   C1, C1,  C1,  C1,  C1,	   C1,	   C1,	   C1,	    T,   NO, C1, NO, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,},  // found [*]

					 	  };

//--------------------------------
// parser::max_form_field_num
	size_t parser::read_buffer_size(size_t read_buffer_size) throw(out_of_range){	
		if(read_buffer_size <= 0) throw out_of_range(get_module_msg("Read buffer size must be more than 0"));
		return myswap(_pconf._read_buffer_size, read_buffer_size);	
	}

//--------------------------------
// parser::parse

	void parser::parse(void){		
		/* we're doing some ianitialization */		
		
		_lexer.init(_pconf);
		l = TERM;
		_current_state = C1;
		_parsed_data.clear();			
		_lexems = stack<lexeme>();//cleaning up
		_im_data = "";			
		
		
		
		while( (l =_lexer.get_lexeme()) != TERM){
		  _lexems.push(l);
		  _im_data  = _lexer.get_lexeme_str();		  		  
		  _parsed_data += _im_data;
		  while(_lexems.size()){		  
		    l = _lexems.top();
			_lexems.pop();
			switch(l){
				case WORD:
								_current_state = Parser[_current_state][3];								
								break;

				case LEFT_SQUARE_BRACKET:
								_current_state = Parser[_current_state][0];								
								_tmp_tag.left_bracket_pos = _parsed_data.length()-1;								
								break;

				case RIGHT_SQUARE_BRACKET:
								_current_state = Parser[_current_state][1];
								_tmp_tag.right_bracket_pos = _parsed_data.length()-1;
								break;

				case SLASH:
								_current_state = Parser[_current_state][8];								
								_tmp_tag.type = tag::closing;
								break;

				case BOLD:
								_current_state = Parser[_current_state][2];								
								break;

				case ITALIC:								
								_current_state = Parser[_current_state][9];								
								break;

								
				case HEADER:								
								_current_state = Parser[_current_state][11];
								break;

				case UNDERLINE:								
								_current_state = Parser[_current_state][10];
								break;

				case SMALL:
								_current_state = Parser[_current_state][12];
								break;
				case SUB:
								_current_state = Parser[_current_state][13];								
								break;

				case SUP:
								_current_state = Parser[_current_state][18];
								break;

				case OFFTOPIC:
								_current_state = Parser[_current_state][19];
								break;
				case COLOR:
								_current_state = Parser[_current_state][20];
								break;
				case RED:
								_current_state = Parser[_current_state][21];
								break;
				case ORANGE:
								_current_state = Parser[_current_state][22];
								break;

				case YELLOW:
								_current_state = Parser[_current_state][23];
								break;

				case GREEN:
								_current_state = Parser[_current_state][24];
								break;
				case BLUE:
								_current_state = Parser[_current_state][25];
								break;
				case PURPLE:
								_current_state = Parser[_current_state][26];
								break;
				case WHITE:
								_current_state = Parser[_current_state][27];
								break;
				case BLACK:
								_current_state = Parser[_current_state][28];
								break;
				case SIZE:
								_current_state = Parser[_current_state][29];
								break;
				case FACE:
								_current_state = Parser[_current_state][30];
								break;
				case URL:
								_current_state = Parser[_current_state][31];
								break;

				case QQUOTE:
								_current_state = Parser[_current_state][32];
								break;

				case PRE:
								_current_state = Parser[_current_state][33];
								break;			

				case CODE:
								_current_state = Parser[_current_state][34];
								break;
				case HR:
								_current_state = Parser[_current_state][35];
								break;
				case IMG:
								_current_state = Parser[_current_state][36];
								break;

				case EMAIL:
								_current_state = Parser[_current_state][37];
								break;
				case LIST:
								_current_state = Parser[_current_state][38];
								break;

				case MULT:
								_current_state = Parser[_current_state][39];
								break;

				case OLIST:
								_current_state = Parser[_current_state][40];
								break;

				case COLON:
								_current_state = Parser[_current_state][4];
								break;
				case SEMICOLON:
								_current_state = Parser[_current_state][4];
								break;
				case QUOTE:
								_current_state = Parser[_current_state][5];								
								break;
				case SPACE:
								_current_state = Parser[_current_state][6];								
								break;				
				case EQUALITY:
								_current_state = Parser[_current_state][7];								
								break;
				
			  }
		  	switch(_current_state){				
				case C1:
						 _tmp_tag.clear();
						 break;
 			
				case C25:						
					    _lexems.push(l);
						_current_state = C1; /* error recovery mode */
						_tmp_tag.clear();
						break;
				case C27: //[b] tag found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _BOLD;						
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;						
						_tmp_tag.clear();						
						break;				
				case C29: //[i] tag found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _ITALIC;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();						
						break;
				case C31: //[u] tag found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _UNDERLINE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();						
						break;
				case C33: //[h] tag found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _HEADER;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();						
						break;
				case C35: //[small] tag found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _SMALL;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();						
						break;
				case C37: //[sub] tag found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _SUB;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();						
						break;
				case C39: //[sup] tag found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _SUP;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();						
						break;
				case C41: //[offtopc] tag found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _OFFTOPIC;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();						
						break;
				case C44: //[color=WORD, WORD found
						_tmp_tag.attr.insert(make_pair(_COLOR, _im_data));							
						break;
	
				case C45: //[color=WORD] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _COLOR;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();						
						break;

				case C47: //[/color] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _COLOR;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C49: //[red] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _RED;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C51: //[orange] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _ORANGE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C53: //[yellow] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _YELLOW;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C55: //[yellow] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _GREEN;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C57: //[blue] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _BLUE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C59: //[purple] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _PURPLE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C61: //[white] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _WHITE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C63: //[black] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _BLACK;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C66: //[size=WORD, WORD found
						_tmp_tag.attr.insert(make_pair(_SIZE, _im_data));
						break;
				case C67: //[size=WORD] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _SIZE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C69: //[size=WORD] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _SIZE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C72: //[face=WORD, WORD found
						_tmp_tag.attr.insert(make_pair(_FACE, _im_data));
						break;
				case C73: //[face=WORD] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _FACE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C75: //[/face] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _FACE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C77: //[url] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _URL;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				
				case C78: //[url]WORD+ accumulating					
						if(!_parsed_tags.empty() && _parsed_tags.back().name == _URL){
							if((_parsed_tags.back().attr).find(_URL) == _parsed_tags.back().attr.end()){
								_parsed_tags.back().attr.insert(make_pair(_URL, _im_data));
							}else{
								_parsed_tags.back().attr[_URL] += _im_data;
							}							
						}
						break;				

				case C81:  //[/url] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _URL;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

			   case C83: //[url]WORD+ accumulating							
						    if(_tmp_tag.attr.find(_URL) == _tmp_tag.attr.end()){
								_tmp_tag.attr.insert(make_pair(_URL, _im_data));
							}else{
								_tmp_tag.attr[_URL] += _im_data;
							}						
						break;
				case C84: //[url=hello world] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _URL;
						_tmp_tag.type = tag::opening;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C86: //[quote]
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _QUOTE;						
						if(_tmp_tag.type == tag::opening)
							_tmp_tag.attr.insert(make_pair(_QUOTE, ""));
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C88: //[quote]
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _QUOTE;						
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C90: //[quote=WORD+ accumulating							
						    if(_tmp_tag.attr.find(_QUOTE) == _tmp_tag.attr.end()){
								_tmp_tag.attr.insert(make_pair(_QUOTE, _im_data));
							}else{
								_tmp_tag.attr[_QUOTE] += _im_data;
							}						
						break;
				case C92:  //[pre] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _PRE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C94:  //[code] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _CODE;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C96:  //[hr] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _HR;
						_tmp_tag.has_closing_tag = false;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C98:  //[img] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _IMG;
						if(_tmp_tag.attr.find(_TITLE) == _tmp_tag.attr.end()){
								_tmp_tag.attr.insert(make_pair(_TITLE, ""));
						}
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C100:  //[/img] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _IMG;
						_tmp_tag.type = tag::closing;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
				case C101:  //[img].+ collecting URL
						if(!_parsed_tags.empty() && _parsed_tags.back().name == _IMG){
							if((_parsed_tags.back().attr).find(_IMG) == _parsed_tags.back().attr.end()){
								_parsed_tags.back().attr.insert(make_pair(_IMG, _im_data));
							}else{
								_parsed_tags.back().attr[_IMG] += _im_data;
							}							
						}							
						break;
				case C104:  //[img=.+ collecting HINT
							if(_tmp_tag.attr.find(_TITLE) == _tmp_tag.attr.end()){
								_tmp_tag.attr.insert(make_pair(_TITLE, _im_data));
							}else{
								_tmp_tag.attr[_TITLE] += _im_data;
							}						
						break;

				case C106:  //[email] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _EMAIL;						
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C108:  //[/email] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _EMAIL;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C109:  //[email].+ collecting EMAIL
						if(!_parsed_tags.empty() && _parsed_tags.back().name == _EMAIL){
							if((_parsed_tags.back().attr).find(_EMAIL) == _parsed_tags.back().attr.end()){
								_parsed_tags.back().attr.insert(make_pair(_EMAIL, _im_data));
							}else{
								_parsed_tags.back().attr[_EMAIL] += _im_data;
							}							
						}

				case C112:  //[email=
							if(_tmp_tag.attr.find(_EMAIL) == _tmp_tag.attr.end()){
								_tmp_tag.attr.insert(make_pair(_EMAIL, _im_data));
							}else{
								_tmp_tag.attr[_EMAIL] += _im_data;
							}						
						break;
				case C113:  //[email=mail to] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _EMAIL;						
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C115:  //[list] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _LIST;	
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C117:  //[*] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _MULT;	
						_tmp_tag.has_closing_tag = false;
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;

				case C119:  //[olist] found
						_tmp_tag.right_bracket_pos = _parsed_data.length();
						_tmp_tag.name = _OLIST;							
						_parsed_tags.push_back(_tmp_tag);
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "found [" << _tmp_tag.name <<"] tag state: " << _tmp_tag.type << std::endl;
						_tmp_tag.clear();					
						break;
			};
			if(Parser[_current_state][14] == T){				
				_current_state = Parser[_current_state][16];				
				_bbcode_replacements();
			}

		  }
		
		}
	}

//--------------------------------
// parser::bbcode_replacements
	void parser::_bbcode_replacements(void){
		string opening, closing;
		_discarded_tags.clear();

		if(!_parsed_tags.size()) return;//we have nothing to process
		
		tag _cur_tag = _parsed_tags.back(); //taking the last tag

		//just in case we have something like <hr> at the begining (no closing tag)
		if(_cur_tag.has_closing_tag == false){
			opening = _tag_replacement(_cur_tag);
			//replacing opening tag
			_parsed_data.erase(_cur_tag.left_bracket_pos, _cur_tag.right_bracket_pos - _cur_tag.left_bracket_pos);
			_parsed_data.insert(_cur_tag.left_bracket_pos, opening);
			_discarded_tags.push_back(_cur_tag);
			_discarded_tags_cleanup();
			if(!_parsed_tags.size()) return;//we have nothing more to process
			_cur_tag = _parsed_tags.back(); //getting the last tag
		}
		
		// we're expecting to find an opening tag,  going from the last closed tag (last tag is not included)
		for(tags::reverse_iterator ci = _parsed_tags.rbegin() + 1; ci != _parsed_tags.rend(); ci++){
			if( _cur_tag.type == tag::closing){				
				tag _t = *ci;				
				if((*ci).name == _cur_tag.name && (*ci).type == tag::opening){ //make sure we found the same openning tag
					opening = _tag_replacement(*ci);
					closing = _tag_replacement(_cur_tag);
					//replacing closing tag
					_parsed_data.erase(_cur_tag.left_bracket_pos, _cur_tag.right_bracket_pos - _cur_tag.left_bracket_pos);
					_parsed_data.insert(_cur_tag.left_bracket_pos, closing);
					//replacing opening tag
					_parsed_data.erase((*ci).left_bracket_pos, (*ci).right_bracket_pos - (*ci).left_bracket_pos);
					_parsed_data.insert((*ci).left_bracket_pos, opening);
					//now when we made replacements, we're going to removed processed tags
					_discarded_tags.push_back(*ci);
					_discarded_tags.push_back(_cur_tag);
					break;
				}else{
					if((*ci).type == tag::opening){ //we found overlapped tag, let's mark it for deletion
						if(_pconf._config && bbcode::DEBUG_MODE_ON) std::cout << "overlapped tag" << (*ci).name;
						_discarded_tags.push_back(*ci);
					}
				}
			}
		}			
		_discarded_tags_cleanup();
	}
//--------------------------------
// parser::_tag_replacement(tag& t)
	string  parser::_tag_replacement(tag& t){
		string res;
		string tmp;
		supported_tag_storage::const_iterator ci;		

		if(t.type == tag::closing)
			ci = _supported_tag_storage.find(_HTML_BSLASH + t.name);			
		else
			ci = _supported_tag_storage.find(t.name);
		
		if(ci == _supported_tag_storage.end())
			return _BBTAG_IS_UNAVAILABLE_RET; //in case you don't want to support some of phpbb tags just upload new schema

		res = (*ci).second;

		if(!t.attr.empty()){
			for(tag::attribs::const_iterator ci = t.attr.begin(); ci != t.attr.end(); ci++){
				size_t p = res.find(_SCHEMA_MACRO_PREFIX + (*ci).first);
				if(p != string::npos){
					res.erase(p, (*ci).first.length() + _SCHEMA_MACRO_PREFIX.length());
					//javascript: guard
					tmp = (*ci).second;
					tmp = _js_guard(tmp);
					//QMessageBox::information(0, "tmp", QString::fromStdString(tmp), QMessageBox::Ok);
					res.insert(p, tmp);
				}
			}
		}else{			
			size_t p = res.find(_SCHEMA_MACRO_PREFIX + (*ci).first);
			//in case we have to clean up our macros
			if(p != string::npos)
				res.erase(p, (*ci).first.length() + _SCHEMA_MACRO_PREFIX.length());			
		}

		return res;
	}

//---------------------------------
//parser::_load_supported_tag_scheme
	void parser::load_supported_tag_schema(const string& schema){
		strings r = split_string(schema, _SHEMA_DELIMITER, false);
		_supported_tag_storage.clear();
		strings r2;
		size_t sz = r.size();
		for(strings::const_iterator ci = r.begin(); ci != r.end(); ci++){
			r2 = split_string(*ci, _SHEMA_TAG_DELIMITER);
			if(r2.size() != 2) throw runtime_error(_THIS_MODULE_STR_IDENT + " bad bb tag schema. " + *ci);
			_supported_tag_storage.insert(make_pair(trim(r2[0]), trim(r2[1])));
		}		
	}
//---------------------------------
//parser::_current_tag_schema
	string parser::current_tag_schema(void) const{
		stringstream r;
		for(supported_tag_storage::const_iterator ci = _supported_tag_storage.begin(); ci != _supported_tag_storage.end(); ci++){
			r << (*ci).first << "|" << (*ci).second << ";" << std::endl;
		}	
		return r.str();		
	}
//---------------------------------
//parser::_js_guard
	string parser::_js_guard(string str){
		size_t _colon_offset = str.find_first_of(_COLON);
		if(_colon_offset != string::npos && _colon_offset >= _MAXIMUM_PROTO_LENGTH)
				str.erase(0, _colon_offset + 1);
		return str;
		
	}
//---------------------------------
//parser::_discarded_tags_cleanup
	void parser::_discarded_tags_cleanup(void){
		//we're discarding overlapped|used tags, we don't need them any longer
		if(!_discarded_tags.empty()){
			for(tags::const_iterator ci = _discarded_tags.begin(); ci != _discarded_tags.end(); ci++){					
				tags::iterator it = find(_parsed_tags.begin(), _parsed_tags.end(), *ci);
				if(it != _parsed_tags.end()){
					_parsed_tags.erase(it);
				}
				
			}
		}		
	}

}
