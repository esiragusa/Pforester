#include "gramset.h"

Pforester_gramset::~Pforester_gramset() {
	delete prior;
	delete pcfg;
	delete pscores;
}

Pforester_gramset* Pforester_gramset_builder::build_gramset(Pforester_params* params) {
	Pforester_gramset* gramset;

	gramset = new Pforester_gramset();

	if (dynamic_cast<Pforester_params_affine *> (params)) {
		Pforester_params_affine* aparams = dynamic_cast<Pforester_params_affine *> (params);
		Pforester_pscores_affine* apscores = new Pforester_pscores_affine(*aparams);
		gramset->pscores = apscores;
		gramset->pcfg = new Pforester_PCFG_affine(*apscores);
	} else {
		Pforester_params_linear* lparams = dynamic_cast<Pforester_params_linear *> (params);
		Pforester_pscores_linear* lpscores = new Pforester_pscores_linear(*lparams);
		gramset->pscores = lpscores;
		gramset->pcfg = new Pforester_PCFG_linear(*lpscores);
	}

	gramset->prior = new Dirichlet_prior(gramset->pcfg->default_prior());

	return gramset;
}
