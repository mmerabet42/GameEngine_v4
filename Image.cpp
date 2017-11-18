#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB_IMAGE\stb_image.h>

dn::Image::Image(const std::string & p_path)
{
	this->SetPath(p_path);
}

dn::Image::Image(unsigned char * p_pixels, const int & p_width, const int & p_height)
	: _pixels(p_pixels), _width(p_width), _height(p_height)
{

}

std::string dn::Image::path() const
{
	return this->_path;
}

void dn::Image::SetPath(const std::string & p_path)
{
	this->_pixels = dn::Image::LoadImage(this->_path = p_path, this->_width, this->_height);
}

unsigned char * dn::Image::pixels() const
{
	return this->_pixels;
}

int dn::Image::width() const
{
	return this->_width;
}

int dn::Image::height() const
{
	return this->_height;
}

unsigned char * dn::Image::LoadImage(const std::string & p_path, int & p_width, int & p_height)
{
	int comp;
	return stbi_load(p_path.c_str(), &p_width, &p_height, &comp, 4);
}
