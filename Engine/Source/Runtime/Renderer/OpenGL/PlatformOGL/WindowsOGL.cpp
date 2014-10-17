#include "PlatformOGL.h"

#ifdef CARBON_IN_WINDOWS

#include <Windows.h>

bool InitOGL(PlatformOGLDevice* device);

struct PlatformOGLDevice
{
	HWND	hwnd;
	HGLRC	context;
	HDC		hdc;

	PlatformOGLDevice(void* _hwnd)
	{
		hwnd = (HWND)_hwnd;
		InitOGL(this);
	}
};

bool InitOGL(PlatformOGLDevice* device)
{
	unsigned int		PixelFormat;	// Holds The Results After Searching For A Match

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	device->hdc = GetDC(device->hwnd);

	PixelFormat = ChoosePixelFormat(device->hdc, &pfd);
	SetPixelFormat(device->hdc, PixelFormat, &pfd);

	device->context = wglCreateContext(device->hdc);

	if (!wglMakeCurrent(device->hdc, device->context))		// Try To Activate The Rendering Context
	{
		//KillGLWindow((HWND)device->hwnd);			// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return true;
}

// create opengl platform device
PlatformOGLDevice*	CreatePlatformOGLDevice(void* hwnd)
{
	return new PlatformOGLDevice(hwnd);
}

// swap OGL buffer
void SwapBuffer(PlatformOGLDevice* device)
{
	// swap buffers
	SwapBuffers(device->hdc);
}

// make OGL context current
void MakeOGLCurrent(PlatformOGLDevice* device)
{
	// make current
	wglMakeCurrent(device->hdc, device->context);
}

#endif