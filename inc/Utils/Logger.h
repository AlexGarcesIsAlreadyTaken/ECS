#include <iostream>
#include <cassert>


#define LOGGER_INFO(_info) std::cout << _info << std::endl;
#define LOGGER_ERROR(_error) LOGGER_INFO("ERROR::" << _error);
#define LOGGER_ASSERT(_condition, _info) assert(_condition && _info);

#ifdef DEBUG
#define DEBUG_MESSAGE(_msg) std::cout << _msg << std::endl;
#else
#define DEBUG_MESSAGE(_msg);
#endif
