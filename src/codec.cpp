#include <doomsound.hpp>

namespace doomsound
{
#pragma pack(push, 1)
    struct WAVHeader
    {
        char riff[4] = {'R', 'I', 'F', 'F'}; // "RIFF"
        uint32_t chunkSize;                  // Size of the WAV file - 8 bytes
        char wave[4] = {'W', 'A', 'V', 'E'}; // "WAVE"
        char fmt[4] = {'f', 'm', 't', ' '};  // "fmt "
        uint32_t subchunk1Size = 16;         // PCM format, size of this chunk (16 for PCM)
        uint16_t audioFormat = 1;            // PCM = 1
        uint16_t numChannels;                // Number of channels
        uint32_t sampleRate;                 // Sampling frequency
        uint32_t byteRate;                   // sampleRate * numChannels * bitsPerSample / 8
        uint16_t blockAlign;                 // numChannels * bitsPerSample / 8
        uint16_t bitsPerSample;              // Bits per sample
        char data[4] = {'d', 'a', 't', 'a'}; // "data"
        uint32_t dataSize;                   // Number of bytes in the data
    };
#pragma pack(pop)

    static void writeWAV(std::vector<uint8_t> &packet, const std::pair<const uint8_t *, size_t> &pcmData, uint32_t sampleRate)
    {
        // Calculate sizes
        uint32_t dataSize = pcmData.second;
        uint32_t chunkSize = 36 + dataSize;

        // Fill WAV header
        WAVHeader header;
        header.chunkSize = chunkSize;
        header.numChannels = 1;
        header.sampleRate = sampleRate;
        header.bitsPerSample = 8;
        header.byteRate = sampleRate * 1 / 8;
        header.blockAlign = 1;
        header.dataSize = static_cast<uint32_t>(dataSize);

        packet.insert(packet.end(), reinterpret_cast<const uint8_t *>(&header), reinterpret_cast<const uint8_t *>(&header) + sizeof(WAVHeader));
        packet.insert(packet.end(), reinterpret_cast<const uint8_t *>(pcmData.first), reinterpret_cast<const uint8_t *>(pcmData.first) + dataSize);
    }

    const uint8_t *basic_encoder::packet_data() const
    {
        return _packet.data();
    }

    size_t basic_encoder::packet_size() const
    {
        return _packet.size();
    }

    void wav_encoder::encode(const uint8_t *data, size_t size)
    {
        std::pair<const uint8_t *, size_t> samples;
        const uint16_t sample_rate = *reinterpret_cast<const uint16_t *>(data + 2);
        const uint32_t sample_count = *reinterpret_cast<const uint32_t *>(data + 4);
        samples.first = data + 24;
        samples.second = static_cast<size_t>(sample_count);
        writeWAV(_packet, samples, static_cast<uint32_t>(sample_rate));
    }

    void midi_encoder::encode(const uint8_t *data, size_t size)
    {
        _packet.resize(size);
        std::copy(data, data + size, _packet.begin());
    }
}