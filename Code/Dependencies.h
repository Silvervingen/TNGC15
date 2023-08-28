#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef TYPEDEFS_DEPENDENCIES
#define TYPEDEFS_DEPENDENCIES

// Constants
constexpr auto epsilon = 1e-4;
constexpr float ray_offset = 3e-2f;
// Settings
constexpr auto minimum_absorp = 0.65;
constexpr auto maximum_absorp = 0.90;

constexpr int maximum_ray_depth = 10;
constexpr int diff_bounces = 1;
constexpr int shadow_rays = 1;
constexpr int samples = 4; 

constexpr float treshold_importance = 0.1f;

constexpr double diff_ref = 0.2;
constexpr double g_color_contribution = 0.3;

constexpr size_t res = 800;



#include <glm.hpp>
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <cstdlib>
#include <math.h>
#include <sstream>
#include <chrono>
#include <thread>

typedef glm::dvec3 dvec3;
typedef glm::vec3 vec3;

//Colors
const dvec3 red{ 1.0, 0.0, 0.0 };
const dvec3 green{ 0.0, 1.0, 0.0 };
const dvec3 blue{ 0.0, 0.0, 1.0 };
const dvec3 white{ 1.0, 1.0, 1.0 };
const dvec3 black{ 0.0, 0.0 ,0.0 };
const dvec3 purple{ 1.0, 0.0, 1.0 };
const dvec3 yellow{ 1.0, 1.0, 0.0 };
const dvec3 cyan{ 0.0, 1.0, 1.0 };
const dvec3 teal{ 0.0, 0.5, 0.5 };
const dvec3 pink{ 1.0, 0.4, 0.7 };

// Forward declarations
//struct PointLight;
struct Pixel;
struct Object;
struct Scene;
struct Ray;
struct Camera;
struct Material;

#include "Pixel.h"
#include "Objects.h"
#include "Scene.h"
#include "Ray.h"
#include "Camera.h"
#include "Material.h"
#include <stdlib.h>
#include <math.h>
#include "Room.h"

#endif