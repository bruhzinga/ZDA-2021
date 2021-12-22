#include "Polish.h"

namespace Polish {
	bool polishNotation(int i, Lex::LEX& lex) {
		std::stack<LT::Entry> stack;
		std::queue<LT::Entry> queue;

		LT::Entry aggregate_symbol;//структура символа которым  заполняется пространство от скобок и запятых в таблице лексем
		aggregate_symbol.idxTI = -1;
		aggregate_symbol.lexema = '#';
		aggregate_symbol.line = lex.lextable.table[i].line;

		LT::Entry function_symbol;//структура сивол вызова функции
		function_symbol.idxTI = LT_TI_NULLIDX;
		function_symbol.lexema = '@';
		function_symbol.line = lex.lextable.table[i].line;
		int idx;

		int lexem_counter = 0;
		int parm_counter = 0;
		int lexem_position = i;
		char* buf = new char[i];

		bool is_function = false;
		//идём по всей строке пока не встретим точку с запятой конец строки
		for (i; lex.lextable.table[i].lexema != LEX_SEMICOLON; i++, lexem_counter++) {
			switch (lex.lextable.table[i].lexema) {//если идентификатор или литреал
			case LEX_ID:
			case LEX_LITERAL:
				if (lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::F) {
					is_function = true;//если ссылается на функцию то
					idx = lex.lextable.table[i].idxTI;// КАКОЙ НОМЕР У ФУНКЦИИ ЧТО ВСТРЕТИЛИ В В ТАБЛИЦЕ ИДЕНТИФИКАТОРОВ кстанавливаем на структуру на которую ссылается лексема функции
				}
				else {
					if (is_function)
						parm_counter++;
					queue.push(lex.lextable.table[i]);//кладём в очередь эту лексему
				}
				continue;

			case LEX_LEFTTHESIS: //левая скобка
				stack.push(lex.lextable.table[i]);
				continue;

			case LEX_RIGHTTHESIS:
				while (stack.top().lexema != LEX_LEFTTHESIS) {
					queue.push(stack.top());
					stack.pop();//скидывает с вершины стека
					if (stack.empty())//лишняя скобка
						return false;
				}

				if (is_function == false) // чё
					stack.pop();
				else {
					function_symbol.idxTI = idx;//ссылаем новую структуру на индентификатор функции в таблице идентификкаторов
					idx = LT_TI_NULLIDX;
					lex.lextable.table[i] = function_symbol;//НЕ ФУНКЦИЯ А ЕЁ ВЫЗОВ кладём на местро старой структру новую структуру функции
					queue.push(lex.lextable.table[i]);
					_itoa_s(parm_counter, buf, 2, 10);//переводит кол-во параметров функции в строку
					stack.top().lexema = buf[0];//число параметров вызываемой функции
					stack.top().idxTI = LT_TI_NULLIDX;//вызов не на что не ссылается
					stack.top().line = function_symbol.line;//на вверх стека кладём линию
					queue.push(stack.top());
					stack.pop();
					parm_counter = 0;
					is_function = false;
				} //по итогу в очереди параметры @ -знак вызова функции и количество параметров
				continue;

			case LEX_OPERATOR:
				while (!stack.empty() && lex.lextable.table[i].priority <= stack.top().priority) {
					queue.push(stack.top());//пока в вершине стека приоритетность больше приоритетность больше чем то что хочем положить всё в очередь и выкидываем со стека
					stack.pop();
				}
				stack.push(lex.lextable.table[i]);//теперь кладём
				continue;
			}
		}

		while (!stack.empty()) {
			if (stack.top().lexema == LEX_LEFTTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
				return false;

			queue.push(stack.top());
			stack.pop();
		}

		while (lexem_counter != 0) {
			if (!queue.empty()) {
				lex.lextable.table[lexem_position++] = queue.front();//в табл лесем записываем нашу выходную строку по 1 влхждению
				queue.pop();
			}
			else
				lex.lextable.table[lexem_position++] = aggregate_symbol;//кладём на пустые места агрегатные символы

			lexem_counter--;
		}
		std::cout << std::endl;//удалить

		for (int i = 0; i < lexem_position; i++) {
			if (lex.lextable.table[i].lexema == LEX_OPERATOR || lex.lextable.table[i].lexema == LEX_LITERAL)//проверить у сани
				lex.idtable.table[lex.lextable.table[i].idxTI].idxFirstLE = i;//меняем ссылку символа структуры таблицы идентификатор  на соответвующую структуру в таблице лексем
		}//

		return true;
	}

	void startPolish(Lex::LEX& lex) {
		for (int i = 0; i < lex.lextable.size; i++) {
			if (lex.lextable.table[i].lexema == '=') {
				polishNotation(i + 1, lex);
			}
			else if (lex.lextable.table[i].lexema == LEX_ID && lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::PROC && lex.lextable.table[i - 1].lexema != LEX_VOID) {//при вызове процедуры
				polishNotation(i, lex);
			}
		}
	}
}