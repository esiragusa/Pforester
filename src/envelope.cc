#include "envelope.h"

Pforester_envelope::Pforester_envelope() :
	Fold_envelope(), alphabet(Pforester_alphabet),
	lbrace(alphabet.nondegenerate_chars()[alphabet.size() - 2]),
	rbrace(alphabet.nondegenerate_chars()[alphabet.size() - 1]) {
}

void Pforester_envelope::initialise_from_flatforest(const sstring& flatforest) {
//	initialise_full(flatforest.length());
	initialise_flatforest_coords(flatforest);
	initialise_from_subseq_coords(flatforest.length(), flatforest_coords);
	clear_flatforest_coords();
}

void Pforester_envelope::initialise_flatforest_coords(const sstring& flatforest) {
	for (unsigned int i = 0; i <= flatforest.length(); i++)
		flatforest_coords.insert(Subseq_coords(i, 0));

	visit_flatforest(flatforest);
}

void Pforester_envelope::clear_flatforest_coords() {
//	for_contents(Subseq_coords_set, flatforest_coords, coord)
//		delete *coord;
//Subseq_coords_set q;

//	flatforest_coords.clear();
}

unsigned int Pforester_envelope::visit_flatforest(const sstring& flatforest, unsigned int i) {
	CSFF_list t;

	while (i < flatforest.length()) {
		if (flatforest[i] == lbrace) {
			int j = visit_flatforest(flatforest, i + 2);
			t.push_back(*new CSFF(i, j));
			i = j + 1;
		} else if (flatforest[i] == rbrace) {
			t.pop_back();
			break;
		} else {
			t.push_back(*new CSFF(i, i));
			i++;
		}
	}

	for_contents(CSFF_list, t, k) {
		if (k->first == k->second) {
			flatforest_coords.insert(*new Subseq_coords(k->first, 1));
			CTAG(0,ENVELOPE) << "(" << k->first << "," << 1 << ")\n";
		} else {
			flatforest_coords.insert(*new Subseq_coords(k->first + 1, k->second - k->first - 1));
			flatforest_coords.insert(*new Subseq_coords(k->first, k->second - k->first + 1));
			CTAG(0,ENVELOPE) << "(" << k->first + 1 << "," << k->second - k->first - 1 << ")\n";
			CTAG(0,ENVELOPE) << "(" << k->first << "," << k->second - k->first + 1 << ")\n";
		}

		CSFF_list::iterator l = k;
		for (++l; l != t.end(); ++l) {
			flatforest_coords.insert(*new Subseq_coords(k->first, l->second - k->first + 1));
			CTAG(0,ENVELOPE) << "(" << k->first << "," << l->second - k->first + 1 << ")\n";
		}
	}

	return i;
}
