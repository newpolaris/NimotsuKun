#include <fstream>
#include <iterator>
#include <algorithm>

#include "file.h"

unsigned getUnsigned( const buffer_value_type* p ) { // const를 붙이자.
	const unsigned char* up;
	up = reinterpret_cast< const unsigned char* >( p );
	unsigned ret = up[0];
	ret |= ( up[ 1 ] << 8 );
	ret |= ( up[ 2 ] << 16 );
	ret |= ( up[ 3 ] << 24 );
	return ret;
}


buffer_type fileRead(const std::string fileName)
{
	using std::ifstream;

	ifstream inputFile;
	inputFile.exceptions( ifstream::badbit );
	inputFile.open(fileName, ifstream::binary);
	if (!inputFile.is_open())
		throw std::exception("Could not open file");

	buffer_type buffer((std::istreambuf_iterator<buffer_value_type>(inputFile)),
					   (std::istreambuf_iterator<buffer_value_type>()));

	return buffer;
}

