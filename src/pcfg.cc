#include "pcfg.h"

void Pforester_params_linear::write_params(ostream& out) const {
	out << sigma_pp << " ";
	out << sigma_p_ << " ";
	out << sigma__p << " ";
	out << sigma_bb << " ";
	out << sigma_b_ << " ";
	out << sigma__b << "\n";

	out << pmu << "\n";
	out << mu << "\n";

	out << f_end << "\n";
}

void Pforester_params_linear::read_params(istream& in) {
	in >> sigma_pp;
	in >> sigma_p_;
	in >> sigma__p;
	in >> sigma_bb;
	in >> sigma_b_;
	in >> sigma__b;

	in >> pmu;
	in >> mu;

	in >> f_end;
}

void Pforester_params_affine::write_params(ostream& out) const {
	out << sigma_nn_pp << " ";
	out << sigma_nn_p_ << " ";
	out << sigma_nn__p << " ";
	out << sigma_nn_bb << " ";
	out << sigma_nn_b_ << " ";
	out << sigma_nn__b << "\n";

	out << sigma_pn_pp << " ";
	out << sigma_pn_p_ << " ";
	out << sigma_pn__p << " ";
	out << sigma_pn_bb << " ";
	out << sigma_pn_b_ << " ";
	out << sigma_pn__b << "\n";

	out << sigma_sn_pp << " ";
	out << sigma_sn_p_ << " ";
	out << sigma_sn__p << " ";
	out << sigma_sn_bb << " ";
	out << sigma_sn_b_ << " ";
	out << sigma_sn__b << "\n";

	out << sigma_ps_pp << " ";
	out << sigma_ps_p_ << " ";
	out << sigma_ps__p << " ";
	out << sigma_ps_bb << " ";
	out << sigma_ps_b_ << " ";
	out << sigma_ps__b << "\n";

	out << sigma_np_pp << " ";
	out << sigma_np_p_ << " ";
	out << sigma_np__p << " ";
	out << sigma_np_bb << " ";
	out << sigma_np_b_ << " ";
	out << sigma_np__b << "\n";

	out << sigma_ns_pp << " ";
	out << sigma_ns_p_ << " ";
	out << sigma_ns__p << " ";
	out << sigma_ns_bb << " ";
	out << sigma_ns_b_ << " ";
	out << sigma_ns__b << "\n";

	out << sigma_sp_pp << " ";
	out << sigma_sp_p_ << " ";
	out << sigma_sp__p << " ";
	out << sigma_sp_bb << " ";
	out << sigma_sp_b_ << " ";
	out << sigma_sp__b << "\n";

	out << pmu << "\n";
	out << mu << "\n";

	out << f_end << "\n";
}

void Pforester_params_affine::read_params(istream& in) {
	in >> sigma_nn_pp;
	in >> sigma_nn_p_;
	in >> sigma_nn__p;
	in >> sigma_nn_bb;
	in >> sigma_nn_b_;
	in >> sigma_nn__b;

	in >> sigma_pn_pp;
	in >> sigma_pn_p_;
	in >> sigma_pn__p;
	in >> sigma_pn_bb;
	in >> sigma_pn_b_;
	in >> sigma_pn__b;

	in >> sigma_sn_pp;
	in >> sigma_sn_p_;
	in >> sigma_sn__p;
	in >> sigma_sn_bb;
	in >> sigma_sn_b_;
	in >> sigma_sn__b;

	in >> sigma_ps_pp;
	in >> sigma_ps_p_;
	in >> sigma_ps__p;
	in >> sigma_ps_bb;
	in >> sigma_ps_b_;
	in >> sigma_ps__b;

	in >> sigma_np_pp;
	in >> sigma_np_p_;
	in >> sigma_np__p;
	in >> sigma_np_bb;
	in >> sigma_np_b_;
	in >> sigma_np__b;

	in >> sigma_ns_pp;
	in >> sigma_ns_p_;
	in >> sigma_ns__p;
	in >> sigma_ns_bb;
	in >> sigma_ns_b_;
	in >> sigma_ns__b;

	in >> sigma_sp_pp;
	in >> sigma_sp_p_;
	in >> sigma_sp__p;
	in >> sigma_sp_bb;
	in >> sigma_sp_b_;
	in >> sigma_sp__b;

	in >> pmu;
	in >> mu;

	in >> f_end;
}

Pforester_pscores::Pforester_pscores(const Pforester_params& params) :
	PScores(),
	f_end(new_boolean_group("f_end"))
{ }

Pforester_pscores_linear::Pforester_pscores_linear(const Pforester_params_linear& params) :
	Pforester_pscores(params),
	sigma(new_group("sigma", "pp p_ _p bb b_ _b")),
	pmu(new_boolean_group("pmu")),
	mu(new_boolean_group("mu"))
{
	init_from_params(params);
}

void Pforester_pscores_linear::init_from_params(const Pforester_params_linear& params) {
	PScores& sc(*this);

	sc[sigma[0]] = Prob2Score (params.sigma_pp);
	sc[sigma[1]] = Prob2Score (params.sigma_p_);
	sc[sigma[2]] = Prob2Score (params.sigma__p);
	sc[sigma[3]] = Prob2Score (params.sigma_bb);
	sc[sigma[4]] = Prob2Score (params.sigma_b_);
	sc[sigma[5]] = Prob2Score (params.sigma__b);

	sc[pmu.y] = Prob2Score (params.pmu);
	sc[pmu.n] = Prob2Score (1. - params.pmu);

	sc[mu.y] = Prob2Score (params.mu);
	sc[mu.n] = Prob2Score (1. - params.mu);

	sc[f_end.y] = Prob2Score (params.f_end);
	sc[f_end.n] = Prob2Score (1. - params.f_end);
}

void Pforester_pscores_linear::update_params(Pforester_params& params) const {
	const PScores& sc(*this);
	Pforester_params_linear* lsparams = dynamic_cast <Pforester_params_linear *> (&params);

	lsparams->sigma_pp = Score2Prob (sc[sigma[0]]);
	lsparams->sigma_p_ = Score2Prob (sc[sigma[1]]);
	lsparams->sigma__p = Score2Prob (sc[sigma[2]]);
	lsparams->sigma_bb = Score2Prob (sc[sigma[3]]);
	lsparams->sigma_b_ = Score2Prob (sc[sigma[4]]);
	lsparams->sigma__b = Score2Prob (sc[sigma[5]]);

	lsparams->pmu = Score2Prob (sc[pmu.y]);
	lsparams->mu = Score2Prob (sc[mu.y]);

	lsparams->f_end = Score2Prob (sc[f_end.y]);
}

Pforester_pscores_affine::Pforester_pscores_affine(const Pforester_params_affine& params) :
	Pforester_pscores(params),
	sigma_nn(new_group("sigma_nn", "pp p_ _p bb b_ _b")),
	sigma_pn(new_group("sigma_pn", "pp p_ _p bb b_ _b")),
	sigma_sn(new_group("sigma_sn", "pp p_ _p bb b_ _b")),
	sigma_ps(new_group("sigma_ps", "pp p_ _p bb b_ _b")),
	sigma_np(new_group("sigma_np", "pp p_ _p bb b_ _b")),
	sigma_ns(new_group("sigma_ns", "pp p_ _p bb b_ _b")),
	sigma_sp(new_group("sigma_sp", "pp p_ _p bb b_ _b")),
	pmu(new_boolean_group("pmu")),
	mu(new_boolean_group("mu"))
{
	init_from_params(params);
}

void Pforester_pscores_affine::init_from_params(const Pforester_params_affine& params) {
	PScores& sc(*this);

	sc[sigma_nn[0]] = Prob2Score (params.sigma_nn_pp);
	sc[sigma_nn[1]] = Prob2Score (params.sigma_nn_p_);
	sc[sigma_nn[2]] = Prob2Score (params.sigma_nn__p);
	sc[sigma_nn[3]] = Prob2Score (params.sigma_nn_bb);
	sc[sigma_nn[4]] = Prob2Score (params.sigma_nn_b_);
	sc[sigma_nn[5]] = Prob2Score (params.sigma_nn__b);

	sc[sigma_pn[0]] = Prob2Score (params.sigma_pn_pp);
	sc[sigma_pn[1]] = Prob2Score (params.sigma_pn_p_);
	sc[sigma_pn[2]] = Prob2Score (params.sigma_pn__p);
	sc[sigma_pn[3]] = Prob2Score (params.sigma_pn_bb);
	sc[sigma_pn[4]] = Prob2Score (params.sigma_pn_b_);
	sc[sigma_pn[5]] = Prob2Score (params.sigma_pn__b);

	sc[sigma_sn[0]] = Prob2Score (params.sigma_sn_pp);
	sc[sigma_sn[1]] = Prob2Score (params.sigma_sn_p_);
	sc[sigma_sn[2]] = Prob2Score (params.sigma_sn__p);
	sc[sigma_sn[3]] = Prob2Score (params.sigma_sn_bb);
	sc[sigma_sn[4]] = Prob2Score (params.sigma_sn_b_);
	sc[sigma_sn[5]] = Prob2Score (params.sigma_sn__b);

	sc[sigma_ps[0]] = Prob2Score (params.sigma_ps_pp);
	sc[sigma_ps[1]] = Prob2Score (params.sigma_ps_p_);
	sc[sigma_ps[2]] = Prob2Score (params.sigma_ps__p);
	sc[sigma_ps[3]] = Prob2Score (params.sigma_ps_bb);
	sc[sigma_ps[4]] = Prob2Score (params.sigma_ps_b_);
	sc[sigma_ps[5]] = Prob2Score (params.sigma_ps__b);

	sc[sigma_np[0]] = Prob2Score (params.sigma_np_pp);
	sc[sigma_np[1]] = Prob2Score (params.sigma_np_p_);
	sc[sigma_np[2]] = Prob2Score (params.sigma_np__p);
	sc[sigma_np[3]] = Prob2Score (params.sigma_np_bb);
	sc[sigma_np[4]] = Prob2Score (params.sigma_np_b_);
	sc[sigma_np[5]] = Prob2Score (params.sigma_np__b);

	sc[sigma_ns[0]] = Prob2Score (params.sigma_ns_pp);
	sc[sigma_ns[1]] = Prob2Score (params.sigma_ns_p_);
	sc[sigma_ns[2]] = Prob2Score (params.sigma_ns__p);
	sc[sigma_ns[3]] = Prob2Score (params.sigma_ns_bb);
	sc[sigma_ns[4]] = Prob2Score (params.sigma_ns_b_);
	sc[sigma_ns[5]] = Prob2Score (params.sigma_ns__b);

	sc[sigma_sp[0]] = Prob2Score (params.sigma_sp_pp);
	sc[sigma_sp[1]] = Prob2Score (params.sigma_sp_p_);
	sc[sigma_sp[2]] = Prob2Score (params.sigma_sp__p);
	sc[sigma_sp[3]] = Prob2Score (params.sigma_sp_bb);
	sc[sigma_sp[4]] = Prob2Score (params.sigma_sp_b_);
	sc[sigma_sp[5]] = Prob2Score (params.sigma_sp__b);

	sc[pmu.y] = Prob2Score (params.pmu);
	sc[pmu.n] = Prob2Score (1. - params.pmu);

	sc[mu.y] = Prob2Score (params.mu);
	sc[mu.n] = Prob2Score (1. - params.mu);

	sc[f_end.y] = Prob2Score (params.f_end);
	sc[f_end.n] = Prob2Score (1. - params.f_end);
}

void Pforester_pscores_affine::update_params(Pforester_params& params) const {
	const PScores& sc(*this);
	Pforester_params_affine* asparams = dynamic_cast <Pforester_params_affine *> (&params);

	asparams->sigma_nn_pp = Score2Prob (sc[sigma_nn[0]]);
	asparams->sigma_nn_p_ = Score2Prob (sc[sigma_nn[1]]);
	asparams->sigma_nn__p = Score2Prob (sc[sigma_nn[2]]);
	asparams->sigma_nn_bb = Score2Prob (sc[sigma_nn[3]]);
	asparams->sigma_nn_b_ = Score2Prob (sc[sigma_nn[4]]);
	asparams->sigma_nn__b = Score2Prob (sc[sigma_nn[5]]);

	asparams->sigma_pn_pp = Score2Prob (sc[sigma_pn[0]]);
	asparams->sigma_pn_p_ = Score2Prob (sc[sigma_pn[1]]);
	asparams->sigma_pn__p = Score2Prob (sc[sigma_pn[2]]);
	asparams->sigma_pn_bb = Score2Prob (sc[sigma_pn[3]]);
	asparams->sigma_pn_b_ = Score2Prob (sc[sigma_pn[4]]);
	asparams->sigma_pn__b = Score2Prob (sc[sigma_pn[5]]);

	asparams->sigma_sn_pp = Score2Prob (sc[sigma_sn[0]]);
	asparams->sigma_sn_p_ = Score2Prob (sc[sigma_sn[1]]);
	asparams->sigma_sn__p = Score2Prob (sc[sigma_sn[2]]);
	asparams->sigma_sn_bb = Score2Prob (sc[sigma_sn[3]]);
	asparams->sigma_sn_b_ = Score2Prob (sc[sigma_sn[4]]);
	asparams->sigma_sn__b = Score2Prob (sc[sigma_sn[5]]);

	asparams->sigma_ps_pp = Score2Prob (sc[sigma_ps[0]]);
	asparams->sigma_ps_p_ = Score2Prob (sc[sigma_ps[1]]);
	asparams->sigma_ps__p = Score2Prob (sc[sigma_ps[2]]);
	asparams->sigma_ps_bb = Score2Prob (sc[sigma_ps[3]]);
	asparams->sigma_ps_b_ = Score2Prob (sc[sigma_ps[4]]);
	asparams->sigma_ps__b = Score2Prob (sc[sigma_ps[5]]);

	asparams->sigma_np_pp = Score2Prob (sc[sigma_np[0]]);
	asparams->sigma_np_p_ = Score2Prob (sc[sigma_np[1]]);
	asparams->sigma_np__p = Score2Prob (sc[sigma_np[2]]);
	asparams->sigma_np_bb = Score2Prob (sc[sigma_np[3]]);
	asparams->sigma_np_b_ = Score2Prob (sc[sigma_np[4]]);
	asparams->sigma_np__b = Score2Prob (sc[sigma_np[5]]);

	asparams->sigma_ns_pp = Score2Prob (sc[sigma_ns[0]]);
	asparams->sigma_ns_p_ = Score2Prob (sc[sigma_ns[1]]);
	asparams->sigma_ns__p = Score2Prob (sc[sigma_ns[2]]);
	asparams->sigma_ns_bb = Score2Prob (sc[sigma_ns[3]]);
	asparams->sigma_ns_b_ = Score2Prob (sc[sigma_ns[4]]);
	asparams->sigma_ns__b = Score2Prob (sc[sigma_ns[5]]);

	asparams->sigma_sp_pp = Score2Prob (sc[sigma_sp[0]]);
	asparams->sigma_sp_p_ = Score2Prob (sc[sigma_sp[1]]);
	asparams->sigma_sp__p = Score2Prob (sc[sigma_sp[2]]);
	asparams->sigma_sp_bb = Score2Prob (sc[sigma_sp[3]]);
	asparams->sigma_sp_b_ = Score2Prob (sc[sigma_sp[4]]);
	asparams->sigma_sp__b = Score2Prob (sc[sigma_sp[5]]);


	asparams->pmu = Score2Prob (sc[pmu.y]);
	asparams->mu = Score2Prob (sc[mu.y]);

	asparams->f_end = Score2Prob (sc[f_end.y]);
}

void Pforester_PCFG::init_mutable_pgroups() {
	for (int g = first_pgroup_idx; g < pscores.pgroups(); ++g)
		mutable_pgroups.push_back (PGroup (g, pscores.group_size (g)));
}

Dirichlet_prior Pforester_PCFG::default_prior() const {
	// pseudocount for all Laplace priors
	const double k = .1;
	Dirichlet_prior prior(pscores);

	for_const_contents (vector<PGroup>, mutable_pgroups, pg)
		prior.assign_Laplace(*pg, k);

	return prior;
}

Pforester_PCFG_linear::Pforester_PCFG_linear(Pforester_pscores_linear& pscores) :
	Pforester_PCFG(pscores, TotalStates) {

	// set model name
	name = "RNAForest_linear";

	// set state names
	state_name[A] = "A";
	state_name[F] = "F";
	state_name[S] = "S";
	state_name[Spp] = "Spp";
	state_name[Sp_] = "Sp_";
	state_name[S_p] = "S_p";
	state_name[Sbb] = "Sbb";
	state_name[Sb_] = "Sb_";
	state_name[S_b] = "S_b";
	state_name[SBp_] = "SBp_";
	state_name[SB_p] = "SB_p";
	state_name[Sbbbb] = "Sbbbb";
	state_name[Sbbb_] = "Sbbb_";
	state_name[Sbb_b] = "Sbb_b";
	state_name[Sb_bb] = "Sb_bb";
	state_name[Sb_b_] = "Sb_b_";
	state_name[S_bbb] = "S_bbb";
	state_name[S_b_b] = "S_b_b";


	// set state types
	const PFunc zero(.0);

	init_emit(F, Null, zero);
	init_emit(S, Null, zero);

	init_emit(Spp, EmitXLRYLR, zero);
	init_emit(Sp_, EmitXLR, zero);
	init_emit(S_p, EmitYLR, zero);
	init_emit(Sbb, EmitXLYL, zero);
	init_emit(Sb_, EmitXL, zero);
	init_emit(S_b, EmitYL, zero);

	init_emit(SBp_, Null, zero);
	init_emit(SB_p, Null, zero);

	init_emit(Sbbbb, EmitXLRYLR, zero);
	init_emit(Sbbb_, EmitXLRYL, zero);
	init_emit(Sbb_b, EmitXLYLR, zero);
	init_emit(Sb_bb, EmitXLRYR, zero);
	init_emit(Sb_b_, EmitXLR, zero);
	init_emit(S_bbb, EmitXRYLR, zero);
	init_emit(S_b_b, EmitYLR, zero);


	// set bifurcations
	init_bifurc(A, S, F);


	// set transitions
	transition(Start, A) = 1;

	transition(F, A) = pscores.f_end.n;
	transition(F, End) = pscores.f_end.y;

	transition(S, Spp) = pscores.sigma[0];
	transition(S, Sp_) = pscores.sigma[1];
	transition(S, S_p) = pscores.sigma[2];
	transition(S, Sbb) = pscores.sigma[3];
	transition(S, Sb_) = pscores.sigma[4];
	transition(S, S_b) = pscores.sigma[5];

	transition(Spp, Sbbbb) = 1;
	transition(Sp_, SBp_) = 1;
	transition(S_p, SB_p) = 1;

	transition(Sbb, End) = 1;
	transition(Sb_, End) = 1;
	transition(S_b, End) = 1;

	transition(SBp_, Sbbbb) = pscores.pmu.y * pscores.pmu.y;
	transition(SBp_, Sbbb_) = pscores.pmu.y * pscores.pmu.n;
	transition(SBp_, Sb_bb) = pscores.pmu.n * pscores.pmu.y;
	transition(SBp_, Sb_b_) = pscores.pmu.n * pscores.pmu.n;

	transition(SB_p, Sbbbb) = pscores.pmu.y * pscores.pmu.y;
	transition(SB_p, Sbb_b) = pscores.pmu.y * pscores.pmu.n;
	transition(SB_p, S_bbb) = pscores.pmu.n * pscores.pmu.y;
	transition(SB_p, S_b_b) = pscores.pmu.n * pscores.pmu.n;

	transition(Sbbbb, F) = 1;
	transition(Sbbb_, F) = 1;
	transition(Sbb_b, F) = 1;
	transition(Sb_bb, F) = 1;
	transition(Sb_b_, F) = 1;
	transition(S_bbb, F) = 1;
	transition(S_b_b, F) = 1;


	// set emissions
	const int A = alphabet().size();
	const int B = A - 2;
	const PFunc one(1.0);

	{
		const int i = A - 2; // (
		const int j = A - 1; // )

		// (p,p)
		const int xy = emit_xl_mul(EmitXLRYLR) * i + emit_xr_mul(EmitXLRYLR) * j
					 + emit_yl_mul(EmitXLRYLR) * i + emit_yr_mul(EmitXLRYLR) * j;
		emit[Spp][xy] = one;

		// (p,-) ; (-,p)
		const int x = emit_xl_mul(EmitXLR) * i + emit_xr_mul(EmitXLR) * j;
		const int y = emit_yl_mul(EmitYLR) * i + emit_yr_mul(EmitYLR) * j;
		emit[Sp_][x] = one;
		emit[S_p][y] = one;
	}


	const PFunc null(.25);
	const PFunc match(pscores.mu.y);
	const PFunc mismatch(pscores.mu.n / 3);

	for (int i = 0; i < B; ++i) {
		for (int k = 0; k < B; ++k) {
			for (int j = 0; j < B; ++j) {
				for (int l = 0; l < B; ++l) {
					const int ikjl = emit_xl_mul(EmitXLRYLR) * i + emit_yl_mul(EmitXLRYLR) * k
								   + emit_xr_mul(EmitXLRYLR) * j + emit_yr_mul(EmitXLRYLR) * l;

					const int ikj_ = emit_xl_mul(EmitXLRYL) * i + emit_yl_mul(EmitXLRYL) * k + emit_xr_mul(EmitXLRYL) * j;
					const int ik_l = emit_xl_mul(EmitXLYLR) * i + emit_xl_mul(EmitXLYLR) * k + emit_yr_mul(EmitXLYLR) * l;
					const int i_jl = emit_xl_mul(EmitXLRYR) * i + emit_xr_mul(EmitXLRYR) * j + emit_yr_mul(EmitXLRYR) * l;
					const int _kjl = emit_yl_mul(EmitXRYLR) * k + emit_xr_mul(EmitXRYLR) * j + emit_yr_mul(EmitXRYLR) * l;

					const int ik__ = emit_xl_mul(EmitXLYL) * i + emit_yl_mul(EmitXLYL) * k;
					const int i_j_ = emit_xl_mul(EmitXLR) * i + emit_xr_mul(EmitXLR) * j;
					const int _k_l = emit_yl_mul(EmitYLR) * k + emit_yr_mul(EmitYLR) * l;

					const int i___ = emit_xl_mul(EmitXL) * i;
					const int _k__ = emit_yl_mul(EmitYL) * k;


					if ((i == k) && (j == l)) {
						emit[Sbbbb][ikjl] = match*match;
					}
					else if (i == k) {
						emit[Sbbbb][ikjl] = match*mismatch;

						emit[Sbbb_][ikj_] = match*null;
						emit[Sbb_b][ik_l] = match*null;

						emit[Sbb][ik__] = match;
					}
					else if (j == l) {
						emit[Sbbbb][ikjl] = mismatch*match;

						emit[Sb_bb][i_jl] = null*match;
						emit[S_bbb][_kjl] = null*match;
					}
					else {
						emit[Sbbbb][ikjl] = mismatch*mismatch;

						emit[Sbbb_][ikj_] = mismatch*null;
						emit[Sbb_b][ik_l] = mismatch*null;

						emit[Sb_bb][i_jl] = null*mismatch;
						emit[S_bbb][_kjl] = null*mismatch;

						emit[Sb_b_][i_j_] = null*null;
						emit[S_b_b][_k_l] = null*null;

						emit[Sbb][ik__] = mismatch;

						emit[Sb_][i___] = null;
						emit[S_b][_k__] = null;
					}

				}
			}
		}
	}

	init_mutable_pgroups();
}

Pforester_PCFG_affine::Pforester_PCFG_affine(Pforester_pscores_affine& pscores) :
	Pforester_PCFG(pscores, TotalStates) {

	// set model name
	name = "RNAForest_affine";

	// set state names
	state_name[Ann] = "Ann";
	state_name[Fnn] = "Fnn";

	state_name[Apn] = "Apn";
	state_name[Fpn] = "Fpn";

	state_name[Asn] = "Asn";
	state_name[Fsn] = "Fsn";

	state_name[Aps] = "Aps";
	state_name[Fps] = "Fps";

	state_name[Anp] = "Anp";
	state_name[Fnp] = "Fnp";

	state_name[Ans] = "Ans";
	state_name[Fns] = "Fns";

	state_name[Asp] = "Asp";
	state_name[Fsp] = "Fsp";

	state_name[Axxpp] = "Axxpp";
	state_name[Axxp_] = "Axxp_";
	state_name[Axx_p] = "Axx_p";
	state_name[Axxbb] = "Axxbb";
	state_name[Axxb_] = "Axxb_";
	state_name[Axx_b] = "Axx_b";

	state_name[Apxpp] = "Apxpp";
	state_name[Apxp_] = "Apxp_";
	state_name[Apx_p] = "Apx_p";
	state_name[Apxbb] = "Apxbb";
	state_name[Apxb_] = "Apxb_";
	state_name[Apx_b] = "Apx_b";

	state_name[Axppp] = "Axppp";
	state_name[Axpp_] = "Axpp_";
	state_name[Axp_p] = "Axp_p";
	state_name[Axpbb] = "Axpbb";
	state_name[Axpb_] = "Axpb_";
	state_name[Axp_b] = "Axp_b";

	state_name[Spp] = "Spp";
	state_name[Sp_] = "Sp_";
	state_name[S_p] = "S_p";
	state_name[SBpp] = "SBpp";
	state_name[SBp_] = "SBp_";
	state_name[SB_p] = "SB_p";

	state_name[Snpbbbb] = "Snpbbbb";
	state_name[Snpbbb_] = "Snpbbb_";
	state_name[Snpb_bb] = "Snpb_bb";
	state_name[Snpb_b_] = "Snpb_b_";

	state_name[Spnbbbb] = "Spnbbbb";
	state_name[Spnbb_b] = "Spnbb_b";
	state_name[Spn_bbb] = "Spn_bbb";
	state_name[Spn_b_b] = "Spn_b_b";

	state_name[Npp] = "Npp";
	state_name[Np_] = "Np_";
	state_name[N_p] = "N_p";


	// set state types
	const PFunc zero(.0);

	init_emit(Ann, Null, zero);
	init_emit(Fnn, Null, zero);

	init_emit(Apn, Null, zero);
	init_emit(Fpn, Null, zero);

	init_emit(Asn, Null, zero);
	init_emit(Fsn, Null, zero);

	init_emit(Aps, Null, zero);
	init_emit(Fps, Null, zero);

	init_emit(Anp, Null, zero);
	init_emit(Fnp, Null, zero);

	init_emit(Ans, Null, zero);
	init_emit(Fns, Null, zero);

	init_emit(Asp, Null, zero);
	init_emit(Fsp, Null, zero);

	init_emit(Axxbb, EmitXLYL, zero);
	init_emit(Axxb_, EmitXL, zero);
	init_emit(Axx_b, EmitYL, zero);

	init_emit(Axxbb, EmitXLYL, zero);
	init_emit(Axxb_, EmitXL, zero);
	init_emit(Axx_b, EmitYL, zero);

	init_emit(Apxbb, EmitXLYL, zero);
	init_emit(Apxb_, EmitXL, zero);
	init_emit(Apx_b, EmitYL, zero);

	init_emit(Axpbb, EmitXLYL, zero);
	init_emit(Axpb_, EmitXL, zero);
	init_emit(Axp_b, EmitYL, zero);

	init_emit(Spp, EmitXLRYLR, zero);
	init_emit(Sp_, EmitXLR, zero);
	init_emit(S_p, EmitYLR, zero);
	init_emit(SBpp, EmitXLRYLR, zero);
	init_emit(SBp_, Null, zero);
	init_emit(SB_p, Null, zero);

	init_emit(Snpbbbb, EmitXLRYLR, zero);
	init_emit(Snpbbb_, EmitXLRYL, zero);
	init_emit(Snpb_bb, EmitXLRYR, zero);
	init_emit(Snpb_b_, EmitXLR, zero);

	init_emit(Spnbbbb, EmitXLRYLR, zero);
	init_emit(Spnbb_b, EmitXLYLR, zero);
	init_emit(Spn_bbb, EmitXRYLR, zero);
	init_emit(Spn_b_b, EmitYLR, zero);

	init_emit(Npp, Null, zero);
	init_emit(Np_, Null, zero);
	init_emit(N_p, Null, zero);


	// set bifurcations
	init_bifurc(Axxpp, Npp, Fnn);
	init_bifurc(Axxp_, Np_, Fns);
	init_bifurc(Axx_p, N_p, Fsn);

	init_bifurc(Apxpp, Npp, Fpn);
	init_bifurc(Apxp_, Np_, Fps);
	init_bifurc(Apx_p, N_p, Fpn);

	init_bifurc(Axppp, Npp, Fnp);
	init_bifurc(Axpp_, Np_, Fnp);
	init_bifurc(Axp_p, N_p, Fsp);


	// set transitions
	transition(Start, Ann) = 1;

	transition(Fnn, Ann) = pscores.f_end.n;
	transition(Fnn, End) = pscores.f_end.y;

	transition(Fpn, Apn) = pscores.f_end.n;
	transition(Fpn, End) = pscores.f_end.y;

	transition(Fsn, Asn) = pscores.f_end.n;
	transition(Fsn, End) = pscores.f_end.y;

	transition(Fps, Aps) = pscores.f_end.n;
	transition(Fps, End) = pscores.f_end.y;

	transition(Fnp, Anp) = pscores.f_end.n;
	transition(Fnp, End) = pscores.f_end.y;

	transition(Fns, Ans) = pscores.f_end.n;
	transition(Fns, End) = pscores.f_end.y;

	transition(Fsp, Asp) = pscores.f_end.n;
	transition(Fsp, End) = pscores.f_end.y;

	transition(Ann, Axxpp) = pscores.sigma_nn[0];
	transition(Ann, Axxp_) = pscores.sigma_nn[1];
	transition(Ann, Axx_p) = pscores.sigma_nn[2];
	transition(Ann, Axxbb) = pscores.sigma_nn[3];
	transition(Ann, Axxb_) = pscores.sigma_nn[4];
	transition(Ann, Axx_b) = pscores.sigma_nn[5];

	transition(Apn, Apxpp) = pscores.sigma_pn[0];
	transition(Apn, Apxp_) = pscores.sigma_pn[1];
	transition(Apn, Apx_p) = pscores.sigma_pn[2];
	transition(Apn, Apxbb) = pscores.sigma_pn[3];
	transition(Apn, Apxb_) = pscores.sigma_pn[4];
	transition(Apn, Apx_b) = pscores.sigma_pn[5];

	transition(Asn, Axxpp) = pscores.sigma_sn[0];
	transition(Asn, Axxp_) = pscores.sigma_sn[1];
	transition(Asn, Axx_p) = pscores.sigma_sn[2];
	transition(Asn, Axxbb) = pscores.sigma_sn[3];
	transition(Asn, Axxb_) = pscores.sigma_sn[4];
	transition(Asn, Axx_b) = pscores.sigma_sn[5];

	transition(Aps, Apxpp) = pscores.sigma_ps[0];
	transition(Aps, Apxp_) = pscores.sigma_ps[1];
	transition(Aps, Apx_p) = pscores.sigma_ps[2];
	transition(Aps, Apxbb) = pscores.sigma_ps[3];
	transition(Aps, Apxb_) = pscores.sigma_ps[4];
	transition(Aps, Apx_b) = pscores.sigma_ps[5];

	transition(Anp, Axppp) = pscores.sigma_np[0];
	transition(Anp, Axpp_) = pscores.sigma_np[1];
	transition(Anp, Axp_p) = pscores.sigma_np[2];
	transition(Anp, Axpbb) = pscores.sigma_np[3];
	transition(Anp, Axpb_) = pscores.sigma_np[4];
	transition(Anp, Axp_b) = pscores.sigma_np[5];

	transition(Ans, Axxpp) = pscores.sigma_ns[0];
	transition(Ans, Axxp_) = pscores.sigma_ns[1];
	transition(Ans, Axx_p) = pscores.sigma_ns[2];
	transition(Ans, Axxbb) = pscores.sigma_ns[3];
	transition(Ans, Axxb_) = pscores.sigma_ns[4];
	transition(Ans, Axx_b) = pscores.sigma_ns[5];

	transition(Asp, Axppp) = pscores.sigma_sp[0];
	transition(Asp, Axpp_) = pscores.sigma_sp[1];
	transition(Asp, Axp_p) = pscores.sigma_sp[2];
	transition(Asp, Axpbb) = pscores.sigma_sp[3];
	transition(Asp, Axpb_) = pscores.sigma_sp[4];
	transition(Asp, Axp_b) = pscores.sigma_sp[5];

	transition(Axxbb, Fnn) = 1;
	transition(Axxb_, Fns) = 1;
	transition(Axx_b, Fsn) = 1;

	transition(Apxbb, Fpn) = 1;
	transition(Apxb_, Fps) = 1;
	transition(Apx_b, Fpn) = 1;

	transition(Axpbb, Fnp) = 1;
	transition(Axpb_, Fnp) = 1;
	transition(Axp_b, Fsp) = 1;

	transition(Npp, Spp) = 1;
	transition(Np_, Sp_) = 1;
	transition(N_p, S_p) = 1;

	transition(Spp, SBpp) = 1;
	transition(Sp_, SBp_) = 1;
	transition(S_p, SB_p) = 1;

	transition(SBpp, Fnn) = 1;

	transition(SBp_, Snpbbbb) = pscores.pmu.y * pscores.pmu.y;
	transition(SBp_, Snpbbb_) = pscores.pmu.y * pscores.pmu.n;
	transition(SBp_, Snpb_bb) = pscores.pmu.n * pscores.pmu.y;
	transition(SBp_, Snpb_b_) = pscores.pmu.n * pscores.pmu.n;

	transition(SB_p, Spnbbbb) = pscores.pmu.y * pscores.pmu.y;
	transition(SB_p, Spnbb_b) = pscores.pmu.y * pscores.pmu.n;
	transition(SB_p, Spn_bbb) = pscores.pmu.n * pscores.pmu.y;
	transition(SB_p, Spn_b_b) = pscores.pmu.n * pscores.pmu.n;

	transition(Snpbbbb, Fnp) = 1;
	transition(Snpbbb_, Fnp) = 1;
	transition(Snpb_bb, Fnp) = 1;
	transition(Snpb_b_, Fnp) = 1;

	transition(Spnbbbb, Fpn) = 1;
	transition(Spnbb_b, Fpn) = 1;
	transition(Spn_bbb, Fpn) = 1;
	transition(Spn_b_b, Fpn) = 1;


	// set emissions
	const int A = alphabet().size();
	const int B = A - 2;
	const PFunc one(1.0);

	{
		const int i = A - 2; // (
		const int j = A - 1; // )

		// (p,p)
		const int xy = emit_xl_mul(EmitXLRYLR) * i + emit_xr_mul(EmitXLRYLR) * j
					 + emit_yl_mul(EmitXLRYLR) * i + emit_yr_mul(EmitXLRYLR) * j;
		emit[Spp][xy] = one;

		// (p,-) ; (-,p)
		const int x = emit_xl_mul(EmitXLR) * i + emit_xr_mul(EmitXLR) * j;
		const int y = emit_yl_mul(EmitYLR) * i + emit_yr_mul(EmitYLR) * j;
		emit[Sp_][x] = one;
		emit[S_p][y] = one;
	}


	const PFunc null(.25);
	const PFunc match(pscores.mu.y);
	const PFunc mismatch(pscores.mu.n / 3);

	for (int i = 0; i < B; ++i) {
		for (int k = 0; k < B; ++k) {
			for (int j = 0; j < B; ++j) {
				for (int l = 0; l < B; ++l) {
					const int ikjl = emit_xl_mul(EmitXLRYLR) * i + emit_yl_mul(EmitXLRYLR) * k
								   + emit_xr_mul(EmitXLRYLR) * j + emit_yr_mul(EmitXLRYLR) * l;

					const int ikj_ = emit_xl_mul(EmitXLRYL) * i + emit_yl_mul(EmitXLRYL) * k + emit_xr_mul(EmitXLRYL) * j;
					const int ik_l = emit_xl_mul(EmitXLYLR) * i + emit_xl_mul(EmitXLYLR) * k + emit_yr_mul(EmitXLYLR) * l;
					const int i_jl = emit_xl_mul(EmitXLRYR) * i + emit_xr_mul(EmitXLRYR) * j + emit_yr_mul(EmitXLRYR) * l;
					const int _kjl = emit_yl_mul(EmitXRYLR) * k + emit_xr_mul(EmitXRYLR) * j + emit_yr_mul(EmitXRYLR) * l;

					const int ik__ = emit_xl_mul(EmitXLYL) * i + emit_yl_mul(EmitXLYL) * k;
					const int i_j_ = emit_xl_mul(EmitXLR) * i + emit_xr_mul(EmitXLR) * j;
					const int _k_l = emit_yl_mul(EmitYLR) * k + emit_yr_mul(EmitYLR) * l;

					const int i___ = emit_xl_mul(EmitXL) * i;
					const int _k__ = emit_yl_mul(EmitYL) * k;



					if ((i == k) && (j == l)) {
						emit[SBpp][ikjl] = match*match;
						emit[Snpbbbb][ikjl] = match*match;
						emit[Spnbbbb][ikjl] = match*match;
					}
					else if (i == k) {
						emit[SBpp][ikjl] = match*mismatch;
						emit[Snpbbbb][ikjl] = match*mismatch;
						emit[Spnbbbb][ikjl] = match*mismatch;

						emit[Snpbbb_][ikj_] = match*null;
						emit[Spnbb_b][ik_l] = match*null;

						emit[Axxbb][ik__] = match;
						emit[Axpbb][ik__] = match;
						emit[Apxbb][ik__] = match;
					}
					else if (j == l) {
						emit[SBpp][ikjl] = mismatch*match;
						emit[Snpbbbb][ikjl] = mismatch*match;
						emit[Spnbbbb][ikjl] = mismatch*match;

						emit[Snpb_bb][i_jl] = null*match;
						emit[Spn_bbb][_kjl] = null*match;
					}
					else {
						emit[SBpp][ikjl] = mismatch*mismatch;
						emit[Snpbbbb][ikjl] = mismatch*mismatch;
						emit[Spnbbbb][ikjl] = mismatch*mismatch;

						emit[Snpbbb_][ikj_] = mismatch*null;
						emit[Spnbb_b][ik_l] = mismatch*null;

						emit[Snpb_bb][i_jl] = null*mismatch;
						emit[Spn_bbb][_kjl] = null*mismatch;

						emit[Snpb_b_][i_j_] = null*null;
						emit[Spn_b_b][_k_l] = null*null;

						emit[Axxbb][ik__] = mismatch;
						emit[Axpbb][ik__] = mismatch;
						emit[Apxbb][ik__] = mismatch;

						emit[Axxb_][i___] = null;
						emit[Axpb_][i___] = null;
						emit[Apxb_][i___] = null;
						emit[Axx_b][_k__] = null;
						emit[Axp_b][_k__] = null;
						emit[Apx_b][_k__] = null;
					}

				}
			}
		}
	}


	init_mutable_pgroups();
}
