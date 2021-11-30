#include"Error.h"
namespace Error {
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Íåäîïóñòèìûé êîä îøèáêè"),
		ERROR_ENTRY(1, "Ñèñòåìíûé ñáîé"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Ïàğàìåòğ -in äîëæåí áûòü çàäàí"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Ïğåâûøåíà äëèíà âõîäíîãî ïàğàìåòğà"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)"),
		ERROR_ENTRY(111, "Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)"),
		ERROR_ENTRY(112, "Îøèáêà ïğè ñîçäàíèè ôàéëà ïğîòîêîëà (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "[ LEXICAL ] Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)"),
		ERROR_ENTRY(201, "[ LEXICAL ] Ïğåâûøåí ğàçìåğ òàáëèöû ëåêñåì"),
		ERROR_ENTRY(202, "[ LEXICAL ] Ïåğåïîëíåíèå òàáëèöû ëåêñåì"),
		ERROR_ENTRY(203, "[ LEXICAL ] Ïğåâûøåí ğàçìåğ òàáëèöû èäåíòèôèêàòîğîâ"),
		ERROR_ENTRY(204, "[ LEXICAL ] Ïåğåïîëíåíèå òàáëèöû èäåíòèôèêàòîğîâ"),
		ERROR_ENTRY(205, "[ LEXICAL ] Íåèçâåñòíàÿ ïîñëåäîâàòåëüíîñòü ñèìâîëîâ"),
		ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250),
		ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "[ SEMANTIC ] Èìååòñÿ íå çàêğûòûé ñòğîêîâûé ëèòåğàë"),							// -	
		ERROR_ENTRY(301, "[ SEMANTIC ] Èìååòñÿ áîëåå îäíîé òî÷êè âõîäà â main"),						// +	
		ERROR_ENTRY(302, "[ SEMANTIC ] Íå èìååòñÿ òî÷êè âõîäà â main"),									// +	
		ERROR_ENTRY(303, "[ SEMANTIC ] Ïğåâûøåí ğàçìåğ ñòğîêîâîãî ëèòåğàëà"),							// -	
		ERROR_ENTRY(304, "[ SEMANTIC ] Îáúÿâëåíèå ïåğåìåííîé áåç êëş÷åâîãî ñëîâà let"),					// -	
		ERROR_ENTRY(305, "[ SEMANTIC ] Íåîáúÿâëåííûé èäåíòèôèêàòîğ"),									// -	
		ERROR_ENTRY(306, "[ SEMANTIC ] Îáúâëåíèå ïåğåìåííîé áåç óêàçàíèÿ òèïà"),						// -											
		ERROR_ENTRY(307, "[ SEMANTIC ] Ïîïûòêà ğåàëèçîâàòü ñóùåñòâóşùóş ôóíêöèş"),						// +											
		ERROR_ENTRY(308, "[ SEMANTIC ] Îáúÿâëåíèå ôóíêöèè áåç óêàçàíèÿ òèïà"),							// -										
		ERROR_ENTRY(309, "[ SEMANTIC ] Íåñîâïàäåíèå òèïîâ ïåğåäàâàåìûõ ïàğàìåòğîâ ôóíêöèè"),			// -					
		ERROR_ENTRY(310, "[ SEMANTIC ] Íåñîîòâåòñòâèå àğèôìåòè÷åñêèõ îïåğàòîğîâ"),						// -											
		ERROR_ENTRY(311, "[ SEMANTIC ] Íåâîçìîæíî äåëåíèå íà íîëü"),									// -								
		ERROR_ENTRY(312, "[ SEMANTIC ] Íåñîîòâåòñâèå òèïîâ äàííûõ"),									// +							
		ERROR_ENTRY(313, "[ SEMANTIC ] Íåñîîòâåòñâèå îòêğûòûõ è çàêğûòûõ ñêîáîê â âûğàæåíèè"),			// -								
		ERROR_ENTRY(314, "[ SEMANTIC ] Ôóíêöèÿ âîçâğàùàåò íåâåğíûé òèï äàííûõ"),						// +								
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id) {
		if (id > 0 && id < ERROR_MAX_ENTRY) {
			return errors[id];
		} else {
			return errors[0];
		}
	}
	ERROR geterrorin(int id, int line = -1, int col = -1) {
		if (id > 0 && id < ERROR_MAX_ENTRY) {
			errors[id].inext.col = col;
			errors[id].inext.line = line;
			return errors[id];
		}
		else {
			return errors[0];
		}
	}
}