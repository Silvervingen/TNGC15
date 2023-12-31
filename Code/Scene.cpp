#include "dependencies.h"

void Scene::addObject(Object* obj) //Could just make a function addObject
{
	objects.push_back(obj);
}

void Scene::addAreaLight(Object* light)
{
	area_lights.push_back(light);
	//Add lights to the scene to see them
	objects.push_back(light);
}

void Scene::addBox(Box* box)
{
	for (int i = 0; i < box->triangles.size(); ++i) {
		addObject(&box->triangles[i]);
	}
}

// Sets the target variable in the input ray
void Scene::rayTarget(Ray& ray) const
{
	float closest_obj = std::numeric_limits<double>::max();

	for (Object* obj : this->objects) {
		float hitX = obj->rayIntersection(&ray);
		if (hitX > 0.0f && hitX < closest_obj) {
			closest_obj = hitX;
			ray.target = obj;
			ray.setEnd(closest_obj);
		}
	}
}

dvec3 Scene::localLighting(Ray& ray) const
{
	dvec3 final_color = black;

	if (ray.target == nullptr) return final_color;

	if (ray.target->material->emittance != 0.0) {
		return ray.target->material->color;
	}

	//According to Lesson
	for (Object* light_source : this->area_lights) {

		dvec3 this_light = black;

		vec3 end_offset = ray.end + ray.target->getNormal(ray.end) * ray_offset;
		std::vector<Ray> shadow_rays = light_source->generateShadowRays(end_offset);

		for (Ray& sr : shadow_rays) {

			bool occluded = false;
			float target_length = glm::length(sr.end - sr.start);

			vec3 targetNormal = ray.target->getNormal(ray.end);
			vec3 lightNormal = light_source->getNormal(sr.end);

			double alpha = glm::dot(targetNormal, sr.direction);
			double beta = glm::dot(-sr.direction, lightNormal);
			double cos_term = alpha * beta;
			cos_term = glm::max(cos_term, 0.0);

			for (Object* shadow_object : this->objects) {

				Ray temp = sr;

				if (shadow_object->material->emittance == 0.0) {
					float hit_x = shadow_object->rayIntersection(&sr);

					temp.setEnd(hit_x);

					if (hit_x > epsilon&& glm::length(temp.end - temp.start) < target_length) {
						occluded = true;
						break;
					}
				}
			}
			// Ray intersection is occluded if the intersected ray is shorter than the original ray
			if (!occluded) {
				double dropoff = glm::pow(glm::length(sr.end - sr.start), 2);
				this_light += light_source->material->emittance * cos_term * light_source->material->color / (dropoff * area_lights.size());
			}
		}
		final_color += this_light / static_cast<double>(shadow_rays.size());
	}
	return final_color * ray.target->material->color;
}

// Creates a tree structure of rays none-recursivly 
// We first create all rays and when we reach the end we set the rays color
// Each ray can have any number of children that will all contribute to the result
void Scene::traceRay(std::shared_ptr<Ray>& root) const
{
	std::shared_ptr<Ray> current = root;

	while (true)
	{
		// Sets color from local lighting for leaf node
		if (current->importance < treshold_importance)
		{
			this->rayTarget(*current);

			if (current->target == nullptr)
			{
				break;
			}
			current->is_leaf = true;

			dvec3 local_color = this->localLighting(*current);
			current->radiance = glm::length(local_color);
			current->color = local_color;// * current->radiance;
			current = current->parent;
		}
		// Create child rays if there are none and current isn't a leaf node
		else if (current->children.size() == 0)
		{
			this->rayTarget(*current);

			if (current->target == nullptr)
			{
				break;
			}
			std::vector<Ray> child_rays = current->target->material->brdf(current);

			for (Ray& r : child_rays)
			{
				r.parent = current;
				current->children.push_back(std::make_shared<Ray>(r));
			}
		}
		// Iterate through the child nodes, if they are all leaves, evaluate color, delete children, make current a leaf and set current to parent.
		// If a child branch is not yet evaluated, evaluate that branch by setting current to that child.
		else
		{
			bool evaluate = true;
			for (std::shared_ptr<Ray>& child : current->children)
			{
				//if evaluation of child branch is needed
				if (!child->is_leaf)
				{
					current = child;
					evaluate = false;
					break;
				}
			}

			if (evaluate)
			{
				dvec3 local_color = this->localLighting(*current);
				current->radiance = glm::length(local_color);

				for (std::shared_ptr<Ray>& child : current->children)
				{
					current->radiance += child->radiance * child->importance / current->importance;

				}
				current->color = local_color * current->radiance;
				for (std::shared_ptr<Ray>& child : current->children)
				{
					current->color += child->color * g_color_contribution;
					child.reset();
				}

				// Reached the root
				if (current->parent == nullptr)
				{
					current.reset();	// Current and root points to the same ray, delete the extra node
					break;	
					//end
				}
				current->is_leaf = true;
				current = current->parent;
			}
		}
	}
}