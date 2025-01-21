#ifndef DOOMSOUND_HPP
#define DOOMSOUND_HPP

#include <functional>
#include <memory>
#include <string>

namespace doomsound
{
    class basic_handle_constructor
    {
    public:
        virtual std::unique_ptr<void, std::function<void(void *)>> init(const uint8_t *data, size_t size) = 0;
    };

    class wav_handle_constructor : public basic_handle_constructor
    {
    public:
        std::unique_ptr<void, std::function<void(void *)>> init(const uint8_t *data, size_t size) override;
    };

    class midi_handle_constructor : public basic_handle_constructor
    {
    public:
        std::unique_ptr<void, std::function<void(void *)>> init(const uint8_t *data, size_t size) override;
    };

    template <class HandleConstructorType>
    class handle
    {
    public:
        handle(const uint8_t *data, size_t size)
        {
            HandleConstructorType constructor;
            _handle = constructor->init(data, size);
        }
        handle(const handle &other) = delete;
        handle(handle &&other) = default;
        ~handle() = default;

        void *get() const
        {
            return _handle.get();
        }

    private:
        std::unique_ptr<void, std::function<void(void *)>> _handle;
    };

    using wav_handle = handle<wav_handle_constructor>;
    using midi_handle = handle<midi_handle_constructor>;

    class basic_encoder
    {
    public:
        virtual void encode(const uint8_t *data, size_t size) = 0;
        const uint8_t *packet_data() const { return _packet.data(); }
        size_t packet_size() const { return _packet.size(); }

    protected:
        std::vector<uint8_t> _packet;
    };

    class wav_encoder : public basic_encoder
    {
    public:
        void encode(const uint8_t *data, size_t size) override;
    };

    class midi_encoder : public basic_encoder
    {
    public:
        void encode(const uint8_t *data, size_t size) override;
    };

    template <class EncoderType, class HandleType>
    HandleType encode_handle(const uint8_t *data, size_t size)
    {
        EncoderType encoder;
        encoder.encode(data, size);
        return HandleType(encoder.packet_data(), encoder.packet_size());
    }

    wav_handle encode_wav(const uint8_t *dmx_data, size_t dmx_size);
    midi_handle encode_midi(const uint8_t *mus_data, size_t mus_size);

    const std::string default_device = "";

    class soundcard
    {
    public:
        soundcard();
        ~soundcard();

        void open(const std::string &device = default_device);
        void close();

    private:
        bool _is_open;
    };
}

#endif