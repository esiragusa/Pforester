#ifndef PFORESTER_FOREST_INCLUDED
#define PFORESTER_FOREST_INCLUDED

#include <seq/stockholm.h>

/*
class Pforester_alignment: public Pair_CFG_alignment {
private:

public:
	Pforester_alignment(const Pair_CFG_alignment alignment);
};
*/

class Pforester_alignment: public Stockholm {
private:
	const Alphabet& alphabet;
	vector<Named_profile> np_rnaforest;
	void produce_rnaforest();

public:
	Pforester_alignment(const Alphabet& alphabet) : Stockholm(), alphabet(alphabet) {};
	void read_Stockholm (istream& in, Sequence_database& db, int max_line = 0);
	Named_profile& get_np(const unsigned int row);
};

class Pforester_database: public Stockholm_database {
private:
	const Alphabet& alphabet;

public:
	list<Pforester_alignment> align;

	Pforester_database(const Alphabet& alphabet) : Stockholm_database(), alphabet(alphabet) {};

	void read(istream& in, Sequence_database& seq_db, int max_line = 0);
	void add(Pforester_alignment& alignment);
};

#endif /* PFORESTER_FOREST_INCLUDED */
