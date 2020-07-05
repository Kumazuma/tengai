#include "stdafx.h"
#include "RenderManager.h"

RenderManager* pRenderManager = nullptr;

RenderManager::RenderManager()
{
	hdc = GetDC(g_hwnd);
	hBitmap = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	hBackBufferDC = CreateCompatibleDC(hdc);
	SelectObject(hBackBufferDC, hBitmap);
	SetBkMode(hBackBufferDC, TRANSPARENT);
}

RenderManager::~RenderManager()
{
	ReleaseDC(g_hwnd, hdc);
	//일단 해제해 주고
	if (hBackBufferDC != nullptr)
	{
		SelectObject(hBackBufferDC, nullptr);
		DeleteDC(hBackBufferDC);
	}
	//백버퍼도 지운다.
	if (hBitmap != nullptr)
	{
		DeleteObject(hBitmap);
	}
}

RenderManager * RenderManager::GetInstance()
{
	if (pRenderManager == nullptr)
	{
		pRenderManager = new RenderManager;
	}
	return pRenderManager;
}

void RenderManager::Release()
{
	delete pRenderManager;
	pRenderManager = nullptr;
}

void RenderManager::DrawRect(const RECT& _rc)
{
	Rectangle(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void RenderManager::DrawRect(const RECT& _rc, COLORREF _innerColor)
{
	HBRUSH hBrush = CreateSolidBrush(_innerColor);
	HGDIOBJ oldBrush = SelectObject(pRenderManager->hBackBufferDC, hBrush);
	Rectangle(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	SelectObject(pRenderManager->hBackBufferDC, oldBrush);
	DeleteObject(hBrush);
}

void RenderManager::DrawRect(const RECT& _rc, COLORREF _innerColor, COLORREF _outlineColor)
{
	HBRUSH hBrush = CreateSolidBrush(_innerColor);
	HPEN hPen = CreatePen(PS_SOLID, 1, _outlineColor);
	HGDIOBJ oldBrush = SelectObject(pRenderManager->hBackBufferDC, hBrush);
	HGDIOBJ oldPen = SelectObject(pRenderManager->hBackBufferDC, hPen);
	Rectangle(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	SelectObject(pRenderManager->hBackBufferDC, oldBrush);
	SelectObject(pRenderManager->hBackBufferDC, oldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void RenderManager::DrawSimpleCollider(const RECT& _rc, COLORREF _outlineColor)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, _outlineColor);
	HGDIOBJ oldPen = SelectObject(pRenderManager->hBackBufferDC, hPen);
	Rectangle(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	SelectObject(pRenderManager->hBackBufferDC, oldPen);
	DeleteObject(hPen);
}

void RenderManager::DrawCircle(const RECT& _rc)
{
	Ellipse(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void RenderManager::DrawCircle(const RECT& _rc, COLORREF _innerColor, COLORREF _outlineColor)
{
	HBRUSH hBrush = CreateSolidBrush(_innerColor);
	HPEN hPen = CreatePen(PS_SOLID, 1, _outlineColor);
	HGDIOBJ oldBrush = SelectObject(pRenderManager->hBackBufferDC, hBrush);
	HGDIOBJ oldPen = SelectObject(pRenderManager->hBackBufferDC, hPen);
	Ellipse(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	SelectObject(pRenderManager->hBackBufferDC, oldBrush);
	SelectObject(pRenderManager->hBackBufferDC, oldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void RenderManager::DrawString(const WCHAR* _str, int _x, int _y)
{
	TextOutW(pRenderManager->hBackBufferDC, _x, _y, _str, wcslen(_str));
}

void RenderManager::DrawString(const WCHAR* _str, int _x, int _y, const WCHAR* _font, int _fontSize, COLORREF _color)
{
	HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _font);
	HFONT oldFont = (HFONT)SelectObject(pRenderManager->hBackBufferDC, hFont);
	COLORREF oldColor = SetTextColor(pRenderManager->hBackBufferDC, _color);
	TextOutW(pRenderManager->hBackBufferDC, _x, _y, _str, wcslen(_str));
	SelectObject(pRenderManager->hBackBufferDC, oldFont);
	DeleteObject(hFont);
	SetTextColor(pRenderManager->hBackBufferDC, oldColor);
}

void RenderManager::Present()
{
	BitBlt(pRenderManager->hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		pRenderManager->hBackBufferDC, 0, 0, SRCCOPY);
}

void RenderManager::Clear()
{
	FillRect(pRenderManager->hBackBufferDC, &pRenderManager->area,
		(HBRUSH)GetStockObject(WHITE_BRUSH));
}
