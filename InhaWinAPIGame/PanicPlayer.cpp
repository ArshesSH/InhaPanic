#include "PanicPlayer.h"

#include "Scene.h"
#include <string>

PanicPlayer::PanicPlayer( const Vec2<int> pos, int width, int height )
	:
	pImage( ImageCodex::Retrieve( imageName ) ),
	collisionRect(pos, width, height)
{
}

void PanicPlayer::Update( float dt, Scene& scene )
{
	sceneTopLeft = scene.GetSceneTopLeft();
	MoveObjectToRelativeCoord( sceneTopLeft );
}

void PanicPlayer::Draw( Gdiplus::Graphics& gfx )
{
	Surface::DrawImageChroma( gfx, pImage.get(), relativeTopLeft, relativeBottomRight, { 0,0 }, imageEnd );

	// Debug
	const std::wstring lineIndices = L"Indices (" + std::to_wstring( curLineIndices.first ) + L", "
		+ std::to_wstring( curLineIndices.second ) + L")";
	Surface::DrawString( gfx, lineIndices, { 0,0 }, Gdiplus::Color( 255, 255, 255, 255 ) );

	const std::wstring firstVertexStr = L"FirstVertex: {" + std::to_wstring( curVertices.first.X ) + L", " + std::to_wstring( curVertices.first.Y ) + L"}";
	const std::wstring secondVertexStr = L"SecondVertex: {" + std::to_wstring( curVertices.second.X ) + L", " + std::to_wstring( curVertices.second.Y ) + L"}";
	const std::wstring playerPosStr = L"PlayerPos: {" + std::to_wstring( collisionRect.GetCenterX() ) + L", " + std::to_wstring( collisionRect.GetCenterY() ) + L"}";

	Surface::DrawString( gfx, firstVertexStr, { 0,20 }, Gdiplus::Color( 255, 255, 255, 255 ) );
	Surface::DrawString( gfx, secondVertexStr, { 0,40 }, Gdiplus::Color( 255, 255, 255, 255 ) );
	Surface::DrawString( gfx, playerPosStr, { 0,60 }, Gdiplus::Color( 255, 255, 255, 255 ) );

	const int debugVal = 0;
	const std::wstring etcDebugStr = L"Desired Debug : " + std::to_wstring( debugVal );
	Surface::DrawString( gfx, etcDebugStr, { 300, 20 }, Gdiplus::Color( 255, 255, 0, 255 ) );
}

void PanicPlayer::MoveObjectToRelativeCoord( const Vec2<int> amount )
{
	relativeTopLeft = collisionRect.GetLeftTop() + amount;
	relativeBottomRight = collisionRect.GetRightBottom() + amount;
}
