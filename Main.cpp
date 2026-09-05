#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

class Mediaengine {
private:
    std::vector<std::string> VideoQueue;

    // Clean path without internal outer quotes
    const std::string ffmpegBin = "D:\\msys64\\ucrt64\\bin\\ffmpeg.exe";

    bool fileExists(const std::string& filename) {
        std::ifstream f(filename);
        return f.good();
    }

public:
    void addMedia(const std::string& filepath) {
        VideoQueue.push_back(filepath);
    }

    void processQueue() {
        for (const std::string& video : VideoQueue) {
            if (!fileExists(video)) {
                std::cout << video << " not found, creating synthetic using ffmpeg.." << std::endl;

                // Wrap whole string in outer quotes to satisfy Windows CMD quote parsing
                std::string CreateCmd = "\"" + ffmpegBin + " -loglevel error -y -f lavfi -i testsrc=duration=3:size=1280x720:rate=30 "
                                        "-f lavfi -i anullsrc=r=44100:cl=stereo -c:v libx264 -c:a aac -shortest \"" + video + "\"\"";
                std::system(CreateCmd.c_str());
            }

            std::cout << "Now Processing.. " << video << std::endl;

            std::string outputFile = "processed_" + video;

            // Double-quoted wrapper around entire command string
            std::string command = "\"" + ffmpegBin + " -loglevel error -y -i \"" + video + "\" -c:v libx264 -preset ultrafast -c:a copy \"" + outputFile + "\"\"";

            int returncode = std::system(command.c_str());

            if (returncode == 0) {
                std::cout << "[SUCCESS] Done encoding " << video << " -> " << outputFile << std::endl;
            } else {
                std::cout << "[ERROR] FFmpeg failed on " << video << " (Exit code: " << returncode << ")" << std::endl;
            }
        }
    }
};

int main() {
    Mediaengine engine;
    engine.addMedia("Chomik.mp4");
    engine.addMedia("yooo.mp4");
    engine.processQueue();
    return 0;
}