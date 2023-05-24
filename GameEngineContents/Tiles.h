#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Tiles : public GameEngineActor
{
public:
	// constrcuter destructer
	Tiles();
	~Tiles();

	// delete Function
	Tiles(const Tiles& _Other) = delete;
	Tiles(Tiles&& _Other) noexcept = delete;
	Tiles& operator=(const Tiles& _Other) = delete;
	Tiles& operator=(Tiles&& _Other) noexcept = delete;

	
	void CreateTile(TileDeg _TileDeg);
	std::shared_ptr<class GameEngineSpriteRenderer> GetRender()
	{
		return m_pRender;
	}

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_pRender = nullptr;

};

