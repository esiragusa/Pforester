#include "forest.h"

/*
Pforester_alignment::Pforester_alignment(const Pair_CFG_alignment alignment) :
Pair_CFG_alignment(alignment) {
// TODO Change npx, npy
// TODO Change xfold, yfold
// TODO Change xseqlen, yseqlen
}
*/

void Pforester_alignment::read_Stockholm (istream& in, Sequence_database& db, int max_line) {
	Stockholm::read_Stockholm(in, db, max_line);
	produce_rnaforest();
}

Named_profile& Pforester_alignment::get_np(const unsigned int row) {
	if (row >= np_rnaforest.size())
		THROWEXPR("Alignment row out of range");
	return np_rnaforest[row];
}

// TODO produce rnaforest
void Pforester_alignment::produce_rnaforest() {
	int n_align = 0;
	for_contents (vector<Named_profile*>, np, npi) {
		++n_align;

		CTAG(6,FOREST) << "Analyzing alignment " << n_align << ", sequence " << (*npi)->name << "\n";

		//const sstring ss = get_gr_annot ((*npi)->name, sstring (Stockholm_secondary_structure_tag));
		//const sstring ss = get_fold_string((*npi)->name);
		const string ss = (*npi)->seq;

		if (ss.size()) {
			Named_profile* npr = new Named_profile();

			npr->name = (*npi)->name;
			npr->cruft = (*npi)->cruft;
			npr->seq = ss;

			npr->seq_update(alphabet, (Profile_flags_enum::Profile_flags)(Profile_flags_enum::ALL));
//			npr->seq2dsq(alphabet);
//			npr->seq2weight(alphabet);

			np_rnaforest.push_back(*npr);

			CTAG(6,FOREST) << "RNA Forest for alignment " << n_align << ", sequence " << npr->name << ":\n"
					<< npr->seq << "\n";
		} else {
			CTAG(5,FOREST) << "Warning: found no secondary structure for alignment " << n_align << ", sequence "
					<< (*npi)->name << "\n";
		}

	}
}

void Pforester_database::read(istream& in, Sequence_database& seq_db, int max_line) {
	int n_align = 0;
	while (in && !in.eof()) {
		Pforester_alignment alignment(alphabet);
		alignment.read_Stockholm(in, seq_db, max_line);
		if (alignment.rows()) {
			Stockholm_database::align.push_back(alignment);
			Pforester_database::align.push_back(alignment);
			++n_align;
		} else
			break;
	}
	update_index();
	CTAG(5,FOREST) << "Read " << n_align << " alignments\n";
}

void Pforester_database::add(Pforester_alignment& alignment) {
	Pforester_database::align.push_back(alignment);
	Stockholm_database::add(alignment);
}
