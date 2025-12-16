#include "Compiler/Parser.h"

using namespace std;

void compile(string src) {
    scanSourceCode(src);
    beginParse();
}

int main(int argc, char const *argv[])
{
    compile("ExampleSourceCode/program2.fz");
}
