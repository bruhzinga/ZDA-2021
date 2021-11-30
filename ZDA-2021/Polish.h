#pragma once
#include "stdafx.h"
#include "LexAnalisys.h"
#include "Error.h"

namespace Polish {
	void startPolish(Lex::LEX& lex);
	bool polishNotation(int i, Lex::LEX& lex);
}