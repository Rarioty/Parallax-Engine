#include <Parallax\Platform.hpp>

#include <string>

namespace Parallax
{
	PlatformData g_platformData
	{
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr
	};

	void setPlatformData(const PlatformData& data)
	{
		memcpy(&g_platformData, &data, sizeof(PlatformData));
	}
}