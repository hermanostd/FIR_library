#include "EasyDSP.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <expected>
#include <fstream>

int main() {
    ///< example: 

    std::cout << "this example generates a matlab script showcasing windows" << std::endl;

    std::fstream file ("windows.m", std::fstream::out);
    if(file.fail()) {
        std::cout << "can't create a file";
        return -1;
    }

    size_t size = 87;
    
    auto hamming = oh::wnd::Window::create(oh::wnd::WindowType::Hamming, size);
    if(!hamming) {
        std::cout << toString(hamming.error());
    }

    auto hanning = oh::wnd::Window::create(oh::wnd::WindowType::Hanning, size);
    if(!hanning) {
        std::cout << toString(hanning.error());
    }

    auto blackman = oh::wnd::Window::create(oh::wnd::WindowType::Blackman, size);
    if(!blackman) {
        std::cout << toString(blackman.error());
    }

    file << "% this is a matlab script for plotting the windows" << std::endl; 
    file << "x = [ ";
    for (int i = 0; i < size; ++i) {
        file << i << ", ";
    }
    file << "];" << std::endl;

    file << "hamming = [ ";
    for (auto ham : hamming -> getCoefficients()) {
        file << ham << ", ";
    }
    file << "];" << std::endl;

    file << "hanning = [ ";
    for (auto hann : hanning -> getCoefficients()) {
        file << hann << ", ";
    }
    file << "];" << std::endl;

        file << "blackman = [ ";
    for (auto black : blackman -> getCoefficients()) {
        file << black << ", ";
    }
    file << "];" << std::endl;

    file << "figure(1);" << std::endl;
    file << "plot(x, hamming, '.');" << std::endl;
    file << "title('Hamming Window');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;

    file << "figure(2);" << std::endl;
    file << "plot(x, hanning, '.');" << std::endl;
    file << "title('Hanning Window');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;

    file << "figure(3);" << std::endl;
    file << "plot(x, blackman, '.');" << std::endl;
    file << "title('Blackman Window');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;

    std::cout << "done, check windows.m" << std::endl;


}