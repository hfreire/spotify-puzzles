#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>

#define MAX_NUMER_OF_TESTCASES 100
#define MIN_NUMBER_OF_PETS 1
#define MAX_NUMBER_OF_PETS 100
#define MIN_NUMBER_VOTERS 0
#define MAX_NUMBER_VOTERS 500

using namespace std;

class Pet {
	private:
	protected:
		unsigned short number;
		unsigned short keptVotes;
		unsigned short thrownVotes;
	public:
		Pet() : number(0), keptVotes(0), thrownVotes(0) {}
		Pet(unsigned short number) : keptVotes(0), thrownVotes(0) { this->number = number; }
		Pet setNumber(unsigned short number) { this->number = number; return *this; }
		unsigned short getNumber() { return this->number; }
		Pet setKeptVotes(unsigned short keptVotes) { this->keptVotes = keptVotes; return *this; }
		unsigned short getKeptVotes() { return this->keptVotes; }
		Pet setThrownVotes(unsigned short thrownVotes) { this->thrownVotes = thrownVotes; return *this; }
		unsigned short getThrownVotes() { return this->thrownVotes; }
};

void parseNumberOfTestcases(unsigned short *numberOfTestcases) {
	string line;
	stringstream iss;

	getline(cin, line);
	iss.str(line);
	iss >> *numberOfTestcases;
	iss.clear();

	assert(*numberOfTestcases <= MAX_NUMER_OF_TESTCASES);
}

void parseTestcaseParams(unsigned short *numberOfCats, unsigned short *numberOfDogs, unsigned short *numberOfVoters) {
	string line;
	stringstream iss;

	getline(cin, line);
	iss.str(line);
	iss >> *numberOfCats;
	iss >> *numberOfDogs;
	iss >> *numberOfVoters;
	iss.clear();

	assert(MIN_NUMBER_OF_PETS <= *numberOfCats <= MAX_NUMBER_OF_PETS);
	assert(MIN_NUMBER_OF_PETS <= *numberOfDogs <= MAX_NUMBER_OF_PETS);
	assert(MIN_NUMBER_VOTERS < *numberOfVoters <= MAX_NUMBER_VOTERS);
}

ostream& operator<< (ostream &out, Pet pet) {
    out << "Pet [" <<
		"number=" << pet.getNumber() << 
	 	" keptVotes=" << pet.getKeptVotes() << 
	 	" thrownVotes=" << pet.getThrownVotes() <<
	 "]";

	return out;
}


void printPets(const map<unsigned short, Pet> &pets) {
	map<unsigned short, Pet>::const_iterator i;
	for(i = pets.begin(); i != pets.end(); ++i)
		cout << i->second << endl;
}

void parseTestcaseVotes(map<unsigned short, Pet> *cats, map<unsigned short, Pet> *dogs) {
	string line;
	stringstream iss;
	string keptVote;
	string thrownVote;
	map<unsigned short, Pet>::iterator containsIter;

	getline(cin, line);
	iss.str(line);
	iss >> keptVote;
	assert(keptVote.c_str()[0] == 'C' || keptVote.c_str()[0] == 'D');
	assert(MIN_NUMBER_OF_PETS < keptVote.c_str()[1] - '0' < MAX_NUMBER_OF_PETS);

	Pet petToKeep(keptVote.c_str()[1] - '0');
	petToKeep.setKeptVotes(1);
	if (keptVote.c_str()[0] == 'C') {
		containsIter = cats->find(petToKeep.getNumber());

		if(containsIter != cats->end()) {
			Pet *p = &(containsIter->second);
			p->setKeptVotes((p->getKeptVotes())+1);
		} else {
			cats->insert(pair<unsigned short, Pet>(petToKeep.getNumber(), petToKeep));
		}
	} else {
		containsIter = dogs->find(petToKeep.getNumber());

		if(containsIter != dogs->end()) {
			Pet *p = &(containsIter->second);
			p->setKeptVotes((p->getKeptVotes())+1);
		} else {
			dogs->insert(pair<unsigned short, Pet>(petToKeep.getNumber(), petToKeep));
		}
	}

	iss >> thrownVote;
	iss.clear();
	assert(thrownVote.c_str()[0] == 'C' || thrownVote.c_str()[0] == 'D');
	assert(MIN_NUMBER_OF_PETS < thrownVote.c_str()[1] - '0' < MAX_NUMBER_OF_PETS);

	Pet petToThrow(thrownVote.c_str()[1] - '0');
	petToThrow.setThrownVotes(1);
	if (thrownVote.c_str()[0] == 'C') {
		containsIter = cats->find(petToThrow.getNumber());

		if(containsIter != cats->end()) {
			Pet *p = &(containsIter->second);
			p->setThrownVotes((p->getThrownVotes())+1);
		} else {
			cats->insert(pair<unsigned short, Pet>(petToThrow.getNumber(), petToThrow));
		}
	} else {
		containsIter = dogs->find(petToThrow.getNumber());

		if(containsIter != dogs->end()) {
			Pet *p = &(containsIter->second);
			p->setThrownVotes((p->getThrownVotes())+1);
		} else {
			dogs->insert(pair<unsigned short, Pet>(petToThrow.getNumber(), petToThrow));
		}
	}
}

unsigned short findMaxSatisfiedVoters(map<unsigned short, Pet> &cats, map<unsigned short, Pet> &dogs) {
	unsigned short maxSatisfiedVoters = 0;
	map<unsigned short, Pet>::iterator i;

	for(i = cats.begin(); i != cats.end(); ++i)
		if (maxSatisfiedVoters < (i->second).getKeptVotes())
			maxSatisfiedVoters = (i->second).getKeptVotes();

	for(i = dogs.begin(); i != dogs.end(); ++i)
		if (maxSatisfiedVoters < (i->second).getKeptVotes())
			maxSatisfiedVoters = (i->second).getKeptVotes();

	return maxSatisfiedVoters;
}

int main() {
	unsigned short numberOfTestcases = 0;
	parseNumberOfTestcases(&numberOfTestcases);

	for (unsigned short i = 0; i < numberOfTestcases; i++) {
		unsigned short numberOfCats = 0;
		unsigned short numberOfDogs = 0;
		unsigned short numberOfVoters = 0;
		parseTestcaseParams(&numberOfCats, &numberOfDogs, &numberOfVoters);

		map<unsigned short, Pet> cats;
		map<unsigned short, Pet> dogs;
		for (unsigned short i = 0; i < numberOfVoters; i++) {
			parseTestcaseVotes(&cats, &dogs);
		}
		cout << findMaxSatisfiedVoters(cats, dogs) << endl;
	}

	return 0;
}