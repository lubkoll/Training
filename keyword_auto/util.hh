#pragma once

#include <string>
#include <type_traits>

#define QUALIFIER(variable) \
    ( std::is_same< decltype(variable), typename std::decay<decltype(variable)>::type >::value ? std::string("\n") :  \
      std::is_same< decltype(variable), const typename std::decay<decltype(variable)>::type >::value ? std::string("const\n") :  \
      std::is_same< decltype(variable), typename std::decay<decltype(variable)>::type& >::value ? std::string("&\n") : \
      std::is_same< decltype(variable), const typename std::decay<decltype(variable)>::type& >::value ? std::string("const&\n") : \
      std::is_same< decltype(variable), typename std::decay<decltype(variable)>::type&& >::value ? std::string("&&\n") : \
      std::string("const&&\n") )
