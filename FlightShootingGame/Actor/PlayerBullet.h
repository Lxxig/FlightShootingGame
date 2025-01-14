#pragma once

#include <Actor/DrawableActor.h>

class PlayerBullet : public DrawableActor
{
	RTTI_DECLARATIONS(PlayerBullet, DrawableActor)

public:
	// ź���� ������ �� ��ġ�� ���� �޾ƾ� ��.
	PlayerBullet(const Vector2& Position);

	virtual void Update(float deltaTime) override;

private:

	// �̵� ���� ����.
	// �̵� �ӷ� (����: ĭ/��)
	float speed = 20.0f;

	// y��ġ.
	float yPosition = 0.0f;

};