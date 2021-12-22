#pragma once
#include "GRB.h"
#include "LT.h"
#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)
#define LEX_TYPE 't'
#define LEX_OPERATION 'p'
#define FUNCTION_PARAMETRS 'F'
#define PARAMETRS_RESTRICTIONS 'P'
#define BODY 'B'
#define STARTING_SYMBOL 'S'
#define INSTRUCTIONS 'N'
#define FUNC_CALL 'K'
#define FUNC_CALL_PARAMETRS 'W'
#define EXPRESSION 'E'
#define CYCLE_AND_IF_PARAMETRS   'R'
#define CYCLE_AND_IF_BODY 'X'
#define ID_OR_LITERAL 'I'
#define MATH 'M'

namespace GRB {
	Greibach greibach(
		NS(STARTING_SYMBOL), TS('$'),
		13,
		Rule(
			NS(STARTING_SYMBOL), GRB_ERROR_SERIES + 0,
			3,
			Rule::Chain(6, TS(LEX_TYPE), TS(LEX_FUNCTION), TS(LEX_ID), NS(FUNCTION_PARAMETRS), NS(BODY), NS(STARTING_SYMBOL)),
			Rule::Chain(7, TS(LEX_VOID), TS(LEX_ID), NS(FUNCTION_PARAMETRS), TS('{'), NS(INSTRUCTIONS), TS('}'), NS(STARTING_SYMBOL)),
			Rule::Chain(4, TS(LEX_MAIN), TS('{'), NS(INSTRUCTIONS), TS('}'))

		),
		Rule(
			NS(FUNCTION_PARAMETRS), GRB_ERROR_SERIES + 1,
			2,
			Rule::Chain(3, TS('('), NS(PARAMETRS_RESTRICTIONS), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(
			NS(PARAMETRS_RESTRICTIONS), GRB_ERROR_SERIES + 2,
			2,
			Rule::Chain(2, TS(LEX_TYPE), TS(LEX_ID)),
			Rule::Chain(4, TS(LEX_TYPE), TS(LEX_ID), TS(','), NS(PARAMETRS_RESTRICTIONS))
		),
		Rule(
			NS(BODY), GRB_ERROR_SERIES + 3,
			3,
			Rule::Chain(6, TS('{'), NS(INSTRUCTIONS), TS(LEX_RET), NS(ID_OR_LITERAL), TS(';'), TS('}')),
			Rule::Chain(5, TS('{'), TS(LEX_RET), NS(ID_OR_LITERAL), TS(';'), TS('}')),
			Rule::Chain(3, TS('{'), NS(INSTRUCTIONS), TS('}'))
		),
		Rule(
			NS(ID_OR_LITERAL), GRB_ERROR_SERIES + 4,
			2,
			Rule::Chain(1, TS(LEX_ID)),
			Rule::Chain(1, TS(LEX_LITERAL))
		),
		Rule(
			NS(INSTRUCTIONS), GRB_ERROR_SERIES + 6,
			20,
			Rule::Chain(5, TS(LEX_LET), TS(LEX_TYPE), TS(LEX_ID), TS(';'), NS(INSTRUCTIONS)),
			Rule::Chain(7, TS(LEX_LET), TS(LEX_TYPE), TS(LEX_ID), TS('='), NS(EXPRESSION), TS(';'), NS(INSTRUCTIONS)),
			Rule::Chain(5, TS(LEX_ID), TS('='), NS(EXPRESSION), TS(';'), NS(INSTRUCTIONS)),
			Rule::Chain(8, TS(LEX_WHILE), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'), NS(INSTRUCTIONS)),
			Rule::Chain(8, TS(LEX_IF), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'), NS(INSTRUCTIONS)),
			Rule::Chain(12, TS(LEX_IF), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'), TS(LEX_ELSE), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'), NS(INSTRUCTIONS)),

			Rule::Chain(4, TS(LEX_WRITE), NS(ID_OR_LITERAL), TS(';'), NS(INSTRUCTIONS)),
			Rule::Chain(4, TS(LEX_WRITELN), NS(ID_OR_LITERAL), TS(';'), NS(INSTRUCTIONS)),
			Rule::Chain(4, TS(LEX_RET), NS(ID_OR_LITERAL), TS(';'), NS(INSTRUCTIONS)),
			Rule::Chain(4, TS(LEX_ID), NS(FUNC_CALL), TS(';'), NS(INSTRUCTIONS)),

			Rule::Chain(4, TS(LEX_LET), TS(LEX_TYPE), TS(LEX_ID), TS(';')),
			Rule::Chain(6, TS(LEX_LET), TS(LEX_TYPE), TS(LEX_ID), TS('='), NS(EXPRESSION), TS(';')),
			Rule::Chain(4, TS(LEX_ID), TS('='), NS(EXPRESSION), TS(';')),
			Rule::Chain(7, TS(LEX_WHILE), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}')),
			Rule::Chain(7, TS(LEX_IF), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}')),
			Rule::Chain(11, TS(LEX_IF), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'), TS(LEX_ELSE), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}')),
			Rule::Chain(3, TS(LEX_WRITE), NS(ID_OR_LITERAL), TS(';')),
			Rule::Chain(3, TS(LEX_WRITELN), NS(ID_OR_LITERAL), TS(';')),
			Rule::Chain(3, TS(LEX_RET), NS(ID_OR_LITERAL), TS(';')),
			Rule::Chain(3, TS(LEX_ID), NS(FUNC_CALL), TS(';'))
		),
		Rule(
			NS(CYCLE_AND_IF_PARAMETRS), GRB_ERROR_SERIES + 7,
			4,
			Rule::Chain(1, TS(LEX_ID)),
			Rule::Chain(3, TS(LEX_ID), TS(LEX_OPERATION), TS(LEX_ID)),
			Rule::Chain(3, TS(LEX_ID), TS(LEX_OPERATION), TS(LEX_LITERAL)),
			Rule::Chain(3, TS(LEX_LITERAL), TS(LEX_OPERATION), TS(LEX_ID))
		),
		Rule(
			NS(FUNC_CALL), GRB_ERROR_SERIES + 8,
			2,
			Rule::Chain(3, TS('('), NS(FUNC_CALL_PARAMETRS), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(
			NS(EXPRESSION), GRB_ERROR_SERIES + 9,
			8,
			Rule::Chain(1, TS(LEX_ID)),
			Rule::Chain(1, TS(LEX_LITERAL)),
			Rule::Chain(3, TS('('), NS(EXPRESSION), TS(')')),
			Rule::Chain(2, TS(LEX_ID), NS(FUNC_CALL)),

			Rule::Chain(2, TS(LEX_ID), NS(MATH)),
			Rule::Chain(2, TS(LEX_LITERAL), NS(MATH)),
			Rule::Chain(4, TS('('), NS(EXPRESSION), TS(')'), NS(MATH)),
			Rule::Chain(3, TS(LEX_ID), NS(FUNC_CALL), NS(MATH))
		),
		Rule(
			NS(FUNC_CALL_PARAMETRS), GRB_ERROR_SERIES + 10,
			4,
			Rule::Chain(1, TS(LEX_ID)),
			Rule::Chain(1, TS(LEX_LITERAL)),
			Rule::Chain(3, TS(LEX_ID), TS(','), NS(FUNC_CALL_PARAMETRS)),
			Rule::Chain(3, TS(LEX_LITERAL), TS(','), NS(FUNC_CALL_PARAMETRS))
		),
		Rule(
			NS(MATH), GRB_ERROR_SERIES + 11,
			2,
			Rule::Chain(2, TS(LEX_OPERATION), NS(EXPRESSION)),
			Rule::Chain(3, TS(LEX_OPERATION), NS(EXPRESSION), NS(MATH))
		),
		Rule(
			NS(CYCLE_AND_IF_BODY), GRB_ERROR_SERIES + 12,
			18,
			Rule::Chain(5, TS(LEX_LET), TS(LEX_TYPE), TS(LEX_ID), TS(';'), NS(CYCLE_AND_IF_BODY)),
			Rule::Chain(7, TS(LEX_LET), TS(LEX_TYPE), TS(LEX_ID), TS('='), NS(EXPRESSION), TS(';'), NS(CYCLE_AND_IF_BODY)),
			Rule::Chain(5, TS(LEX_ID), TS('='), NS(EXPRESSION), TS(';'), NS(CYCLE_AND_IF_BODY)),
			Rule::Chain(4, TS(LEX_WRITE), NS(ID_OR_LITERAL), TS(';'), NS(CYCLE_AND_IF_BODY)),
			Rule::Chain(4, TS(LEX_WRITELN), NS(ID_OR_LITERAL), TS(';'), NS(CYCLE_AND_IF_BODY)),
			Rule::Chain(4, TS(LEX_RET), NS(ID_OR_LITERAL), TS(';'), NS(CYCLE_AND_IF_BODY)),
			Rule::Chain(4, TS(LEX_ID), NS(FUNC_CALL), TS(';'), NS(CYCLE_AND_IF_BODY)),
			Rule::Chain(7, TS(LEX_IF), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}')),

			Rule::Chain(4, TS(LEX_LET), TS(LEX_TYPE), TS(LEX_ID), TS(';')),
			Rule::Chain(6, TS(LEX_LET), TS(LEX_TYPE), TS(LEX_ID), TS('='), NS(CYCLE_AND_IF_BODY), TS(';')),
			Rule::Chain(4, TS(LEX_ID), TS('='), NS(EXPRESSION), TS(';')),
			Rule::Chain(3, TS(LEX_WRITE), NS(ID_OR_LITERAL), TS(';')),
			Rule::Chain(3, TS(LEX_WRITELN), NS(ID_OR_LITERAL), TS(';')),
			Rule::Chain(3, TS(LEX_RET), NS(ID_OR_LITERAL), TS(';')),
			Rule::Chain(3, TS(LEX_ID), NS(FUNC_CALL), TS(';')),
			Rule::Chain(8, TS(LEX_IF), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'), NS(CYCLE_AND_IF_BODY)),
			Rule::Chain(12, TS(LEX_IF), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'), TS(LEX_ELSE), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'), NS(CYCLE_AND_IF_BODY)),
			Rule::Chain(11, TS(LEX_IF), TS('('), NS(CYCLE_AND_IF_PARAMETRS), TS(')'), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'), TS(LEX_ELSE), TS('{'), NS(CYCLE_AND_IF_BODY), TS('}'))

		)

	);
}