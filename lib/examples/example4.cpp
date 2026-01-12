#include "EasyDSP.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <expected>
#include <fstream>

int main() {
    ///< example: 

    std::cout << "this example generates a matlab script showcasing fir filters" << std::endl;

    std::fstream file ("filters.m", std::fstream::out);
    if(file.fail()) {
        std::cout << "can't create a file";
        return -1;
    }

    size_t size = 87;
    
    auto lowpass = oh::fir::WindowLowpass::create(0.25, size);
    if(!lowpass) {
        std::cout << toString(lowpass.error());
    }

    auto bandpass = oh::fir::WindowBandpass::create(0.1, 0.4, size);
    if(!bandpass) {
        std::cout << toString(bandpass.error());
    }

    auto highpass = oh::fir::WindowHighpass::create(0.25, size);
    if(!highpass) {
        std::cout << toString(highpass.error());
    }

    file << "% this is a matlab script for plotting the fir filters" << std::endl; 
    file << "clc,clear,close all;" << std::endl; 
    file << "x = [ ";
    for (int i = 0; i < size; ++i) {
        file << i << ", ";
    }
    file << "];" << std::endl;

    file << "lowpass = [ ";
    for (auto lp : lowpass -> getCoefficients()) {
        file << lp << ", ";
    }
    file << "];" << std::endl;

    file << "bandpass = [ ";
    for (auto bp : bandpass -> getCoefficients()) {
        file << bp << ", ";
    }
    file << "];" << std::endl;

        file << "highpass = [ ";
    for (auto hp : highpass -> getCoefficients()) {
        file << hp << ", ";
    }
    file << "];" << std::endl;

    file << "figure(1);" << std::endl;
    file << "plot(x, lowpass, '-.');" << std::endl;
    file << "title('Lowpass FIR');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;

    file << "figure(2);" << std::endl;
    file << "plot(x, bandpass, '-.');" << std::endl;
    file << "title('Bandpass FIR');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;

    file << "figure(3);" << std::endl;
    file << "plot(x, highpass, '-.');" << std::endl;
    file << "title('Highpass FIR');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;

    std::cout << "done, check filters.m" << std::endl;


}