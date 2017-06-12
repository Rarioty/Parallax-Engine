#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <cstdint>

namespace Parallax
{
    /*
     * \brief   Definition of fixed size types
     */
    typedef int8_t      I8;             /*!<    8 bits long integer                         */
    typedef int16_t     I16;            /*!<    16 bits long integer                        */
    typedef int32_t     I32;            /*!<    32 bits long integer                        */
    typedef int64_t     I64;            /*!<    64 bits long integer                        */

    typedef uint8_t     U8;             /*!<    8 bits long unsigned                        */
    typedef uint16_t    U16;            /*!<    16 bits long unsigned                       */
    typedef uint32_t    U32;            /*!<    32 bits long unsigned                       */
    typedef uint64_t    U64;            /*!<    64 bits long unsigned                       */

    typedef std::size_t size_t;         /*!<    include size_t type in Parallax             */
    typedef intptr_t    Pointer;        /*!<    Pointer size                                */
    typedef uintptr_t   UPointer;       /*!<    Pointer size with unsigned representation   */

    #define  I8_MAX     INT8_MAX        /*!<    Maximum value for a 8 bits long integer     */
    #define  I16_MAX    INT16_MAX       /*!<    Maximum value for a 16 bits long integer    */
    #define  I32_MAX    INT32_MAX       /*!<    Maximum value for a 32 bits long integer    */
    #define  I64_MAX    INT64_MAX       /*!<    Maximum value for a 64 bits long integer    */

    #define  I8_MIN     INT8_MIN        /*!<    Minimum value for a 8 bits long integer     */
    #define  I16_MIN    INT16_MIN       /*!<    Minimum value for a 16 bits long integer    */
    #define  I32_MIN    INT32_MIN       /*!<    Minimum value for a 32 bits long integer    */
    #define  I64_MIN    INT64_MIN       /*!<    Minimum value for a 64 bits long integer    */

    #define  U8_MAX     UINT8_MAX       /*!<    Maximum value for a 8 bits long unsigned    */
    #define  U16_MAX    UINT16_MAX      /*!<    Maximum value for a 16 bits long unsigned   */
    #define  U32_MAX    UINT32_MAX      /*!<    Maximum value for a 32 bits long unsigned   */
    #define  U64_MAX    UINT64_MAX      /*!<    Maximum value for a 64 bits long unsigned   */
}

#endif
