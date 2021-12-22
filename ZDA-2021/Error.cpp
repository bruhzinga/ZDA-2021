#include"Error.h"
namespace Error {
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Invalid error code"),
		ERROR_ENTRY(1, "System failure"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "The -in parameter must be given"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Length of input parameter exceeded"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Error opening source file (-in)"),
		ERROR_ENTRY(111, "Invalid character in source file(-in)"),
		ERROR_ENTRY(112, "Error creating log file (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "[ LEXICAL ] Invalid character in source file (-in)"),
		ERROR_ENTRY(201, "[ LEXICAL ] Token table size exceeded"),
		ERROR_ENTRY(202, "[ LEXICAL ] Token table overflow"),
		ERROR_ENTRY(203, "[ LEXICAL ] The size of the identifier table has been exceeded"),
		ERROR_ENTRY(204, "[ LEXICAL ] ID table overflow"),
		ERROR_ENTRY(205, "[ LEXICAL ] Unknown character sequence"),
		ERROR_ENTRY(206, "[ LEXICAL ] Int out of range"),
		ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250),
		ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "[ LEXICAL ] There is a non-closed string literal "),
		ERROR_ENTRY(301, "[ SEMANTIC ] There is more than one entry point to main "),
		ERROR_ENTRY(302, "[ SEMANTIC ] There is no entry point  "),
		ERROR_ENTRY(303, "[ LEXICAL ] The size of the string literal has been exceeded "),    //TA
		ERROR_ENTRY_NODEF(304),
		ERROR_ENTRY(305, "[ SEMANTIC ] Undeclared identifier "),                               //TA
		ERROR_ENTRY_NODEF(306),
		ERROR_ENTRY(307, "[ SEMANTIC ] An attempt to implement an existing function "),
		ERROR_ENTRY_NODEF(308),
		ERROR_ENTRY(309, "[ SEMANTIC ] 	Mismatch of types of passed function parameters "),			//TA
		ERROR_ENTRY_NODEF(310),
		ERROR_ENTRY_NODEF(311),
		ERROR_ENTRY(312, "[ SEMANTIC ] 	Data type mismatch "),
		ERROR_ENTRY(313, "[ SEMANTIC ]	Inconsistency between open and closed parentheses in the expression "), //TA
		ERROR_ENTRY(314, "[ SEMANTIC ]	The function returns the wrong data type "),
		ERROR_ENTRY_NODEF(315),
		ERROR_ENTRY(316, "[ SEMANTIC ]	Variable redeclaration "),
		ERROR_ENTRY(317, "[ SEMANTIC ]	Incorrect use of operators in expression "),
		ERROR_ENTRY_NODEF(318), ERROR_ENTRY_NODEF(319),
		ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),
		ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF10(500), ERROR_ENTRY_NODEF10(510), ERROR_ENTRY_NODEF10(520), ERROR_ENTRY_NODEF10(530), ERROR_ENTRY_NODEF10(540),
		ERROR_ENTRY_NODEF10(550), ERROR_ENTRY_NODEF10(560), ERROR_ENTRY_NODEF10(570), ERROR_ENTRY_NODEF10(580), ERROR_ENTRY_NODEF10(590),
		ERROR_ENTRY(600, "[ SYNTAX ] Incorrect program structure "),
		ERROR_ENTRY(601, "[ SYNTAX ] Missing parametrs "),
		ERROR_ENTRY(602, "[ SYNTAX ] Incorrect function parametrs "),
		ERROR_ENTRY(603, "[ SYNTAX ] The body of the function is missing "),
		ERROR_ENTRY(604, "[ SYNTAX ] Invalid expression "),
		ERROR_ENTRY(605, "[ SYNTAX ] Invalid instruction "),
		ERROR_ENTRY(606, "[ SYNTAX ] Incorrect construction of the function body "),
		ERROR_ENTRY(607, "[ SYNTAX ] Error in parametrs of body of loop or condition "),
		ERROR_ENTRY(608, "[ SYNTAX ] Error in function call "),
		ERROR_ENTRY(609, "[ SYNTAX ] Error in arithmetic expression "),
		ERROR_ENTRY(610, "[ SYNTAX ] Error in the parameter list when calling the function "),
		ERROR_ENTRY(611, "[ SYNTAX ] Error in arithmetic expression "),
		ERROR_ENTRY(612, "[ SYNTAX ] Invalid construction in the body of  loop or condition "),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id) {
		if (id > 0 && id < ERROR_MAX_ENTRY) {
			return errors[id];
		}
		else {
			return errors[0];
		}
	}
	ERROR geterrorin(int id, int line = -1, int col = -1) {
		if (id > 0 && id < ERROR_MAX_ENTRY) {
			errors[id].inext.col = col;
			errors[id].inext.line = line;
			return errors[id];
		}
		else {
			return errors[0];
		}
	}
}