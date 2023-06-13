#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "EditGui.h"
#include "Tiles.h"
#include "Planet.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Update(float _DeltaTime)
{
	PlanetSwap();

	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(m_pCenter->GetTransform()->GetWorldPosition());

}

void PlayLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
}
void PlayLevel::LevelChangeStart()
{
	EditGui::Editor->LoadtoString("");

	m_pStageInfo = EditGui::Editor->GetStageInfo(0);

	m_pRed = CreateActor<Planet>(OrderNum::PLANET);
	m_pBlue = CreateActor<Planet>(OrderNum::PLANET);
	m_pBlue->GetTransform()->SetParent(m_pRed->GetTransform());
	m_pBlue->GetTransform()->AddLocalPosition({ -150.f,0.f,0.f });
	m_pCenter = m_pRed;
	m_pTurn = m_pBlue;

	m_pCenter->GetTransform()->SetWorldPosition(m_pStageInfo.AllTile[0].m_pTile->GetPivotPos());

	EditGui::Editor->Off();
}

void PlayLevel::LevelChangeEnd()
{
}

void PlayLevel::PlanetSwap()
{
	if (true == GameEngineInput::IsAnyKey())
	{
		float4 f4CenterPos = m_pCenter->GetTransform()->GetWorldPosition();
		float4 f4TurnPos = m_pTurn->GetTransform()->GetWorldPosition();
		std::shared_ptr<Tiles> pNextTile = m_pStageInfo.AllTile[m_iCurIndex + 1].m_pTile;
		float4 f4NextTilePos = pNextTile->GetPivotPos();

		float fAngle = 0.f;

		float4 f4Angle = DirectX::XMVector2AngleBetweenVectors(f4NextTilePos- f4CenterPos, f4TurnPos- f4CenterPos);

		fAngle = f4Angle.x* GameEngineMath::RadToDeg;;
		float NextTileDeg = pNextTile->m_fData.z;
		int a = 0;

		m_pTurn->GetTransform()->SetParent(nullptr);
		if (true == m_pRed->IsCenter())
		{
			m_pRed->CenterChange();
			m_pBlue->CenterChange();
			m_pCenter = m_pBlue;
			m_pTurn = m_pRed;
		}
		else
		{
			m_pRed->CenterChange();
			m_pBlue->CenterChange();
			m_pCenter = m_pRed;
			m_pTurn = m_pBlue;
		}
		m_pTurn->GetTransform()->SetParent(m_pCenter->GetTransform());

		m_pCenter->GetTransform()->SetWorldPosition(f4NextTilePos);

		m_pStageInfo.AllTile[m_iCurIndex + 1].m_pTile->GlowOn();


		++m_iCurIndex;
	}
}