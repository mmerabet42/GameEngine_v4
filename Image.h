#pragma once

#include <string>

namespace dn
{
	class Image
	{
	public:
		Image(const std::string & p_path = "none");
		Image(unsigned char * p_pixels, const int & p_width, const int & p_height);

		std::string path() const;
		void SetPath(const std::string & p_path);

		unsigned char * pixels() const;
		int width() const;
		int height() const;
			
		static unsigned char * LoadImage(const std::string & p_path, int & p_width, int & p_height);

	private:

		std::string _path;

		unsigned char * _pixels;
		int _width;
		int _height;
	};
}

