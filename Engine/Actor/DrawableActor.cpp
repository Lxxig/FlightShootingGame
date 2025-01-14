#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"

DrawableActor::DrawableActor(const char* image)
	: Actor(), image(nullptr)
{
	// ���޹��� ���ڿ� ����.
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, image);

	// �ʺ� ����.
	width = (int)strlen(image);
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();

	// �׸���.
	// 1�ܰ�: �ܼ� ��ǥ �ű��.
	Engine::Get().SetCursorPosition(position);

	// 2�ܰ�: �׸��� (�ܼ� ���).
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Log(image);
}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	// ������ ��ġ�� ���� �����.
	/*Engine::Get().SetCursorPosition(position);
	Log(" ");*/

	// ��ġ�� ���� �ű��.
	Super::SetPosition(newPosition);
}