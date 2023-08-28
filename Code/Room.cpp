
#include "Dependencies.h"


Room::Room() {
	createRoom();
}

void Room::createRoom() {

	std::cout << "Creating camera\n";
	vec3 main_observer(-2, 0, 0);
	vec3 sub_observer(-1, 0, 0);
	Camera camera(main_observer, sub_observer);
	std::cout << "----------------------------\n";
	std::cout << "Changing to secondary observer\n";
	camera.toggleObserver();
	std::cout << "----------------------------\n";
	std::cout << "Creating scene\n";
	Scene scene;
	std::cout << "----------------------------\n";
	std::cout << "Creating all materials\n";
	std::cout << "----------------------------\n";
	std::cout << "Setting up room\n";


	Mirror mirror{};
	Light white_light{ white, 30.0 };
	Light red_light{ red, 40.0 };
	Light blue_light{ blue, 40.0 };
	Light green_light{ green, 1.0 };
	DiffuseLambertian white_lambertian{ white, diff_ref };
	DiffuseLambertian black_lambertian{ black, diff_ref };
	DiffuseLambertian red_lambertian{ red, diff_ref };
	DiffuseLambertian green_lambertian{ green, diff_ref };
	DiffuseLambertian blue_lambertian{ blue, diff_ref };
	DiffuseLambertian cyan_lambertian{ cyan, diff_ref };
	DiffuseLambertian teal_lambertian{ teal, diff_ref };
	DiffuseLambertian purple_lambertian{ purple, diff_ref };
	DiffuseLambertian yellow_lambertian{ yellow, diff_ref };
	DiffuseLambertian pink_lambertian{ pink, diff_ref };


	//Top
	const vec3 P1 = vec3(0.0f, 6.0f, -5.0f); 
	const vec3 P2 = vec3(-3.0f, 0.0f, -5.0f);
	const vec3 P3 = vec3(0.0f, -6.0f, -5.0f);
	const vec3 P4 = vec3(10.0f, -6.0f, -5.0f);
	const vec3 P5 = vec3(13.0f, 0.0f, -5.0f);
	const vec3 P6 = vec3(10.0f, 6.0f, -5.0f);

	//Bottom
	const vec3 P7 = vec3(0.0f, 6.0f, 5.0f);
	const vec3 P8 = vec3(-3.0f, 0.0f, 5.0f);
	const vec3 P9 = vec3(0.0f, -6.0f, 5.0f);
	const vec3 P10 = vec3(10.0f, -6.0f, 5.0f);
	const vec3 P11 = vec3(13.0f, 0.0f, 5.0f);
	const vec3 P12 = vec3(10.0f, 6.0f, 5.0f);

	//Square light												
	const vec3 P13 = vec3(6.0f, -1.0f, -4.8f);
	const vec3 P14 = vec3(5.0f, -3.0f, -4.8f);
	const vec3 P15 = vec3(5.0f, -1.0f, -4.8f);
	const vec3 P16 = vec3(6.0f, -3.0f, -4.8f);//4.8f

	//Lamp border (Punkter som beskriver en ram för lampan.)
	const vec3 P17 = vec3(5.0f, -1.0f, -4.8f); //A
	const vec3 P18 = vec3(5.0f, -1.0f, -5.0f); //B

	const vec3 P19 = vec3(5.0f, -3.0f, -5.0f); //C
	const vec3 P20 = vec3(5.0f, -3.0f, -4.8f); //D
	
	const vec3 P21 = vec3(6.0f, -1.0f, -4.8f); //E
	const vec3 P22 = vec3(6.0f, -1.0f, -5.0f); //F

	const vec3 P23 = vec3(6.0f, -3.0f, -5.0f); //G
	const vec3 P24 = vec3(6.0f, -3.0f, -4.8f); //H

	//Top
	Triangle triangle1 = Triangle(P1, P3, P2, &purple_lambertian);
	Triangle triangle2 = Triangle(P4, P5, P6, &purple_lambertian);
	Rectangle rectangle1 = Rectangle(P1, P3, P4, P6, &purple_lambertian);

	//Bottom
	Triangle triangle5 = Triangle(P7, P8, P9, &pink_lambertian);
	Triangle triangle6 = Triangle(P12, P11, P10, &pink_lambertian);
	Rectangle rectangle2 = Rectangle(P7, P12, P10, P9, &pink_lambertian);

	//Wall 1 Front center
	Rectangle rectangle3 = Rectangle(P3, P9, P10, P4, &blue_lambertian);

	//Wall 2 Front left (left of from inside)
	Rectangle rectangle4 = Rectangle(P10, P11, P5, P4, &mirror);

	//Wall 3 Back right (right of camera)
	Rectangle rectangle5 = Rectangle(P12, P6, P5, P11, &green_lambertian);

	//Wall 4 Back cénter
	Rectangle rectangle6 = Rectangle(P12, P7, P1, P6, &cyan_lambertian);

	//Wall 5
	Rectangle rectangle7 = Rectangle(P7, P8, P2, P1, &white_lambertian);

	//Wall 6
	Rectangle rectangle8 = Rectangle(P2, P8, P9, P3, &white_lambertian);

	//Lamp borders										
	Triangle triangle21 = Triangle(P17, P18, P19, &black_lambertian);
	Triangle triangle22 = Triangle(P17, P19, P20, &black_lambertian);
	Triangle triangle23 = Triangle(P17, P21, P18, &black_lambertian);
	Triangle triangle24 = Triangle(P18, P21, P22, &black_lambertian);
	Triangle triangle25 = Triangle(P21, P23, P22, &black_lambertian);
	Triangle triangle26 = Triangle(P21, P24, P23, &black_lambertian);
	Triangle triangle27 = Triangle(P19, P23, P24, &black_lambertian);
	Triangle triangle28 = Triangle(P19, P24, P20, &black_lambertian);

	//Top
	scene.addObject(&triangle1);
	scene.addObject(&triangle2);
	scene.addObject(&rectangle1);

	//Bottom
	scene.addObject(&triangle5);
	scene.addObject(&triangle6);
	scene.addObject(&rectangle2);

	//Walls
	scene.addObject(&rectangle3);
	scene.addObject(&rectangle4);
	scene.addObject(&rectangle5);
	scene.addObject(&rectangle6);
	scene.addObject(&rectangle7);
	scene.addObject(&rectangle8);

	scene.addObject(&triangle21);
	scene.addObject(&triangle22);
	scene.addObject(&triangle23);
	scene.addObject(&triangle24);
	scene.addObject(&triangle25);
	scene.addObject(&triangle26);
	scene.addObject(&triangle27);
	scene.addObject(&triangle28);

	std::cout << "----------------------------\n";
	std::cout << "Adding purple sphere\n";
	Sphere s1{ vec3(5.0f, -3.0f, 3.0f), 1.5f, &red_lambertian };
	scene.addObject(&s1);
	std::cout << "----------------------------\n";

	std::cout << "Adding yellow sphere\n";
	Sphere s2{ dvec3(8.0f, 2.5f, 0.65f), 1.0f, &yellow_lambertian };
	scene.addObject(&s2);
	std::cout << "----------------------------\n";

	std::cout << "Adding white box\n";
	Box b2 = Box(vec3(8.0f, 3.0f, 3.5f), 3.5f, 3.5f, 3.5f, &white_lambertian);
	scene.addBox(&b2);
	std::cout << "----------------------------\n";
	std::cout << "Number of objects: " << scene.objects.size() << "\n";
	std::cout << "----------------------------\n";

	std::cout << "Adding square area light\n";										
	Triangle al1 = Triangle(P14, P13, P15, &white_light);
	Triangle al2 = Triangle(P16, P13, P14, &white_light); 
	scene.addAreaLight(&al1);
	scene.addAreaLight(&al2);
	std::cout << "Number of area lights: " << scene.area_lights.size() << "\n";
	std::cout << "----------------------------\n";

	std::cout << "Rendering scene\n";
	auto start_time{ std::chrono::high_resolution_clock::now() };
	camera.render(scene, 0, res, 0, res);

	auto end_time{ std::chrono::high_resolution_clock::now() };
	std::cout << "----------------------------\n";
	auto seconds{ std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() };
	auto minutes = std::floor(seconds / 60);
	seconds = seconds % 60;
	std::cout << "Rendered in " << minutes << " minutes and " << seconds << " seconds.\n";
	std::cout << "----------------------------\n";
	std::cout << "Creating image\n";
	std::ostringstream file_path;
	file_path << "../Project/Renderings/samples-" << samples << "_sray-" << shadow_rays << "_diff_b-" << diff_bounces
		<< "_dif_r-" << diff_ref << "_g_color-" << g_color_contribution << "_test_2022-11-06_" << ".png";
	const std::string s = file_path.str();
	camera.createImage(s.c_str());
	std::cout << "Image created!\n";

}
