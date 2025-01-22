#ifndef DOOMSOUND_SOUNDCARD_HPP
#define DOOMSOUND_SOUNDCARD_HPP

#include "common.hpp"

namespace doomsound
{
    const std::string default_device = "";

    std::list<std::string> get_devices();

    class soundcard
    {
    public:
        soundcard();
        ~soundcard();

        void open(const std::string &device = default_device);
        void close();
        bool is_open() const;

        void play_sfx(const wav_handle &sfx);
        void play_music(const midi_handle &mus);
        void pause_music(){}
        void resume_music(){}
        void stop_music(){}
    private:
        bool _is_open;
    };
}

#endif