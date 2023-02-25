#pragma once
#include <utilities/Includes/commonIncludes.hpp>

template<typename... T>
using UniqPtr = std::unique_ptr<T...>;

using String = std::string;

template<typename... T>
using Vector = std::vector<T...>;

template<typename... T>
using Tuple = std::tuple<T...>;

template<typename T>
using Opt = std::optional<T>;

template<typename... T>
using Set = std::set<T...>;