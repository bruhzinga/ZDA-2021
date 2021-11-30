#include "stdafx.h"
#include "FST.h"

namespace FST {
	RELATION::RELATION(char c, short ns) {
		symbol = c;
		nnode = ns;
	}

	NODE::NODE() {
		n_relation = 0;
		relations = NULL;
	}

	NODE::NODE(short n, RELATION rel, ...) {
		n_relation = n;
		RELATION* ptr = &rel;
		relations = new RELATION[n_relation];
		for (int i = 0; i < n_relation; i++) {
			relations[i] = ptr[i];
		}
	}
	
	FST::FST(char* s, short ns, NODE n, ...) {
		//string = s;
		//position = -1; // p = 0
		//nstates = ns;

		//rstates = new short[nstates];
		//NODE* ptr = &n;
		//nodes = new NODE[nstates];
		//for (int i = 0; i < nstates; i++) {
		//	rstates[i] = 0;
		//	nodes[i] = ptr[i];
		//}

		string = s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE* p = &n;
		for (int k = 0; k < ns; k++)
			nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
	}
	
	bool step(FST& fst, short*& rstates) {
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (int i = 0; i < fst.nstates; i++) {
			if (rstates[i] == fst.position) {
				for (int j = 0; j < fst.nodes[i].n_relation; j++) {
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) {
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				}
			}
		}
		return rc;
	}

	bool execute(FST fst) {
		short* rstates = new short[fst.nstates];			// массив размера nstates
		memset(rstates, 0xff, sizeof(short) * fst.nstates); // заполняется нулями

		short length = strlen(fst.string);
		bool rc = true;
		for (int i = 0; i < length && rc; i++) {
			fst.position++;
			rc = step(fst, rstates);
		}
		delete[] rstates;

		return (rc ? (fst.rstates[fst.nstates - 1] == length) : rc);
	}
}
