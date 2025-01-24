#include <wadsnd.hpp>

namespace wadsnd
{
    void shell::launch()
    {
        std::cerr << "wadsnd::shell::launch()" << std::endl;
    }

}

void wadsnd::main_loop(const std::string& path)
{
    std::unique_ptr<wadsnd::shell> shell;
    try
    {
        shell = std::make_unique<wadsnd::shell>(path);
        shell->launch();
    }
    catch(const std::exception& error)
    {
        std::cerr << error.what() << std::endl;
    }
        
}