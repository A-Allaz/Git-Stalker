#ifndef __MAPPED_TYPE_H__
#define __MAPPED_TYPE_H__

#include <variant>

class File;
class Function;

using MappedType = std::variant<Function*, File*>;

#endif