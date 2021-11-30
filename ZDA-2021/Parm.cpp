#include"stdafx.h"
#include"Parm.h"
#include"Error.h"

namespace Parm {
	PARM getparm(int argc, wchar_t* argv[]) {
		PARM parm;
		bool in_found = false,
			out_found = false,
			log_found = false;

		for (int i = 1; i < argc; i++) {
			if (wcslen(argv[i]) > PARM_MAX_SIZE) 
				throw ERROR_THROW(104);

			if (wcsstr(argv[i], PARM_IN)) {
				wcscpy_s(parm.in, argv[i] + wcslen(PARM_IN));
				in_found = true;
			}

			if (wcsstr(argv[i], PARM_OUT)) {
				wcscpy_s(parm.out, argv[i] + wcslen(PARM_OUT));
				out_found = true;
			}

			if (wcsstr(argv[i], PARM_LOG)) {
				wcscpy_s(parm.log, argv[i] + wcslen(PARM_LOG));
				log_found = true;
			}

			if (!_wcsnicmp(argv[i], PARM_ID, wcslen(PARM_ID)))
				parm.id = true;
			if (!_wcsnicmp(argv[i], PARM_LEX, wcslen(PARM_LEX)))
				parm.lex = true;
			if (!_wcsnicmp(argv[i], PARM_RULES, wcslen(PARM_RULES)))
				parm.rules = true;
			if (!_wcsnicmp(argv[i], PARM_TOKENS, wcslen(PARM_TOKENS)))
				parm.tokens = true;
		}

		if (!in_found) throw ERROR_THROW(100);
		if (!out_found) {
			wcscpy_s(parm.out, parm.in);
			wcscat_s(parm.out, PARM_OUT_DEFAULT_EXT);
		}
		if (!log_found) {
			wcscpy_s(parm.log, parm.in);
			wcscat_s(parm.log, PARM_LOG_DEFAULT_EXT);
		}

		return parm;
	}
}