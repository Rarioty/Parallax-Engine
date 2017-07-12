#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <Parallax/Types.hpp>
#include <functional>
#include <iostream>
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
        class LinkedListIterator;

        /**
         * \class   LinkedList
         * \brief   Single linked-list container, you can see performance below.
         *
         * \tparam  T   Type of the elements in the container.
         */
        template <typename T>
        class LinkedList
        {
        public:
            using Iterator = LinkedListIterator<T>;     /*!<    Iterator class for this container   */
            friend class LinkedListIterator<T>;

            /**
             * \struct  node
             * \brief   Node in the linked-list
             */
            struct node
            {
                node*   m_next;         /*!<    Next node           */
                T       m_data;         /*!<    Data in this node   */

                node(T data, node* next)
                    : m_next(next)
                    , m_data(data)
                {}
            };

        public:
            /**
             * \brief
             *  Constructor
             */
            LinkedList();
            /**
             * \brief
             *  Destructor
             */
            ~LinkedList();

        public:
            /**
             * \brief
             *  Return an iterator corresponding at the start of this container
             *
             * \return  Iterator positioned at the beginning
             */
            Iterator                begin();
            /**
             * \brief
             *  Return an iterator corresponding at the end of this container
             *
             * \return  Iterator positioned at the end
             */
            Iterator                end();

            /**
             * \brief
             *  Push element in the front of this container
             *
             * \param[in]   element     Element to add
             */
            void                    push_front(T element);
            /**
             * \brief
             *  Push element in the back of this container
             *
             * \param[in]   element     Element to add
             */
            void                    push_back(T element);
            /**
             * \brief
             *  Push element in a specified position of this container
             *
             * \param[in]   element     Element to add
             * \param[in]   position    Where to add the element
             */
            void                    insert(T element, U32 position);

            /**
             * \brief
             *  Return size of this container
             *
             * \return  Current size of this container
             */
            U32                     size();

            /**
             * \brief
             *  Remove a specified position in this container
             *
             * \param[in]   position    Position to remove
             */
            void                    remove(U32 position);
            /**
             * \brief
             *  Remove nodes in this container with a special function.
             *  When the function return true then the node is removed otherwise the node remains.
             *  The arguments sent to the function are the position of this node and the element inside this node.
             *
             * \param   func    Test function
             */
            void                    remove(const std::function<bool(U32, T)>& func);
            /**
             * \brief
             *  Remove the node described by an iterator
             *
             * \param[in]   it  Position of the node to remove
             */
            void                    remove(Iterator it);

            /**
             * \brief
             *  Return the value at a specified position
             *
             * \param[in]   position    Position to get
             *
             * \return  Found value at this position
             */
            T                       get(U32 position);
            /**
             * \brief
             *  Return the value in the front of the container
             *
             * \return  Found value
             */
            T                       front();
            /**
             * \brief
             *  Return the value in the back of the container
             *
             * \return  Found value
             */
            T                       back();

            /**
             * \brief
             *  Swap two elemens in the container
             *
             * \param[in]   first   First element to swap
             * \param[in]   second  Second element to swap
             */
            void                    swap(U32 first, U32 second);

            /**
             * \brief
             *  Execute a function on each element of this container.
             *  The arguments of the function are the position of the node and a pointer to the element
             *
             * \param[in]   func    Function to apply to each element
             */
            void                    execute(const std::function<void(U32, T*)>& func);
            /**
             * \brief
             *  Execute a function on each element of this container.
             *  The arguments of the function are the position of the node and a pointer to the element.
             *  The iteration of the nodes continue while the function return true.
             *
             * \param[in]   func    Function to apply to each element
             */
            void                    execute(const std::function<bool(U32, T*)>& func);

            /**
             * \brief
             *  Return a random position value
             *
             * \return  Random node value
             */
            T                       random();

            /**
             * \brief
             *  Return the position of a given value
             *
             * \param[in]   needle  Value to search
             *
             * \return     A pair composed of a boolean that indicates wether or not the value is found and the position of the value
             */
            std::pair<bool, U32>    find(T needle);
            /**
             * \brief
             *  Return the position of a given value from the back of the container
             *
             * \param[in]   needle  Value to search
             *
             * \return     A pair composed of a boolean that indicates wether or not the value is found and the position of the value
             */
            std::pair<bool, U32>    find_back(T needle);
            /**
             * \brief
             *  Return the position of all values corresponding to the given one
             *
             * \param[in]   needle  Value to search
             *
             * \return     A pair composed of a boolean that indicates wether or not the value is found and the position of all the values
             */
            std::pair<U32, U32*>     find_all(T needle);
            /**
             * \brief
             *  Return the position of values accepted by a specified function.
             *  The arguments of the function are the current node position and a pointer to the element.
             *
             * \param[in]   func    Search function
             *
             * \return     A pair composed of a boolean that indicates wether or not the value is found and the position of the value
             */
            std::pair<U32, U32*>     find_all(const std::function<bool(U32, T*)>& func);

            /**
             * \brief
             *  Sort this container with a comparator function
             *
             * \param[in]   comparator  Function to compare two elements
             */
            void                    sort(const std::function<bool(T, T)>& comparator);

        private:
            struct node*    m_front;            /*!<    Front node of the container     */
            struct node*    m_back;             /*!<    Back node of the container      */

            U32             m_current_size;     /*!<    Current size of the container   */
        };

        /**
         * \class   LinkedListIterator
         * \brief   Iterator for the LinkedList class
         *
         * \tparam  T   Type of the elements in the corresponding LinkedList
         */
        template <typename T>
        class LinkedListIterator
        {
        public:
            friend class LinkedList<T>;

        public:
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   node    Starting node for this iterator
             */
            LinkedListIterator(struct LinkedList<T>::node* node);
            /**
             * \brief
             *  Constructor
             */
            LinkedListIterator();
            /**
             * \brief
             *  Destructor
             */
            ~LinkedListIterator();

        public:
            /**
             * \brief
             *  Access operator of this iterator
             *
             * \return  The value pointed by this iterator
             */
            T&      operator*();

            /**
             * \brief
             *  Make a step with this iterator
             */
            void    next();

            /**
             * \brief
             *  Make a step with this iterator. see next()
             */
            void    operator++();

            /**
             * \brief
             *  Comparator operator
             *
             * \param[in]   it  Other iterator to compare with
             *
             * \return  Whether or not the iterators are different
             */
            bool    operator!=(LinkedListIterator<T> it);
            /**
             * \brief
             *  Comparator operator
             *
             * \param[in]   it  Other iterator to compare with
             *
             * \return  Whether or not the iterators are equals
             */
            bool    operator==(LinkedListIterator<T> it);

        private:
            struct LinkedList<T>::node* m_current_node;     /*!<    Node pointed by this iterator   */
        };

        #include "LinkedList.inc"
    }
}

#endif
