#include "art_parser.h"


vector<author_books> all_author_books;

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


vector<string> parse_data(const string& data)
{
	vector<string> splitted = split_words(data);
	vector<string> res;

	for (auto& s : splitted) if (!is_rus_capital(s[0])) res.push_back(s);

	return res;
}


vector<string> parse_text(const string& filename)
{
	return parse_data(readFile(filename));
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

vector<string> get_author_paths()
{
	string base = R"(D:\Projects\Literature_analyzer\res\Books\Loading)";
	return lsdir(base);
}

void load_author_books()
{
	vector<string> paths = get_author_paths();
	for(auto& author_path : paths) {
		author_books &this_author = all_author_books.emplace_back();
		this_author.path = author_path;
		this_author.name = split(author_path, {'\\', '/'}).back();
		// cout << this_author.name << " " << this_author.path << " " << endl;
		vector<string> dirs;
		try {
			dirs = lsdir(author_path);
		}
		catch (exception & e) {
			cout << e.what() << endl;
		}
		for(auto& artwork_path : dirs) {
			artwork& this_artwork = this_author.artworks.emplace_back();
			this_artwork.path = artwork_path;
			this_artwork.name = split(artwork_path, {'/', '\\'}).back();
			string text_path = this_artwork.path + "\\text.txt";

			// cout << text_path << endl;
			
			if (find_files(artwork_path, ".txt").empty()) continue;

			
			string raw_data = readFile(text_path);
			
			this_artwork.content = parse_data(raw_data);
			
			// cout << this_author.name << " " << this_artwork.name << endl;
		}
	}
}

