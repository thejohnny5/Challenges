#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Outline for a CommandLineArgument
*/
struct CommandLineArgument {
    std::string name;
    char shortFlag;
    std::string longFlag;
    bool required;
    std::string description;
    bool hasValue;
    std::string defaultValue;
    std::string value;
    bool used;
    bool stdinAllowed;  // New field to indicate if stdin is allowed as default
};

class ArgumentParser {
private:
    // Array of CommandLineArguments
    std::vector<CommandLineArgument> arguments;

    // the default argument at the end of the command line arg 
    std::string default_arg;

    // Name of the command line tool. Will be displaying in the usage
    std::string toolName;

    // Info about the command line tool. Will be displayed in usage
    std::string info;
public:

    ArgumentParser(std::string name, std::string programinfo = "") : toolName(name), info(programinfo) {};
    
    // Essentially a constructor for a CommandLineArgument struct, which gets added to arguments
    void addArgument(const std::string& name, char shortFlag, const std::string& longFlag, bool required, const std::string& description, bool hasValue = false, const std::string& defaultValue = "", bool stdinAllowed = false);
    
    // Parse the main arguments into arguments
    bool parse(int argc, const char* argv[]);

    // Value associated with parsed argument
    std::string getArgumentValue(const std::string& name);

    // Shows how to use the command line tool
    void showUsage();

    // Returns the commandLine argument in the arguments vector
    CommandLineArgument* findArgument(const std::string& arg);

    void handleDefaultArgument(const std::string& arg);

    // getter for 'default_arg'
    std::string getDefault();

    bool isUsed(const std::string& name);
};