#include "FIR.hpp"
#include "Lowpass.hpp"
#include "Bandpass.hpp"
#include "Highpass.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <expected>


std::string FIRError_to_string(oh::fir::FIRError fir_error) {
    switch (fir_error) {
        case oh::fir::FIRError::InvalidParameterValue:
            return "InvalidParameterValue";
        case oh::fir::FIRError::InvalidParameterOrder:
            return "InvalidParameterOrder";
        case oh::fir::FIRError::InvalidSize:
            return "InvalidSize";
        case oh::fir::FIRError::MismatchedSize:
            return "MismatchedSize";
        default:
            return "Unknown";
    }
}

std::string FIRType_to_string(oh::fir::FIRType fir_type) {
    switch (fir_type) {
        case oh::fir::FIRType::Lowpass:
            return "Lowpass";
        case oh::fir::FIRType::Bandpass:
            return "Bandpass";
        case oh::fir::FIRType::Highpass:
            return "Highpass";
        case oh::fir::FIRType::Custom:
            return "Custom";
        default:
            return "Undefined";
    }
}

int main() {
    std::cout << "this is a simple program to showcase the features of easydsp" << std::endl;
    std::cout << std::endl;

    /// creating a lowpass
    auto lp = oh::fir::Lowpass::create(0.25, 9);
    if(!lp) {
        std::cout << FIRError_to_string(lp.error());
    } else {
        std::cout << "succesfully created Lowpass" << std::endl;
    }
    /// creating a bandpass
    auto bp = oh::fir::Bandpass::create(0.1, 0.4, 9);
    if(!bp) {
        std::cout << FIRError_to_string(lp.error());
    } else {
        std::cout << "succesfully created Bandpass" << std::endl;
    }
    /// creating a highpass
    auto hp = oh::fir::Highpass::create(0.25, 9);
    if(!hp) {
        std::cout << FIRError_to_string(lp.error());
    } else {
        std::cout << "succesfully created Highpass" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "---checking getters---" << std::endl;

    std::cout << std::endl;
    std::cout << "-------getType--------" << std::endl;
    std::cout << std::endl;

    std::cout << "Lowpass: " << FIRType_to_string(lp -> getType()) << std::endl;
    std::cout << "Bandpass: " << FIRType_to_string(bp -> getType()) << std::endl;
    std::cout << "Highpass: " << FIRType_to_string(hp -> getType()) << std::endl;

    std::cout << std::endl;
    std::cout << "-------getSize--------" << std::endl;
    std::cout << std::endl;

    std::cout << "Lowpass: " << lp -> getSize() << std::endl;;
    std::cout << "Bandpass: " << bp -> getSize() << std::endl;
    std::cout << "Highpass: " << hp -> getSize() << std::endl;

    std::cout << std::endl;
    std::cout << "----getCoefficients----" << std::endl;
    std::cout << std::endl;

    std::cout << "Lowpass: " << std::endl;
    for(auto w : lp -> getCoefficients()) {
        std::cout << w << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Bandpass: " << std::endl;
    for(auto w : bp -> getCoefficients()) {
        std::cout << w << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Highpass: " << std::endl;
    for(auto w : hp -> getCoefficients()) {
        std::cout << w << std::endl;
    }
    
}