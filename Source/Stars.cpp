#include "Stars.h"

//BACKGROUND
void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render()
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}


void Background::Initialize(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		Star newStar;

		newStar.initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
		newStar.initPosition.y = GetRandomValue(0, GetScreenHeight());

		//random color?
		newStar.color = SKYBLUE;

		newStar.size = GetRandomValue(1, 4) / 2;

		Stars.push_back(newStar);

	}
}

void Background::Update(float offset)
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Update(offset);
	}

}

void Background::Render()
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Render();
	}
}