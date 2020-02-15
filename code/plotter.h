#pragma once

#include <mylibs.hpp>

inline void add_to_plot_scary_val(map<string, pair<double, double>>& data)
{
	pms for_plot;
	for (auto& p : data) for_plot.push_back({ p.second.first, p.second.second });
	add_to_plot(for_plot, "default", "scatter");
}