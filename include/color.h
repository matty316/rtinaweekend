#pragma once

#include <iostream>

using color = glm::vec3;

inline float linear_to_gamma(float linear_component) {
	if (linear_component > 0)
		return glm::sqrt(linear_component);

	return 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
	auto r = pixel_color.r;
	auto g = pixel_color.g;
	auto b = pixel_color.b;

	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	static const interval intensity(0.000f, 0.999f);
	int rbyte = int(255 * intensity.clamp(r));
	int gbyte = int(255 * intensity.clamp(g));
	int bbyte = int(255 * intensity.clamp(b));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}