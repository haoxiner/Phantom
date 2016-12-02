#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
namespace phtm
{
HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob **ppBlobOut);
}