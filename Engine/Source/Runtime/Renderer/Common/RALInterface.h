#ifndef CARBON_RALINTERFACE
#define CARBON_RALINTERFACE

#include "Common\Math\Color.h"
#include "RALDefine.h"

struct RALViewport;
class RALView;
class RALRenderTarget;
class RALVertexBuffer;
class RALIndexBuffer;
class RALShader;

// Rendering Abstraction Layer Interface
class RALInterface
{
public:
	RALInterface();
	virtual ~RALInterface(){}

#define RAL_METHOD(ReturnType,FuncName,FuncParaDecl,FuncParaDef,FuncPara) virtual ReturnType FuncName FuncParaDecl = 0;
	#include "RALMethods.h"
#undef RAL_METHOD

protected:
	// Pending Render target
	RALRenderTarget*	m_pendingRT[MAX_RT_COUNT];
	// Current Render target
	RALRenderTarget*	m_currentRT[MAX_RT_COUNT];
	// If the render target is changed
	bool				m_rtChanged;
	// Valie render target number
	unsigned			m_validRTNum;

	// flush render target if neccessary
	virtual void _flushRT() = 0;
	// check if the RT is changed
	void _checkRTChanged();
};

#endif