#include "Compiler/Parser.h"

using namespace std;

void compile(string src) {
    cout << "Compiling file: " + src + "\n";
    scanSourceCode(src);
    cout << "Scan complete. Beginning parse...\n";
    beginParse();
}

int main(int argc, char const *argv[])
{
    compile("ExampleSourceCode/program2.fz");
}
