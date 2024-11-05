#include <iostream>
#include <cassert>


#define LOGGER_INFO(_info) std::cout << _info << std::endl;
#define LOGGER_ASSERT(_condition, _info) assert(_condition && _info);
