#include "Functions.h"
#include <algorithm>
#include <iomanip>
using std::string;

typedef std::pair<std::string,int> pair;

string ValidatePavadinimas() {
	string pavadinimas;
	while (true) {
		std::cout << "Iveskite failo pavadinima: ";
		std::cin >> pavadinimas;
		std::ifstream in(pavadinimas);
		if (!in.good()) {
			std::cerr << "Klaida. Toks failas neegzistuoja" << std::endl;
		}
		else {
			in.close();
			return pavadinimas;
			break;
		}
	}
}

bool usedSymbols(const char& character) {
	bool first = false;
	bool second = false;

	if (character == 32 || character == 39 || (character >= 65 && character <= 90) || (character >= 97 && character <= 122)) {
		return false;
	} return true;
}

string lowerAndRemove(string eilute) {
	eilute.erase(std::remove_if(eilute.begin(), eilute.end(), usedSymbols), eilute.end());
	std::transform(eilute.begin(), eilute.end(), eilute.begin(), ::tolower);
	return eilute;
}

void visasTekstas(string pavadinimas) {
	std::ifstream in(pavadinimas);
	string eilute;
	std::map<string, std::size_t> zodziai;

	while (getline(in, eilute)) {
		eilute = lowerAndRemove(eilute);

		std::vector<string> visiZodziai;
		std::istringstream buferis(eilute);
		for (string zodis; buferis >> zodis; )
			visiZodziai.push_back(zodis);

		for (const auto& zodis : visiZodziai)
		{
			++zodziai[zodis];
		}
	}

	std::vector<pair> vec;

	std::copy(zodziai.begin(),
			zodziai.end(),
			std::back_inserter<std::vector<pair>>(vec));

	std::sort(vec.begin(), vec.end(),
			[](const pair& l, const pair& r) {
				if (l.second != r.second)
					return l.second < r.second;

				return l.first < r.first;
			});
	std::ofstream out("rezultatai.txt");
	for (auto const &pair: vec) {
		if(pair.second > 1) out << "zodis " << pair.first << " pasikartojo " << pair.second << std::endl;
	}
}



void visasTekstasEilutem(string pavadinimas) {
	std::ifstream in(pavadinimas);
	string eilute;
	std::map<string, std::vector<int>> zodziai;

	int eile = 0;
	while (getline(in, eilute)) {
		eile++;
		eilute = lowerAndRemove(eilute);

		std::vector<string> visiZodziai;
		std::istringstream buferis(eilute);
		for (string zodis; buferis >> zodis; )
			visiZodziai.push_back(zodis);

		for (const auto& zodis : visiZodziai)
		{
			zodziai[zodis].push_back(eile);
		}
	}
	std::ofstream out("rezultatai.txt");
	for (const auto&[zodis, sk] : zodziai)
		{
			if (sk.size() > 1) {
				out <<std::left<< "zodis " <<std::setw(20) << zodis << " pasikartojo " << std::setw(4) <<sk.size() << " kart, eilutese: "<< sk[0];
				for (int i = 1; i < sk.size(); i++) {
					if (sk[i - 1] != sk[i]) out << " " << sk[i];
				}
				out << std::endl;
			}
		}
}

void raskURL(string pavadinimas) {
	std::ifstream in(pavadinimas);
	string eilute;
	std::ofstream out("rezultatai.txt");
	std::regex url(".*\x77\x77\x77\x2e..*");

	while (getline(in, eilute)) {
		std::vector<string> visiZodziai;
		std::istringstream buferis(eilute);
		for (string zodis; buferis >> zodis; )
			visiZodziai.push_back(zodis);

		for (const auto& zodis : visiZodziai)
		{
			if (regex_match(zodis, url)) out << zodis << std::endl;
		}
	}
}

void menu(string pavadinimas) {
	std::cout << "Pasirinkite ka norite daryti: " << std::endl;
	std::cout << "1. Isvesti pasikartojancius zodzius" << std::endl;
	std::cout << "2. Isvesti pasikartojancius zodzius ir ju vietas" << std::endl;
	std::cout << "3. Isvesti url" << std::endl;
	int pasirinkimas = 0;
	std::cin >> pasirinkimas;
	switch (pasirinkimas) {
	case 1: visasTekstas(pavadinimas);
		break;
	case 2: visasTekstasEilutem(pavadinimas);
		break;
	case 3: raskURL(pavadinimas);
		break;
	default: std::cout << "Klaida. Neteisingai ivestas pasirinkimas" << std::endl;
		menu(pavadinimas);
		break;
	}
}
