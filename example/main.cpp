#include <wadtek.hpp>

#include <iostream>
#include <unordered_map>

class audio_manager
{
public:
    audio_manager() = default;
    audio_manager(const audio_manager& other) = delete;
    audio_manager(audio_manager&& other) noexcept = default;
    ~audio_manager() = default;

    void upload_sfx(const std::string& name, const uint8_t* data, size_t size)
    {
        std::cerr << "uploading sfx: " << name << std::endl;
    }
private:
    std::unordered_map<std::string, uint32_t> _sfx;
};

static void wadsnd_main(const std::string& path)
{
    wadtek::file file(path);
    audio_manager audio;
    std::for_each(file.begin(), file.end(), [&](const wadtek::lump& lump)
    {
        if(lump.name().find("DS") == 0)
        {
            audio.upload_sfx(lump.name(), lump.data(), lump.size());
        }
    });
}

int main(int argc, char** argv) 
{
    if (argc > 1)
    {
        wadsnd_main(argv[1]);
    }
    else
    {
        std::cerr << "usage: wadsnd <path>" << std::endl;
    }
    return 0;
}