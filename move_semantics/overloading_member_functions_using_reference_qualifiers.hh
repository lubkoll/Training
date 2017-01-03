#pragma once

#include <functional>
#include <iostream>

using Choice = std::function<bool(int)>;

struct Or
{
    Or(Choice&& choice, Choice&& other_choice)
        : choice_( std::move(choice) ),
          other_choice_( std::move(other_choice) )
    {}

    bool operator()(int a) const
    {
        return choice_(a) || other_choice_(a);
    }

private:
    Choice choice_, other_choice_;
};

template <class T>
struct Binder
{
    Choice bind(Choice&& choice) &&
    {
        return Or( std::move(static_cast<T&>(*this)), std::move(choice) );
    }
};

struct ChooseFromVector : Binder<ChooseFromVector>
{
  ChooseFromVector(std::vector<int>&& vec)
      : vec_(std::move(vec))
  {}

  bool operator()(int a) const
  {
    for( int b : vec_ )
        if( a == b )
            return true;
    return false;
  }

  std::vector<int> vec_;
};

struct ChooseOdd : Binder<ChooseOdd>
{
  bool operator()(int a) const
  {
      return a%2 == 1;
  }
};

template <class T>
std::vector<int> get_vector(T size)
{
    std::vector<int> vec;
    vec.reserve(size);

    for(T i=1; i<=size; ++i)
        vec.emplace_back(i);
    return vec;
}

void print_vector(const std::vector<int>& v)
{
    std::cout << "vec = [ ";
    for(decltype(v.size()) i = 0; i < v.size(); ++i)
        if( i+1 == v.size() )
            std::cout << v[i] << " ]\n\n";
        else
            std::cout << v[i] << ", ";
}


void overloading_member_functions_using_reference_qualifiers()
{
    // Overloading member functions using reference qualifiers

    std::vector<int> reference = get_vector(10);
    std::vector<int> vec = get_vector(20);
    print_vector(vec);
    Choice remover = ChooseFromVector(std::move(reference)).bind( ChooseOdd() );
    vec.erase( remove_if( begin(vec), end(vec), remover ),
               end(vec) );
    print_vector(vec);
}
