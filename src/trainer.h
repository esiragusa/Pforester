#ifndef PFORESTER_TRAINER_INCLUDED
#define PFORESTER_TRAINER_INCLUDED

#include "gramset.h"
#include "forest.h"
#include "envelope.h"

class Pforester_trainer {
private:
	Pforester_database& forest;
	Pforester_gramset& gramset;

public:
	Pforester_trainer(Pforester_database& forest, Pforester_gramset& gramset);
	void train_pairwise(double min_inc = .001, int max_rounds = -1, int forgive = 0);
};

#endif /* PFORESTER_TRAINER_INCLUDED */
