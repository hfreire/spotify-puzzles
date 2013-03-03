#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <cassert>

using namespace std;

#define MAX_NUMBER_OF_ALBUM_SONGS 500000

class Song {
private:
	string name;
	uint64_t numberOfTimesListened;
	unsigned int albumPosition;
	double zipfsLawPrediction;
	double quality;
public:
	Song() { }
	Song(string name, uint64_t numberOfTimesListened, unsigned int albumPosition, double zipfsLawPrediction) {
		setName(name); 
		setNumberOfTimesListened(numberOfTimesListened);
		setAlbumPosition(albumPosition);
		setZipfsLawPrediction(zipfsLawPrediction);
		setQuality(numberOfTimesListened/zipfsLawPrediction);
	}
	string getName() { return name; }
	double getZipfsLawPrediction() { return zipfsLawPrediction; }
	uint64_t getNumberOfTimesListened() { return numberOfTimesListened; }
	unsigned int getAlbumPosition() { return albumPosition; }
	double getQuality() { return quality; }
	Song setName(string name) { this->name = name; return *this; }
	Song setNumberOfTimesListened(uint64_t numberOfTimesListened) { this->numberOfTimesListened = numberOfTimesListened; return *this; }
	Song setZipfsLawPrediction(double zipfsLawPrediction) { this->zipfsLawPrediction = zipfsLawPrediction; return *this; }
	Song setAlbumPosition(unsigned int albumPosition) { this->albumPosition = albumPosition; return *this; }
	Song setQuality(double quality) { this->quality = quality; return *this; }
};

ostream& operator<< (ostream &out, Song song) {
/*	out << "Song [" <<
		"name=" << song.getName() << 
	 	" numberOfTimesListened=" << song.getNumberOfTimesListened() << 
	 	" albumPosition=" << song.getAlbumPosition() <<
	 	" zipfsLawPrediction=" << song.getZipfsLawPrediction() <<
	 	" quality=" << song.getQuality() <<
	 "]";*/

	out << song.getName();

	return out;
}


void printSongs(const list<Song> &songs) {
	list<Song>::const_iterator i;
	for(i = songs.begin(); i != songs.end(); ++i)
		cout << *i << endl;
}


class Album {
private:
	list<Song> songs;
public:
	Album() { 

	}
	list<Song> getSongs() { return songs; }
	Album setSongs(list<Song> songs) { this->songs = songs; return *this; }
};

void parseParams(unsigned int *numberOfSongsOnTheAlbum, unsigned int *numberOfSongsToSelect) {
	string line;
	getline(cin, line);
	stringstream iss(line);

	iss >> *numberOfSongsOnTheAlbum;
	iss >> *numberOfSongsToSelect;

	// Assert that 1 ≤ numberOfSongsOnTheAlbum ≤ 50000
	assert(1 <= *numberOfSongsOnTheAlbum && *numberOfSongsOnTheAlbum <= MAX_NUMBER_OF_ALBUM_SONGS);
	// Assert that 1 ≤ numberOfSongsToSelect ≤ numberOfSongsOnTheAlbum
	assert(1 <= *numberOfSongsToSelect && *numberOfSongsToSelect <= *numberOfSongsOnTheAlbum);
}

void parseAlbum(Album *album, int numberOfSongsOnTheAlbum) {
	uint64_t numberOfTimesListened;
	uint64_t numberOfTimesListenedOfFirstSong;
	double zipfsLawPrediction;
	string name = "";
	string line;
	list<Song> songs;

	for (int i = 1; i < numberOfSongsOnTheAlbum+1; i++)
	{
		getline(cin, line);
		stringstream iss(line);

		iss >> numberOfTimesListened;
		iss >> name;

		// Assert that 0 ≤ numberOfTimesListened ≤ 10e12
		assert(0 <= numberOfTimesListened && numberOfTimesListened <= (10e12));

		if (i == 1) {
			numberOfTimesListenedOfFirstSong = numberOfTimesListened;
		}

		Song *song = new Song(name, numberOfTimesListened, i, numberOfTimesListenedOfFirstSong/i);
		songs.push_back(*song);
	}

	album->setSongs(songs);

	printSongs(album->getSongs());
}

bool sortSongsByDescendingQuality (Song first, Song second) {
  return first.getQuality() > second.getQuality();
}

// sort a list of songs by their quality and select only the top ones
void findTopQualitySongs(Album *album, unsigned int numberOfSongsToSelect, list<Song> *songs) {
	*songs = album->getSongs();
	(*songs).sort(sortSongsByDescendingQuality);
	(*songs).resize(numberOfSongsToSelect);
}

int main() {
	unsigned int numberOfSongsOnTheAlbum;
	unsigned int numberOfSongsToSelect;
	parseParams(&numberOfSongsOnTheAlbum, &numberOfSongsToSelect);

	Album album;
	parseAlbum(&album, numberOfSongsOnTheAlbum);

	list<Song> selectedSongs;
	findTopQualitySongs(&album, numberOfSongsToSelect, &selectedSongs);

	printSongs(selectedSongs);

	return 0;
}