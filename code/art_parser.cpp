#include "art_parser.h"

vector<string> get_all_art_files()
{
	auto alls = find_files(R"(D:\Projects\Sholokhov\data\decoded\other)", ".txt");
	/*
	vector<string> ans = {
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\bahchevnik.txt", 
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\batraki.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\chervotochina.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\donprodkom.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\dorozhenka.txt",
		R"(D:\Projects\Sholokhov\data\decoded\\other\dvuhmuzhnyaya.txt)",
		R"(D:\Projects\Sholokhov\data\decoded\\other\\ilyuha.txt)",
		R"(D:\Projects\Sholokhov\data\\decoded\other\\kaloshi.txt)",
		R"(D:\Projects\Sholokhov\data\\decoded\other\\kolchak.txt)",
		R"(D:\Projects\Sholokhov\data\decoded\\other\\kolovert.txt)",
		"D:\\Projects\\Sholokhov\\data\decoded\\other\\krov.txt",
		R"(D:\Projects\Sholokhov\data\\decoded\other\\myagkotelyj.txt)",
		"D:\\Projects\\Sholokhov\\data\decoded\\other\\nahalenok.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\obida.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\pastuh.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\predsedatel.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\prodkomissar.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\rodina.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\rodinka.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\semejnyj.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\semya.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\serdtse.txt",
		"D:\\Projects\\\Sholokhov\\data\\decoded\\other\\slovo.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\step.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\stezhka.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\tselina.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\vrag.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\yazik.txt",
		"D:\\Projects\\Sholokhov\\data\\decoded\\other\\zherebenok.txt"
	};
	*/
	return alls;
}

vector<string> get_all_nareches()
{
	string filename = R"(D:\Projects\Sholokhov\data\decoded\_phrases.txt)";
	string s = readFile(filename);
	auto v = split_lines(s);
	vector<string> res;
	for (auto& val : v) if (!is_space_word(val)) res.push_back(val); else cout << "Spacieve phrase detected! (" << val << ")" << endl;
	return res;
}

static size_t count_all_of(string &resource, string& val)
{
	size_t res = 0;
	size_t last_pos = 0;
	
	while(true) {
		auto pos = resource.find(val, last_pos + val.size());
		if (pos == string::npos) return res;
		res++;
		last_pos = pos;
	}
}


map<string, pair<double, double>> count_freqs(vector<string>& artwork1, vector<string>& artwork2, vector<string>& params)
{
	string a1 = join(" ", artwork1);
	string a2 = join(" ", artwork2);


	map<string, pair<double, double>> res;
	
	for (auto& param : params) {
		res[param] = pair(double(count_all_of(a1, param)) / a1.size(), double(count_all_of(a2, param)) / a2.size());
		// cout << param << " " << res[param] << " " << double(res.size()) / params.size() * 100 << "%" << endl;
	}

	return res;
}


vector<string> parse_text(const string& filename)
{
	auto raw_data = readFile(filename);
	vector<string> splitted = split_words(raw_data);
	vector<string> res;
	
	for (auto& s : splitted) if (!is_rus_capital(s[0])) res.push_back(s);

	return res;
}


vector<string> get_files_texts(vector<vector<string>>&& texts)
{
	vector<string> res;
	size_t s = 0;
	for (auto& v : texts) s += v.size();
	res.reserve(s + 10);

	for (auto& t : texts) {
		for (auto & ss : t)
			res.emplace_back(ss);
	}

	return res;
}


pair<vector<string>, vector<string>> get_sholokhov_texts()
{
	auto paths = get_all_art_files();
	vector<vector<string>> texts;
	for (auto& path : paths) texts.emplace_back(parse_text(path));
	auto others = get_files_texts(move(texts));
	vector<string> don = parse_text(R"(D:\Projects\Sholokhov\data\decoded\_don.txt)");

	// cout << join("", don).size() << " " << join("", others).size() << endl;
	return {don, others};
}

map<string, pair<double, double>> get_logariphmated_freqs(map<string, pair<double, double>>& data)
{
	double min_freq = 1;
	for(auto& p : data) {
		min_freq = min(min_freq, ((p.second.first == 0) ? (1.0) : (p.second.first)));
		min_freq = min(min_freq, ((p.second.second == 0) ? (1.0) : (p.second.second)));
	}

	map<string, pair<double, double>> res;
	for (auto& p : data) {
		if (p.second.first != 0 || p.second.second != 0) res[p.first] = {
			(p.second.first == 0) ? (log(min_freq / 10)) : (log(p.second.first)),
			(p.second.second == 0) ? (log(min_freq / 10)) : (log(p.second.second)),
		};
	}
	return res;
}

void plot_sholokhov_data()
{
	auto [don, others] = get_sholokhov_texts();
	auto params = get_all_nareches();
	auto freqs = count_freqs(don, others, params);
	auto logged = get_logariphmated_freqs(freqs);
	cout << logged << endl;
	pms for_plot;
	for (auto& p : logged) for_plot.push_back({ p.second.first, p.second.second });
	add_to_plot(for_plot, "green", "scatter");
	show_plot();
}
