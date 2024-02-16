#include <iostream>
using namespace std;

struct StatInfo
{
	int hp;
	int attack;
	int defence;
};

// 값 복사 (메모리 오염은 없음)
// 대신 복사하는 데이터가 크면 클수록 비용이 커진다.
StatInfo CreatePlayer()
{
	StatInfo info;

	cout << "플레이어 생성" << endl;

	info.hp = 100;
	info.attack = 10;
	info.defence = 2;

	return info;
}

// 주소값만 복사(8 byte)
// 원본 값에 접근해서 작업을 하는 거이기 때문에 메모리 오염이 있을 수 있음
void CreateMonster(StatInfo* info)
{
	cout << "몬스터 생성" << endl;

	info->hp = 40;
	info->attack = 8;
	info->defence = 1;
}

// 이 함수는 문제가 있다.
// Stack 영역에 지역변수로 선언된 값은 리턴하면 함수가 해제되었을때 사라진다.
// 따라서 정상적인 로직이 돌아가지 않는다.
StatInfo* CreatePlayer2()
{
	StatInfo info;

	cout << "플레이어 생성" << endl;

	info.hp = 100;
	info.attack = 10;
	info.defence = 1;

	return &info;
}

void Battle(StatInfo* player, StatInfo* monster)
{
	while (true)
	{
		int damage = player->attack - monster->defence;
		if (damage < 0)
			damage = 0;

		monster->hp -= damage;
		if (monster->hp < 0)
			monster->hp = 0;

		cout << "몬스터 HP : " << monster->hp << endl;

		if (monster->hp == 0)
			return;

		damage = monster->attack - player->defence;
		if (damage < 0)
			damage = 0;

		cout << "플레이어 HP : " << player->hp << endl;

		player->hp -= damage;
		if (player->hp < 0)
			player->hp = 0;

		if (player->hp == 0)
			return;
	}
}

int main()
{
	StatInfo player;
	player = CreatePlayer();

	StatInfo monster;
	CreateMonster(&monster);

	Battle(&player, &monster);
}