#include <Parallax/fs/Path.hpp>

#include <tests.hpp>
#include <iostream>
#include <string>

using namespace Parallax;

int main(int argc, char* argv[])
{
    fs::Path tmp;
    fs::Path path(tmp);

    path = fs::Path("test.txt") = fs::Path(std::string("folder/"));
    path.setPath("C:\\test\\directory\\..\\here\\file.testextension");

    std::cout << "Path: " << path.path() << std::endl;
    std::cout << "Native: " << path.toNative() << std::endl;
    std::cout << "Empty: " << path.isEmpty() << std::endl;
    std::cout << "Points to contents: " << path.pointsToContents() << std::endl;
    std::cout << "Full path: " << path.fullPath() << std::endl;
    std::cout << "Filename: " << path.filename() << std::endl;
    std::cout << "Basename: " << path.basename() << std::endl;
    std::cout << "Extension: " << path.extension() << std::endl;
    std::cout << "Directory path: " << path.directoryPath() << std::endl;
    std::cout << "Drive letter: " << path.driveLetter() << std::endl;
    std::cout << "Absolute: " << path.isAbsolute() << std::endl;
    std::cout << "Relative: " << path.isRelative() << std::endl;
    std::cout << "Resolving ..: " << path.resolve("..").path() << std::endl;
    std::cout << "Resolved: " << path.resolved() << std::endl;

    std::cout << "Resolving empty path: " << fs::Path().resolve("").path() << std::endl;
    std::cout << "Resolving with empty path: " << path.resolve("").path() << std::endl;
    std::cout << "Resolving with absolute: " << path.resolve("D:\\test").path() << std::endl;

    return end_test();
}
