// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

template <typename T>
using com_ptr = Microsoft::WRL::ComPtr<T>;

#ifdef PRAGMA_COMMENT_LIB
	#pragma comment(lib, "d3d11.lib")
	#pragma comment(lib, "D3DCompiler.lib")
	#pragma comment(lib, "DXGI.lib")
	#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "DirectXTK.lib")
#endif // PRAGMA_COMMENT_LIB