#ifndef PARALLAX_HPP
#define PARALLAX_HPP

#include <string>

/**
 * Version of the project
 */
#define PARALLAX_VERSION_MAJOR		"1"        /*!<    Major version of Parallax Engine    */
#define PARALLAX_VERSION_MINOR		"0"        /*!<    Minor version of Parallax Engine    */
#define PARALLAX_MAKE_DATE          "071217"            /*!<    Build date of Parallax Engine       */
#define PARALLAX_MAKE_HOUR          "092352"            /*!<    Build hour of Parallax Engine       */

/**
 * Build type
 */
#define PARALLAX_BUILD_TYPE         "Debug"                    /*!<    Build type of Parallax Engine       */

/**
 * Function to identify version
 */
std::string getParallaxVersion();

/**
 * \defgroup    PIL     Platform Independance Layer
 * \defgroup    Core    Core systems of the engine
 */

#endif
