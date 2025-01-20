#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

#include <memory.h>
#include <iostream>

inline float random_float() {
	return glm::linearRand(0.0f, 1.0f);
}

#include "vec.h"
#include "interval.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "camera.h"
