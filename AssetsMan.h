#pragma once
#include<map>
#include<memory>
#include<iostream>
#include<string>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Font.hpp>
using namespace std;
using namespace sf;

namespace Engine {
	class AssetsMan
	{
	private:
		map< int, unique_ptr<Texture> > m_texture;
		map< int, unique_ptr<Font> > m_font;


	public:
		AssetsMan()  ;
		~AssetsMan() ;

		void AddTexture(int id , const string &filePath , bool isRepeated=false);

		void AddFont(int id, const string& filePath);
		
	    const Texture &GetTexture(int id) const;

		const Font &GetFont(int id) const;


	};

}

