#include "Wall.h"

void Wall::Render(Texture2D texture) const noexcept
{
	DrawTexturePro(texture,
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);


	DrawText(TextFormat("%i", health), position.x - 21, position.y + 10, 40, RED);

}

void Wall::Update() noexcept
{

	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}


}