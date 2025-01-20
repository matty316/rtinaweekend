#pragma once

struct camera {
public:
	float aspect_ratio = 1.0f;
	int image_width = 100;
	int samples_per_pixel = 10;
	int max_depth = 10;

	float vfov = 90;
	point lookfrom{ 0.0f,0.0f,0.0f };
	point lookat{ 0.0f, 0.0f, -1.0f };
	glm::vec3 vup{ 0.0f, 1.0f, 0.0f };

	float defocus_angle = 0.0f;
	float focus_dist = 10.0f;

	void render(const hittable& world) {
		init();

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++) {
			std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
			for (int i = 0; i < image_width; i++) {
				color pixel_color{ 0.0f, 0.0f, 0.0f };
				for (int sample = 0; sample < samples_per_pixel; sample++) {
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth, world);
				}
				write_color(std::cout, pixel_samples_scale * pixel_color);
			}
		}

		std::clog << "\r Done.                    \n";
	}
private:
	int image_height;
	point center;
	point pixel00_loc;
	glm::vec3 pixel_delta_u;
	glm::vec3 pixel_delta_v;
	float pixel_samples_scale;
	glm::vec3 u, v, w;
	glm::vec3 defocus_disk_u;
	glm::vec3 defocus_disk_v;

	void init() {
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		pixel_samples_scale = 1.0f / samples_per_pixel;

		center = lookfrom;
		
		auto theta = glm::radians(vfov);
		auto h = glm::tan(theta / 2.0f);
		auto viewport_height = 2.0f * h * focus_dist;
		auto viewport_width = viewport_height * (float(image_width) / image_height);

		w = glm::normalize(lookfrom - lookat);
		u = glm::normalize(glm::cross(vup, w));
		v = glm::cross(w, u);

		auto viewport_u = viewport_width * u;
		auto viewport_v = viewport_height * -v;

		pixel_delta_u = viewport_u / float(image_width);
		pixel_delta_v = viewport_v / float(image_height);

		auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2.0f - viewport_v / 2.0f;
		pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);

		auto defocus_radius = focus_dist * glm::tan(glm::radians(defocus_angle / 2.0f));
		defocus_disk_u = u * defocus_radius;
		defocus_disk_v = v * defocus_radius;
	}

	ray get_ray(int i, int j) const {
		auto offset = sample_square();
		auto pixel_sample = pixel00_loc + ((i + offset.x) * pixel_delta_u) + ((j + offset.y) * pixel_delta_v);

		auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
		auto ray_direction = pixel_sample - ray_origin;

		return ray(ray_origin, ray_direction);
	}

	glm::vec3 sample_square() const {
		return glm::vec3(random_float() - 0.5f, random_float() - 0.5f, 0.0f);
	}

	point defocus_disk_sample() const {
		auto p = random_in_unit_disk();
		return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
	}

	color ray_color(const ray& r, int depth, const hittable& world) {
		if (depth <= 0)
			return color(0.0f, 0.0f, 0.0f);

		hit_record rec;
		if (world.hit(r, interval(0.001f, INFINITY), rec)) {
			ray scattered;
			color attenuation;
			if (rec.mat->scatter(r, rec, attenuation, scattered))
				return attenuation * ray_color(scattered, depth - 1, world);
			return color(0.0f, 0.0f, 0.0f);
		}
		glm::vec3 unit_direction = glm::normalize(r.direction);
		auto a = 0.5f * (unit_direction.y + 1.0f);
		return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
	}
};