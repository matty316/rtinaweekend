#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

#include <memory.h>
#include <iostream>

inline float random_float() {
	return glm::linearRand(0.0f, 1.0f);
}

inline float random_float(float min, float max) {
	return glm::linearRand(min, max);
}

#include "vec.h"
#include "interval.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "material.h"
#include "camera.h"
