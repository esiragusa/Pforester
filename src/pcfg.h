#ifndef PFORESTER_PCFG_INCLUDED
#define PFORESTER_PCFG_INCLUDED

#include <scfg/pairpcfg.h>

/*
struct Pforester_submat : Pforester_type_enum {
	array2d<Prob> submat;

	Pforester_submat(Pforester_type type = ALL);

	void write_submat (ostream& out) const;
	void read_submat (istream& in);
};
*/

struct Pforester_params {
	Prob f_end;

	Pforester_params() :
	f_end(.0) { }
	virtual ~Pforester_params() {};
	virtual void write_params(ostream& out) const {};
	virtual void read_params(istream& in) {};
};

struct Pforester_params_linear : Pforester_params {
	Prob sigma_pp, sigma_p_, sigma__p, sigma_bb, sigma_b_, sigma__b;

	Prob pmu;
	Prob mu;

	Pforester_params_linear() :
		Pforester_params(),
		sigma_pp(.0), sigma_p_(.0), sigma_bb(.0), sigma_b_(.0),
		pmu(.0),
		mu(.0)
	{ }

	virtual ~Pforester_params_linear() {};
	void write_params(ostream& out) const;
	void read_params(istream& in);
};

struct Pforester_params_affine : Pforester_params {
	Prob sigma_nn_pp, sigma_nn_p_, sigma_nn__p, sigma_nn_bb, sigma_nn_b_, sigma_nn__b;
	Prob sigma_pn_pp, sigma_pn_p_, sigma_pn__p, sigma_pn_bb, sigma_pn_b_, sigma_pn__b;
	Prob sigma_sn_pp, sigma_sn_p_, sigma_sn__p, sigma_sn_bb, sigma_sn_b_, sigma_sn__b;
	Prob sigma_ps_pp, sigma_ps_p_, sigma_ps__p, sigma_ps_bb, sigma_ps_b_, sigma_ps__b;
	Prob sigma_np_pp, sigma_np_p_, sigma_np__p, sigma_np_bb, sigma_np_b_, sigma_np__b;
	Prob sigma_ns_pp, sigma_ns_p_, sigma_ns__p, sigma_ns_bb, sigma_ns_b_, sigma_ns__b;
	Prob sigma_sp_pp, sigma_sp_p_, sigma_sp__p, sigma_sp_bb, sigma_sp_b_, sigma_sp__b;

	Prob pmu;
	Prob mu;

	Pforester_params_affine() :
		Pforester_params(),
		sigma_nn_pp(.0), sigma_nn_p_(.0), sigma_nn__p(.0), sigma_nn_bb(.0), sigma_nn_b_(.0), sigma_nn__b(.0),
		sigma_pn_pp(.0), sigma_pn_p_(.0), sigma_pn__p(.0), sigma_pn_bb(.0), sigma_pn_b_(.0), sigma_pn__b(.0),
		sigma_sn_pp(.0), sigma_sn_p_(.0), sigma_sn__p(.0), sigma_sn_bb(.0), sigma_sn_b_(.0), sigma_sn__b(.0),
		sigma_ps_pp(.0), sigma_ps_p_(.0), sigma_ps__p(.0), sigma_ps_bb(.0), sigma_ps_b_(.0), sigma_ps__b(.0),
		sigma_np_pp(.0), sigma_np_p_(.0), sigma_np__p(.0), sigma_np_bb(.0), sigma_np_b_(.0), sigma_np__b(.0),
		sigma_ns_pp(.0), sigma_ns_p_(.0), sigma_ns__p(.0), sigma_ns_bb(.0), sigma_ns_b_(.0), sigma_ns__b(.0),
		sigma_sp_pp(.0), sigma_sp_p_(.0), sigma_sp__p(.0), sigma_sp_bb(.0), sigma_sp_b_(.0), sigma_sp__b(.0),
		pmu(.0),
		mu(.0)
	{ }

	virtual ~Pforester_params_affine() {};
	void write_params(ostream& out) const;
	void read_params(istream& in);
};

struct Pforester_pscores: public PScores {
	Boolean_group f_end;

	Pforester_pscores(const Pforester_params& params);
	virtual void init_from_params(const Pforester_params& params) {};
	virtual void update_params(Pforester_params& params) const {};
};

struct Pforester_pscores_linear: public Pforester_pscores {
	PGroup sigma;

	Boolean_group pmu;
	Boolean_group mu;

	Pforester_pscores_linear(const Pforester_params_linear& params);
	void init_from_params(const Pforester_params_linear& params);
	void update_params(Pforester_params& params) const;
};

struct Pforester_pscores_affine: public Pforester_pscores {
	PGroup sigma_nn;
	PGroup sigma_pn;
	PGroup sigma_sn;
	PGroup sigma_ps;
	PGroup sigma_np;
	PGroup sigma_ns;
	PGroup sigma_sp;

	Boolean_group pmu;
	Boolean_group mu;

	Pforester_pscores_affine(const Pforester_params_affine& params);
	void init_from_params(const Pforester_params_affine& params);
	void update_params(Pforester_params& params) const;
};

/** Pforester Pair PCFG, using PFunc class to represent transition/emission funcs */
class Pforester_PCFG: public Pair_PCFG {
private:
	Pforester_pscores& pscores;
	int first_pgroup_idx;
	vector<PGroup> mutable_pgroups;

protected:
	void init_mutable_pgroups();

public:
	Pforester_PCFG(Pforester_pscores& pscores, int states) :
		Pair_PCFG(states), pscores(pscores), first_pgroup_idx(0) { };

	virtual Dirichlet_prior default_prior() const;
};

class Pforester_PCFG_linear: public Pforester_PCFG {
private:
	enum {
		A = 0,
		F = 1,
		S = 2,

		Spp = 3,
		Sp_ = 4,
		S_p = 5,
		Sbb = 6,
		Sb_ = 7,
		S_b = 8,

		SBp_ = 9,
		SB_p = 10,

		Sbbbb = 11,
		Sbbb_ = 12,
		Sbb_b = 13,
		Sb_bb = 14,
		Sb_b_ = 15,
		S_bbb = 16,
		S_b_b = 17,

		TotalStates = 18
	};

public:
	Pforester_PCFG_linear(Pforester_pscores_linear& pscores);
};

class Pforester_PCFG_affine: public Pforester_PCFG {
private:
	enum {
		// case 1: nn
		Ann = 0,
		Fnn = 1,

		// case 2: pn
		Apn = 2,
		Fpn = 3,

		// case 3: sn
		Asn = 4,
		Fsn = 5,

		// case 4: ps
		Aps = 6,
		Fps = 7,

		// case 5: np
		Anp = 8,
		Fnp = 9,

		// case 6: ns
		Ans = 10,
		Fns = 11,

		// case 7: sp
		Asp = 12,
		Fsp = 13,

		// case 1,3,6
		Axxpp = 14,
		Axxp_ = 15,
		Axx_p = 16,
		Axxbb = 17,
		Axxb_ = 18,
		Axx_b = 19,

		// case 2,4
		Apxpp = 20,
		Apxp_ = 21,
		Apx_p = 22,
		Apxbb = 23,
		Apxb_ = 24,
		Apx_b = 25,

		// case 5,7
		Axppp = 26,
		Axpp_ = 27,
		Axp_p = 28,
		Axpbb = 29,
		Axpb_ = 30,
		Axp_b = 31,

		// cases 1-7
		Spp = 32,
		Sp_ = 33,
		S_p = 34,
		SBpp = 35,
		SBp_ = 36,
		SB_p = 37,

		Snpbbbb = 38,
		Snpbbb_ = 39,
		Snpb_bb = 40,
		Snpb_b_ = 41,

		Spnbbbb = 42,
		Spnbb_b = 43,
		Spn_bbb = 44,
		Spn_b_b = 45,

		Npp = 46,
		Np_ = 47,
		N_p = 48,

		TotalStates = 49
	};

public:
	Pforester_PCFG_affine(Pforester_pscores_affine& pscores);
};

#endif /* PFORESTER_PCFG_INCLUDED */
