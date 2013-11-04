#include <vector>
#include <string>

typedef char buffer_value_type;
typedef std::vector<buffer_value_type> buffer_type;
unsigned getUnsigned( const buffer_value_type* p );
buffer_type fileRead(const std::string fileName);
