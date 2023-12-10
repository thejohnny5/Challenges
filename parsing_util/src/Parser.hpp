#include <iostream>
#include <vector>
#include <string>

struct CommandLineArgument {
    std::string name;
    char shortFlag;
    std::string longFlag;
    bool required;
    bool hasValue;
    std::string defaultValue;
    std::string value;
    bool used;
    bool stdinAllowed;  // New field to indicate if stdin is allowed as default
};

class ArgumentParser {
private:
    std::vector<CommandLineArgument> arguments;
    std::string default_arg;
public:
    void addArgument(const std::string& name, char shortFlag, const std::string& longFlag, bool required, bool hasValue = false, const std::string& defaultValue = "", bool stdinAllowed = false);

    bool parse(int argc, const char* argv[]);

    std::string getArgumentValue(const std::string& name);

    void showUsage();

    CommandLineArgument* findArgument(const std::string& arg);
    void handleDefaultArgument(const std::string& arg);
    std::string getDefault();
};

// int main(int argc, char* argv[]) {
//     ArgumentParser parser;
//     // Add an argument that can default to stdin
//     parser.addArgument("input", 'i', "input", false, "", true);

//     if (!parser.parse(argc, argv)) {
//         parser.showUsage();
//         return 1;
//     }

//     std::string inputValue = parser.getArgumentValue("input");
//     if (inputValue == "") {
//         // No input argument provided, read from stdin
//         std::string line;
//         while (std::getline(std::cin, line)) {
//             // Process each line from stdin
//         }
//     } else {
//         // Use the provided argument value
//     }

//     return 0;
// }
