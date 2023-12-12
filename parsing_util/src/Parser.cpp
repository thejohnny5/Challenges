#include "Parser.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <memory>
#include <sstream>
#include <unistd.h>


void ArgumentParser::addArgument(const std::string& name, char shortFlag, const std::string& longFlag, bool required, const std::string& description,bool hasValue, const std::string& defaultValue, bool stdinAllowed)
{
    arguments.push_back({name, shortFlag, longFlag, required, description, hasValue, defaultValue, "", false, stdinAllowed});
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
    
    if (!defaultArgumentUsed){
        defaultInputSource = InputSource::Stdin;
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
        defaultInputSource = InputSource::File;
        default_arg = arg;
    }  
    //  if (isatty(STDIN_FILENO)) {
        
    //     std::cout << "Input is from a terminal (or a file redirection)." << std::endl;
    // } else {
    //     std::cout << "Input is from a pipe." << std::endl;
    // }

    // if (fileExists(arg)) {
    //     defaultInputSource = InputSource::File;
    //     default_arg = arg;
    // } else if (arg == "-") {
    //     defaultInputSource = InputSource::Stdin;
    // } else {
    //     defaultInputSource = InputSource::Stdin;
        // defaultInputSource = InputSource::DirectString;
        // default_arg = arg;
    // }
}


std::string ArgumentParser::getDefault(){
    return default_arg;
}


std::string ArgumentParser::getArgumentValue(const std::string& name){
    for (auto &arg: arguments){
        if (arg.name == name && arg.used){
            return arg.value;
        } else if (arg.name == name){
            return arg.defaultValue;
        }
    }
    std::cerr << "No argument for name: " << name << std::endl;
    return "";
}

void ArgumentParser::showUsage(){
    std::cout << "Usage: " << toolName << " [OPTIONS] <File>" << std::endl;  
    std::cout << std::endl << "Options: " << std::endl;
    for (auto &c: arguments){
        std::cout << "    ";
        if (c.shortFlag != ' ' && c.longFlag!=""){
            std::cout << "-" << c.shortFlag << ",--" << c.longFlag;
        } else if (c.shortFlag == ' '){
            std::cout << "   --" <<c.longFlag;
        } else if (c.longFlag == ""){
            std::cout << "-" << c.shortFlag << " " << "     ";
        }
        std::cout << "    " << c.description << std::endl;
    }

    std::cout << info << std::endl;
}

bool ArgumentParser::isUsed(const std::string& name){
    for (auto &arg: arguments){
        if (arg.name == name){
            return arg.used;
        }
    }
    return false;
}