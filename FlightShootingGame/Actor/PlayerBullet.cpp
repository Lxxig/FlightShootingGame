#include "PlayerBullet.h"
#include <cmath>

PlayerBullet::PlayerBullet(const Vector2& Position)
	: DrawableActor("!")
{
	// ź�� ��ġ ����.
	this->position = Position;
	yPosition = (float)position.y;
}

void PlayerBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ��ġ ����.
	// ������ ������ �̵�.
	// --position.y;

	// ������ �ð��� ����� �̵�.
	yPosition -= speed * deltaTime;
	//position.y = (int)roundf(yPosition);
	// �츮 ���ӿ����� �ݿø� �� �ʿ䰡 ����.
	position.y = (int)(yPosition);

	// y��ǥ�� ȭ���� ����� ���� ����.
	//if (position.y < 0)
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}
}
