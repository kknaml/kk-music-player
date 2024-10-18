

#include <fstream>
#include <music_player.hpp>

namespace kmp {
    void MusicPlayer::load(const char *path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error(std::format("Failed to open file {}", path));
        }
        // read to mData -> vector<u8>
        file.seekg(0, std::ios::end);
        mData.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char *>(mData.data()), mData.size());
        mIsLoaded = true;
    }
}


