#pragma once
#include <type_traits>

// Because we're using c++17 but this feature is pretty useful !
template< class T >
struct remove_cvref {
    typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

// Instead of writting "typename ..."
template< class T >
using remove_cvref_t = typename remove_cvref<T>::type;