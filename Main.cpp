#include<iostream>
#include<string>
#include<vector>
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
        }
    }
};
int main(){
    Mediaengine engine;
}