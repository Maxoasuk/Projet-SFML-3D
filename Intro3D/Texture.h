#ifndef TEXTURE_H__
#define TEXTURE_H__

#include <iostream>

class Texture {
	unsigned int m_texture;

public:
	void load(std::string _path);
	void active();
	void desactive();
};

#endif

