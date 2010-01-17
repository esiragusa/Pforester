#ifndef PFORESTER_ENVELOPE_INCLUDED
#define PFORESTER_ENVELOPE_INCLUDED

#include <scfg/foldenv.h>

class Pforester_envelope: public Fold_envelope {
public:
	void initialise_from_flatforest(const sstring& flatforest);
	Pforester_envelope();

private:
	typedef std::pair<int, int> CSFF;
	typedef std::list<CSFF> CSFF_list;

	const Alphabet& alphabet;
	const char lbrace, rbrace;
	Subseq_coords_set flatforest_coords;

	void initialise_flatforest_coords(const sstring& flatforest);
	unsigned int visit_flatforest(const sstring& flatforest, unsigned int start = 0);
	void clear_flatforest_coords();
};

#endif /* PFORESTER_ENVELOPE_INCLUDED */
