#include "PanicPlayer.h"

#include "SceneStage.h"
#include <string>

PanicPlayer::PanicPlayer( const Vec2<int> pos, int width, int height )
	:
	pImage( ImageCodex::Retrieve( imageName ) ),
	collisionRect(pos, width, height)
{
}

void PanicPlayer::Update( float dt, SceneStage& stage )
{
	if ( state == MoveState::MoveOnEdge )
	{
		startPos = collisionRect.GetCenter();
	}

	KbdInput();
	
	sceneTopLeft = stage.GetSceneTopLeft();
	MoveObjectToRelativeCoord( sceneTopLeft );
}

void PanicPlayer::Draw( Gdiplus::Graphics& gfx )
{
	Surface::DrawImageChroma( gfx, pImage.get(), relativeTopLeft, relativeBottomRight, { 0,0 }, imageEnd );

	// Debug
	const std::wstring etcDebugStr = L"Desired Debug : " + std::to_wstring( debugVal );
	Surface::DrawString( gfx, etcDebugStr, { 0, 20 }, Gdiplus::Color( 255, 255, 0, 255 ) );
}

void PanicPlayer::MoveObjectToRelativeCoord( const Vec2<int> amount )
{
	relativeTopLeft = collisionRect.GetLeftTop() + amount;
	relativeBottomRight = collisionRect.GetRightBottom() + amount;
}
