#include "Snake.h"
#include"GamePlay.h"
Snake::Snake():m_body(list<Sprite>(4)) {
	
	m_head = -- m_body.end();

	// 0 1 2 3  null
	m_tail = m_body.begin();

}

Snake::~Snake() {

}

void Snake::Init(const Texture& texture) {
	
	float x = 16.f;
	
	for (auto & piece : m_body) {
		
		piece.setTexture(texture);
		piece.setScale(0.3, 0.3);
		piece.setPosition({x,16.f});
		x += 16.f;
	}

}
void Snake::Move(Vector2f& direction) {
	m_tail->setPosition(m_head->getPosition() + direction);
	m_head = m_tail;
	++m_tail;
	if (m_tail == m_body.end()) {

		m_tail = m_body.begin();

	}

}

bool Snake::IsOn(const Sprite& other)const{
	return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

void Snake::Grow(Vector2f& direction){
	Sprite newPiece;
	newPiece.setScale(0.3, 0.3);
	newPiece.setTexture(*(m_body.begin()->getTexture()));
	newPiece.setPosition(m_head->getPosition() + direction);

	m_head = m_body.insert(++m_head, newPiece);
}

bool Snake::Shrink() {

	// Check if the snake has more than one segment
	if (m_body.size() > 1) {
		// Remove the last segment from the snake body
		if (m_tail != m_body.begin()) {
			// Update the head to point to the last element in the body
			--m_tail;
			m_body.pop_back();	
			return true;
		}	
		else {
			return false;
		}
	}
}

void Snake::draw(RenderTarget& target, RenderStates states)const{
	for (auto& piece : m_body) {
		target.draw(piece);
	}

}

bool Snake::IsSelfIntersecting() const
{
	bool flag = false;
	for (auto piece = m_body.begin(); piece != m_body.end();++piece) {
		if (m_head != piece) {
			
				flag = IsOn(*piece);
				if (flag)
				{
					break;
				}
		}
	}
	return flag;
}
