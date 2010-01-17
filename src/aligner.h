#ifndef FOREST_ALIGNER_INCLUDED
#define FOREST_ALIGNER_INCLUDED

#include "gramset.h"
#include "forest.h"
#include "envelope.h"

class Pforester_aligner
{
private:
	Pforester_database& forest;
	Pforester_gramset& gramset;

public:
	Pforester_aligner(Pforester_database& forest, Pforester_gramset& gramset);
	void align_pairwise(bool local = false, int max_hits = 1);
};

#endif /* FOREST_ALIGNER_INCLUDED */
