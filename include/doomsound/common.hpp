#ifndef DOOMSOUND_COMMON_HPP
#define DOOMSOUND_COMMON_HPP

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
            _handle = constructor.init(data, size);
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
}

#endif