#include "PrecompileHeader.h"
#include "DFICore.h"
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "EditLevel.h"
#include "CenterLevel.h"
#include "EditGui.h"

DFICore::DFICore()
{
}

DFICore::~DFICore()
{
}



void DFICore::GameStart()
{
	// 이전에 매쉬는 만들어져 있어야 한다.


	//GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");


	ContentsResourcesCreate();


	GameEngineCore::CreateLevel<EditLevel>();
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>() ;
	GameEngineCore::CreateLevel<CenterLevel>();
	std::string Level = "PlayLevel";
	if (Level== "PlayLevel")
	{
		EditGui::Editor->SetLevel(1);
		EditGui::Editor->SetBPM(150);
	}
	GameEngineCore::ChangeLevel("CenterLevel");
}

void DFICore::GameEnd()
{

}