#include "PlayerBullet.h"
#include <cmath>

PlayerBullet::PlayerBullet(const Vector2& Position)
	: DrawableActor("!")
{
	// 탄약 위치 설정.
	this->position = Position;
	yPosition = (float)position.y;
}

void PlayerBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 위치 갱신.
	// 프레임 단위로 이동.
	// --position.y;

	// 프레임 시간을 고려한 이동.
	yPosition -= speed * deltaTime;
	//position.y = (int)roundf(yPosition);
	// 우리 게임에서는 반올림 할 필요가 없음.
	position.y = (int)(yPosition);

	// y좌표가 화면을 벗어나면 액터 삭제.
	//if (position.y < 0)
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}
}
