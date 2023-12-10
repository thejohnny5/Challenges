#include <iostream>
#include <fstream>
#include <string>

namespace FH {

    enum ffmode {
        BINARY,
        DEFAULT,
    };

    // Class to open file
    class FF {
    private:
        std::ifstream ff;
    public:
        FF(std::string file, ffmode mode);
        ~FF();
        int charCount();
        uint16_t getLines();
        uint32_t getWords();
        void close();
        void open(std::string file, ffmode mode);
};
}
