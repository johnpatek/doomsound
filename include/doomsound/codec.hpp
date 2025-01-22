#ifndef DOOMSOUND_CODEC_HPP
#define DOOMSOUND_CODEC_HPP

#include "common.hpp"
#include <iostream>

namespace doomsound
{
    class basic_encoder
    {
    public:
        virtual void encode(const uint8_t *data, size_t size) = 0;
        const uint8_t *packet_data() const;
        size_t packet_size() const;
    protected:
        std::vector<uint8_t> _packet;
    };

    class wav_encoder : public basic_encoder
    {
    public:
        wav_encoder() = default;
        void encode(const uint8_t *dmx_data, size_t dmx_size) override;
    };

    class midi_encoder : public basic_encoder
    {
    public:
        midi_encoder() = default;
        void encode(const uint8_t *mus_data, size_t mus_size) override;
    };

    template<class EncoderType> 
    void encode(const uint8_t *data, size_t size, const std::function<void(const uint8_t*, size_t)>& callback)
    {
        static_assert(std::is_base_of<basic_encoder, EncoderType>::value, "EncoderType must derive from basic_encoder");
        EncoderType encoder;
        encoder.encode(data, size);
        callback(encoder.packet_data(), encoder.packet_size());
    }
}
#endif