#pragma once
#include "stdafx.h"
#include "Log.h"
#include "LexAnalisys.h"

namespace Semantic {
	bool Analyze(Lex::LEX lex, Log::LOG log);
}