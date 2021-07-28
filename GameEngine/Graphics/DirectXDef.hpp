#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

template<typename T>
using com_ptr = Microsoft::WRL::ComPtr<T>;

#ifdef PRAGMA_COMMENT_LIB
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "DXGI.lib")
#endif // PRAGMA_COMMENT_LIB