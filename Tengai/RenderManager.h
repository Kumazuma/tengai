#pragma once
#include <Windows.h>

class RenderManager
{
private:
	RenderManager();
	~RenderManager();

public:
	static RenderManager* GetInstance();
	static void Release();
	static void DrawRect(const RECT& _rc);
	static void DrawRect(const RECT& _rc, COLORREF _innerColor);
	static void DrawRect(const RECT& _rc, COLORREF _innerColor, COLORREF _outlineColor);
	static void DrawSimpleCollider(const RECT& _rc, COLORREF _outlineColor);
	static void DrawCircle(const RECT& _rc);
	static void DrawCircle(const RECT& _rc, COLORREF _innerColor, COLORREF _outlineColor);
	static void DrawString(const WCHAR* _str,int _x, int _y);
	static void DrawString(const WCHAR* _str, int _x, int _y, const WCHAR* _font, int _fontSize, COLORREF _color);
	static void Present();
	static void Clear();

private:
	HDC hdc;
	HBITMAP hBitmap;
	HDC hBackBufferDC;
	RECT area = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
};

