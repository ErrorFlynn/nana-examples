/*
	This example shows how to implement a splash screen that displays some
	text and an image loaded from a file. I have used Visual Studio to build
	the example, and I have tested using this image file:
	https://github.com/ErrorFlynn/nana-examples/blob/master/splash_screen.bmp

	BE ADVISED: Nana release 1.6.2 has a bug in the `label` widget that causes
	newline characters ('\n') to be displayed as two new lines instead of one.
	The bug is fixed in branch "hotfix-1.6.2" and subsequent releases.
*/

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/widgets/label.hpp>

#include <cassert>

int main()
{
	using namespace nana;

	form fm; // main form

	form splash(API::make_center(1280, 720), appear::bald<>());
	splash.bgcolor(color{"#e8dcc8"});

	// check if the image file exists
	assert(std::experimental::filesystem::exists("splash_screen.bmp"));

	paint::image img{"splash_screen.bmp"};
	assert(!img.empty()); // check if the image loaded

	picture pic{splash};
	pic.load(img);
	pic.stretchable(true); // scales the image preserving the aspect ratio

	label text_top{splash};
	text_top.format(true);
	text_top.text_align(align::center, align_v::center);
	text_top.caption("<bold size=60 color=0x234567>Nana C++ Library</>");
	text_top.bgcolor(colors::white);

	label text_bot{splash};
	text_bot.format(true);
	text_bot.text_align(align::center, align_v::center);
	text_bot.caption("<size=30 green>splash screen\n\n\n</><size=10>to stare at for eight seconds\n\n\n</>"
		"<size=20 color=0x663300>cotidie damnatur qui semper timet\n\n\n\n</>");
	text_bot.bgcolor(color{"#fff9f0"});

	// this layout places the picture in the top left corner, and gives it a size of 455x256 px
	splash.div("vert margin=3 <weight=256 <pic weight=455> <weight=3> <text_top> > <text_bot margin=[3]>");

	splash["pic"] << pic;
	splash["text_top"] << text_top;
	splash["text_bot"] << text_bot;
	splash.collocate();

	splash.show();
	splash.events().unload([&] { fm.show(); });

	timer t;
	t.elapse([&] { splash.close(); });
	t.interval(8000); // the splash window will be displayed for 8000 milliseconds
	t.start();

	exec();
}
