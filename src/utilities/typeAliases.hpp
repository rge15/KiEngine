#include <utilities/Includes/commonIncludes.hpp>


template<typename... T>
using UniqPtr = std::unique_ptr<T...>;

using String = std::string;

template<typename... T>
using Vector = std::vector<T...>;