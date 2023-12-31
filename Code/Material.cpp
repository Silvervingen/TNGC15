#include "dependencies.h"

Material::Material()
	: color{ black }, emittance{ 0.0 }
{
	this->absorption = minimum_absorp + (maximum_absorp - minimum_absorp) * glm::length(color) / glm::length(white);
}

Material::Material(const dvec3& color)
	: color{ color }, emittance{ 0.0 }
{
	this->absorption = minimum_absorp + (maximum_absorp - minimum_absorp) * glm::length(color) / glm::length(white);
}

Material::Material(const dvec3& color, double emittance)
	: color{ color }, emittance{ emittance }
{
	this->absorption = minimum_absorp + (maximum_absorp - minimum_absorp) * glm::length(color) / glm::length(white);
}


Mirror::Mirror()
{
	this->absorption = 0.0;
}

std::vector<Ray> Mirror::brdf(const std::shared_ptr<Ray>& incoming) const
{
	double reflected_importance = 0.0;

	if (incoming->depth < maximum_ray_depth)
	{
		reflected_importance = incoming->importance;
	}

	Ray reflected_ray{ incoming->end + incoming->target->getNormal(incoming->end) * ray_offset,	// Start with offset
				glm::normalize(glm::reflect(incoming->end, incoming->target->getNormal(incoming->end))),	// Perfect reflection
				reflected_importance };

	reflected_ray.depth = incoming->depth + 1;

	std::vector<Ray> reflected;
	reflected.push_back(reflected_ray);

	return reflected;
}

DiffuseLambertian::DiffuseLambertian(dvec3 color, double reflectance)
	: Material(color), reflectance{ reflectance }{};

std::vector<Ray> DiffuseLambertian::brdf(const std::shared_ptr<Ray>& incoming) const
{

	vec3 Z = incoming->target->getNormal(incoming->end);
	vec3 X = glm::normalize(incoming->direction - glm::dot(incoming->direction, Z) * Z);
	vec3 Y = normalize(cross(-X, Z));

	// Local coordinates
	glm::mat4 M{ X.x, X.y, X.z, 0.0f,
				Y.x, Y.y, Y.z, 0.0f,
				Z.x, Z.y, Z.z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f };

	std::vector<Ray> reflected;

	for (int i = 0; i < diff_bounces; ++i)
	{
		double phi = (static_cast<double>(rand()) / RAND_MAX) * 2 * M_PI;	// [0, 2*PI] around the normal
		double theta = (static_cast<double>(rand()) / RAND_MAX)* M_PI_2;	// [0, PI/2] towards the normal

		// Cartesian coordinates
		float x = cos(phi) * sin(theta);
		float y = sin(phi) * sin(theta);
		float z = cos(theta);
		vec3 local_dir = vec3(x, y, z);

		// Transform direction to world coordinates
		vec3 world_dir = glm::inverse(glm::transpose(M)) * glm::vec4(local_dir, 1.0);
		//vec3 worldDir = glm::inverse(M) * glm::vec4(localDir, 1.0); 

		// Russian Roulette for ref
		double reflected_importance = 0.0;
		if (static_cast<double>(rand()) / RAND_MAX < this->absorption)
		{
			reflected_importance = incoming->importance * this->reflectance / (this->absorption * diff_bounces);
		}

		Ray reflected_ray{ incoming->end + incoming->target->getNormal(incoming->end) * ray_offset, world_dir, reflected_importance };

		reflected_ray.depth = incoming->depth + 1;

		reflected.push_back(reflected_ray);
	}

	return reflected;
}

Light::Light(dvec3 color, double emittance)
	: Material(color, emittance) {};

std::vector<Ray> Light::brdf(const std::shared_ptr<Ray>& incoming) const
{
	double reflected_importance = 0.0;

	Ray stopped{ incoming->end, glm::normalize(glm::reflect(incoming->end, incoming->target->getNormal(incoming->end))), reflected_importance };

	std::vector<Ray> result;

	result.push_back(stopped);

	return result;
}











