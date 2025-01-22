#include <doomsound.hpp>

#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>

namespace doomsound
{
    template <class Type, Type *(*LoadFunc)(SDL_RWops *, int), void (*FreeFunc)(Type *)>
    std::unique_ptr<void, std::function<void(void *)>> opaque_constructor(const uint8_t *data, size_t size)
    {
        SDL_RWops *rw = SDL_RWFromConstMem(data, size);
        Type *opaque = LoadFunc(rw, 1);
        if(opaque == nullptr)
        {
            std::cerr << "bad chunk: " << Mix_GetError() << std::endl;
        }
        const std::function deleter = [](void *opaque)
        {
            FreeFunc(static_cast<Type *>(opaque));
        };
        return std::unique_ptr<void, std::function<void(void *)>>(opaque, deleter);
    }

    std::unique_ptr<void, std::function<void(void *)>> wav_handle_constructor::init(const uint8_t *data, size_t size)
    {
        return opaque_constructor<Mix_Chunk, &Mix_LoadWAV_RW, &Mix_FreeChunk>(data, size);
    }

    std::unique_ptr<void, std::function<void(void *)>> midi_handle_constructor::init(const uint8_t *data, size_t size)
    {
        return opaque_constructor<Mix_Music, &Mix_LoadMUS_RW, &Mix_FreeMusic>(data, size);
    }


    std::list<std::string> get_devices()
    {
        std::list<std::string> devices;
        int num = SDL_GetNumAudioDevices(0);
        for (int i = 0; i < num; i++)
        {
            devices.push_back(SDL_GetAudioDeviceName(i, 0));
        }
        return devices;
    }

    soundcard::soundcard() : _is_open(false) {}
    soundcard::~soundcard()
    {
        if (_is_open)
        {
            close();
        }
    }

    void soundcard::open(const std::string &device)
    {
        const char *device_name = device.empty() ? nullptr : device.c_str();
        if(Mix_OpenAudioDevice(
            MIX_DEFAULT_FREQUENCY,
            MIX_DEFAULT_FORMAT,
            MIX_DEFAULT_CHANNELS,
            2048,
            device_name,
            SDL_AUDIO_ALLOW_ANY_CHANGE) < 0)
        {
            std::cerr << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        }
        _is_open = true;
    }

    void soundcard::close()
    {
        Mix_CloseAudio();
        _is_open = false;
    }

    void soundcard::play_sfx(const wav_handle &sfx)
    {
        if(Mix_PlayChannel(-1, static_cast<Mix_Chunk *>(sfx.get()), 0) < 0)
        {
            std::cerr << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
        }
    }

    void soundcard::play_music(const midi_handle &mus)
    {
        Mix_PlayMusic(static_cast<Mix_Music *>(mus.get()), 0);
    }
}