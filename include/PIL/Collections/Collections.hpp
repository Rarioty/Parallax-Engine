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
            virtual void                    push_front(T element) = 0;
            virtual void                    push_back(T element) = 0;
            virtual void                    insert(T element, U32 position) = 0;

            virtual U32                     size() = 0;

            virtual void                    remove(U32 position) = 0;
            virtual void                    remove(const std::function<bool(U32, T)>& func) = 0;

            virtual T                       get(U32 position) = 0;
            virtual T                       front() = 0;
            virtual T                       back() = 0;

            virtual void                    execute(const std::function<void(U32, T*)>& func) = 0;
            virtual void                    execute(const std::function<bool(U32, T*)>& func) = 0;

            virtual T                       random() = 0;

            virtual std::pair<bool, U32>    find(T needle) = 0;
            virtual std::pair<bool, U32>    find_back(T needle) = 0;
            virtual std::pair<bool, U32*>   find_all(T needle) = 0;
            virtual std::pair<bool, U32*>   find_all(const std::function<bool(U32, T*)>& func) = 0;

            virtual void                    sort(const std::function<bool(T*, T*)>& comparator) = 0;
        };

        #include "Collections.inc"
    }
}

#endif
