#include <mylibs.hpp>
#include <Windows.h>
#include "art_parser.h"
#include "estimater.h"
#include "plotter.h"

extern vector<author_books> all_author_books;

void plot_sholokhov_data()
{
	auto [don, others] = get_sholokhov_texts();
	auto params = get_all_nareches();
	auto freqs = count_freqs(don, others, params);
	// add_to_plot_scary_val(freqs);
	// show_plot();
	auto logged = get_logariphmated_freqs(freqs);
	cout << logged << endl;

	pre_estimove_points(logged);

	cout << logged << endl;
	double sigma = estimate_sigma(logged);

	cout << sigma << endl;
	
	// add_to_plot_scary_val(logged);
	// show_plot();
	// add_to_plot();
	return sigma;
}


void plot_all_sigmas()
{
	vector<double> sigmas;
	vector<double> author_sigmas;
	auto params = get_all_nareches();
	load_author_books();
	for (auto& a : all_author_books) {
		cout << a.name << endl;
		double this_ssum = 0;
		size_t art_counter = 0;
		vector<vector<string>> texts;
		for(auto & pr : a.artworks) {
			texts.push_back(pr.content);
		}
		vector<string> all_author_arts = get_files_texts(move(texts));
		if (all_author_arts.size() < 1000000) continue;
		for (auto & extra_stuff : a.artworks) {
			if (extra_stuff.content.empty()) continue;
			if (extra_stuff.content.size() < 50000) continue;
			scary_val v = count_freqs(extra_stuff.content, all_author_arts, params);
			auto logged = get_logariphmated_freqs(v);
			pre_estimove_points(logged);
			double this_sigma = estimate_sigma(logged);

			cout << this_sigma << endl;
			this_ssum += this_sigma;
			art_counter++;




			sigmas.push_back(this_sigma);



			
		}
		author_sigmas.push_back(this_ssum / art_counter);
	}

	cout << endl << sigmas << endl;
	
	auto ps = count_number_density(sigmas, 0.1, 10000, 1);
	auto author_ps = count_number_density(author_sigmas, 0.1, 10000, 1);
	add_to_plot(ps);
	add_to_plot(author_ps);
	show_plot();
}


void existing()
{
	string s = string(R"(D:\Projects\Tests\sup\out.txt)");
	auto aa = readFile(s);
	vector<string> vals = split_lines(aa);
	cout << vals[3];
	vector<double> valss;
	for(auto& val : vals) {
		stringstream ss;
		ss << val;
		double b;
		ss >> b;
		valss.push_back(b);
	}

	auto ps = count_number_density(valss, 0.1, 10000, 1);
	add_to_plot(ps);
	show_plot();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	plot_all_sigmas();
	// load_author_books();
	// plot_sholokhov_data();
	// plot_sholokhov_data();
	// print(parse_text(s));
	
	return 0;
}

