#pragma once

#include <array>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

struct Widget;

std::vector< std::shared_ptr<Widget> > processed_widgets;

struct Widget : std::enable_shared_from_this<Widget>
{
    static std::shared_ptr<Widget> create()
    {
        return std::shared_ptr<Widget>(new Widget);
    }

    void process()
    {
        // wrong: processed_wigets.emplace_back(this);
        processed_widgets.emplace_back(shared_from_this());
    }

private:
    Widget() = default;
};

void section_shared_ptr()
{
    std::shared_ptr<char> ptr;
    std::cout << "contains something: " << (ptr ? true : false) << std::endl;
    ptr = std::make_shared<char>('c');
    std::cout << "contains something: " << (ptr ? true : false) << std::endl;
    auto other = ptr;

    std::cout << *ptr << " | " << *other << std::endl;

    *ptr = 'd';
    std::cout << *ptr << " | " << *other << std::endl;

    ptr = std::make_shared<char>('e');
    std::cout << *ptr << " | " << *other << std::endl;

    {
        std::shared_ptr<char> shared = std::make_unique<char>('f');
    }

    // custom deleters are not part of the type
    ptr = std::shared_ptr<char>( new char('f'),
                                 [](char* c)
                                { std::cout << *c << std::endl;
                                  delete c; } );

    std::cout << "unique: " << ptr.unique() << ", use_count: " << ptr.use_count() << std::endl;
    other = ptr;
    std::cout << "unique: " << ptr.unique() << ", use_count: " << ptr.use_count() << std::endl;

    // How-to use std::enable_shared_from_this:
    std::cout << "processed: " << processed_widgets.size() << std::endl;
    auto widget = Widget::create();
    widget->process();
    std::cout << "processed: " << processed_widgets.size() << std::endl;

    // Special casts for shared_ptr:
    // - static_pointer_cast
    // - dynamic_pointer_cast
    // - const_pointer_cast
    // - reinterpret_pointer_cast

    // the aliasing constructor
    char* l = new char('l');
    // aptr deletes o, but else uses l
    auto aptr = std::shared_ptr<char>(std::make_shared<char>('o'), l);
    std::cout << *aptr << std::endl;
    delete l;

    // Small buffer optimization with shared pointers.
 }

