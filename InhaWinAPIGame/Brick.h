#pragma once

#include "Actor.h"
#include "PhysicsEntity.h"

class Brick : public Actor
{
public:
	Brick( const Vec2<float>& pos, float width, float height, int id );

	~Brick() {}
	Brick( const Brick& ) = default;
	Brick( Brick&& ) = default;
	Brick& operator=( const Brick& ) = default;
	Brick& operator=( Brick&& ) noexcept = default;

	void Update( float dt, const class Scene& scene ) override;
	void Draw( HDC hdc ) override;
	RECT GetRECT() const
	{
		return rigidBody.GetRECT();
	}
	void ReduceHealth()
	{
		health = --health;
	}
	void SetCenterX(float p)
	{
		rigidBody.SetCenterX( p );
	}
private:
	static constexpr int maxHealth = 2;

	PhysicsEntity rigidBody;
	
	Gdiplus::Color color;
	int health = maxHealth;
};
