#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include "In.h"
#include "Log.h"
#include "Out.h"
#include "FST.h"
#include "Polish.h"
#include "LexAnalisys.h"
#include "MFST.h"
#include "GRB.h"
#include "SemAnalysis.h"
#include "Generation.h"

int wmain(int argc, wchar_t* argv[]) {
	setlocale(LC_ALL, "RUS");

	Log::LOG log = Log::INITLOG;

	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm);
		Log::WriteIn(log, in);
		Lex::LEX lex = Lex::LexAnaliz(log, in);
		MFST::check_syntax(lex, log, *log.stream);
		if (parm.rules)
			MFST::check_syntax(lex, log, std::cout);
		if (!Semantic::Analyze(lex, log)) {
			std::cout << "Semantic errors. Check log file to get more info";
			exit(-1);
		}
		Polish::startPolish(lex);
		Lex::Synchronization(lex);

		IT::ShowTable(lex.idtable, *log.stream);
		if (parm.id)
			IT::ShowTable(lex.idtable, std::cout);
		Log::WriteLexTableLog(lex.lextable, *log.stream);
		if (parm.tokens)
			Log::WriteLexTableLog(lex.lextable, std::cout);
		LT::ShowTable(lex.lextable, *log.stream);
		if (parm.lex)
			LT::ShowTable(lex.lextable, std::cout);

		Gen::Generator Gener(lex.lextable, lex.idtable);
		Log::Close(log);
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
}