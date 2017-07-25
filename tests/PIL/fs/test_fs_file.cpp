#include <Parallax/FS/fs.hpp>

#include <Parallax/Collections/Vector.hpp>

#include <tests.hpp>
#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    FS::File rootdir;
    FS::File tmp;

    // Creating architecture
    rootdir = FS::File(FS::open("testdir"));
    FS::File a(rootdir);

    a = FS::File();
    register_test(!a.createDirectory(), "Error when creating directory without handler");
    register_test(!a.removeDirectory(), "Error when removing directory without handler");

    rootdir.createDirectory();
    rootdir.updateFileInfo();

    tmp = rootdir.open("testfile");

    register_test(tmp.writeFile("testcontent"), "Successfully write into file");
    register_test(rootdir.isDirectory(), "Directory checked");
    register_test(tmp.isFile(), "File checked");
    register_test(!tmp.isSymbolicLink(), "Symbolic link checked");

    std::cout << "Path: " << tmp.path() << std::endl;
    std::cout << "Filename: " << tmp.filename() << std::endl;
    std::cout << "Size: " << tmp.size() << std::endl;
    std::cout << "Atime: " << tmp.lastAccessTime() << std::endl;
    std::cout << "Mtime: " << tmp.lastModificationTime() << std::endl;
    std::cout << "SHA1: " << tmp.sha1() << std::endl;
    std::cout << "Parent directory: " << tmp.parentDirectory().path() << std::endl;

    // Try copy testfile
    FS::File copy = FS::open("testdir/testcopy");
    FS::File move = FS::open("testmove");
    FS::File link = FS::open("link");
    FS::File symlink = FS::open("symlink");
    register_test(tmp.createSymbolicLink(symlink), "Successfully created symlink");
    register_test(symlink.isSymbolicLink(), "Correct symlink");
    symlink.remove();
    register_test(tmp.copy(copy), "Successfully copied");
    register_test(copy.move(move), "Successfully moved");
    register_test(tmp.createLink(link), "Successfully created link");
    register_test(tmp.rename("ahah"), "Successfully renamed");

    register_test(tmp.readFile() == "testcontent", "Successfully readed file");

    Collections::Vector<std::string> files(FS::open(".").listFiles());

    // Removing architecture
    tmp.remove();
    copy.remove();
    link.remove();
    rootdir.removeDirectory();

    return end_test();
}
