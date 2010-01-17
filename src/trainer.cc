#include "trainer.h"

Pforester_trainer::Pforester_trainer(Pforester_database& forest, Pforester_gramset& gramset) :
	forest(forest), gramset(gramset) {
}

void Pforester_trainer::train_pairwise(double min_inc, int max_rounds, int forgive) {
	// print initial log message
	if (CTAGGING(3,TRAINER)) {
		CL << "Training the following pair CFG by EM:\n";
		gramset.pcfg->show(CL);
		CL << "PScores before EM:\n";
		gramset.pscores->show(CL);
	}

	// check alignment database isn't empty
	if (forest.size() == 0)
		THROWEXPR ("Forest alignment database is empty");

	// do EM
	Loge prev_loglike = -InfinityLoge;
	int dec = 0;

	for (int round = 0;; ++round) {
		// check if max no. of rounds reached
		if (max_rounds > 0 && round >= max_rounds) {
			CTAG(5,TRAINER) << "Stopping after " << round << " rounds of EM\n";
			break;
		}
		CTAG(5,TRAINER) << "Beginning EM round " << round + 1 << "\n";

		// create Pair_CFG_scores for current parameters
		const Pair_CFG_scores cfg_scores = gramset.pcfg->eval_cfg_scores(*(gramset.pscores));

		if (CTAGGING(4,TRAINER)) {
			CL << "Pair CFG for EM round " << round + 1 << ":\n";
			cfg_scores.show(CL);
		}

		// accumulate counts for whole database
		PCounts pcounts(*(gramset.pscores));
		Loge total_loglike = 0;
		int n_align = 0;


		for_contents (list<Pforester_alignment>, forest.align, falign) {
			++n_align; // update counter

			// check that forest alignment is pairwise
			if (falign->rows() < 2) {
				CTAG(5,TRAINER) << "Warning: forest alignment " << n_align << " has " << falign->rows()
						<< " rows; skipping\n";
				continue;
			} else if (falign->rows() > 2)
				CTAG(5,TRAINER) << "Warning: forest alignment " << n_align << " has " << falign->rows()
						<< " rows; I will only use the first two\n";


			const Named_profile& npx = falign->get_np(0);
			const Named_profile& npy = falign->get_np(1);

			// create and init fold envelopes
			Pforester_envelope envx, envy;
			envx.initialise_from_flatforest(npx.seq);
			envy.initialise_from_flatforest(npy.seq);


			// fill inside-outside matrix; add final score; accumulate counts for this alignment
			Pair_inside_outside_matrix inout(npx, npy, envx, envy, cfg_scores, FALSE);

			const Score sc = inout.inside.final_score;
			const double weight = falign->get_alignment_weight();

			if (sc > -InfinityScore) {
				CTAG(5,TRAINER) << "Adding counts for alignment " << n_align << ": '" << npx.name << "' vs '"
						<< npy.name << "' (log-likelihood " << Score2Bits(sc) << " bits; alignment weight is "
						<< weight << ")\n";
				NatsPMulAcc (total_loglike, Score2Nats(sc) * weight);
				gramset.pcfg->inc_var_counts(pcounts, *(gramset.pscores), inout.count, weight);

				if (CTAGGING(-1,CFG_CUMULATIVE_PCOUNTS)) {
					CL << "Cumulative PVar counts:\n";
					pcounts.show(CL);
				}
			}
		}

		// report counts & score; check for improvement
		CTAG(5,TRAINER) << "Total (weighted) log-likelihood is " << Nats2Bits(total_loglike) << " bits\n";
		if (CTAGGING(4,TRAINER)) {
			CL << "Parameter counts:\n";
			pcounts.show(CL);
		}

		const double inc = abs((total_loglike - prev_loglike) / (abs(prev_loglike) < TINY ? 1. : prev_loglike));
		if (total_loglike <= prev_loglike || inc < min_inc) {
			if (total_loglike < prev_loglike)
				CTAG(7,TRAINER) << "Warning: log-likelihood dropped from " << Nats2Bits(prev_loglike) << " to "
						<< Nats2Bits(total_loglike) << " bits during EM\n";
			if (++dec > forgive) {
				CTAG(7,TRAINER) << "Failed EM improvement threshold for the " << dec << "th time; stopping\n";
				break;
			}
		} else
			dec = 0;

		prev_loglike = total_loglike;

		// use Dirichlet prior to update PScores
		gramset.prior->pscores = gramset.pscores;
		gramset.prior->optimise(pcounts);
	}
}
