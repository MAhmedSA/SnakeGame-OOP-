#pragma once
#include<list>
#include<iostream>
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/RenderStates.hpp>
using namespace std;
using namespace sf;

class Snake : public Drawable
{

private:
	
	list<Sprite> m_body;
	list<Sprite>::iterator m_head;
	list<Sprite>::iterator m_tail;
public:

	Snake();
	~Snake();


	void Init(const Texture &texture);
	void Move(Vector2f & direction);
	bool IsOn(const Sprite& other) const;
	void Grow(Vector2f& direction);
	bool Shrink();
	void draw(RenderTarget& target,RenderStates states)const override;
	bool IsSelfIntersecting()const;

};

