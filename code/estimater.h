#pragma once

#include <mylibs.hpp>

#define DEBUG_ESTIMATER 0

map<string, pair<double, double>> get_logariphmated_freqs(map<string, pair<double, double>>& data);

inline double point_line_dist(point p)
{
	return abs(p.x - p.y) / sqrt(2);
}

inline void pre_estimove_points(map<string, pair<double, double>>& data)
{
	for(auto &p : data) {
		double x = p.second.first, y = p.second.second;
		double k = sqrt(exp(x)) + sqrt(exp(y));
		auto d = point_line_dist({ x, y });
		double sgn_k = (x > y) ? (-1) : (1);

		double dx0 = - d * sgn_k / sqrt(2), dy0 = d * sgn_k / sqrt(2);
		double dx1 = dx0 * k, dy1 = dy0 * k;

#if  DEBUG_ESTIMATER
		cout << x << " " << y << " " << d << " " << dx0 << " " << dx1 << endl;
#endif

		p.second = {p.second.first - dx0 + dx1, p.second.second - dy0 + dy1};
	}
}

inline double estimate_sigma(map<string, pair<double, double>>& data)
{
	vector<double> vals;
	vals.reserve(data.size());
	for (auto& p : data) vals.push_back(point_line_dist({ p.second.first, p.second.second }) * sgn(p.second.first - p.second.second));
	double s = square(sigma(vals));
	return s;
}

