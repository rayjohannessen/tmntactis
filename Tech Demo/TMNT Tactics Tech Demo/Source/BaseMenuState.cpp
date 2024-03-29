#include "BaseMenuState.h"
#include "Assets.h"
#include "Game.h"
#include "CSGD_TextureManager.h"
#include "CSGD_Direct3D.h"
#include "CSGD_DirectInput.h"
#include "BitmapFont.h"
//#include "fmod.hpp"

CBaseMenuState::CBaseMenuState()
{

}
CBaseMenuState::~CBaseMenuState()
{

}
void CBaseMenuState::Render()
{
	m_pTM->DrawWithZSort(m_nBGImageID, m_nBGX, m_nBGY, 0.5f);
}

void CBaseMenuState::Update(float fElapsedTime)
{

}

void CBaseMenuState::Enter()
{
	m_pAssets		= CAssets::GetInstance();
	m_pDI			= CSGD_DirectInput::GetInstance();
	m_pTM			= CSGD_TextureManager::GetInstance();
	m_nScreenWidth	= CGame::GetInstance()->GetScreenWidth();
	m_nScreenHeight = CGame::GetInstance()->GetScreenHeight();
	m_pBitmapFont   = CBitmapFont::GetInstance();

	m_nMenuItemSpacing = 45;
	//m_pFMOD		= CGame::GetInstance()->GetFMODSystem();
}

bool CBaseMenuState::Input(float elapsedTime, POINT mousePt)
{

	return true;
}

void CBaseMenuState::Exit()
{
	if (m_pAssets)
		m_pAssets = NULL;
	if (m_pTM)
		m_pTM = NULL;
	if (m_pDI)
		m_pDI = NULL;
// 	if (m_pBitmapFont)
// 		m_pBitmapFont = NULL;
// 	if (m_pFMOD)
// 		m_pFMOD = NULL;
}

void CBaseMenuState::CenterBGImage()
{
	m_nBGX = (m_nScreenWidth >> 1) - (m_nImageWidth >> 1);
	m_nBGY = (m_nScreenHeight >> 1) - (m_nImageHeight >> 1);
}