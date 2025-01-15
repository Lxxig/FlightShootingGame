#include "Enemy.h"
#include "Engine/Engine.h"
#include "Actor/EnemyBullet.h"

Enemy::Enemy(const char* image, int yPosition)
	:DrawableActor(image)
{
	// 랜덤으로 이동방향 선택.
	int random = Random(1, 10);
	if (random % 2 == 0)
	{
		// 짝수인 경우에는 왼쪽으로 이동하도록 설정.
		direction = Direction::Left;

		xPosition = (float)(Engine::Get().ScreenSize().x - width);
	}
	else
	{
		// 홀수인 경우에는 오른쪽으로 이동하도록 설정.
		direction = Direction::Right;
		xPosition = 0.0f;
	}

	// 시작 위치 설정.
	this->position = Vector2(xPosition, yPosition);
}

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 좌우 이동.
	float factor = direction == Direction::Left ? -1.0f : 1.0f;
	xPosition += deltaTime * factor * speed;
	position.x = (int)xPosition;

	// 화면 빡으로 벗어나지 않게 처리.
	if (xPosition < 0.0f || xPosition > (float)(Engine::Get().ScreenSize().x - width))
	{
		Destroy();
		return;
	}
	
	// 탄약 발사.
	static float elapsedTime = 0.0f;
	static float fireInterval = RandomPercent(1.0f, 2.0f);

	// 타이머 업데이트.
	elapsedTime += deltaTime;

	// 타이머 처리.
	if (elapsedTime < fireInterval)
	{
		return;
	}

	elapsedTime = 0.0f;
	fireInterval = RandomPercent(1.0f, 2.0f);

	// 탄약 생성.
	Engine::Get().AddActor(
		new EnemyBullet(Vector2(position.x + width / 2, position.y))
	);

}