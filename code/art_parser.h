#pragma once

#include <mylibs.hpp>
#include "file_walker.h"

vector<string> get_all_art_files();
vector<string> parse_text(const string& filename);
vector<string> get_all_nareches();

map<string, pair<double, double>> count_freqs(vector<string> &artwork1, vector<string> &artwork2, vector<string>& params);
pair<vector<string>, vector<string>> get_sholokhov_texts();
void plot_sholokhov_data(void);
vector<string> get_author_paths();
void load_author_books();
vector<string> get_files_texts(vector<vector<string>>&& texts);



using scary_val = map<string, pair<double, double>>;

struct artwork
{
	string name;
	string path;
	vector<string> content;
};

struct author_books
{
	string name;
	string path;
	vector<artwork> artworks;
};