#include "Div.h"

void cleanup(char source[], int size, Log::LOG logfile) {
	char Separators[] = { " ,;(){}=+-*/|" };
	bool findLiteral = false;
	int count = NULL;

	for (int i = 0; i < size; i++) {
		if (source[i] == '\'') {
			findLiteral = !findLiteral;
			count++;
		}
		
		if ((source[i] == ' ' || source[i] == '\t') && !findLiteral) {
			for (int j = 0; j < sizeof(Separators) - 1; j++) {
				if (source[i + 1] == Separators[j] || source[i - 1] == Separators[j] || i == 0) {
					for (int k = i; k < size; k++) {
						source[k] = source[k + 1];
					}
					i--;
					break;
				}
			}
		}
	}

	if (count % 2 != 0)
		Log::WriteError(logfile, Error::geterror(300));
}

char** divideText(char source[], int size)
{
	char** word = new char* [max_word];
	for (int i = 0; i < max_word; i++) {
		word[i] = new char[size_word] {NULL};
	}

	bool findSeparator, findLiteral = false;
	int j = 0;
	char Separators[] = { " ,;(){}=+-*/|" };
	for (int i = 0, k = 0; i < size - 1; i++, k++) {
		findSeparator = false;
		if (source[i] == '\'') findLiteral = !findLiteral;
		for (int t = 0; t < sizeof(Separators) - 1; t++) {
			if (source[i] == Separators[t] && !findLiteral) {
				findSeparator = true;
				if (word[j][0] != NULL) { 
					word[j++][k] = '\0';
					k = 0;
				}
				if (Separators[t] == ' ') {
					k = -1;
					break;
				}
				word[j][k++] = Separators[t];
				word[j++][k] = '\0';
				k = -1;
				break;
			}
		}

		if (!findSeparator) word[j][k] = source[i];
	}

	word[j] = NULL;
	for (int i = 0; i < j; i++) {
		if (!strcmp((char*)word[i], "")) return NULL;
	}

	return word;
}