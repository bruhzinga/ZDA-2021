#include"Out.h"

namespace Out {
	OUT getout(wchar_t outfile[]) {
		OUT out;
		out.stream = new std::ofstream;
		out.stream->open(outfile);
		if (out.stream->fail())
			throw ERROR_THROW(112);

		wcscpy_s(out.outfile, outfile);
		return out;
	}

	void WriteOut(OUT out, In::IN in) {
		*out.stream << in.text;
	}

	void Close(OUT out) {
		out.stream->close();
		delete out.stream;
	}
}