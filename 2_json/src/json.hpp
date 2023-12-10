#include <cstddef>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct JSONNode;

using JSONObject = std::unordered_map<std::string,  std::shared_ptr<JSONNode> >;
using JSONList = std::vector<std::shared_ptr<JSONNode> >;
struct JSONNode {
    enum class Type {OBJECT, LIST, STRING, NUMBER, BOOLEAN, NULL_TYPE};
    union Values {
        JSONObject *object;
        JSONList *list;
        std::string *s;
        float fVal;
        bool bVal;
    } values;
    Type type;
};

enum class TOKEN{
    CURLY_OPEN,
    CURLY_CLOSED,
    BRACKET_OPEN,
    BRACKET_CLOSED,
    COMMA,
    ESCAPECHAR,
    STRING,
    NUMBER,
    COLON,
    NULL_TYPE
};

struct Token{
    std::string value;
    TOKEN type;
    std::string toString();
};

class Tokenizer
{
    private:
        std::fstream file;
        size_t prevPos;
    public:
        Tokenizer(std::string fileName);
        char getWithoutWhiteSpace();
        Token getToken();
        bool hasMoreTokens();
        void rollBackToken();
};

class JSONParser {
    std::fstream file;
    std::shared_ptr<JSONNode> root;
    std::unique_ptr<JSONNode> current;
    Tokenizer tokenizer;

    public:
        JSONParser(const std::string filename) : tokenizer(filename){};
        void parse();
        std::unique_ptr<JSONNode> parseObject();
};
