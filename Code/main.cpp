#include "dependencies.h"


int main()
{
	std::cout << "Current settings: \n";
	std::cout << "\t-Picture resolution: " << res << " x " << res << " pixels\n";
	std::cout << "\t-Number of samples per pixel: " << samples << "\n";
	std::cout << "\t-Number of shadow rays: " << shadow_rays << "\n";
	std::cout << "\t-Number of bounces on diffuse surfaces: " << diff_bounces << "\n";
	std::cout << "\t-Importance threshold: " << treshold_importance << "\n";
	std::cout << "\t-Minimum absorption: " << minimum_absorp << "\n";
	std::cout << "\t-Maximum absorption: " << maximum_absorp << "\n";
	std::cout << "\t-Diffuse standard reflectance: " << diff_ref << "\n";
	std::cout << "\t-Global color contribution: " << g_color_contribution << "\n";
	std::cout << "\t-Maximum ray depth: " << maximum_ray_depth << "\n";
	std::cout << "\n";

	
	//Create the whole thing
	Room room;


	return 0;
}