#pragma once 

#include <vector>

struct Image
{
public:
	typedef unsigned value_type;
	typedef std::vector<value_type> container_type;

	Image(unsigned width, unsigned height, container_type& image)
		: m_width(width), m_height(height), m_image(image) {}

	Image(const std::string& fileName);

	unsigned width() const { return m_width; }

	value_type operator[](int i) const
	{
		return m_image[i];
	}
	value_type operator()(int x, int y) const
	{
		return m_image[ y * m_width + x ];
	}

	void draw(int dstX, int dstY, int srcX, int srcY, int srcW, int srcH) const; 

	unsigned m_width;
	unsigned m_height;
	container_type m_image;
};

