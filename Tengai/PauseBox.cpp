#include "stdafx.h"
#include "PauseBox.h"

PauseBox::PauseBox()
{
	
	position.x = WINDOW_WIDTH / 2;
	position.y = WINDOW_HEIGHT / 2;

	isEnable = false;
	isVisible = false;
	area = { -150,-100,150,100 };

	pResumeButton = new ResumeButton;
	pExitButton = new ExitButton;
	pResumeButton->pParent = this;
	pExitButton->pParent = this;
}

PauseBox::~PauseBox()
{
	delete pResumeButton;
	delete pExitButton;
}
void PauseBox::Update()
{
	if (!isEnable) return;

	if (InputManager::GetKeyDown(VK_ESCAPE))
	{
		this->Hide();
		return;
	}

	if (InputManager::GetKeyDown(VK_UP))
	{
		selector = !selector;
	}
	else if (InputManager::GetKeyDown(VK_DOWN))
	{
		selector = !selector;
	}

	if (InputManager::GetKeyDown(VK_RETURN))
	{
		Select();
	}
	else if (InputManager::GetKeyDown(VK_SPACE))
	{
		Select();
	}
	else if (InputManager::GetKeyDown('A'))
	{
		Select();
	}

	if (selector)
	{
		pResumeButton->isFocused = true;
		pExitButton->isFocused = false;
	}
	else
	{
		pResumeButton->isFocused = false;
		pExitButton->isFocused = true;
	}

	pResumeButton->Update();
	pExitButton->Update();
}

void PauseBox::Render()
{
	if (!isVisible) return;

	RenderManager::DrawRect(area+ position, RGB(100, 100, 100), RGB(0, 0, 0));

	pResumeButton->Render();
	pExitButton->Render();
}

void PauseBox::Show()
{
	isEnable = true;
	isVisible = true;
}

void PauseBox::Hide()
{
	isEnable = false;
	isVisible = false;
	Die();
}

void PauseBox::Select()
{
	SceneManager::GetInstance()->pCurrentScene->HideBox();
	if (selector)
	{
		MainGame::Resume();
		
	}
	else
	{
		MainGame::Shutdown();
	}
}
