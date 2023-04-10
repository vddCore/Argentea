#ifndef ARGENTEA_DXGI_H
#define ARGENTEA_DXGI_H

#include <windows.h>

typedef HRESULT(WINAPI* PDXGIDumpJournal)(
    void* lpvUnk_0
);

typedef HRESULT(WINAPI* PCreateDXGIFactory)(
    REFIID riid,
    void** ppFactory
);

typedef HRESULT(WINAPI* PCreateDXGIFactory1)(
    REFIID riid,
    void** ppFactory
);

typedef HRESULT(WINAPI* PCreateDXGIFactory2)(
    UINT Flags,
    REFIID riid,
    void** ppFactory
);

typedef HRESULT(WINAPI* PDXGID3D10CreateDevice)(
    HANDLE handle,
    void* pFactory,
    void* pAdapter,
    UINT Flags,
    REFIID riid,
    void* ppDevice
);

typedef HRESULT(WINAPI* PDXGID3D10CreateLayeredDevice)(
    HANDLE handle,
    ULONG64 flags,
    void* pAdapter,
    REFIID riid,
    void** ppDevice
);

typedef size_t(WINAPI* PDXGID3D10GetLayeredDeviceSize)(
    const void* pLayers,
    UINT NumLayers
);

typedef HRESULT(WINAPI* PDXGID3D10RegisterLayers)(
    const void* pLayers,
    UINT NumLayers
);

typedef HRESULT(WINAPI* PDXGIGetDebugInterface1)(
    UINT Flags,
    REFIID riid,
    void** pDebug
);

typedef HRESULT(WINAPI* PDXGIReportAdapterConfiguration)(
    DWORD dwUnk_0
);

typedef struct _DXGIHook {
    PDXGIDumpJournal DXGIDumpJournal;
    PCreateDXGIFactory CreateDXGIFactory;
    PCreateDXGIFactory1 CreateDXGIFactory1;
    PCreateDXGIFactory2 CreateDXGIFactory2;
    PDXGID3D10CreateDevice DXGID3D10CreateDevice;
    PDXGID3D10CreateLayeredDevice DXGID3D10CreateLayeredDevice;
    PDXGID3D10GetLayeredDeviceSize DXGID3D10GetLayeredDeviceSize;
    PDXGID3D10RegisterLayers DXGID3D10RegisterLayers;
    PDXGIGetDebugInterface1 DXGIGetDebugInterface1;
    PDXGIReportAdapterConfiguration DXGIReportAdapterConfiguration;
} DXGIHook, *PDXGIHook;

#endif //ARGENTEA_DXGI_H
