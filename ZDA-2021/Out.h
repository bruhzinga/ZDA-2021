#include"stdafx.h"
#include"In.h"
#include"Parm.h"
#include"Error.h"
#include"FST.h"

namespace Out {
	struct OUT {
		wchar_t outfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const OUT INITOUT = { L"", NULL };
	OUT getout(wchar_t logfile[]);
	void WriteOut(OUT out, In::IN in);
	void Close(OUT out);
}