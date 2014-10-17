#ifndef CARBON_OGLVIEW
#define CARBON_OGLVIEW

#include "Renderer\Common\RALView.h"
#include "PlatformOGL\PlatformOGL.h"

class OGLView : public RALView
{
public:
	OGLView(void* WindowHandle, unsigned width, unsigned height, bool bIsFullscreen, RAL_FORMAT format);
	~OGLView();

	// Resize viewport
	void	Resize(unsigned w, unsigned h);
	// Release resources
	void	Release();

	// Get Render Target
	RALRenderTarget* GetRenderTarget() const;


private:
	PlatformOGLDevice*	m_OglDevice;

	friend class OGLInterface;
};

#endif