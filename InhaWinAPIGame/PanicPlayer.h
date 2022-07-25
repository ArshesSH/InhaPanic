#pragma once

#include "Actor.h"

#include <vector>
#include "Rect.h"

#include "PlayerArea.h"

class PanicPlayer : public Actor
{

public:
	enum class MoveState
	{
		MoveOnEdge,
		MoveInside,
		RollBack
	};

public:
	PanicPlayer( const Vec2<int> pos, int width, int height );

	void Update( float dt, class SceneStage& stage );
	void Draw( Gdiplus::Graphics& gfx ) override;

private:
	void MoveObjectToRelativeCoord( const Vec2<int> amount );
	void Move(float dt)
	{
		moveTime += dt;
		if ( moveTime >= movePeriod )
		{
			collisionRect.SetCenter( collisionRect.GetCenter() + curDir * speed );
			moveTime = 0.0f;
		}
	}
	void KbdInput()
	{
		if ( GetAsyncKeyState( VK_LEFT ) & 0x8001 )
		{
			state = MoveState::MoveOnEdge;
		}
		else if ( startPos == collisionRect.GetCenter() )
		{
			
		}

		if ( GetAsyncKeyState( VK_LEFT ) & 0x8001 )
		{
			//Move( dt, dirLeft );
			curDir = dirLeft;
		}
		else if ( GetAsyncKeyState( VK_RIGHT ) & 0x8001  )
		{
			//Move( dt, dirRight );
			curDir = dirRight;
		}
		else if ( GetAsyncKeyState( VK_UP ) & 0x8001  )
		{
			//Move( dt, dirUp );
			curDir = dirUp;
		}
		else if ( GetAsyncKeyState( VK_DOWN ) & 0x8001 )
		{
			//Move( dt, dirDown );
			curDir = dirDown;
		}
		else
		{
			curDir = noDir;
		}
	}
	
	void RideEdge( PlayerArea& area )
	{
		const Vec2<int> nextPos = curDir + collisionRect.GetCenter();
		if ( area.polygon.IsOnLine( nextPos, 0, 1 ) )
		{

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
	Vec2<int> curDir = noDir;
	Vec2<int> lastDir = noDir;
	int speed = 2;
	Rect<int> collisionRect;
	float moveTime = 0.0f;
	MoveState state = MoveState::MoveOnEdge;

	// Player Move Node Setting
	std::pair<int, int> indices = {0, 1};
	Vec2<int> startPos;
	ArshesSH::Polygon trackingVertices;

	// Player Drawing Setting
	Vec2<int> sceneTopLeft;
	Vec2<int> relativeTopLeft;
	Vec2<int> relativeBottomRight;

	//Debug
	int debugVal = 0;
	Vec2<float> debugPos;
};