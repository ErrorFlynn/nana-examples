/*
	This example shows how to implement a simple splash screen that displays
	an image loaded from a Bitmap file. I have used Visual Studio to build
	the example, and I have tested using the file that can be found here: 
	https://github.com/ErrorFlynn/nana-examples/blob/master/splash_screen.bmp
*/

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

#include <cassert>

int main()
{
	using namespace nana;

	form fm; // main form
	
	// This is the splash window. If its size is different than the size of the image,
	// the image will be stretched to fill it.
	form splash(API::make_center(1280, 720), appear::bald<>());

	// check if the image file exists
	assert(std::experimental::filesystem::exists("splash_screen.bmp"));

	paint::image img{"splash_screen.bmp"};
	assert(!img.empty()); // check if the image loaded
	
	drawing{splash}.draw([&](paint::graphics &graph)
	{
		rectangle r_src{point{0, 0}, img.size()};
		rectangle r_dst{point{0, 0}, splash.size()};
		img.stretch(r_src, graph, r_dst);
	});
	
	splash.show();
	splash.events().unload([&] { fm.show(); });

	timer t;
	t.elapse([&] { splash.close(); });
	t.interval(3000); // the splash window will be displayed for 3000 milliseconds
	t.start();

	exec();
}
