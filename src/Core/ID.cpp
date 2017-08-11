#include <Parallax/ID.hpp>

#include <Parallax/Debug/Debug.hpp>
#include <Parallax/Maths/Hash.hpp>
#include <cstring>
#include <map>

namespace Parallax::ID
{
    static std::map<const char*, U32>   s_StringsIDs;

    U32 generateStringHashID(const char* name)
    {
        auto it = s_StringsIDs.find(name);

        if (it == s_StringsIDs.end())
        {
            PARALLAX_TRACE("Name %s was not referenced in the IDs", name);
            std::pair<std::map<const char*, U32>::iterator, bool>
            res = s_StringsIDs.insert(std::pair<const char*, U32>(name, Maths::crc32(name, strlen(name))));
            PARALLAX_FATAL(res.second, "Checking if new ID was inserted...");

            it = res.first;
        }

        return it->second;
    }
}
