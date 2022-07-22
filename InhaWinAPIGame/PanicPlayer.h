#pragma once

#include "Actor.h"

#include <vector>
#include "Rect.h"
#include "PlayerArea.h"

class PanicPlayer : public Actor
{

public:
	enum class MoveMode
	{
		Edge,
		Inside
	};

public:
	PanicPlayer( const Vec2<int> pos, int width, int height );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx ) override;

private:
	void MoveObjectToRelativeCoord( const Vec2<int> amount );
	
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
	Vec2<int> lastDir = noDir;

	// Player status
	Vec2<int> dir;
	int speed = 2;
	Rect<int> collisionRect;
	float moveTime = 0.0f;

	// Player Move Node Setting
	MoveMode moveMode = MoveMode::Edge;
	std::pair<int, int> curLineIndices = {0,1};
	ArshesSH::Polygon trackingVertices;

	bool isStartTracking = false;
	std::pair<int, int> trackingStartIndices;
	std::pair<int, int> trackingEndIndices;

	// Player Drawing Setting
	Vec2<int> sceneTopLeft;
	Vec2<int> relativeTopLeft;
	Vec2<int> relativeBottomRight;

	//Debug
	std::pair<Gdiplus::Point, Gdiplus::Point> curVertices;
};