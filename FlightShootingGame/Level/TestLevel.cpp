#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/PlayerBullet.h"
#include "Actor/Enemy.h"
#include "Actor/EnemyBullet.h"

#include <Windows.h>

// �� ĳ���� ����.
static const char* enemyType[]
{
	";(^);",
	"zZTZz",
	"oO&Oo",
	"<=-=>",
	")~O~(",
	"[[0]]"
};

TestLevel::TestLevel()
{
	AddActor(new Player("<A>"));
}

TestLevel::~TestLevel()
{

}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (deltaTime > 1.0f)
	{
		return;
	}

	// ESC Ű�� ����.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// ���� ���.
	SetColor(Color::Green);
	Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y + 1);
	Log("Score: %d", score);
	SetColor(Color::White);

	// �� ����.
	SpawnEnemy(deltaTime);

	// �÷��̾� ź��� ���� �浹 ó��.
	ProcessCollisionPlayerBulletAndEnemy();

	// �÷��̾�� ���� ź����� �浹 ó��.
	ProcessCollisionPlayerAndEnemyBullet();

}

void TestLevel::SpawnEnemy(float deltaTime)
{
	// �� ����. static�����̱� ������ �����ɶ� �� ���� �ʱ�ȭ�� �ȴ�.
	static float elapsedTime = 0.0f;
	static float spawnTime = RandomPercent(1.0f, 3.0f);

	// Ÿ�̸�.
	elapsedTime += deltaTime;
	if (elapsedTime < spawnTime)
	{
		return;
	}

	// Ÿ�̸� ����.
	elapsedTime = 0.0f;
	spawnTime = RandomPercent(1.0f, 3.0f);

	// �� ����.
	// static int length = sizeof(enemyType) / sizeof(enemyType[0]);
	// Windows.h ����� �ִ� ���. �Ʒ��� ���� �迭�� ���̸� ���� �� �ִ�.
	static int length = __crt_countof(enemyType);
	int index = Random(0, length - 1);
	//AddActor(new Enemy("[[0]]", Random(1, 10)));
	AddActor(new Enemy(enemyType[index], Random(5, 15)));
}

void TestLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	// ź�� �� �� ĳ���� �迭 ����.
	List<PlayerBullet*> bullets;
	List<Enemy*> enemies;

	// ������ ��ġ�� ���͸� ��ȸ�ϸ鼭 ����Ʈ ä���.
	for (Actor* actor : actors)
	{
		// ź������ ����ȯ �� Ȯ���ؼ� ����Ʈ ä���.
		PlayerBullet* bullet = actor->As<PlayerBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
			continue;
		}

		// ������ ����ȯ �� Ȯ���ؼ� ����Ʈ ä���.
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.PushBack(enemy);
			continue;
		}
	}

	// ���� ó��.
	if (bullets.Size() == 0 || enemies.Size() == 0)
	{
		return;
	}

	// �� �迭�� ��ȸ�ϸ鼭 �浹 ó��.
	for (PlayerBullet* bullet : bullets)
	{
		for (Enemy* enemy : enemies)
		{
			// ���� ��Ȱ��ȭ ���¶�� �ǳʶٱ�.
			if (!enemy->IsAcive())
			{
				continue;
			}

			// �浹 ó��.
			if (enemy->Intersect(*bullet))
			{
				// �浹������ �� ����.
				enemy->Destroy();

				// ź�൵ ����.
				bullet->Destroy();

				// ���� �߰�.
				score += 100;
			}
		}
	}
}

void TestLevel::ProcessCollisionPlayerAndEnemyBullet()
{
	// �÷��̾�� �� ź�� ���� ����.
	Player* player = nullptr;
	List<EnemyBullet*> bullets;

	// ������ ��ġ�� ���͸� ��ȸ�ϸ鼭 ����Ʈ ä���.
	for (Actor* actor : actors)
	{
		// �÷��̾� �˻�.
		Player* tempPlayer = actor->As<Player>();
		if (!player)
		{
			player = tempPlayer;
			continue;
		}

		// �� ź������ ��ȯ �� Ȯ���ؼ� ����Ʈ�� �߰�.
		EnemyBullet* bullet = actor->As<EnemyBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
			continue;
		}
	}


	// ���� ó��.
	if (player == nullptr || bullets.Size() == 0)
	{
		return;
	}

	for (EnemyBullet* bullet : bullets)
	{
		// ź��� �÷��̾ �浹�ߴ��� Ȯ��.
		if (player->Intersect(*bullet))
		{
			// �÷��̾� ����.
			player->Destroy();

			int y = Engine::Get().ScreenSize().y;
			Engine::Get().SetCursorPosition(
				player->Position().x - player->Width() / 2, y - 1);
			Log("  .  ");

			Engine::Get().SetCursorPosition(
				player->Position().x - player->Width() / 2, y);
			Log(".:V:.");
			Engine::Get().SetCursorPosition(
				player->Position().x - player->Width() / 2, y + 1);
			Log("GameOver!\n");

			// �� 2�ʰ� ����.
			Sleep(2000);

			// ���� ����.
			Engine::Get().QuitGame();
		}
	}
}
