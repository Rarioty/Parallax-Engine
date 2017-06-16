#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <PIL/Collections/Collections.hpp>

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
            Iterator    begin();
            Iterator    end();

            U32         size();

            void        push(T element);

            void        remove(U32 position);
            void        remove(Iterator it);

            T           get(U32 position);

        private:
            struct node* m_front;
            struct node* m_back;
        };

        #include "LinkedList.inc"
    }
}

#endif
