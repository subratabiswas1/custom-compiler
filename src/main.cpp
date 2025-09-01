#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

#include "generation.hpp"
using namespace std;
int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Incorrect usage. Correct usage is..." << endl;
        cerr << "basic <input.bl>" << endl;
        return EXIT_FAILURE;
    }

    string contents;
    {
        stringstream contents_stream;
        fstream input(argv[1], ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(move(contents));
    vector<Token> tokens = tokenizer.tokenize();

    Parser parser(move(tokens));
    optional<NodeProg> prog = parser.parse_prog();

    if (!prog.has_value()) {
        cerr << "Invalid program" << endl;
        exit(EXIT_FAILURE);
    }

    {
        Generator generator(prog.value());
        fstream file("out.asm", ios::out);
        file << generator.gen_prog();
    }

    system("nasm -felf64 out.asm");
    system("ld out.o -o out");
    system("./out");

    return EXIT_SUCCESS;
}