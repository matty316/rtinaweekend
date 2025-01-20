#pragma once

struct interval {
	float min, max;
	interval() : min(+INFINITY), max(-INFINITY) {}
	interval(float min, float max) : min(min), max(max) {}
	
	float size() const {
		return max - min;
	}

	bool contains(float x) const {
		return min <= x && x <= max;
	}

	bool surrounds(float x) const {
		return min < x && x < max;
	}

	float clamp(float x) const {
		if (x < min)
			return min;
		if (x > max)
			return max;
	}

	static const interval empty, universe;
};

const interval interval::empty = interval(+INFINITY, -INFINITY);
const interval interval::universe = interval(-INFINITY, +INFINITY);
