#ifndef COLLECTIONS_HPP
#define COLLECTIONS_HPP

#include <PIL/Types.hpp>

#include <functional>
#include <iostream>

namespace Parallax
{
    /**
     * \namespace   Parallax::Collections
     * \ingroup     PIL
     */
    namespace Collections
    {
        template <typename T>
        class Container
        {
        protected:
            Container();
            ~Container();

        protected:
            virtual void push(T element) = 0;
            virtual void push_front(T& element);
            virtual void push_back(T& element);
            virtual void insert(T& element, U32 position);

            virtual void remove(U32 position) = 0;

            virtual void remove(const std::function<bool()>& func);

            virtual T get(U32 position) = 0;
            virtual T front();
            virtual T back();

            virtual void execute(const std::function<void(U32, T*)>& func);
            virtual void execute(const std::function<bool(U32, T*)>& func);

            virtual T random();

            virtual U32 find(T& needle);
            virtual U32 find_back(T& needle);
            virtual U32* find_all(T& needle);
            virtual U32* find_all(const std::function<bool(U32, T*)>& func);

            virtual void sort(const std::function<bool(T*, T*)>& func);
        };

        #include "Collections.inc"
    }
}

#endif
