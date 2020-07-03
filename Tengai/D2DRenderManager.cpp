#include "D2DRenderManager.h"
#include "Define.h"
#include "stdafx.h"/*
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
std::unique_ptr<D2DRenderManager> pInstance{};
D2DRenderManager::D2DRenderManager()
{
    ID2D1Factory* pFactory = nullptr;
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
    auto dxProperties =
        D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE,
            D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));
    auto propertyWndRenderTarget = D2D1::HwndRenderTargetProperties(
        g_hwnd, D2D1::SizeU(WINDOW_WIDTH, WINDOW_HEIGHT));
    pFactory->CreateHwndRenderTarget(&dxProperties, &propertyWndRenderTarget, &this->pRenderTarget);
    this->pRenderTarget->SetDpi(96, 96);

    pFactory->Release();

    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackSolidBrush);
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pWhiteSolidBrush);
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pWriteFactory));
    pWriteFactory->CreateTextFormat(L"µ¸¿ò", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 12.f, L"ko-kr", &pWriteTextFormat);
}
D2DRenderManager::~D2DRenderManager()
{
    if (pWriteTextFormat != nullptr)
    {
        pWriteTextFormat->Release();
    }
    if (pWriteFactory != nullptr)
    {
        pWriteFactory->Release();
    }
    if (pWhiteSolidBrush != nullptr)
    {
        pWhiteSolidBrush->Release();
    }
    if (pBlackSolidBrush != nullptr)
    {
        pBlackSolidBrush->Release();
    }
    if (pRenderTarget != nullptr)
    {
        pRenderTarget->Release();
    }
}

const std::unique_ptr<D2DRenderManager>& D2DRenderManager::GetInstance()
{
    if (pInstance == nullptr)
    {
        pInstance.reset( new D2DRenderManager{});
    }
    return pInstance;
}
void D2DRenderManager::_DrawRect(const RECT& _rc)
{
    auto rc = D2D1::RectF(_rc.left, _rc.top, _rc.right, _rc.bottom);
    pRenderTarget->FillRectangle(rc, pWhiteSolidBrush);
    pRenderTarget->DrawRectangle(rc, pBlackSolidBrush);
}
void D2DRenderManager::_DrawCircle(const RECT& _rc)
{
    Transform center{ (_rc.left + _rc.right) / 2.f, (_rc.top + _rc.bottom) / 2.f };
    Transform radius{ abs(_rc.right - _rc.left) / 2.f, abs(_rc.bottom - _rc.top) / 2.f };
    auto ellipse = D2D1::Ellipse(D2D1::Point2F(center.x, center.y), radius.x, radius.y);
    pRenderTarget->FillEllipse(ellipse, pWhiteSolidBrush);
    pRenderTarget->DrawEllipse(ellipse, pBlackSolidBrush);
}
void D2DRenderManager::_DrawString(const wchar_t* const _str, int _x, int _y)
{
    pRenderTarget->DrawTextW(_str, wcslen(_str), pWriteTextFormat, D2D1::RectF((float)_x, (float)_y, (float)_x + 999, (float)_y + 999), pBlackSolidBrush);
}
void D2DRenderManager::DrawRect(const RECT& _rc)
{
    pInstance->_DrawRect(_rc);
}

void D2DRenderManager::DrawCircle(const RECT& _rc)
{
    pInstance->_DrawCircle(_rc);
}


void D2DRenderManager::DrawString(const WCHAR* _str, int _x, int _y)
{
    pInstance->_DrawString(_str, _x, _y);
}

void D2DRenderManager::Present()
{
    pInstance->pRenderTarget->EndDraw();
}

void D2DRenderManager::Clear()
{
    pInstance->pRenderTarget->BeginDraw();
    pInstance->pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    pInstance->pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}*/
