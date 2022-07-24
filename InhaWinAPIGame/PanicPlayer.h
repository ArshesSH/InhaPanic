#pragma once

#include "Actor.h"

#include <vector>
#include "Rect.h"

#include "PlayerArea.h"

class PanicPlayer : public Actor
{

public:

public:
	PanicPlayer( const Vec2<int> pos, int width, int height );

	void Update( float dt, class SceneStage& stage );
	void Draw( Gdiplus::Graphics& gfx ) override;

private:
	void MoveObjectToRelativeCoord( const Vec2<int> amount );
	void Move(float dt, const Vec2<int>& dir)
	{
		moveTime += dt;
		if ( moveTime >= movePeriod )
		{
			collisionRect.SetCenter( collisionRect.GetCenter() + dir * speed );
			moveTime = 0.0f;
		}
	}
	void MoveByKbdInput(float dt)
	{
		if ( GetAsyncKeyState( VK_LEFT ) & 0x8001 )
		{
			Move( dt, dirLeft );
		}
		else if ( GetAsyncKeyState( VK_RIGHT ) & 0x8001  )
		{
			Move( dt, dirRight );
		}
		else if ( GetAsyncKeyState( VK_UP ) & 0x8001  )
		{
			Move( dt, dirUp );
		}
		else if ( GetAsyncKeyState( VK_DOWN ) & 0x8001 )
		{
			Move( dt, dirDown );
		}
	}
	

	
private:
	// Image Setting
	static constexpr wchar_t imageName[] = L"Images/awsom.bmp";
	static constexpr float movePeriod = 0.01f;
	std::shared_ptr<Gdiplus::Image> pImage;
	Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };

	// Move Dir Setting
	const Vec2<int> noDir = { 0, 0 };
	const Vec2<int> dirLeft = { -1,0 };
	const Vec2<int> dirUp = { 0,-1 };
	const Vec2<int> dirRight = { 1, 0 };
	const Vec2<int> dirDown = { 0, 1 };

	// Player status
	Vec2<int> lastDir = noDir;
	int speed = 2;
	Rect<int> collisionRect;
	float moveTime = 0.0f;

	// Player Move Node Setting
	ArshesSH::Polygon trackingVertices;

	// Player Drawing Setting
	Vec2<int> sceneTopLeft;
	Vec2<int> relativeTopLeft;
	Vec2<int> relativeBottomRight;

	//Debug
	int debugVal = 0;
	Vec2<float> debugPos;
};