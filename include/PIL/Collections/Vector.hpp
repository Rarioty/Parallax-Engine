#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <PIL/Types.hpp>
#include <functional>
#include <cstring>
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
            Vector(U32 start_size = 32);
            ~Vector();

        public:
            Iterator                begin();
            Iterator                end();

            void                    push_front(T element);
            void                    push_back(T element);
            void                    insert(T element, U32 position);

            U32                     size();
            void                    resize(U32 new_size);

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
            std::pair<U32, U32*>    find_all(T needle);
            std::pair<U32, U32*>    find_all(const std::function<bool(U32, T*)>& func);

            void                    sort(const std::function<bool(T, T)>& comparator);

        private:
            U32     m_max_size;
            U32     m_current;
            T*      m_array;
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
            T       operator*();

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
