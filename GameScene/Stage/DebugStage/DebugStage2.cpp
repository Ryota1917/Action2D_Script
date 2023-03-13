#include "DebugStage2.h"
#include"../StageManeger.h"
// TODO: includeが増えるのはどうにもならないのか（調査）
#include"../../../Actors/Character/Kaguya/Kaguya.h"
#include"../../../Actors/Character/Enemy/SimpleEnemy.h"
#include"../../../Actors/StageParts/CrackedWall.h"
#include"../../../Drawer/RectDrawer.h"
#include"../../../Core/Game.h"
#include"../../../Core/GameParameter.h"
#include"../../../Components/GravityComponent.h"
#include"../../../Components/CollisionComponent/AABBCollisionComponent.h"
#include"../../../Components/RevertPositionComponent.h"
#include"../../../Components/GroundComponent.h"
#include"../../../Components/JumpComponent.h"
#include"../../../Components/MoveFloorComponent.h"
#include"../../../Components/LadderComponent.h"
#include"../../../Components/TerrainComponents/TerrainComponent.h"
#include"../../../Components/StageTransComponent.h"
#include"../../../Drawer/TextDrawer.h"
#include"../../../Actors/ItemActor/SwordItemActor.h"
#include"../../../Actors/ItemActor/BombItemActor.h"
#include"../../../Drawer/SpriteLineDrawer.h"
#include"../../../Components/GameEventComponent/EventSender/StageTransSender.h"
#include"../../../Components/GameEventComponent/EventSender/UIEventSender.h"
#include"../../../Components/GameEventComponent/ButtonEventComponent.h"

DebugStage2::DebugStage2(StageManeger* maneger):
	StageBase(maneger,0x11)
{
	mPlayerPos.emplace_back(Vector2(100, 100));
	mPlayerPos.emplace_back(Vector2(200, 650+16));
}

void DebugStage2::OnEnter(StageManeger* maneger)
{
	auto game = maneger->GetGame();

	//床
	auto size = Vector2(GameParameter::WindowWidth, 32);
	auto ground = new Actor(game);
	ground->SetPosition(Vector2(512, 700));
	new SpriteLineDrawer(ground, "../Assets/Images/Block.png", size);
	auto collision = new AABBCollisionComponent(ground, size);
	new RevertPositionComponent(ground, collision);
	new TerrainComponent(ground);

	// ドア
	auto door = new Actor(game);
	door->SetPosition(Vector2(200, 650));
	Vector2 doorSize{ 64,64 };
	auto doorSP = new SpriteDrawer("../Assets/Images/door.png", door);
	doorSP->SetWidth(doorSize.x);
	doorSP->SetHeight(doorSize.y);
	collision = new AABBCollisionComponent(door, doorSize);
	new ButtonEventComponent(door, collision, std::make_unique<StageTransSender>(0x11, 1));

	//壁
	size = Vector2(32, 684);
	auto wall = new Actor(game);
	wall->SetPosition(Vector2(GameParameter::WindowWidth-16, 342));
	new SpriteLineDrawer(wall, "../Assets/Images/Block.png", size, 100 , LineDrawerAnchor::DOWN_VERTICAL);
	collision = new AABBCollisionComponent(wall, size-Vector2::Unit);
	new RevertPositionComponent(wall, collision);
	new TerrainComponent(wall);

	wall = new Actor(game);
	wall->SetPosition(Vector2(16, 342));
	new SpriteLineDrawer(wall, "../Assets/Images/Block.png", size, 100, LineDrawerAnchor::DOWN_VERTICAL);
	collision = new AABBCollisionComponent(wall, size-Vector2::Unit);
	new RevertPositionComponent(wall, collision);
	new TerrainComponent(wall);


	// ボムアイテム
	auto bomb = new BombItemActor(maneger->GetGame());
	bomb->SetPosition(Vector2(700, 700-32));

	// 壊れる壁
	auto cwall = new CrackedWall(maneger->GetGame());
	cwall->SetPosition(Vector2(800, 700-32));
	cwall = new CrackedWall(maneger->GetGame());
	cwall->SetPosition(Vector2(800, 700 - 64));

	// はしご
	Vector2 ladderSize{ 32,400-32 };
	auto ladder = new Actor(maneger->GetGame());
	ladder->SetPosition(Vector2(GameParameter::WindowWidth - 50, 700-16-ladderSize.y/2));
	collision = new AABBCollisionComponent(ladder, ladderSize);
	new LadderComponent(ladder, collision);
	new SpriteLineDrawer(ladder, "../Assets/Images/Ladder.png", ladderSize, 100, LineDrawerAnchor::DOWN_VERTICAL);



	// 二段目の床
	size = Vector2(GameParameter::WindowWidth-100, 32);
	ground = new Actor(game);
	ground->SetPosition(Vector2(512-50, 500));
	new SpriteLineDrawer(ground, "../Assets/Images/Block.png", size);
	collision = new AABBCollisionComponent(ground, size);
	new RevertPositionComponent(ground, collision);
	new TerrainComponent(ground);

	size = Vector2(100, 32);
	ground = new Actor(game);
	ground->SetPosition(Vector2(512 , 450));
	new SpriteLineDrawer(ground, "../Assets/Images/Block.png", size);
	collision = new AABBCollisionComponent(ground, size);
	new RevertPositionComponent(ground, collision);
	new TerrainComponent(ground);

	// 看板
	auto sign = new Actor(maneger->GetGame());
	sign->SetPosition(Vector2(700, 500 - 32));
	Vector2 signSize{ 32,32 };
	auto signSP = new SpriteDrawer("../Assets/Images/Signboard.png", sign);
	signSP->SetWidth(signSize.x);
	signSP->SetHeight(signSize.y);
	collision = new AABBCollisionComponent(sign, signSize);
	new ButtonEventComponent(sign, collision, std::make_unique<UIEventSender>(UIEventCommand(
		UIEventAdress::UISCREEN, UIEventFlag::TEXT, 1, u8"これはデバック用のデータです．\nこれが見えているのはおかしいよ"
	)));

	// ソードアイテム
	auto sword = new SwordItemActor(maneger->GetGame());
	sword->SetPosition(Vector2(512, 450-32));



	// 敵
	SimpleEnemy* enemy = new SimpleEnemy(game, maneger, Vector2(200, 0), 3.0f);
	enemy->SetPosition(Vector2(200, 450));

	enemy = new SimpleEnemy(game, maneger, Vector2(0, 200), 1.0f);
	enemy->SetPosition(Vector2(80, 80));


	// 三段目の床
	size = Vector2(GameParameter::WindowWidth - 100, 32);
	ground = new Actor(game);
	ground->SetPosition(Vector2(512 + 50, 300));
	new SpriteLineDrawer(ground, "../Assets/Images/Block.png", size);
	collision = new AABBCollisionComponent(ground, size);
	new RevertPositionComponent(ground, collision);
	new TerrainComponent(ground);

	// ボムアイテム
	bomb = new BombItemActor(maneger->GetGame());
	bomb->SetPosition(Vector2(300, 300 - 32));

	// 壊れる壁
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= 10; j++) {
			cwall = new CrackedWall(maneger->GetGame());
			cwall->SetPosition(Vector2(400 + 32 * i, 300 - 32*j));
		}
	}

	//床
	size = Vector2(100, 32);
	ground = new Actor(game);
	ground->SetPosition(Vector2(700, 300-32));
	new SpriteLineDrawer(ground, "../Assets/Images/Block.png", size);
	collision = new AABBCollisionComponent(ground, size);
	new RevertPositionComponent(ground, collision);
	new TerrainComponent(ground);

	// 動く床のテスト
	auto moveFloor = new MoveActor(maneger->GetGame());
	moveFloor->SetPosition(Vector2(800, 100));
	collision = new AABBCollisionComponent(moveFloor, Vector2(100, 32));
	new RevertPositionComponent(moveFloor, collision);
	auto moveFloorComponent = new MoveFloorComponent(moveFloor, collision, Vector2(800, 300-64));
	moveFloorComponent->SetSpeed(100);
	new SpriteLineDrawer(moveFloor, "../Assets/Images/Block.png", Vector2(100, 32));



	// 四段目の床
	size = Vector2(100, 32);
	ground = new Actor(game);
	ground->SetPosition(Vector2(GameParameter::WindowWidth-32-50, 100));
	new SpriteLineDrawer(ground, "../Assets/Images/Block.png", size);
	collision = new AABBCollisionComponent(ground, size);
	new RevertPositionComponent(ground, collision);
	new TerrainComponent(ground);

	// ドア
	door = new Actor(game);
	door->SetPosition(Vector2(GameParameter::WindowWidth - 32 - 50, 100-48));
	doorSP = new SpriteDrawer("../Assets/Images/door.png", door);
	doorSP->SetWidth(doorSize.x);
	doorSP->SetHeight(doorSize.y);
	collision = new AABBCollisionComponent(door, doorSize);
	new ButtonEventComponent(door, collision, std::make_unique<StageTransSender>(0x11, 1));

	// 見えない天井
	auto ceil = new Actor(game);
	ceil->SetPosition(Vector2(512, -16));
	Vector2 ceilSize{ GameParameter::WindowWidth, 32 };
	collision = new AABBCollisionComponent(ceil, ceilSize);
	new RevertPositionComponent(ceil, collision);
}

void DebugStage2::OnExit(StageManeger* maneger)
{
}
