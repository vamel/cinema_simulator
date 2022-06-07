#ifndef PLAYABLE_H
#define PLAYABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "json.hpp"
using namespace std;

class Playable {
protected:
	string title;
	int length;
public:
	//Contructors and Destructor:
	Playable();
	Playable(string title, int length);
	virtual ~Playable() {};

	//Getters
	string get_title() const;
	int get_length() const;

	//Setters
	void set_title(string new_title);
	void set_length(int new_length);

	friend ostream& operator<<(ostream& os, const Playable& playable);
};

class Ad : public Playable {
private:
	string product;
	string company;
public:
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Ad, title, length, product, company);
	//Constructors:
	Ad();
	Ad(string title, int length, string product, string company);

	//Getters:
	string get_product() const;
	string get_company() const;

	//Setters
	void set_product(string new_product);
	void set_company(string new_company);

	//Operator overloading:
	bool operator != (Ad other_ad);
	bool operator == (Ad other_ad);
	friend ostream& operator<<(ostream& os, const Ad& ad);
	Ad& operator=(const Ad& other_ad);
};

class VR_Experience :public Playable {
private:
	string summary;
	string genre;
public:
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(VR_Experience, title, length, summary, genre);
	//Constructors:
	VR_Experience();
	VR_Experience(string title, int length, string summary, string genre);

	//Getters:
	string get_summary() const;
	string get_genre() const;

	//Setters:
	void set_summary(string sum);
	void set_genre(string gen);

	//Operator overloading:
	bool operator != (VR_Experience other_vr);
	bool operator == (VR_Experience other_vr);
	friend ostream& operator<<(ostream& os, const VR_Experience& vr);
	VR_Experience& operator=(const VR_Experience& other_vr);
};

class Movie : public Playable {
private:
	string director_name;
	string writer_name;
	string production_company;
	string genre;
	string production_country;
	string language;
	string summary;
	vector<string> cast;
	int premiere_year;
	int budget;

public:
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Movie, title, director_name, writer_name, production_company, genre, production_country, language, summary, cast, length, premiere_year, budget);
	//Constructors:
	Movie(string title, string director_name, string writer_name, string production_company, string genre, string production_country,
		string language, string summary, vector<string> cast, int length, int premiere_year, int budget);
	Movie();
	void ConstrMovie(string title, string director_name, string writer_name, string production_company, string genre, string production_country,
		string language, string summary, vector<string> cast, int length, int premiere_year, int budget);

	//Movie getters:
	string get_director() const;
	string get_writer() const;
	string get_production_company() const;
	string get_genre() const;
	string get_production_country() const;
	string get_language() const;
	string get_summary() const;
	vector<string> get_cast();
	int get_premiere_year() const;
	int get_budget() const;

	//Movie setters:
	void set_director(string director_name);
	void set_writer(string writer_name);
	void set_production_company(string production_company);
	void set_genre(string genre);
	void set_production_country(string production_country);
	void set_language(string language);
	void set_summary(string summary);
	void set_cast(vector<string> cast);
	void set_premiere_year(int premiere_year);
	void set_budget(int budget);

	//Methods that allow a change in the movie's cast:
	void change_cast(unsigned int old_actor_pos, string new_actor);
	void change_cast_name(string old_actor, string new_actor);
	void add_to_cast(string new_actor);
	void erase_from_cast(unsigned int old_actor_pos);
	void erase_from_cast_name(string old_actor_name);
	string cast_to_str();
	//Method that creates a new language version:
	Movie create_new_lang_version(string new_lang);
	//Method that compares the director and the writer:
	bool compare_director_and_writer();

	//Overloading the != == << and = operators:
	bool operator != (Movie other_movie);
	bool operator == (Movie other_movie);
	friend ostream& operator<<(ostream& os, const Movie& movie);
	Movie& operator=(const Movie& other_movie);
};

class Concert : public Playable
{
private:
	string tour_name;
	string artist_name;
	string music_genre;

public:
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Concert, title, tour_name, artist_name, music_genre, length);
	// constructors
	Concert();
	Concert(string concert_title, string tour_name, string artist_name, string music_genre, int length);
	// destructor

	//Getters
	string get_tour_name() const { return tour_name; };
	string get_artist_name() const { return artist_name; };
	string get_music_genre() const { return music_genre; };

	//Setters
	void set_concert_title(string concert_title);
	void set_tour_name(string tour_name);
	void set_artist_name(string artist_name);
	void set_music_genre(string music_genre);

	//Operator overloading
	bool operator != (Concert other_concert);
	bool operator == (Concert other_concert);
	friend ostream& operator<<(ostream& os, const Concert& concert);
	Concert& operator=(const Concert& other_concert);
};

class Meeting : public Playable
{
private:
	string guest_name;

public:
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Meeting, title, guest_name, length);
	// constructors
	Meeting();
	Meeting(string title, string guest, int meeting_length);
	// destructor

	string get_meeting_title() const { return title; };
	string get_guest_name() const { return guest_name; };

	void set_meeting_title(string title);
	void set_guest_name(string guest);

	//Operator overloading
	bool operator != (Meeting other_meeting);
	bool operator == (Meeting other_meeting);
	friend ostream& operator<<(ostream& os, const Meeting& meeting);
	Meeting& operator=(const Meeting& other_meeting);
};

#endif