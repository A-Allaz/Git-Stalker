#ifndef __MAPPED_TYPE_H__
#define __MAPPED_TYPE_H__

#include <variant>

using namespace std;

class File;
class Function;

using MappedType = variant<Function*, File*>;

#endif