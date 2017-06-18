#ifndef VECTOR_HPP
#define VECTOR_HPP

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
        template <typename T>
        class VectorIterator;

        /**
         * \class   Vector
         * \brief   Dynamic array container
         *
         * \tparam  T   Type of the elements in the container.
         */
        template <typename T>
        class Vector
        {
        public:
            using Iterator = VectorIterator<T>;
            friend class VectorIterator<T>;

        public:
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   start_size  Default starting size to the container
             */
            Vector(U32 start_size = 32);
            /**
             * \brief
             *  Destructor
             */
            ~Vector();

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
             *  Pop an element from the back of the vector
             */
            void                    pop_back();

            /**
             * \brief
             *  Return size of this container
             *
             * \return  Current size of this container
             */
            U32                     size();
            /**
             * \brief
             *  Resize this vector with a specified size
             *
             * \param[in]   new_size    New size for the container
             */
            void                    resize(U32 new_size);

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
             *  Get a reference to the value in a specified position
             *
             * \param[in]   position    Position of the wanted value
             *
             * \return  Reference to the value
             */
            T&                      at(U32 position);

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
            U32     m_max_size;     /*!<    Size of the allocated array     */
            U32     m_current;      /*!<    Current size used by the vector */
            T*      m_array;        /*!<    Array of elements               */
        };

        /**
         * \class   VectorIterator
         * \brief   Iterator for the vector container
         *
         * \tparam  T   Type of value inside the vector container
         */
        template <typename T>
        class VectorIterator
        {
        public:
            friend class Vector<T>;

        public:
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   vector              The target vector to iterate
             * \param[in]   starting_position   Starting position in the vector
             */
            VectorIterator(Vector<T>* vector, U32 starting_position);
            /**
             * \brief
             *  Constructor
             */
            VectorIterator();
            /**
             * \brief
             *  Destructor
             */
            ~VectorIterator();

        public:
            /**
             * \brief
             *  Access operator
             *
             * \return  Value pointed by this iterator
             */
            T&      operator*();

            /**
             * \brief
             *  Make the iterator to do a step forward
             */
            void    next();
            /**
             * \brief
             *  Make the iterator to do a step forward
             */
            void    operator++();

            /**
             * \brief
             *  Comparison operator
             *
             * \param[in]   it  Iterator to compare to
             *
             * \return  Whether or not the iterators are different
             */
            bool    operator!=(VectorIterator<T> it);
            /**
             * \brief
             *  Comparison operator
             *
             * \param[in]   it  Iterator to compare to
             *
             * \return  Whether or not the iterators are equals
             */
            bool    operator==(VectorIterator<T> it);

        private:
            Vector<T>*  m_vector;   /*!<    Target container                    */
            U32         m_current;  /*!<    Current position in the container   */
        };

        #include "Vector.inc"
    }
}

#endif
