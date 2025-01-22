#include <wadtek.hpp>
#include <doomsound.hpp>

#include <iostream>
#include <thread>
#include <unordered_map>

#include <random>
#include <cmath>
#include <SDL.h>
#include <SDL_mixer.h>

#ifdef _WIN32
#undef main
#endif

#include <wadsnd.hpp>

class audio_manager
{
public:
    audio_manager()
    {
        _soundcard.open("Speakers (Realtek(R) Audio)");
    }
    audio_manager(const audio_manager &other) = delete;
    audio_manager(audio_manager &&other) noexcept = default;
    ~audio_manager() = default;

    void upload_sfx(const std::string &name, const uint8_t *data, size_t size)
    {
        const std::function<void(const uint8_t *, size_t)> callback = [&](const uint8_t *wav_data, size_t wav_size)
        {
            _sfx.emplace(name, doomsound::wav_handle(wav_data, wav_size));
        };
        doomsound::encode<doomsound::wav_encoder>(data, size, callback);
    }

    void play_sfx(const std::string &name)
    {
        auto it = _sfx.find(name);
        if (it != _sfx.end())
        {
            _soundcard.play_sfx(it->second);
        }
    }

private:
    doomsound::soundcard _soundcard;
    std::unordered_map<std::string, doomsound::wav_handle> _sfx;
};

static void wadsnd_main(const std::string &path)
{
    auto seed = std::random_device()();
    srand(seed);
    wadtek::file file(path);
    audio_manager audio;
    const std::list<std::string> devices = doomsound::get_devices();
    std::for_each(devices.begin(), devices.end(), [&](const std::string &device)
                  { std::cerr << "device: " << device << std::endl; });

    std::vector<std::string> sfx_names;
    std::for_each(file.begin(), file.end(), [&](const wadtek::lump &lump)
                  {
        if(lump.name().find("DS") == 0)
        {
            audio.upload_sfx(lump.name(), lump.data(), lump.size());
            sfx_names.push_back(lump.name());
        } });
    const int index = rand() % sfx_names.size();
    const std::string &sfx_name = sfx_names[index];
    std::cerr << "playing: " << sfx_name << std::endl;
    audio.play_sfx(sfx_name);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS);
        wadtek::file file(argv[1]);
        
        SDL_Quit();
    }
    else
    {
        std::cerr << "usage: wadsnd <path>" << std::endl;
    }
    return 0;
}