#include "stdafx.h"
#include "IT.h"
#include "Error.h"
using namespace std;

namespace IT {
	IdTable Create(int size) {
		IdTable* table = new IdTable;
		if (size < TI_MAXSIZE) throw ERROR_THROW(203);
		table->maxsize = size;
		table->size = 0;
		table->table = new Entry[size];
		return *table;
	}

	void Add(IdTable& idtable, Entry entry) {
		if (idtable.size + 1 > idtable.maxsize) throw ERROR_THROW(204);

		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n) {
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0) return i;
		}

		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable) {
		delete[] idtable.table;
	}

	void ShowTable(IdTable& idtable, std::ostream& stream_out) {
		int i, j, numberOP = 0;
		stream_out << "\n";
		stream_out << setfill('-') << setw(87) << '-' << endl;
		stream_out << "   #" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора"
			<< " | " << "Индекс в ТЛ" << " | " << "Значение" << endl;
		stream_out << setw(87) << '-' << endl;

		for (i = 0, j = 0; i < idtable.size; i++, j++) {
			stream_out << setfill('0') << setw(4) << right << j << " | ";
			stream_out << setfill(' ') << setw(13) << left << idtable.table[i].id << " | ";

			if (idtable.table[i].idtype == IT::OP) stream_out << setw(10) << left << "-" << " | ";
			else {
				switch (idtable.table[i].iddatatype) {
				case INT:
					stream_out << setw(10) << left;
					stream_out << "int" << " | ";
					break;
				case STR:
					stream_out << setw(10) << left;
					stream_out << "string" << " | ";
					break;
				case BOOL:
					stream_out << setw(10) << left;
					stream_out << "bool" << " | ";
					break;
				default:
					stream_out << setw(10) << left << "unknown" << " | ";
					break;
				}
			}

			switch (idtable.table[i].idtype) {
			case V: stream_out << setw(18) << left << "переменная" << " | "; break;
			case F: stream_out << setw(18) << left << "функция" << " | "; break;
			case P: stream_out << setw(18) << left << "параметр" << " | "; break;
			case L: stream_out << setw(18) << left << "литерал" << " | "; break;
			case OP:
				stream_out << setw(18) << left << "оператор" << " | ";
				numberOP++;
				break;
			default: stream_out << setw(18) << left << "unknown" << " | "; break;
			}
			stream_out << setw(11) << left << idtable.table[i].idxFirstLE << " | ";

			if (idtable.table[i].iddatatype == INT && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				stream_out << setw(18) << left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				stream_out << "[" << idtable.table[i].value.vstr.len << "]\"" << idtable.table[i].value.vstr.str << "\"";
			else if (idtable.table[i].iddatatype == BOOL && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				stream_out << setw(18) << left << (idtable.table[i].value.vint == 0 ? "false" : "true");
			else stream_out << "-";
			stream_out << endl;
		}

		stream_out << setfill('-') << setw(87) << "-" << endl;
		stream_out << "Количество идентификаторов: " << i << endl;
		stream_out << setw(87) << "-" << endl;
	}
}