#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "GameLib/Framework.h"
#include "image.h"
#include "file.h"

Image::Image(const std::string& fileName)
{
	static const unsigned offset = 4;
	static const unsigned height_offset = 8;
	static const unsigned width_offset = 12;
	static const unsigned image_offset = 128;
	static const unsigned argb_size = 4; 

	buffer_type file(fileRead(fileName));
	m_height = getUnsigned(&file[offset+height_offset]);
	m_width  = getUnsigned(&file[offset+width_offset]);

	m_image.resize(m_width*m_height);

	for (unsigned i = 0; i < m_width*m_height; ++i ) 
		m_image[i] = getUnsigned(&file[image_offset+ i*argb_size]);
}

void Image::draw(int dstX, int dstY,
                 int srcX, int srcY,
                 int srcW, int srcH) const
{
    unsigned* vram = GameLib::Framework::instance().videoMemory();
    unsigned windowWidth = GameLib::Framework::instance().width();

    for (int y=0; y < srcH; ++y)
    for (int x=0; x < srcW; ++x)
	{
		size_t dst_pos = (dstY+y)*windowWidth+(dstX+x);
		size_t src_pos = (srcY+y)*width()+(srcX+x);

        unsigned src = m_image[src_pos];
		unsigned dst = vram[dst_pos];

		unsigned sa = src >> 24;
		unsigned sr = src & 0x00ff0000;
		unsigned sg = src & 0x0000ff00;
		unsigned sb = src & 0x000000ff;

		unsigned dr = dst & 0x00ff0000;
		unsigned dg = dst & 0x0000ff00;
		unsigned db = dst & 0x000000ff;

		dr = (sr-dr)*sa/0xff+dr;
		dg = (sg-dg)*sa/0xff+dg;
		db = (sb-db)*sa/0xff+db;

		vram[dst_pos] = 0xff<<24|(dr&0xff0000)|(dg&0x00ff00)|db;
	}
}

