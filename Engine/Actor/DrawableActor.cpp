#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"

DrawableActor::DrawableActor(const char* image)
	: Actor(), image(nullptr)
{
	// 전달받은 문자열 복사.
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, image);

	// 너비 설정.
	width = (int)strlen(image);
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();

	// 그리기.
	// 1단계: 콘솔 좌표 옮기기.
	Engine::Get().SetCursorPosition(position);

	// 2단계: 그리기 (콘솔 출력).
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Log(image);
}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	// 이전의 위치를 먼저 지우기.
	/*Engine::Get().SetCursorPosition(position);
	Log(" ");*/

	// 위치를 새로 옮기기.
	Super::SetPosition(newPosition);
}