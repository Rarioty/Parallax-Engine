#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <PIL/Collections/Collections.hpp>
#include <cstdlib>

namespace Parallax
{
    /**
     * \namespace   Parallax::Collections
     * \ingroup     PIL
     */
    namespace Collections
    {
        template <typename T>
        class LinkedListIterator
        {
        public:
            LinkedListIterator();
            ~LinkedListIterator();

        public:
            T                       operator*();

            LinkedListIterator<T>&  next();
        };

        template <typename T>
        class LinkedList : public Container<T>
        {
        public:
            using Iterator = LinkedListIterator<T>;

            struct node
            {
                node*   m_next;
                T       m_data;

                node(T data, node* next)
                    : m_next(next)
                    , m_data(data)
                {}
            };

        public:
            LinkedList();
            ~LinkedList();

        public:
            Iterator                begin();
            Iterator                end();

            void                    push_front(T element);
            void                    push_back(T element);
            void                    insert(T element, U32 position);

            U32                     size();

            void                    remove(U32 position);
            void                    remove(const std::function<bool(U32, T)>& func);
            void                    remove(Iterator it);

            T                       get(U32 position);
            T                       front();
            T                       back();

            void                    execute(const std::function<void(U32, T*)>& func);
            void                    execute(const std::function<bool(U32, T*)>& func);

            T                       random();

            std::pair<bool, U32>    find(T needle);
            std::pair<bool, U32>    find_back(T needle);
            std::pair<bool, U32*>   find_all(T needle);
            std::pair<bool, U32*>   find_all(const std::function<bool(U32, T*)>& func);

            void                    sort(const std::function<bool(T*, T*)>& comparator);

        private:
            struct node* m_front;
            struct node* m_back;
        };

        #include "LinkedList.inc"
    }
}

#endif
