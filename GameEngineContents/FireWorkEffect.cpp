#include "PrecompileHeader.h"
#include "FireWorkEffect.h"

FireWorkEffect::FireWorkEffect() 
{
}

FireWorkEffect::~FireWorkEffect() 
{
}

void FireWorkEffect::Start(GameEngineRenderTarget* _Target)
{
	m_pFWUnit = std::make_shared<GameEngineRenderUnit>();
	m_pFWUnit->SetMesh("FullRect");
	m_pFWUnit->SetPipeLine("FireWork");

	m_sBaseValue.ScreenScale = GameEngineWindow::GetScreenSize();

	m_pFWUnit->ShaderResHelper.SetConstantBufferLink("FireWorkValue", m_sBaseValue);

	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void FireWorkEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	m_sBaseValue.Mouse = GameEngineWindow::GetMousePosition();
	m_sBaseValue.Mouse.z = GameEngineInput::IsPress("EngineMouseLeft");
	m_sBaseValue.Mouse.w = GameEngineInput::IsPress("EngineMouseLeft");

	m_sBaseValue.Time.x += _DeltaTime;
	m_sBaseValue.Time.y = _DeltaTime;

	ResultTarget->Clear();
	m_pFWUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	ResultTarget->Setting();
	m_pFWUnit->Render(_DeltaTime);
	m_pFWUnit->ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ResultTarget);
}
