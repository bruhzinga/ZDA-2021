#include "SemAnalysis.h"

namespace Semantic {
	bool Analyze(Lex::LEX lex, Log::LOG log) {
		bool is_ok = true;
		int j = 0;
		std::vector<std::string> functions_id;
		std::vector<std::string> variables_id;
		for (int i = 0; i < lex.lextable.size; i++) {
			switch (lex.lextable.table[i].lexema) {
			case LEX_LET:
				if (lex.lextable.table[i + 2].lexema == LEX_ID)
					if (std::count(variables_id.begin(), variables_id.end(), lex.idtable.table[lex.lextable.table[i + 2].idxTI].id)) {
						Log::WriteError(log, Error::geterrorin(316, lex.lextable.table[j].line, -1)); //correct it
						is_ok = false;
					}
					else
						variables_id.push_back(lex.idtable.table[lex.lextable.table[i + 2].idxTI].id);

				break;
			case LEX_EQUAL:
				j = i + 1;
				for (j; lex.lextable.table[j].lexema != LEX_SEMICOLON; j++) {
					switch (lex.lextable.table[j].lexema) {
					case LEX_ID:
					case LEX_LITERAL:
						if ((lex.idtable.table[lex.lextable.table[j].idxTI].idDataType != lex.idtable.table[lex.lextable.table[i - 1].idxTI].idDataType)) {
							Log::WriteError(log, Error::geterrorin(312, lex.lextable.table[j].line, -1));
							is_ok = false;
						}
						continue;

					case LEX_LEFTTHESIS:
						if (lex.lextable.table[j - 1].lexema == LEX_FUNCTION) {
							do {
								j++;
							} while (lex.lextable.table[j].lexema != LEX_RIGHTTHESIS);
						}
						continue;
					case LEX_OPERATOR:
						if (lex.idtable.table[lex.lextable.table[i - 1].idxTI].idDataType == IT::STR) {
							Log::WriteError(log, Error::geterrorin(317, lex.lextable.table[j].line, -1));
							is_ok = false;
						}
						switch (lex.lextable.table[j].op)
						{
						case LT::OMORE:
						case LT::OLESS:
						case LT::ONEQU:
						case LT::OEQU:
							Log::WriteError(log, Error::geterrorin(317, lex.lextable.table[j].line, -1));
							is_ok = false;
							break;
						default:
							break;
						}

						continue;
					}
				}

				continue;
			case LEX_FUNCTION:
				if (std::count(functions_id.begin(), functions_id.end(), lex.idtable.table[lex.lextable.table[i + 1].idxTI].id)) {
					Log::WriteError(log, Error::geterrorin(307, lex.lextable.table[i + 1].line, -1));
					is_ok = false;
				}
				functions_id.push_back(lex.idtable.table[lex.lextable.table[i + 1].idxTI].id);

				j = i + 1;
				int type = lex.idtable.table[lex.lextable.table[j].idxTI].idDataType;
				do {
					j++;
				} while ((lex.lextable.table[j].lexema != LEX_RET));
				if (lex.idtable.table[lex.lextable.table[j + 1].idxTI].idDataType != type) {
					Log::WriteError(log, Error::geterrorin(314, lex.lextable.table[j].line, -1));
					is_ok = false;
				}
			}
		}

		return is_ok;
	}
}