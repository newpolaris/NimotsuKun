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

	void draw() const;
	void draw(int dstX, int dstY, int srcX, int srcY, int srcW, int srcH) const; 

	unsigned m_width;
	unsigned m_height;
	container_type m_image;
};

