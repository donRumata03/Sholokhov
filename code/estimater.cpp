#include <mylibs.hpp>

map<string, pair<double, double>> get_logariphmated_freqs(map<string, pair<double, double>>& data)
{
	double min_freq = 1;
	for (auto& p : data) {
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