#ifndef STACK_HPP
#define STACK_HPP

#include <PIL/Types.hpp>
#include <functional>
#include <cstring>

namespace Parallax
{
    /**
     * \namespace   Parallax::Collections
     * \ingroup     PIL
     */
    namespace Collections
    {
        /**
         * \class   Stack
         * \brief   Stack container
         *
         * \tparam  T   Type of the elements in the container.
         */
        template <typename T>
        class Stack
        {
        public:
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   starting_size   Starting size of the allocated array
             */
            Stack(U32 starting_size = 32);
            /**
             * \brief
             *  Destructor
             */
            ~Stack();

        public:
            /**
             * \brief
             *  Get the top element of the stack
             *
             * \return  The top element of the stack
             */
            T&      top();

            /**
             * \brief
             *  Is the stack empty ?
             *
             * \return  Whether the stack is empty or not
             */
            bool    empty();
            /**
             * \brief
             *  Return the size of the stack
             *
             * \return  Size of the stack
             */
            U32     size();

            /**
             * \brief
             *  Push element on the top of the stack
             *
             * \param[in]   element     Element to push
             */
            void    push(T element);
            /**
             * \brief
             *  Pop the top element
             *
             * \return  The element which was on the top of the stack
             */
            T       pop();

        private:
            /**
             * \brief
             *  Resize the allocated array for the stack
             *
             * \param[in]   new_size    New size for the array
             */
            void    resize(U32 new_size);

        private:
            U32     m_max_size;     /*!<    Size of the allocated array     */
            U32     m_current;      /*!<    Current size of the stack       */
            T*      m_array;        /*!<    Array of elements               */
        };

        #include "Stack.inc"
    }
}

#endif
