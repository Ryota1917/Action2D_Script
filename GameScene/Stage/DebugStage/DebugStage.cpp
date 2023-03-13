#include "DebugStage.h"
#include"../StageManeger.h"
// TODO: includeが増えるのはどうにもならないのか（調査）
#include"../../../Actors/Character/Kaguya/Kaguya.h"
#include"../../../Actors/Character/Enemy/SimpleEnemy.h"
#include"../../../Actors/StageParts/CrackedWall.h"
#include"../../../Drawer/RectDrawer.h"
#include"../../../Core/Game.h"
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

DebugStage::DebugStage(StageManeger* maneger):
	StageBase(maneger, 0x10)
{
	mPlayerPos.emplace_back(Vector2(300, 350));
}

void DebugStage::OnEnter(StageManeger* maneger)
{
	//床のテスト
	Vector2 groundSize{ 900, 32 };
	auto ground = new Actor(maneger->GetGame());
	ground->SetPosition(Vector2(512, 700));
	auto collision = new AABBCollisionComponent(ground, groundSize);
	new RevertPositionComponent(ground, collision);
	new TerrainComponent(ground);
	auto lineDrawer = new SpriteLineDrawer(ground, "../Assets/Images/Block.png", groundSize, 100);

	//滑る床のテスト
	auto ground2 = new Actor(maneger->GetGame());
	ground2->SetPosition(Vector2(500, 650));
	auto gDrawer2 = new RectDrawer(Vector2(100, 32), ground2);
	gDrawer2->SetColor(142, 205, 247, 255);
	collision = new AABBCollisionComponent(ground2, Vector2(100, 32));
	new RevertPositionComponent(ground2, collision);
	auto terrain = new TerrainComponent(ground2);
	terrain->SetFriction(0.98f);

	//大量の床のテスト
	//for (int i = 0; i < 500; i++) {
	//	auto ground3 = new Actor(maneger->GetGame());
	//	ground3->SetPosition(Vector2(32*i, 32));
	//	auto gDrawer3 = new RectDrawer(Vector2(32, 32), ground3);
	//	gDrawer3->SetColor(142, 205, 247, 255);
	//	collision = new AABBCollisionComponent(ground3, Vector2(32, 32));
	//	new RevertPositionComponent(ground3, collision);
	//	auto terrain3 = new TerrainComponent(ground3);
	//}

	//壁のテスト
	auto wall = new Actor(maneger->GetGame());
	wall->SetPosition(Vector2(700, 609));
	//auto wDrawer = new RectDrawer(Vector2(32, 150), wall);
	//wDrawer->SetColor(162, 115, 82, 255);
	new SpriteLineDrawer(wall, "../Assets/Images/Block.png", Vector2(32, 150), 100, LineDrawerAnchor::DOWN_VERTICAL);
	collision = new AABBCollisionComponent(wall, Vector2(32, 149));
	new RevertPositionComponent(wall, collision);
	new TerrainComponent(wall);

	wall = new Actor(maneger->GetGame());
	wall->SetPosition(Vector2(600, 634));
	//wDrawer = new RectDrawer(Vector2(32, 100), wall);
	//wDrawer->SetColor(162, 115, 82, 255);
	new SpriteLineDrawer(wall, "../Assets/Images/Block.png", Vector2(32, 100), 100, LineDrawerAnchor::DOWN_VERTICAL);
	collision = new AABBCollisionComponent(wall, Vector2(32, 99));
	new RevertPositionComponent(wall, collision);
	new TerrainComponent(wall);

	// 動く床のテスト
	auto moveFloor = new MoveActor(maneger->GetGame());
	moveFloor->SetPosition(Vector2(300, 650));
	auto fDrawer = new RectDrawer(Vector2(100, 32), moveFloor);
	fDrawer->SetColor(0, 0, 255, 255);
	collision = new AABBCollisionComponent(moveFloor, Vector2(100, 32));
	new RevertPositionComponent(moveFloor, collision);
	auto moveFloorComponent = new MoveFloorComponent(moveFloor, collision, Vector2(100, 650));
	moveFloorComponent->SetSpeed(100);
	new SpriteLineDrawer(moveFloor, "../Assets/Images/Block.png", Vector2(100, 32));

	// はしごのテスト
	Vector2 ladderSize{ 32,500 };
	auto ladder = new Actor(maneger->GetGame());
	ladder->SetPosition(Vector2(750, 300));
	collision = new AABBCollisionComponent(ladder, ladderSize);
	new LadderComponent(ladder, collision);
	lineDrawer = new SpriteLineDrawer(ladder, "../Assets/Images/Ladder.png", ladderSize, 100, LineDrawerAnchor::DOWN_VERTICAL);

	// ステージ遷移のテスト
	auto transStage = new Actor(maneger->GetGame());
	transStage->SetPosition(Vector2(900, 600));
	new StageTransComponent(transStage, maneger, 0x11, Vector2(8, 16), Vector2(100, 100));

	// 敵のテスト
	auto enemy = new SimpleEnemy(maneger->GetGame(), maneger, Vector2(-100,100));
	enemy->SetPosition(Vector2(700, 100));

	// テキストのテスト
	//auto textActor = new Actor(maneger->GetGame());
	//textActor->SetPosition(Vector2(256, 128));
	//auto text = new TextDrawer(textActor, 1000);
	//text->SetText(u8"Hello World !!はろーわーるど！");

	// ソードアイテムのテスト
	auto sword = new SwordItemActor(maneger->GetGame());
	sword->SetPosition(Vector2(550, 600));

	// ボムアイテムのテスト
	auto bomb = new BombItemActor(maneger->GetGame());
	bomb->SetPosition(Vector2(300, 500));

	// ドアのテスト
	auto door = new Actor(maneger->GetGame());
	door->SetPosition(Vector2(200, 600));
	Vector2 doorSize{ 64,64 };
	auto doorSP = new SpriteDrawer("../Assets/Images/door.png", door);
	doorSP->SetWidth(doorSize.x);
	doorSP->SetHeight(doorSize.y);
	collision = new AABBCollisionComponent(door, doorSize);
	collision->SetCollisonType(CollisionComponentType::TRIGGER);
	new ButtonEventComponent(door, collision, std::make_unique<StageTransSender>(0x11, 1));

	// 看板のテスト
	auto sign = new Actor(maneger->GetGame());
	sign->SetPosition(Vector2(600, 568));
	Vector2 signSize{ 32,32 };
	auto signSP = new SpriteDrawer("../Assets/Images/Signboard.png", sign);
	signSP->SetWidth(signSize.x);
	signSP->SetHeight(signSize.y);
	collision = new AABBCollisionComponent(sign, signSize);
	new ButtonEventComponent(sign, collision, std::make_unique<UIEventSender>(UIEventCommand(
	UIEventAdress::UISCREEN, UIEventFlag::TEXT, 1, u8"これは看板のつもりですが？"
	)));

	// 壊れる壁のテスト
	auto cwall = new CrackedWall(maneger->GetGame());
	cwall->SetPosition(Vector2(500, 600));

}

void DebugStage::OnExit(StageManeger* maneger)
{
}
