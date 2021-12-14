#pragma once
#include "stdafx.h"
#include "Parm.h"
#include "LT.h"
#include "IT.h"

namespace Gen {
#define OutName "C:/Users/Dima/Desktop/KURSACH/ZDA-2021/ASM/output.asm"
	struct Generator {
		LT::LexTable lexT;
		IT::IdTable idT;
		std::ofstream out;

		Generator(LT::LexTable plexT, IT::IdTable pidT);

		void Head();
		void Const();
		void Data();
		void Code();
	};
}