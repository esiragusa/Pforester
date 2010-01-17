#include "pforester.h"

Pforester::Pforester(int argc, char** argv) :
	opts(argc, argv) { }

Pforester::~Pforester()
{
	delete gramset;
	delete params;
}

void Pforester::init_opts() {
	INIT_CONSTRUCTED_OPTS_LIST (opts, -1, "[options] <sequence file(s)>",
			"RNAforester probabilistic clone using Pair SCFGs");

	opts.print_title("General options");
	opts.add("t -train", train = false, "train a grammar on pairs of RNA secondary structures");
	opts.add("a -align", align = false, "align pairs of RNA secondary structures");
	//opts.add("g -generate", generate = false, "generate pairwise alignments of RNA secondary structures");
	opts.newline();

	opts.print_title("Grammar options");
	opts.add("lp -loadparams", loadparams = "", "load grammar parameters from a file", false);
	opts.add("sp -saveparams", saveparams = "", "save grammar parameters to a file", false);
	opts.add("-structure", structure = true, "pure structure alignment scoring scheme", true, "-ribosum", "RIBOSUM scoring scheme");
	opts.add("-linear", linear = true, "linear gap model", true, "-affine", "affine gap model");
	opts.newline();

	opts.print_title("Alignment options");
	opts.add("as -alignmentset", alignmentset = "", "RNA secondary structures file (FlatForest format)", false);
	opts.add("-local", local = false, "force local alignment", true, "-global", "force global alignment");
	opts.newline();

//	opts.print_title("Generation options");
//	opts.newline();

	opts.print_title("Training options");
	opts.add("ts -trainingset", trainingset = "", "RNA secondary structures file (FlatForest format)", false);
	opts.add("mr -maxrounds", em_max_iter = -1, "max number of rounds (iterations) of EM", false);
	opts.add("mi -mininc", em_min_inc = .001, "minimum fractional increase in log-likelihood per round of EM");
	opts.add("f -forgive", em_forgive = 0, "number of non-increasing rounds of EM to forgive");
	opts.newline();
}

void Pforester::parse_opts() {
	opts.parse_or_die();
}

void Pforester::load_params() {
	if (linear)
		params = new Pforester_params_linear();
	else
		params = new Pforester_params_affine();

	if (loadparams.size()) {
		ifstream params_file(loadparams.c_str());
		if (!params_file)
			THROWEXPR ("Parameter-set file'" << loadparams << "' not loaded");
		params->read_params(params_file);
	}
}

void Pforester::init_gramset() {
	gramset = Pforester_gramset_builder::build_gramset(params);
}

void Pforester::save_params() {
	if (saveparams.size()) {
		ofstream params_file(saveparams.c_str());
		if (!params_file)
			THROWEXPR ("Parameter-set file'" << saveparams << "' not saved");
		params->write_params(params_file);
	}
}

void Pforester::run_trainer() {
	if (trainingset.size()) {
		Pforester_database train_db(gramset->alphabet);
		Sequence_database seq_db;

		CTAG(6, RNAFORESTER) << "Training grammar parameters from file '" << trainingset << "'\n";

		// read in forest alignments
		ifstream stk_db_file(trainingset.c_str());
		if (!stk_db_file)
			THROWEXPR ("Flat Forest training database '" << trainingset << "' not found");
		train_db.read(stk_db_file, seq_db);

		// fit null model to training sequences before starting EM
		// (this prevents the first round of training being dominated by the null model)
		//gramset->pscores.set_null_model(seq_db, scfg.cfg.null_emit, scfg.cfg.null_extend);

		// do EM
		Pforester_trainer trainer(train_db, *gramset);
		trainer.train_pairwise(em_min_inc, em_max_iter, em_forgive);

		// update initial params
		gramset->pscores->update_params(*params);
	}
}

void Pforester::run_aligner() {
	if (alignmentset.size()) {
		Pforester_database align_db(gramset->alphabet);
		FASTA_sequence_database seq_db;

		CTAG(6, RNAFORESTER) << "Building pairwise alignments from file '" << alignmentset << "'\n";

		ifstream stk_db_file(alignmentset.c_str());
		if (!stk_db_file)
			THROWEXPR ("Flat Forest alignment database '" << alignmentset << "' not found");
		align_db.read(stk_db_file, seq_db);

		// check names are unique
		seq_db.index.assert_names_unique(true);

		// update the sequence database index
		seq_db.update_index();
		seq_db.update_alphabet(&(gramset->alphabet));
		seq_db.seqs_update(gramset->alphabet, (Profile_flags_enum::Profile_flags) (Profile_flags_enum::DSQ
				| Profile_flags_enum::SCORE));

		// initialise null model
		//null_emit_prob = vector<Prob> (gramset->alphabet.size(), 1. / (double) gramset->alphabet.size()); // default null model
		// get the null model
		//null_emit_prob = seq_db.get_null_model(gramset->alphabet.size());

		// do CYK
		Pforester_aligner aligner(align_db, *gramset);
		aligner.align_pairwise(local);
	}
}

int Pforester::run() {
	try {
		init_opts();
		parse_opts();
		load_params();
		init_gramset();

		if (train)
			run_trainer();

		if (align)
			run_aligner();

		save_params();

	} catch (const Dart_exception& e) {
		CLOGERR << e.what();
		exit(1);
	}

	return 0;
}
