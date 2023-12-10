#include "Parser.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <memory>
#include <sstream>


void ArgumentParser::addArgument(const std::string& name, char shortFlag, const std::string& longFlag, bool required, bool hasValue, const std::string& defaultValue, bool stdinAllowed)
{
        arguments.push_back({name, shortFlag, longFlag, required, hasValue, defaultValue, "", false, stdinAllowed});
}

bool ArgumentParser::parse(int argc, const char* argv[]) {
    bool defaultArgumentUsed = false;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg[0] == '-') {  // This is a flag
            CommandLineArgument* cli = findArgument(arg);
            if (!cli) {
                std::cerr << "Unknown argument: " << arg << std::endl;
                showUsage();
                return false;
            }

            if (cli->hasValue) {
                if (i + 1 >= argc) {
                    std::cerr << "No value provided for argument: " << arg << std::endl;
                    showUsage();
                    return false;
                }
                cli->value = argv[++i];
            }

            cli->used = true;
        } else {
            // This is the default argument
            if (defaultArgumentUsed) {
                std::cerr << "Multiple default arguments provided." << std::endl;
                showUsage();
                return false;
            }
            ArgumentParser::handleDefaultArgument(arg);
            defaultArgumentUsed = true;
        }
    }

    // Check for missing required arguments
    for (const auto& cli : arguments) {
        if (cli.required && !cli.used) {
            std::cerr << "Missing required argument: " << cli.name << std::endl;
            showUsage();
            return false;
        }
    }

    return true;
}

CommandLineArgument* ArgumentParser::findArgument(const std::string& arg) {
    for (auto& cli : arguments) {
        if (arg[1] == '-' && arg.substr(2) == cli.longFlag) return &cli;
        if (arg[1] != '-' && arg[1] == cli.shortFlag) return &cli;
    }
    return nullptr;
}
bool fileExists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void ArgumentParser::handleDefaultArgument(const std::string& arg) {
    if (fileExists(arg)) {
        std::ifstream fileStream(arg);
        if (!fileStream) {
            std::cerr << "Could not open file: " << arg << std::endl;
            exit(EXIT_FAILURE);
        }

        std::stringstream buffer;
        buffer << fileStream.rdbuf(); // Reads the entire content of the file

        default_arg = buffer.str(); //
    } else {
        // Treat as a string stream
        default_arg = arg;
    }

}

std::string ArgumentParser::getDefault(){
    return default_arg;
}


std::string ArgumentParser::getArgumentValue(const std::string& name){
    for (auto &arg: arguments){
        if (arg.name == name){
            return arg.value;
        }
    }
    std::cerr << "No argument for name: " << name << std::endl;
    return "";
}

void ArgumentParser::showUsage(){
    std::cout << "Usage: " << std::endl;
}