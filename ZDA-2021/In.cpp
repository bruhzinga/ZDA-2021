#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include "Parm.h"

using namespace std;

namespace In
{
	IN getin(Parm::PARM parm)
	{
		IN in;
		unsigned char letter;
		int i = 0, position = 0;
		bool str_literal = false;

		in.size = 0;
		in.lines = 0;
		in.ignor = 0;
		in.text = new char[IN_MAX_LEN_TEXT];

		int col = 0;

		char* text = new char[IN_MAX_LEN_TEXT];

		ifstream file(parm.in);
		if (file.fail())
			throw ERROR_THROW(102);

		int lines = 0;

		while (in.size < IN_MAX_LEN_TEXT)
		{
			letter = file.get();
			if (file.eof()) break;

			switch (in.code[(int)letter])
			{
			case in.L:
				str_literal = !str_literal;
				in.text[i] = letter;
				i++;
				in.size++;
				position++;
				break;
			case in.C:
				if (!str_literal)
					while (!file.eof() && in.code[(int)letter] != in.BR)
						letter = file.get();
				else {
					in.text[i] = letter;
					i++;
					in.size++;
					position++;
				}
				break;
			case in.BR:
				in.lines++;
				position = 0;
				in.text[i] = '|';
				i++;
				in.size++;
				break;
			case in.T:
				in.text[i] = letter;
				i++;
				in.size++;
				position++;
				break;
			case in.I:
				in.ignor++;
				position++;
				break;
			case in.F: 
				throw ERROR_THROW_IN(200, in.lines + 1, position);
			default:
				in.text[i] = in.code[(int)letter];
				i++;
				in.size++;
				position++;
			}
		}
		file.close();
		in.text[i] = '\0';
		return in;
	}
}