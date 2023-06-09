#include "PrecompileHeader.h"
#include "CenterLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFont.h>

#include "EditGui.h"
#include "TestScreen.h"
#include "TestObject.h"
#include "FadeEffect.h"
#include "FireWorkEffect.h"

CenterLevel::CenterLevel() 
{
}

CenterLevel::~CenterLevel() 
{
}

void CenterLevel::Start()
{
	EditGui::Editor->Off();
	GameEngineInput::CreateKey("Level1", '1');
	GameEngineInput::CreateKey("Level2", '2');
	GameEngineInput::CreateKey("TitleLevel", '7');
	GameEngineInput::CreateKey("PlayLevel", '8');
	GameEngineInput::CreateKey("EditLevel", '9');
	GameEngineInput::CreateKey("CenterLevel", '0');
	GameEngineInput::CreateKey("Reset", 'R');

	

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");


		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Sound");

		GameEngineSound::Load(NewDir.GetPlusFileName("1-X.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("sndKick.wav").GetFullPath());
	}
	{
		GameEngineFont::Load("Ch2.0-1");
	}
	//윗쪽은 MainCam 아랫쪽은 UICam
	//왼쪽은 배경x	오른쪽은 배경o

	//		Main + 배경x    Main + 배경o
	
	//		UI  + 배경x     UI  + 배경o 
	

}

void CenterLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TitleLevel"))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (GameEngineInput::IsDown("PlayLevel"))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
		EditGui::Editor->SetLevel(1);
		EditGui::Editor->SetBPM(150);
	}

	if (GameEngineInput::IsDown("EditLevel"))
	{
		GameEngineCore::ChangeLevel("EditLevel");
	}
}

void CenterLevel::LevelChangeStart()
{
	ptr = GetLastTarget()->CreateEffect<FireWorkEffect>();
	ptr->SetColor(float4::Blue);
	ptr->On();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	{
		std::shared_ptr<TestScreen> render = CreateActor<TestScreen>();
	}

	{
		std::shared_ptr<TestObject> render = CreateActor<TestObject>();
		render->GetTransform()->AddLocalPosition({ -500.f,0.f });
	}
	{
		std::shared_ptr<TestObject> render = CreateActor<TestObject>();
		render->GetTransform()->AddLocalPosition({ 500.f,0.f });
	}

}

void CenterLevel::LevelChangeEnd()
{
	AllActorDestroy();
}

