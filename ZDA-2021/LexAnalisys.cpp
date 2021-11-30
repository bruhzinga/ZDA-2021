#include "stdafx.h"
#include "LexAnalisys.h"
#include "Div.h"
#include "FST.h"
#include "Graphs.h"
#define DIV			'|'
#define SPACE		' '
#define PLUS		'+'
#define MINUS		'-'
#define STAR		'*'
#define DIRSLASH	'/'
#define MOD			'%'
#define MORE		'>'
#define LESS		'<'
#define EQU			'~'
#define NEQU		'!'
#define EQUAL		'='
using namespace std;

namespace Lex {
	LEX LexAnaliz(Log::LOG log, In::IN in, std::stack<std::string>& libs) {
		LEX lex;
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);

		cleanup(in.text, in.size, log);

		char** word = new char* [max_word];
		for (int i = 0; i < max_word; i++)
			word[i] = new char[size_word] {NULL};

		do {
			word = divideText(in.text, in.size);
		} while (word == NULL);

		int indexLex = 0;
		int literalCounter = 1;
		int line = 1;
		int position = 0;
		bool findMain = false;
		int mainCounter = 0;
		bool findDeclaration = false;
		bool findType = false;
		bool findProc = false;
		int is_cycle = 0;

		bool findMath = false;
		bool findString = false;

		std::stack<std::string> functions;
		char* bufprefix = new char[10]{ "" };
		char* L = new char[2]{ "L" };
		char* bufL = new char[TI_STR_MAXSIZE];
		char* nameLiteral = new char[10]{ "" };
		char* charclit = new char[10]{ "" };

		bool findFunc = false;
		bool findParm = false;
		IT::Entry entryIT;

		for (int i = 0; word[i] != NULL; i++, indexLex++) {
			bool findSameID = false;
			position += strlen(word[i]);
			if (FST::execute(FST::FST(word[i], FST_MATH))) {
				libs.push("math");
				findMath = true;
			}
			else if (FST::execute(FST::FST(word[i], FST_STRINGLIB))) {
				libs.push("string");
				findString = true;
			}
			else if (FST::execute(FST::FST(word[i], FST_LET))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_LET, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findDeclaration = true;
			}
			else if (FST::execute(FST::FST(word[i], FST_INT))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_INT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::INT;
			}
			else if (FST::execute(FST::FST(word[i], FST_BOOL))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_BOOL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::BOOL;
			}
			else if (FST::execute(FST::FST(word[i], FST_STRING))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_STRING, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::STR;
				strcpy(entryIT.value.vstr.str, "");
			}
			else if (FST::execute(FST::FST(word[i], FST_FUNCTION))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findFunc = true;
			}
			else if (FST::execute(FST::FST(word[i], FST_PROCEDURE))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_PROCEDURE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findFunc = true;
				findProc = true;
			}
			else if (FST::execute(FST::FST(word[i], FST_RET))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_RET, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_WRITE))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_WRITE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_WRITELN))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_WRITELN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_MAIN))) {
				strcpy(entryIT.id, word[i]);
				entryIT.idxFirstLE = indexLex;
				entryIT.idtype = IT::F;
				entryIT.iddatatype = IT::INT;
				IT::Add(idtable, entryIT);
				entryIT = {};

				LT::Entry entryLT = WriteEntry(entryLT, LEX_MAIN, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
				functions.push(word[i]);
				findMain = true;
				mainCounter++;
			}
			else if (FST::execute(FST::FST(word[i], FST_REPEAT))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_REPEAT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				is_cycle++;
			}
			else if (FST::execute(FST::FST(word[i], FST_WHERE))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_WHERE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				is_cycle++;
			}
			else if (FST::execute(FST::FST(word[i], FST_ELSE))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_ELSE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				is_cycle++;
			}
			else if (FST::execute(FST::FST(word[i], FST_TRUE)) || FST::execute(FST::FST(word[i], FST_FALSE))) {
				int value;
				if (!strcmp((char*)word[i], "true")) value = 1;
				else value = 0;

				for (int k = 0; k < idtable.size; k++) {
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::BOOL) {
						LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}

				if (findSameID) continue;

				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::BOOL;
				entryIT.value.vint = value;
				entryIT.idxFirstLE = indexLex;
				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, L);
				word[i] = strcat(bufL, charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};

				LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_SLEN)) && findString) {
				if (int idx = IT::IsId(idtable, word[i]) == TI_NULLIDX) {
					entryIT.idtype = IT::F;
					entryIT.iddatatype = IT::INT;
					entryIT.idxFirstLE = indexLex;
					strcpy(entryIT.id, word[i]);
					IT::Add(idtable, entryIT);
					entryIT = {};
				}

				LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_SCPY)) && findString) {
				if (int idx = IT::IsId(idtable, word[i]) == TI_NULLIDX) {
					entryIT.idtype = IT::F;
					entryIT.iddatatype = IT::STR;
					entryIT.idxFirstLE = indexLex;
					strcpy(entryIT.id, word[i]);
					IT::Add(idtable, entryIT);
					entryIT = {};
				}

				LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
			}
			else if ((FST::execute(FST::FST(word[i], FST_POW)) || FST::execute(FST::FST(word[i], FST_RAND))) && findMath) {
				if (int idx = IT::IsId(idtable, word[i]) == TI_NULLIDX) {
					entryIT.idtype = IT::F;
					entryIT.iddatatype = IT::INT;
					entryIT.idxFirstLE = indexLex;
					strcpy(entryIT.id, word[i]);
					IT::Add(idtable, entryIT);
					entryIT = {};
				}

				LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_INTLIT))) {
				int value = atoi((char*)word[i]);
				for (int k = 0; k < idtable.size; k++) {
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::INT) {
						LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}

				if (findSameID) continue;
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxFirstLE = indexLex;
				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, L);
				word[i] = strcat(bufL, charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};

				LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_INTLITHEX))) {
				char* numBuf = new char;
				int j = 0;
				for (int k = 0; k < strlen(word[i]); k++, j++) {
					numBuf[j] = word[i][k];
				}
				numBuf[j + 1] = '\0';
				int value = strtol(numBuf, NULL, 16);

				for (int k = 0; k < idtable.size; k++) {
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::INT) {
						LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}

				if (findSameID) continue;
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxFirstLE = indexLex;
				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, L);
				word[i] = strcat(bufL, charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};

				LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_STRLIT))) {
				int length = strlen(word[i]);
				for (int k = 0; k < length; k++)
					word[i][k] = word[i][k + 1];
				word[i][length - 2] = 0;

				for (int k = 0; k < idtable.size; k++) {
					if (!(strcmp(idtable.table[k].value.vstr.str, word[i]))) {
						findSameID = true;
						LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						break;
					}
				}
				if (findSameID) continue;

				strcpy(entryIT.value.vstr.str, word[i]);
				entryIT.value.vstr.len = length - 2;
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::STR;
				entryIT.idxFirstLE = indexLex;

				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, L);
				nameLiteral = strcat(bufL, (char*)charclit);
				strcpy(entryIT.id, nameLiteral);
				IT::Add(idtable, entryIT);
				entryIT = {};

				int k = 0;
				for (k = 0; k < idtable.size; k++) {
					if (!(strcmp(idtable.table[k].value.vstr.str, word[i])))
						break;
				}
				LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_ID))) {
				if (findParm)
					entryIT.idtype = IT::P;
				else if (findFunc) {
					if (findProc)
						entryIT.iddatatype = IT::PROC;
					entryIT.idtype = IT::F;
					functions.push(word[i]);
				}
				else {
					entryIT.idtype = IT::V;
					int idx = IT::IsId(idtable, word[i]);
					if (idx != TI_NULLIDX) {
						LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						entryIT = { };
						continue;
					}
					if (entryIT.iddatatype == IT::INT)
						entryIT.value.vint = TI_INT_DEFAULT;
					else if (entryIT.iddatatype == IT::STR) {
						entryIT.value.vstr.len = 0;
						memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
					}
				}

				entryIT.idxFirstLE = indexLex;
				if (entryIT.idtype != IT::F && !functions.empty()) {
					strcpy(bufprefix, functions.top().c_str());
					word[i] = strcat(bufprefix, word[i]);
				}
				strcpy(entryIT.id, word[i]);
				int idx = IT::IsId(idtable, word[i]);
				if (idx == TI_NULLIDX)
					IT::Add(idtable, entryIT);
				LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
				entryIT = { };
			}
			else if (FST::execute(FST::FST(word[i], FST_OPERATOR))) {
				strcpy(entryIT.id, word[i]);
				entryIT.idxFirstLE = indexLex;
				entryIT.idtype = IT::OP;
				if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
					IT::Add(idtable, entryIT);
				entryIT = { };

				LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
				switch (word[i][0]) {
				case MORE:
					entryLT.priority = 0;
					entryLT.op = LT::operations::OMORE;
					break;
				case LESS:
					entryLT.priority = 0;
					entryLT.op = LT::operations::OLESS;
					break;
				case EQU:
					entryLT.priority = 0;
					entryLT.op = LT::operations::OEQU;
					break;
				case NEQU:
					entryLT.priority = 0;
					entryLT.op = LT::operations::ONEQU;
					break;
				case PLUS:
					entryLT.priority = 2;
					entryLT.op = LT::operations::OPLUS;
					break;
				case MINUS:
					entryLT.priority = 2;
					entryLT.op = LT::operations::OMINUS;
					break;
				case DIRSLASH: 
					entryLT.priority = 3;
					entryLT.op = LT::operations::ODIV;
					break;
				case STAR:
					entryLT.priority = 3;
					entryLT.op = LT::operations::OMUL;
					break;
				case MOD:
					entryLT.priority = 3;
					entryLT.op = LT::operations::OMOD;
				}
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_SEMICOLON))) {
				if (findDeclaration && findFunc && findType)
					functions.pop();
				LT::Entry entryLT = WriteEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findDeclaration = findFunc = findType = findParm = false;
				entryIT = { };
			}
			else if (FST::execute(FST::FST(word[i], FST_COMMA))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				entryLT.priority = 1;
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_LEFTBRACE))) {
				findType = findDeclaration = findFunc = findParm = findProc = false;
				LT::Entry entryLT = WriteEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_BRACELET))) {
				if (!functions.empty() && is_cycle == 0)
					functions.pop();
				else if (is_cycle != 0) is_cycle--;
				LT::Entry entryLT = WriteEntry(entryLT, LEX_BRACELET, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_LEFTTHESIS))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lextable, entryLT);
				if (findFunc || findProc)
					findParm = true;
			}
			else if (FST::execute(FST::FST(word[i], FST_RIGHTTHESIS))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_RIGHTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				findParm = false;
				LT::Add(lextable, entryLT);
			}
			else if (FST::execute(FST::FST(word[i], FST_EQUAL))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (word[i][0] == DIV) {
				line++;
				position = 0;
				indexLex--;
			}
			else
				throw ERROR_THROW_IN(205, line, position);
		}

		if (!findMain) throw ERROR_THROW(302);
		if (mainCounter > 1) throw ERROR_THROW(301);

		lex.idtable = idtable;
		lex.lextable = lextable;
		return lex;
	}

	void Synchronization(Lex::LEX& lex) {
		bool* is_changed = new bool[lex.idtable.size]{ false };
		for (int i = 0; i < lex.lextable.size; i++) {
			if (lex.lextable.table[i].idxTI != -1 && !is_changed[lex.lextable.table[i].idxTI]) {
				lex.idtable.table[lex.lextable.table[i].idxTI].idxFirstLE = i;
				is_changed[lex.lextable.table[i].idxTI] = true;
			}
		}
		delete[] is_changed;
	}
}