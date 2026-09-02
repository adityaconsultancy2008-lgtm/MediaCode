#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

class Mediaengine {
private:
    std::vector<std::string> VideoQueue;
    
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
                
                // Added space before video and wrapped path in quotes!
                std::string CreateCmd = "ffmpeg -loglevel error -y -f lavfi -i testsrc=duration=3:size=1280x720:rate=30 \"" + video + "\"";
                std::system(CreateCmd.c_str()); // added missing semicolon here
            }
            
            std::cout << "Now Processing.. " << video << std::endl;
            
            // wrapped paths in quotes to protect against spaces in filenames(no shit sherlock)
            std::string command = "ffmpeg -loglevel error -i \"" + video + "\" -c:v libx264 -preset ultrafast \"output_" + video + "\"";
            
            int returncode = std::system(command.c_str());
            
            if (returncode == 0) {
                std::cout << "[SUCCESS] Done encoding " << video << std::endl;
            } else {
                std::cout << "[ERROR] FFmpeg failed on " << video << std::endl;
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
