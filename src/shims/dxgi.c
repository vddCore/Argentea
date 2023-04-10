#include <stdlib.h>
#include <stdio.h>

#include "shims.h"
#include "dxgi.h"

static volatile PDXGIHook _DXGI = NULL;

ShimCreateResult SHIMS_CreateDXGI(HMODULE hModule, OUT PDXGIHook* outHookStruct) {
    _DXGI = (PDXGIHook)malloc(sizeof(DXGIHook));

    if (!_DXGI) {
        return SHIM_OUT_OF_MEMORY;
    }
    
    memset(_DXGI, 0, sizeof(DXGIHook));

    SHIM_INIT_OR_QUIT(_DXGI, DXGIDumpJournal);
    SHIM_INIT_OR_QUIT(_DXGI, CreateDXGIFactory);
    SHIM_INIT_OR_QUIT(_DXGI, CreateDXGIFactory1);
    SHIM_INIT_OR_QUIT(_DXGI, CreateDXGIFactory2);
    SHIM_INIT_OR_QUIT(_DXGI, DXGID3D10CreateDevice);
    SHIM_INIT_OR_QUIT(_DXGI, DXGID3D10CreateLayeredDevice);
    SHIM_INIT_OR_QUIT(_DXGI, DXGID3D10GetLayeredDeviceSize);
    SHIM_INIT_OR_QUIT(_DXGI, DXGID3D10RegisterLayers);
    SHIM_INIT_OR_QUIT(_DXGI, DXGIGetDebugInterface1);
    SHIM_INIT_OR_QUIT(_DXGI, DXGIReportAdapterConfiguration);
    
    if (outHookStruct) {
        *outHookStruct = _DXGI;
    }
    
    return SHIM_OK;
}

void SHIMS_DestroyDXGI(void) {
    HOOK_DESTROY(_DXGI);
}

SHIM HRESULT WINAPI DXGIDumpJournal(void* lpvUnk_0) {
    return _DXGI->DXGIDumpJournal(lpvUnk_0);
}

SHIM HRESULT WINAPI CreateDXGIFactory(REFIID riid, void** ppFactory) {
    return _DXGI->CreateDXGIFactory(riid, ppFactory);
}

SHIM HRESULT WINAPI CreateDXGIFactory1(REFIID riid, void** ppFactory) {
    return _DXGI->CreateDXGIFactory1(riid, ppFactory);
}

SHIM HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, void** ppFactory) {
    return _DXGI->CreateDXGIFactory2(Flags, riid, ppFactory);
}

SHIM HRESULT WINAPI DXGID3D10CreateDevice(
    HANDLE handle,
    void* pFactory,
    void* pAdapter,
    UINT Flags,
    REFIID riid,
    void* ppDevice
) {
    return _DXGI->DXGID3D10CreateDevice(handle, pFactory, pAdapter, Flags, riid, ppDevice);
}

SHIM HRESULT WINAPI DXGID3D10CreateLayeredDevice(
    HANDLE handle,
    ULONG64 flags,
    void* pAdapter,
    REFIID riid,
    void** ppDevice
) {
    return _DXGI->DXGID3D10CreateLayeredDevice(handle, flags, pAdapter, riid, ppDevice);
}

SHIM size_t WINAPI DXGID3D10GetLayeredDeviceSize(const void* pLayer, UINT NumLayers) {
    return _DXGI->DXGID3D10GetLayeredDeviceSize(pLayer, NumLayers);
}

SHIM HRESULT WINAPI DXGID3D10RegisterLayers(const void* layers, UINT NumLayers) {
    return _DXGI->DXGID3D10RegisterLayers(layers, NumLayers);
}

SHIM HRESULT WINAPI DXGIGetDebugInterface1(UINT Flags, REFIID riid, void** pDebug) {
    return _DXGI->DXGIGetDebugInterface1(Flags, riid, pDebug);
}

SHIM HRESULT WINAPI DXGIReportAdapterConfiguration(DWORD dwUnk_0) {
    return _DXGI->DXGIReportAdapterConfiguration(dwUnk_0);
}