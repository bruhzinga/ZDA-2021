#pragma once
#define ID_MAXSIZE 10
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x00000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255

namespace IT {
	enum IDDATATYPE {INT = 1, STR = 2, BOOL = 3, PROC = 4};
	enum IDTYPE {V = 1, F = 2, P = 3, L = 4, OP = 5};

	struct Entry {
		int idxFirstLE;
		char visibility[ID_MAXSIZE];
		char id[ID_MAXSIZE];

		IDDATATYPE iddatatype;
		IDTYPE idtype;
		int countOfPar = 0;
		union {
			int vint = 0;
			struct {
				int len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr;
		} value;
	};

	struct IdTable {
		int maxsize;
		int size;
		Entry* table;
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);

	void Delete(IdTable& idtable);
	void ShowTable(IdTable& idtable, std::ostream& stream_out);
}