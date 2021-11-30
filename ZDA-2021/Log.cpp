#include"Log.h"

namespace Log {
	LOG getlog(wchar_t logfile[]) {
		LOG log;
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (log.stream->fail())
			throw ERROR_THROW(112);

		wcscpy_s(log.logfile, logfile);
		return log;
	}

	void WriteLine(LOG log, const char* c, ...) {
		const char** ptr = &c;
		while (*ptr != "") {
			*log.stream << *ptr;
			ptr++;
		}

		*log.stream << std::endl;
	}

	void WriteLine(LOG log, const wchar_t* c, ...) {
		const wchar_t** ptr = &c;

		char temp[100];

		while (*ptr != L"") {
			wcstombs(temp, *ptr++, sizeof(temp));
			*log.stream << temp;
		}
		*log.stream << std::endl;
	}

	void WriteLog(LOG log) {
		time_t rawtime;
		tm current_time;
		char temp[100];

		time(&rawtime);
		localtime_s(&current_time, &rawtime);

		*log.stream << "\n|----- Протокол --------------|\n";
		strftime(temp, 100, "| Время: %d.%m.%Y, %H:%M:%S |\n", &current_time);
		*log.stream << temp <<
			"|-----------------------------|\n";
	}

	void WriteParm(LOG log, Parm::PARM parm) {
		char in_text[PARM_MAX_SIZE];
		char out_text[PARM_MAX_SIZE];
		char log_text[PARM_MAX_SIZE];

		wcstombs(in_text, parm.in, PARM_MAX_SIZE);
		wcstombs(out_text, parm.out, PARM_MAX_SIZE);
		wcstombs(log_text, parm.log, PARM_MAX_SIZE);

		*log.stream << "\n ---- Параметры ---- \n\n-in: " << in_text
			<< "\n-out: " << out_text
			<< "\n-log: " << log_text << std::endl;
	}

	void WriteIn(LOG log, In::IN in) {
		*log.stream << "\n ---- Данные ----"
			<< "\n\nВсего символов: " << in.size
			<< "\nВсего строк: " << in.lines
			<< "\nПропущено: " << in.ignor << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error) {
		if (log.stream) {
			*log.stream << "\nОшибка " << error.id
				<< ": " << error.message
				<< "\nСтрока " << error.inext.line
				<< " позиция " << error.inext.col << std::endl;
			//Close(log);
		}
		else {
			std::cout << "\nОшибка " << error.id
				<< ": " << error.message
				<< "\nСтрока " << error.inext.line
				<< " позиция " << error.inext.col << std::endl;
		}
	}

	void WriteLexTableLog(LT::LexTable& lextable, std::ostream& out) {
		int i;
		out << "\n\t\tТаблица лексем" << std::endl;
		out << std::setfill('-') << std::setw(90) << '-' << std::endl;
		out << "   #" << " | " << "Лексема" << std::setfill(' ') << std::setw(20) << ' ' << std::left 
			<< " | " << "Строка" << std::setw(21) << ' ' << std::left << " | " << "Индекс в ТИ" << std::endl;
		out << std::setfill('-') << std::setw(90) << '-' << std::endl;
		for (i = 0; i < lextable.size; i++) {
			char op = ' ';
			switch (lextable.table[i].op) {
			case LT::operations::OPLUS:
				op = '+';
				break;
			case LT::operations::OMINUS:
				op = '-';
				break;
			case LT::operations::OMUL:
				op = '*';
				break;
			case LT::operations::ODIV:
				op = '/';
				break;
			case LT::operations::OMOD:
				op = '%';
				break;
			}
			out << std::setfill('0') << std::setw(4) << std::right << i << " | " << std::setfill(' ')
				<< std::setw(24) << std::left << lextable.table[i].lexema << op << "   | " << std::setw(24) << std::left
				<< lextable.table[i].line << "    | ";
			if (lextable.table[i].idxTI == LT_TI_NULLIDX)
				out << "-" << std::endl;
			else
				out << std::setw(23) << lextable.table[i].idxTI << std::endl;
		}
		out << std::setfill('-') << std::setw(90) << '-' << std::endl;
		out << "\tВсего лексем: " << i << std::endl;
		out << std::setfill('-') << std::setw(90) << '-' << std::endl;
	}

	void Close(LOG log) {
		log.stream->close();
		delete log.stream;
	}
}