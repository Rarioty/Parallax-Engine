#include <Core/Parsers/CSV/CSVParser.hpp>

#include <PIL/fs/File.hpp>
#include <PIL/fs/fs.hpp>
#include <tests.hpp>

using namespace Parallax;

int main(int argc, char* argv[])
{
    int ret;
    fs::File f = fs::open("test.csv");
    (*f.createOutputStream()) << "x,y\n1,2\n3,4\n5,6";

    Core::Parser::CSVParser parser("test.csv", ',');

    register_test(parser.rowCount() == 3, "Correct row count");
    register_test(parser.columnCount() == 2, "Correct column count");

    Core::Parser::CSVRow row = parser.getRow(1);

    row.set("t", "32");
    row.set("x", "10");

    std::cout << row[0] << " ==? 10" << std::endl;
    register_test(row[0] == "10", "Correct element");

    ret = 0;
    try {
        row[10];
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when accessing too far element on row");

    std::string key = "y";

    std::cout << row[key] << " ==? 4" << std::endl;
    register_test(row[key] == "4", "Correct element with key");

    key = "p";

    ret = 0;
    try {
        row[key];
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when accessing too far element on row with key");

    std::cout << "Row: " << row << std::endl;

    ret = 0;
    try {
        row = parser[10];
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised error when getting too far row");

    Collections::Vector<std::string> headers = parser.getHeaders();

    register_test(parser.getHeaderElement(0) == "x", "Correct header element");
    ret = 0;
    try {
        parser.getHeaderElement(5);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised error when getting too far header element");

    parser.deleteRow(10);
    parser.deleteRow(0);

    Collections::Vector<std::string> vec;
    vec.push_back("3");
    vec.push_back("2");

    parser.addRow(10, vec);
    parser.addRow(0, vec);

    parser.sync();

    parser.getFilename();

    f.remove();

    return end_test();
}
