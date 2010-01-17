#ifndef PFORESTERER_INCLUDED
#define PFORESTERER_INCLUDED

#include "forest.h"
#include "gramset.h"
#include "trainer.h"
#include "aligner.h"

class Pforester {
private:
	// option list
	Opts_list opts;

	// params
	Pforester_params* params;

	// gramset
	Pforester_gramset* gramset;

	// gramset options
	sstring loadparams;
	sstring saveparams;
	bool structure;
	bool linear;

	// run-time options
	bool train;
	bool align;
	//bool generate;

	// sequence files
	sstring trainingset;
	sstring alignmentset;

	// alignment options
	bool local;

	// em-training options
	double em_min_inc;
	int em_max_iter;
	int em_forgive;

	// private methods
	void init_opts();
	void parse_opts();
	void load_params();
	void init_gramset();
	void save_params();
	void run_trainer();
	void run_aligner();
	//void run_generator();

public:
	// run method
	int run();

	// constructor
	Pforester(int argc, char** argv);

	// destructor
	~Pforester();
};

#endif /* PFORESTERER_INCLUDED */
