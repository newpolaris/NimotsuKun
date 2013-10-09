#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "image.h"
#include "file.h"

Image::Image(const std::string& fileName)
{
	static const unsigned offset = 4;
	static const unsigned height_offset = 8;
	static const unsigned width_offset = 12;
	static const unsigned image_offset = 128;
	static const unsigned argb_size = 4; 

	buffer_type fileImage(fileRead(fileName));
	m_height = getUnsigned(&fileImage.data()[offset+height_offset]);
	m_width  = getUnsigned(&fileImage.data()[offset+width_offset]);

	m_image.resize(m_width*m_height);

	for (unsigned i = 0; i < m_width*m_height; ++i ) 
		m_image[i] = getUnsigned(&fileImage.data()[ image_offset+ i*argb_size]);
}