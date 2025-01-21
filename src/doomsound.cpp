#include <doomsound.hpp>

#include <SDL.h>
#include <SDL_mixer.h>

namespace doomsound
{
    std::unique_ptr<void, std::function<void(void *)>> wav_handle_constructor::init(const uint8_t *data, size_t size)
    {
        return nullptr;
    }

    std::unique_ptr<void, std::function<void(void *)>> midi_handle_constructor::init(const uint8_t *data, size_t size)
    {
        return nullptr;
    }

    wav_handle encode_wav(const uint8_t *dmx_data, size_t dmx_size)
    {
        return encode_handle<wav_encoder, wav_handle>(dmx_data, dmx_size);
    }

    midi_handle encode_midi(const uint8_t *mus_data, size_t mus_size)
    {
        return encode_handle<midi_encoder, midi_handle>(mus_data, mus_size);
    }

}