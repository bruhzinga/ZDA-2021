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
		ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250),
		ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "[ SEMANTIC ] There is a non-closed string literal"),
		ERROR_ENTRY(301, "[ SEMANTIC ] There is more than one entry point in main"),
		ERROR_ENTRY(302, "[ SEMANTIC ] No entry point"),
		ERROR_ENTRY(303, "[ SEMANTIC ] Exceeded size of string literal"),
		ERROR_ENTRY(304, "[ SEMANTIC ] Variable declaration without let keyword"),
		ERROR_ENTRY(305, "[ SEMANTIC ] Undeclared identifier"),
		ERROR_ENTRY(306, "[ SEMANTIC ] Declaring a variable without specifying a type"),
		ERROR_ENTRY(307, "[ SEMANTIC ] Trying to implement an existing function"),
		ERROR_ENTRY(308, "[ SEMANTIC ] Declaring a function without specifying a type"),
		ERROR_ENTRY(309, "[ SEMANTIC ] Mismatch of types of passed function parameters"),
		ERROR_ENTRY(310, "[ SEMANTIC ] Arithmetic Operator Mismatch"),
		ERROR_ENTRY(311, "[ SEMANTIC ] Division by zero is not possible"),
		ERROR_ENTRY(312, "[ SEMANTIC ] Data type mismatch"),
		ERROR_ENTRY(313, "[ SEMANTIC ] Mismatch of open and closed parentheses in an expression"),
		ERROR_ENTRY(314, "[ SEMANTIC ] The function returns the wrong data type"),
		ERROR_ENTRY(315, "[ SEMANTIC ] Int out of range"),
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