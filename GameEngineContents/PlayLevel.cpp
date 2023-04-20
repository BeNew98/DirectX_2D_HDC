#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}


void PlayLevel::Start()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		int a = 0;
	}
	GetMainCamera()->GetTransform()->SetLocalPosition({0, 0, -1000.0f});
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>("Player");


}