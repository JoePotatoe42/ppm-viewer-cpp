#include "read_file.h"
#include "window.h"


int main(int argc, char** argv)
{
    std::string file_address;
    if (argc < 2) {
        std::cout << "Please input the absolute address of the ppm file: ";
        std::cin >> file_address;
    }
    else file_address = argv[1];
    

    std::ifstream file_handle(file_address, std::ios::binary);
    
    if (file_handle.is_open()) 
    {
        PPMImage image = readHeader(file_handle);
        if (image.isWrongFormat()) 
        {
            std::cerr << "Unsupported format: " << image.format << "\n";
            std::cin >> file_address;
            return 1;
        }
        std::vector<RGB> test = readAllPixels(file_handle, image);
        createWindow(image.width, image.height, file_address, test);        
    }
    else 
    {
        std::cout<<"Failed to open file: "<<file_address<<std::endl;
    }
    return 0;
}