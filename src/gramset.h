#ifndef PFORESTER_GRAMSET_INCLUDED
#define PFORESTER_GRAMSET_INCLUDED

#include "pcfg.h"

// Pforester grammar set
struct Pforester_gramset {
	const Alphabet& alphabet;

	Pforester_pscores* pscores;
	Pforester_PCFG* pcfg;
	Dirichlet_prior* prior;

	Pforester_gramset() : alphabet(Pforester_alphabet) { };
	~Pforester_gramset();
};

class Pforester_gramset_builder {
public:
	static Pforester_gramset* build_gramset(Pforester_params* params);
};

#endif /* PFORESTER_GRAMSET_INCLUDED */
