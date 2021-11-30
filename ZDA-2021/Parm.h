#pragma once
#define PARM_IN		L"-in:"
#define PARM_OUT	L"-out:"
#define PARM_LOG	L"-log:"

#define PARM_LEX	L"-lex"
#define PARM_ID		L"-id"
#define PARM_RULES	L"-rules"
#define PARM_TOKENS	L"-tokens"

#define PARM_MAX_SIZE 300
#define PARM_OUT_DEFAULT_EXT L".out.asm"
#define PARM_LOG_DEFAULT_EXT L".log"

namespace Parm {
	struct PARM {
		wchar_t in[PARM_MAX_SIZE];
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];

		bool lex = false;
		bool id = false;
		bool rules = false;
		bool tokens = false;
	};

	PARM getparm(int argc, wchar_t* argv[]);
}