#include <iostream>
#include "playable.h"
using namespace std;

//Playable:

Playable::Playable() : title("None"), length(0) {}

Playable::Playable(string title, int length) : title(title), length(length) {}

string Playable::get_title() const {
	return title;
}

int Playable::get_length() const {
	return length;
}

void Playable::set_title(string new_title) {
	title = new_title;
}

void Playable::set_length(int new_length) {
	length = new_length;
}

ostream& operator<<(ostream& os, const Playable& playable) {
	os << "Title: " << playable.title << endl;
	os << "Length: " << playable.length << endl;
	return os;
}

//Ad:
Ad::Ad() : Playable(), product("None"), company("None") {}
Ad::Ad(string title, int length, string product, string company) : Playable(title, length), product(product), company(company) {}

string Ad::get_product() const {
	return product;
}

string Ad::get_company() const {
	return company;
}

void Ad::set_product(string new_product) {
	product = new_product;
}

void Ad::set_company(string new_company) {
	company = new_company;
}

bool Ad::operator!=(Ad other_ad) {
	if (product == other_ad.get_product()
		&& title == other_ad.get_title()) {
		return false;
	}
	else {
		return true;
	}
}

bool Ad::operator==(Ad other_ad) {
	if (product == other_ad.get_product()
		&& title == other_ad.get_title()) {
		return true;
	}
	else {
		return false;
	}
}

ostream& operator<<(ostream& os, const Ad& ad) {
	os << "Advertisement information:" << endl;
	os << (const Playable&)ad;
	os << "Advertised product: " << ad.product << endl;
	os << "Advertising company: " << ad.company << endl;
	return os;
}

Ad& Ad::operator=(const Ad& other_ad) {
	this->set_title(other_ad.get_title());
	this->set_length(other_ad.get_length());
	product = other_ad.product;
	company = other_ad.company;
	return *this;
}

//VR_Experience
VR_Experience::VR_Experience() : Playable(), summary("None"), genre("None") {}
VR_Experience::VR_Experience(string title, int length, string summary, string genre) : Playable(title, length), summary(summary), genre(genre) {}

string VR_Experience::get_summary() const {
	return summary;
}

string VR_Experience::get_genre() const {
	return genre;
}

void VR_Experience::set_summary(string sum) {
	summary = sum;
}

void VR_Experience::set_genre(string gen) {
	genre = gen;
}

bool VR_Experience::operator!=(VR_Experience other_vr) {
	if (summary == other_vr.get_summary()
		&& title == other_vr.get_title()) {
		return false;
	}
	else {
		return true;
	}
}

bool VR_Experience::operator==(VR_Experience other_vr) {
	if (summary == other_vr.get_summary()
		&& title == other_vr.get_title()) {
		return true;
	}
	else {
		return false;
	}
}

ostream& operator<<(ostream& os, const VR_Experience& vr) {
	os << "VR Experience information:" << endl;
	os << (const Playable&)vr;
	os << "Experience genre: " << vr.genre << endl;
	os << "Experience summary: " << vr.summary << endl;
	return os;
}

VR_Experience& VR_Experience::operator=(const VR_Experience& other_vr) {
	this->set_title(other_vr.get_title());
	this->set_length(other_vr.get_length());
	summary = other_vr.summary;
	genre = other_vr.genre;
	return *this;
}

//Concert
Concert::Concert() : Playable()
{
	tour_name = "None";
	artist_name = "None";
	music_genre = "None";
}

Concert::Concert(string title, string tour, string artist, string genre, int concert_length) : Playable(title, concert_length)
{
	tour_name = tour;
	artist_name = artist;
	music_genre = genre;
}

void Concert::set_tour_name(string tour)
{
	tour_name = tour;
}

void Concert::set_artist_name(string name)
{
	artist_name = name;
}

void Concert::set_music_genre(string genre)
{
	music_genre = genre;
}

bool Concert::operator!=(Concert other_concert) {
	if (artist_name == other_concert.get_artist_name()
		&& title == other_concert.get_title()) {
		return false;
	}
	else {
		return true;
	}
}

bool Concert::operator==(Concert other_concert) {
	if (artist_name == other_concert.get_artist_name()
		&& title == other_concert.get_title()) {
		return true;
	}
	else {
		return false;
	}
}

ostream& operator<<(ostream& os, const Concert& concert) {
	os << "Concert information:" << endl;
	os << (const Playable&)concert;
	os << "Tour name " << concert.tour_name << endl;
	os << "Artist name " << concert.artist_name << endl;
	os << "Music genre " << concert.music_genre << endl;
	return os;
}

Concert& Concert::operator=(const Concert& other_concert) {
	this->set_title(other_concert.get_title());
	this->set_length(other_concert.get_length());
	tour_name = other_concert.tour_name;
	artist_name = other_concert.artist_name;
	music_genre = other_concert.music_genre;
	return *this;
}

//Meeting
Meeting::Meeting() : Playable()
{
	guest_name = "None";
}

Meeting::Meeting(string title, string guest, int meeting_length) : Playable(title, meeting_length)
{
	cout << "constructor meeting " << title << endl;
	guest_name = guest;
}

void Meeting::set_guest_name(string guest)
{
	guest_name = guest;
}

bool Meeting::operator != (Meeting other_meeting) {
	if (guest_name == other_meeting.get_guest_name()
		&& title == other_meeting.get_title()) {
		return false;
	}
	else {
		return true;
	}
}

bool Meeting::operator == (const Meeting other_meeting) {
	if (guest_name == other_meeting.get_guest_name()
		&& title == other_meeting.get_title()) {
		return true;
	}
	else {
		return false;
	}
}

ostream& operator<<(ostream& os, const Meeting& meeting) {
	os << "Meeting information:" << endl;
	os << (const Playable&)meeting;
	os << "Guest name " << meeting.guest_name << endl;
	return os;
}

Meeting& Meeting::operator=(const Meeting& other_meeting) {
	this->set_title(other_meeting.get_title());
	this->set_length(other_meeting.get_length());
	guest_name = other_meeting.guest_name;
	return *this;
}

//Movie
// Constructors:

//Custom constructor:
Movie::Movie(string title, string director_name, string writer_name, string production_company, string genre, string production_country,
	string language, string summary, vector<string> cast, int length, int premiere_year, int budget) {
	ConstrMovie(title, director_name, writer_name, production_company, genre, production_country,
		language, summary, cast, length, premiere_year, budget);
}

// Default constructor
Movie::Movie(): Playable() {
	director_name = "None";
	writer_name = "None";
	production_company = "None";
	genre = "None";
	production_country = "None";
	language = "None";
	summary = "None";
	vector<string> empty_cast;
	cast = empty_cast;
	premiere_year = 0;
	budget = 0;
}

//Function that constructs a movie object:
void Movie::ConstrMovie(string title, string director_name, string writer_name, string production_company, string genre, string production_country,
	string language, string summary, vector<string> cast, int length, int premiere_year, int budget) {
	this->title = title;
	this->length = length;
	this->director_name = director_name;
	this->writer_name = writer_name;
	this->production_company = production_company;
	this->genre = genre;
	this->production_country = production_country;
	this->language = language;
	this->summary = summary;
	this->cast = cast;
	this->premiere_year = premiere_year;
	this->budget = budget;
}

//Movie getters:


string Movie::get_director() const {
	return director_name;
}

string Movie::get_writer() const {
	return writer_name;
}

string Movie::get_production_company() const {
	return production_company;
}

string Movie::get_genre() const {
	return genre;
}

string Movie::get_production_country() const {
	return production_country;
}

string Movie::get_language() const {
	return language;
}

string Movie::get_summary() const {
	return summary;
}

vector<string> Movie::get_cast() {
	return cast;
}

int Movie::get_premiere_year() const {
	return premiere_year;
}

int Movie::get_budget() const {
	return budget;
}


//Movie setters:

void Movie::set_director(string director_name) {
	this->director_name = director_name;
}

void Movie::set_writer(string writer_name) {
	this->writer_name = writer_name;
}

void Movie::set_production_company(string production_company) {
	this->production_company = production_company;
}

void Movie::set_genre(string genre) {
	this->genre = genre;
}

void Movie::set_production_country(string production_country) {
	this->production_country = production_country;
}

void Movie::set_language(string language) {
	this->language = language;
}

void Movie::set_summary(string summary) {
	this->summary = summary;
}

void Movie::set_cast(vector<string> cast) {
	this->cast = cast;
}

void Movie::set_premiere_year(int premiere_year) {
	this->premiere_year = premiere_year;
}

void Movie::set_budget(int budget) {
	this->budget = budget;
}

//Methods that allow a change in the movie's cast:
void Movie::change_cast(unsigned int old_actor_pos, string new_actor) {
	if (old_actor_pos < cast.size()) {
		cast[old_actor_pos] = new_actor;
	}
}

void Movie::change_cast_name(string old_actor, string new_actor) {
	if (find(cast.begin(), cast.end(), old_actor) != cast.end()) {
		vector<string>::iterator iter = find(cast.begin(), cast.end(), old_actor);
		int index = distance(cast.begin(), iter);
		change_cast(index, new_actor);
	}
}

void Movie::add_to_cast(string new_actor) {
	cast.push_back(new_actor);
}

void Movie::erase_from_cast(unsigned int old_actor_pos) {
	if (old_actor_pos < cast.size()) {
		cast.erase(cast.begin() + old_actor_pos);
	}
}

void Movie::erase_from_cast_name(string old_actor_name) {
	if (find(cast.begin(), cast.end(), old_actor_name) != cast.end()) {
		vector<string>::iterator iter = find(cast.begin(), cast.end(), old_actor_name);
		int index = distance(cast.begin(), iter);
		erase_from_cast(index);
	}
}

string Movie::cast_to_str() {
	string movie_cast = "";
	for (unsigned int i = 0; i < cast.size(); i++) {
		movie_cast.append(cast[i]);
		movie_cast.append(" ");
	}
	return movie_cast;
}

//Method that creates a new language version:

Movie Movie::create_new_lang_version(string new_lang) {
	Movie new_version(this->get_title(), director_name, writer_name, production_company, genre, production_country,
		new_lang, summary, cast, this->get_length(), premiere_year, budget);
	return new_version;
}

//Method that compares the director and the writer:

bool Movie::compare_director_and_writer() {
	if (director_name == writer_name) {
		return true;
	}
	else {
		return false;
	}
}


//Overloading the != == << and = operators:
bool Movie::operator!=(Movie other_movie) {
	if (this->get_title() == other_movie.get_title()
		&& premiere_year == other_movie.get_premiere_year()) {
		return false;
	}
	else {
		return true;
	}
}

bool Movie::operator==(Movie other_movie) {
	if (this->get_title() == other_movie.get_title()
		&& premiere_year == other_movie.get_premiere_year()) {
		return true;
	}
	else {
		return false;
	}
}

ostream& operator<<(ostream& os, const Movie& movie) {
	os << "Movie information:" << endl;
	os << (const Playable&)movie;
	os << "Director: " << movie.director_name << endl;
	os << "Writer: " << movie.writer_name << endl;
	os << "Production company: " << movie.production_company << endl;
	os << "Production country: " << movie.production_country << endl;
	os << "Genre: " << movie.genre << endl;
	os << "Language: " << movie.language << endl;
	os << "Summary: " << movie.summary << endl;
	os << "Cast: ";
	for (unsigned int i = 0; i < movie.cast.size(); i++) {
		os << movie.cast[i] << " ";
	}
	os << endl;
	os << "Premiere year: " << movie.premiere_year << endl;
	os << "Budget: " << movie.budget << endl;
	return os;
}

Movie& Movie::operator=(const Movie& other_movie) {
	ConstrMovie(other_movie.get_title(), other_movie.director_name, other_movie.writer_name,
		other_movie.production_company, other_movie.genre, other_movie.production_country,
		other_movie.language, other_movie.summary, other_movie.cast, other_movie.get_length(),
		other_movie.premiere_year, other_movie.budget);
	return *this;
}