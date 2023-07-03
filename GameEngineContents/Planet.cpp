#include "PrecompileHeader.h"
#include "Planet.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "EditGui.h"

int Planet::m_iUseCount = 0;

Planet::Planet()
{
}

Planet::~Planet() 
{
}
 

void Planet::CenterChange()
{
	m_bCenter = !m_bCenter;
	if (true == m_bCenter)
	{
		float4 test = m_pBall->GetTransform()->GetLocalPosition();
		m_pBall->GetTransform()->AddLocalPosition({ 0.f,0.f,-1.f });
		float4 test1 = m_pBall->GetTransform()->GetLocalPosition();
		int a = 0;
	}
	else
	{
		float4 test = m_pBall->GetTransform()->GetLocalPosition();
 		m_pBall->GetTransform()->AddLocalPosition({ 0.f,0.f,1.f });
		float4 test1 = m_pBall->GetTransform()->GetLocalPosition();
		int a = 0;
	}
}

void Planet::CreateEffect()
{
}

void Planet::Start()
{
	m_pBall = CreateComponent<GameEngineSpriteRenderer>(OrderNum::PLANET);


	m_fSpeed = EditGui::Editor->GetStageInfo(0).RotSpeed;
	m_fScaleRatio = m_fDistance *2.f / 60.f * EditGui::Editor->GetStageInfo(0).BPM;
	m_pCollision = CreateComponent<GameEngineCollision>(ColNum::PLANET);
	m_pCollision->GetTransform()->SetLocalScale({ 74.f, 74.f, 1.f });
	m_pRing = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	m_pRing->SetTexture("white-ring.png");
	//m_pRing->GetTransform()->SetLocalScale({ m_fDistance*2.f,m_fDistance*2.f,1.f });

	if (m_iUseCount != 0)
	{
		m_pBall->SetScaleToTexture("ballsprites_blue_sheet_grid_0_Sprite.png");
		m_iUseCount = 0;
		m_bCenter = false;
		m_pRing->ColorOptionValue.PlusColor = float4{ 0.f, 0.f,1.f ,0.f };
		m_pRing->ColorOptionValue.MulColor = float4{ 0.f, 0.f,1.f,0.35f };

	}
	else
	{
		m_pBall->SetScaleToTexture("ballsprites_red_sheet_grid_0_Sprite.png");
		m_pBall->GetTransform()->AddLocalPosition({ 0.f,0.f,-1.f });
		m_bCenter = true;
		m_bStartDistance = true;
		++m_iUseCount;

		m_pRing->ColorOptionValue.PlusColor = float4{ 1.f, 0.f, 0.f ,0.f };
		m_pRing->ColorOptionValue.MulColor = float4{ 1.f, 0.f,0.f,0.35f };
	}


	//GetTransform()->SetLocalScale({ 64.f, 64.f, 1.f });
}

bool bTiming = false;
float fTime = 0.f;
float fStarttime = 0.f;
void Planet::Update(float _DeltaTime)
{
	float4 test = m_pBall->GetTransform()->GetLocalPosition();
	if (m_bGameStart == false)
	{
		return;		
	}
	fStarttime += _DeltaTime;
	if (fStarttime<= static_cast<float>(EditGui::Editor->GetStageInfo(0).BPM) / 60.f / 2.f/4.f)
	{
		return;
	}
	//fTime += _DeltaTime;
	//
	//if (fTime >= static_cast<float>(EditGui::Editor->GetStageInfo(0).BPM) / 60.f/2.f)
	//{
	//	fTime -= static_cast<float>(EditGui::Editor->GetStageInfo(0).BPM) / 60.f /2.f;
	//	bTiming = !bTiming;
	//
	//
	//}
	//if (bTiming)
	//{
	//	pBall->ColorOptionValue.MulColor = float4::Zero;
	//}
	//else
	//{
	//	pBall->ColorOptionValue.MulColor = float4::One;
	//
	//}
	if (m_bCenter == false && false == m_bStartDistance)
	{
		if (GetTransform()->GetLocalPosition().x >= -m_fDistance && m_bStartDistance == false)
		{
			GetTransform()->AddLocalPosition(float4(-m_fDistance * _DeltaTime * 2.f, 0.f) );
		}
		else if (GetTransform()->GetLocalPosition().x <= -m_fDistance && m_bStartDistance == false)
		{
			GetTransform()->SetLocalPosition(float4(-m_fDistance, 0.f));
			m_bStartDistance = true;
		}
	}
	if (m_bCenter==true)
	{
		GetTransform()->AddLocalRotation({ 0.f,0.f,-m_fSpeed * _DeltaTime });
		m_pRing->GetTransform()->AddWorldRotation({ 0.f,0.f,-m_fSpeed * _DeltaTime / 6.f });
		if (m_pRing->GetTransform()->GetLocalScale().x >= m_fDistance * 2.f)
		{
			return;
		}
		m_pRing->GetTransform()->AddLocalScale(float4{ m_fScaleRatio ,m_fScaleRatio ,0.f,0.f }*_DeltaTime*2.f);
	}
	else
	{
		if (m_bGameEnd == true && m_bCenter == false && true == m_bStartDistance)
		{
			if (GetTransform()->GetLocalPosition().x <= 0.f && m_bStartDistance == true)
			{
				GetTransform()->AddLocalPosition(float4(m_fDistance * _DeltaTime * 2.f, 0.f));

				if (GetTransform()->GetLocalPosition().x >= 0.f && m_bStartDistance == true)
				{
					//TransformData data = GetTransform()->GetTransDataRef();
					GetTransform()->SetLocalPosition(float4(0.f, 0.f));
					m_bStartDistance = false;
					m_bGameStart = false;
				}
			}


			else if (GetTransform()->GetLocalPosition().x >= 0.f && m_bStartDistance == true)
			{
				GetTransform()->AddLocalPosition(float4(-m_fDistance * _DeltaTime * 2.f, 0.f));

				if (GetTransform()->GetLocalPosition().x <= 0.f && m_bStartDistance == true)
				{
					//TransformData data = GetTransform()->GetTransDataRef();
					GetTransform()->SetLocalPosition(float4(0.f, 0.f));
					m_bStartDistance = false;
					m_bGameStart = false;
				}
			}
		}

		if (m_pRing->GetTransform()->GetLocalScale().x<= 74.f)
		{
			return;
		}
		m_pRing->GetTransform()->AddLocalScale(-float4{ m_fScaleRatio ,m_fScaleRatio ,0.f,0.f}*_DeltaTime * 2.f);

	}
	

	
}

