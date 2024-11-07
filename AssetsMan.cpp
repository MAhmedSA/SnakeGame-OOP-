#include "AssetsMan.h"

Engine::AssetsMan::AssetsMan() {

}

Engine::AssetsMan::~AssetsMan() {


}

void Engine::AssetsMan::AddTexture(int id, const string& filePath, bool isRepeated) {

	auto texture = make_unique<Texture>();

	if (texture->loadFromFile(filePath)){

		texture->setRepeated(isRepeated);

		m_texture[id] = move(texture);

		
	}
		
}

void Engine::AssetsMan::AddFont(int id, const string& filePath) {
	auto font = make_unique<Font>();

	if (font->loadFromFile(filePath)) {
		
		m_font[id] = move(font);

	}

}

const Texture& Engine::AssetsMan::GetTexture(int id) const {


		return *(m_texture.at(id).get());
}

const Font& Engine::AssetsMan::GetFont(int id) const {

	return *(m_font.at(id).get());

}