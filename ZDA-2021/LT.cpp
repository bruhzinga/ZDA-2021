#include "stdafx.h"
#include "LT.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
using namespace Log;
using namespace std;

namespace LT {
	LexTable Create(int size) {
		LexTable* Table = new LexTable;
		if (size > LT_MAXSIZE) throw ERROR_THROW(201);
		Table->maxsize = size;
		Table->size = 0;
		Table->table = new Entry[size];
	}

	void Add(LexTable& lextable, Entry entry) {
		if (lextable.size + 1 > lextable.maxsize) throw ERROR_THROW(202);
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n) {
		return lextable.table[n];
	}

	void Delete(LexTable& lextable) {
		delete[] lextable.table;
	}

	Entry WriteEntry(Entry& entry, char lexema, int indx, int line) {
		entry.lexema = lexema;
		entry.idxTI = indx;
		entry.line = line;
		return entry;
	}

	void ShowTable(LexTable lextable, std::ostream& stream_out) {
		int line = 2;
		stream_out << "\n\t\tПромежуточное представление\n";
		stream_out << "0001| ";
		for (int i = 0; i < lextable.size; i++) {
			if (lextable.table[i].lexema == ';') {
				stream_out << lextable.table[i].lexema << endl;
				if (i + 1 == lextable.size) break;
				line > 999 ? stream_out << line << "| " : line > 99 ? stream_out << "0" << line << "| " : line > 9 ? stream_out << "00" << line <<
					"| " : stream_out << "000" << line << "| ";
				line++;
			}
			else stream_out << lextable.table[i].lexema;
		}
	}
}