#include "aligner.h"

Pforester_aligner::Pforester_aligner(Pforester_database& forest, Pforester_gramset& gramset) :
	forest(forest), gramset(gramset) {
}

void Pforester_aligner::align_pairwise(bool local, int max_hits) {
	// create Pair_CFG_scores for current parameters
	const Pair_CFG_scores cfg_scores = gramset.pcfg->eval_cfg_scores(*(gramset.pscores));

	// loop through sequence database, do CYK algorithm on all sequence pairs
	for_contents (list<Pforester_alignment>, forest.align, falign) {
		// get sequences
		const Named_profile& npx = falign->get_np(0);
		const Named_profile& npy = falign->get_np(1);

		// create and init fold envelopes
		Pforester_envelope envx, envy;
		envx.initialise_from_flatforest(npx.seq);
		envy.initialise_from_flatforest(npy.seq);


		// print log message
		CTAG(6, ALIGNER) << "Aligning '" << npx.name << "' and '" << npy.name << "'\n";

		// do CYK with Waterman-Eggert style blocking
		int hit = 0;
		while (1) {
			if (++hit > max_hits) {
				CTAG(5, ALIGNER) << "Reported " << max_hits << " alignments for this sequence-pair; stopping\n";
				break;
			}
			CTAG(5, ALIGNER) << "Finding alignment #" << hit << " for '" << npx.name << "' and '" << npy.name
					<< "'\n";

			// build the DP matrix
			const Pair_CYK_matrix cyk(npx, npy, envx, envy, cfg_scores, local);
			if (CTAGGING(1, ALIGNER))
				CL << cyk.cfg_dump();

			// test for -inf score
			if (cyk.final_score == -InfinityScore && hit == 1) {
				CLOGERR << "Warning: alignment score for '" << npx.name << "' and '" << npy.name
						<< "' is -infinity; skipping.\n";
				break;
			}

			// get alignment
			const Pair_CFG_alignment cyk_alignment = cyk.alignment();
			//Pforester_alignment alignment = new Pforester_alignment(cyk_alignment);

/*
			// check if hit is worth reporting
			if (Score2Bits(cyk.final_score) < min_bitscore) {
				CTAG(5, ALIGNER) << "Score of " << Score2Bits(cyk.final_score) << " bits is below threshold of "
						<< min_bitscore << " bits; stopping\n";
				break;
			}
*/

			// output
			//Pforester_alignment alignment = new Pforester_alignment(cyk_alignment);
			//alignment.show(cout);
			cyk_alignment.show(cout);

			// do Waterman-Eggert style blocking-out
			//cyk_alignment.add_pairwise_path(pair_env, false);
		}

	}
}
