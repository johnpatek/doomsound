#include <wadtek.hpp>

#include <iostream>

namespace wadsnd
{
    class shell
    {
    public:
        shell(const std::string& path);
        ~shell() = default;
        void launch();
    };

    void main_loop(const std::string& path);
}