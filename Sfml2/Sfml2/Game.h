#pragma once
#include <string>
class Character
{
public:
	Character();
	~Character();

	void MoveTo(float x, float y);
	void Update(float dt);


private:
    int health;
	int mana;
	std::string name;

protected:
};

