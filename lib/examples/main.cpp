#include "EasyDSP.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <expected>

int main() {
    std::cout << "this is a simple program to showcase the features of easydsp" << std::endl;
    std::cout << std::endl;

    /// creating a window lowpass

    auto lp = oh::fir::WindowLowpass::create(0.25, 9);
    if(!lp) {
        std::cout << toString(lp.error());
    } else {
        std::cout << "succesfully created WindowLowpass(1)" << std::endl;
    }

    /// creating a window bandpass

    auto bp = oh::fir::WindowBandpass::create(0.1, 0.4, 9);
    if(!bp) {
        std::cout << toString(lp.error());
    } else {
        std::cout << "succesfully created WindowBandpass(2)" << std::endl;
    }

    /// creating a window highpass

    auto hp = oh::fir::WindowHighpass::create(0.25, 9);
    if(!hp) {
        std::cout << toString(lp.error());
    } else {
        std::cout << "succesfully created WindowHighpass(3)" << std::endl;
    }

    /// creating a frequency sampling filter

    std::vector <double> H = {0.5, 0.5, 1, 1};

    auto fs = oh::fir::FrequencySampling::create(H);
    if(!fs) {
        std::cout << toString(lp.error());
    } else {
        std::cout << "succesfully created Frequencysampling(4)" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "---checking getters---" << std::endl;

    std::cout << std::endl;
    std::cout << "-------getType--------" << std::endl;
    std::cout << std::endl;

    std::cout << "1: " << toString(lp -> getType()) << std::endl;
    std::cout << "2: " << toString(bp -> getType()) << std::endl;
    std::cout << "3: " << toString(hp -> getType()) << std::endl;
    std::cout << "4: " << toString(fs -> getType()) << std::endl;

    std::cout << std::endl;
    std::cout << "-------getSize--------" << std::endl;
    std::cout << std::endl;

    std::cout << "1: " << lp -> getSize() << std::endl;
    std::cout << "2: " << bp -> getSize() << std::endl;
    std::cout << "3: " << hp -> getSize() << std::endl;
    std::cout << "4: " << fs -> getSize() << std::endl;

    std::cout << std::endl;
    std::cout << "----getCoefficients----" << std::endl;
    std::cout << std::endl;

    std::cout << "WindowLowpass: " << std::endl;
    for(auto w : lp -> getCoefficients()) {
        std::cout << w << std::endl;
    }

    std::cout << std::endl;

    std::cout << "WindowBandpass: " << std::endl;
    for(auto w : bp -> getCoefficients()) {
        std::cout << w << std::endl;
    }

    std::cout << std::endl;

    std::cout << "WindowHighpass: " << std::endl;
    for(auto w : hp -> getCoefficients()) {
        std::cout << w << std::endl;
    }

    std::cout << std::endl;

    std::cout << "FrequencySampling " << std::endl;
    for(auto w : fs -> getCoefficients()) {
        std::cout << w << std::endl;
    }
    
}