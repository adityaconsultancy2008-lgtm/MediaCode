#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
class Mediaengine{
    private:
         std::vector<std::string> VideoQueue;

    public:
       void addMedia (const std::string& filepath){
        VideoQueue.push_back(filepath);
       }
    void processQueue(){
        for(const std::string& video:VideoQueue){
            std::cout << "Now Processing.." << video <<std::endl;
            std::string command = "ffmpeg -i "+ video + " -c:v libx264 -preset ultrafast output_" + video;
          int returncode = std::system(command.c_str());
          if (returncode == 0) {
                std::cout << "[SUCCESS] Done encoding " << video << std::endl;
            } else {
                std::cout << "[ERROR] FFmpeg failed on " << video << std::endl;
            }
        }
    }
};
int main(){
    Mediaengine engine;
    engine.addMedia("Chomik.mp4");
    engine.addMedia("yooo.mp4");
    engine.processQueue();
    return 0;

}