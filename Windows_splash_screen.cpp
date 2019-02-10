/*
	This Windows-only example demonstrates how to implement a simple splash screen that displays 
	an image from a Bitmap resource. It's the user's responsibility to build an executable that
	contains a Bitmap resource, with whatever IDE or toolchain they're using (how to do that is 
	beyond the scope of this example). I have used Visual Studio to build and test the example.
*/

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>
#include <nana/paint/pixel_buffer.hpp>

#include <Windows.h>

#define IDB_SPLASH 103 // change this integer value to whatever the ID of the Bitmap resource is

using namespace nana;

void get_pixels_from_bmp_resource(unsigned height, RGBQUAD *buf, int resid)
{
	HBITMAP bmp = reinterpret_cast<HBITMAP>(LoadImageA(GetModuleHandleA(0), MAKEINTRESOURCEA(resid), IMAGE_BITMAP, 0, 0, 0));
	HDC memdc = CreateCompatibleDC(0);
	SelectObject(memdc, bmp);

	BITMAPINFO bmi = {0};
	bmi.bmiHeader.biSize = sizeof bmi.bmiHeader;
	GetDIBits(memdc, bmp, 0, 0, NULL, &bmi, DIB_RGB_COLORS);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	GetDIBits(memdc, bmp, 0, height, buf, &bmi, DIB_RGB_COLORS);
	DeleteDC(memdc);
	DeleteObject(bmp);
}

int main()
{
	// change these values to the actual width and height of the BMP image
	const unsigned IMG_W{1920}, IMG_H{1080};

	auto pixels{std::make_unique<RGBQUAD[]>(IMG_W * IMG_H)}; // allocate memory for pixel buffer
	get_pixels_from_bmp_resource(IMG_H, pixels.get(), IDB_SPLASH); // IDB_SPLASH is the ID of the BMP resource

	form fm; // main form

	// This is the splash window. If its size is different than the size of the image,
	// the image will be stretched to fill it.
	form splash(API::make_center(1280, 720), appear::bald<>());

	drawing{splash}.draw([&](paint::graphics &graph)
	{
		paint::pixel_buffer pxbuf(IMG_W, IMG_H);
		pxbuf.put(reinterpret_cast<const unsigned char*>(pixels.get()), IMG_W, IMG_H, 32, IMG_W*sizeof(RGBQUAD), false);

		rectangle r{point{0, 0}, pxbuf.size()};
		rectangle rw{point{0, 0}, splash.size()};
		pxbuf.stretch(r, graph.handle(), rw);
	});

	splash.show();
	splash.events().unload([&] { fm.show(); });
	nana::timer timer_;
	timer_.elapse([&] { splash.close(); });
	timer_.interval(3000); // the splash window will be displayed for 3000 milliseconds
	timer_.start();
	exec();
}
