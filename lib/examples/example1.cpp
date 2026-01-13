#include "EasyDSP.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <expected>
#include <ctime>
#include <cstdlib>
#include <fstream>


int main() {
    ///< example: 

    std::cout << "this example shows: " << std::endl;
    std::cout << "-how to create a basic FIR filter" << std::endl;
    std::cout << "-how to create a basic FIR filter with a window" << std::endl;
    std::cout << "-how to change a window type in a FIR filter object" << std::endl;
    std::cout << "-how to use getters in oh::fir" << std::endl;
    std::cout << std::endl;

    std::srand(std::time({}));  

    size_t size_of_signal = 127;
    std::vector <double> random_signal(size_of_signal, 0.0);
    int i = 0;
    for (auto &v : random_signal) {
        v = double(std::rand() % 1000 )/10000 + std::sin(i/20) + 0.5 * std::sin(i/100);
        i++;
    }

    std::vector <oh::wnd::WindowType> w_types = {oh::wnd::WindowType::Rectangular, oh::wnd::WindowType::Hanning, oh::wnd::WindowType::Hamming, oh::wnd::WindowType::Blackman};

    size_t first_size = 87;       ///< std::cout << "wAS tHAT tTHE bITE oF " << first_size << "!!!"; ///:DD 
    size_t second_size = 9;     ///< easy to print


    std::cout << "This is the default way of creating FIR filters" << std::endl;
    {
        auto lp = oh::fir::WindowLowpass::create(0.25, first_size, oh::wnd::WindowType::Rectangular);
        if(!lp) {
            std::cout << toString(lp.error());
        } else {
            std::cout << "succesfully created " << toString(lp -> getWindowType()) << " with window: " << toString(lp -> getWindowType()) << std::endl;
        }

        auto hp = oh::fir::WindowHighpass::create(0.25, first_size, oh::wnd::WindowType::Rectangular);
        if(!hp) {
            std::cout << toString(hp.error());
        } else {
            std::cout << "succesfully created " << toString(hp -> getWindowType()) << " with window: " << toString(hp -> getWindowType()) << std::endl;
        }

        std::cout << std::endl;
        std::cout << "checking operator == ";
        if(lp == hp) {
            std::cout << "true";
        } else {
            std::cout << "false";
        }
        std::cout << std::endl;

        std::cout << "checking operator != ";
        if(lp != hp) {
            std::cout << "true";
        } else {
            std::cout << "false";
        }
        std::cout << std::endl;


    }

    std::cout << std::endl;

    std::cout << "but you can also create them without specyfing the WindowType" << std::endl;

    std::cout << std::endl;

    /// creating a window lowpass (default window: Rectangular)

    auto lp = oh::fir::WindowLowpass::create(0.25, second_size);
    if(!lp) {
        std::cout << toString(lp.error());
    } else {
        std::cout << "succesfully created WindowLowpass(1)" << std::endl;
    }

    /// creating a window bandpass (default window: Rectangular)

    auto bp = oh::fir::WindowBandpass::create(0.1, 0.4, second_size);
    if(!bp) {
        std::cout << toString(lp.error());
    } else {
        std::cout << "succesfully created WindowBandpass(2)" << std::endl;
    }

    /// creating a window highpass (default window: Rectangular)

    auto hp = oh::fir::WindowHighpass::create(0.25, second_size);
    if(!hp) {
        std::cout << toString(lp.error());
    } else {
        std::cout << "succesfully created WindowHighpass(3)" << std::endl;
    }

    /// creating a frequency sampling filter (default window: Rectangular)

    std::vector <double> H = {0.5, 0.5, 1, 2};      /// desired half frequency spectrum

    auto fs = oh::fir::FrequencySampling::create(H);
    if(!fs) {
        std::cout << toString(lp.error());
    } else {
        std::cout << "succesfully created Frequencysampling(4)" << std::endl;
    }

    for (auto window : w_types) {
        std::cout << std::endl;
        std::cout << "window type tested: " << toString(window);

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "---checking setWindowType---" << std::endl;

        ///     checking setWindowType
        
        if(auto w = lp -> setWindowType(window); !w) {
            std::cout << toString(w.error());
        } else {
            std::cout << "succesfully set window(1): " << toString(window) << std::endl;
        }

        if(auto w = bp -> setWindowType(window); !w) {
            std::cout << toString(w.error());
        } else {
            std::cout << "succesfully set window(2): " << toString(window) << std::endl;
        }

        if(auto w = hp -> setWindowType(window); !w) {
            std::cout << toString(w.error());
        } else {
            std::cout << "succesfully set window(3): " << toString(window) << std::endl;
        }

        if(auto w = fs -> setWindowType(window); !w) {
            std::cout << toString(w.error());
        } else {
            std::cout << "succesfully set window(4): " << toString(window) << std::endl;
        }

        ///     checking getters

        std::cout << std::endl;
        std::cout << "---checking getters---" << std::endl;

        ///     checking getType

        std::cout << std::endl;
        std::cout << "-------getType(1-4)--------" << std::endl;
        std::cout << std::endl;

        std::cout << "1: " << toString(lp -> getType()) << std::endl;
        std::cout << "2: " << toString(bp -> getType()) << std::endl;
        std::cout << "3: " << toString(hp -> getType()) << std::endl;
        std::cout << "4: " << toString(fs -> getType()) << std::endl;

        ///     checking getSize

        std::cout << std::endl;
        std::cout << "-------getSize(1-4)--------" << std::endl;
        std::cout << std::endl;

        std::cout << "1: " << lp -> getSize() << std::endl;
        std::cout << "2: " << bp -> getSize() << std::endl;
        std::cout << "3: " << hp -> getSize() << std::endl;
        std::cout << "4: " << fs -> getSize() << std::endl;

        ///     checking getWindowType

        std::cout << std::endl;
        std::cout << "-------getWindowType(1-4)--------" << std::endl;
        std::cout << std::endl;

        std::cout << "1: " << toString(lp -> getWindowType()) << std::endl;
        std::cout << "2: " << toString(bp -> getWindowType()) << std::endl;
        std::cout << "3: " << toString(hp -> getWindowType()) << std::endl;
        std::cout << "4: " << toString(fs -> getWindowType()) << std::endl;

        ///     checking getCoefficients

        std::cout << std::endl;
        std::cout << "----getCoefficients(1-4)----" << std::endl;
        std::cout << std::endl;

        std::cout << "1:  ";
        for (auto w : lp -> getCoefficients()) {
            std::cout << w << " ";
        }

        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "2:  ";
        for (auto w : bp -> getCoefficients()) {
            std::cout << w << " ";
        }

        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "3:  ";
        for (auto w : hp -> getCoefficients()) {
            std::cout << w << " ";
        }

        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "4: ";
        for (auto w : fs -> getCoefficients()) {
            std::cout << w << " ";
        }

        std::cout << std::endl;
        std::cout << std::endl;

        ///     checking getHalfFrequencySpectrum (for FrequencySampling)

        std::cout << "----getFrequencyHalfSpectrum(4)----" << std::endl;
        std::cout << std::endl;

        for (auto w : fs -> getFrequencyHalfSpectrum()) {
            std::cout << w << " ";
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "lets filter some random noise trough our filters" << std::endl;

    std::cout << std::endl;

    std::fstream file ("filtering.m", std::fstream::out);
    if(file.fail()) {
        std::cout << "can't create a file";
        return -1;
    }

    file << "% this is a matlab script for plotting the fir filters" << std::endl;
    file << "clc,clear,close all;" << std::endl;  
    file << "x = [ ";
    for (int i = 0; i < size_of_signal; ++i) {
        file << i << ", ";
    }
    file << "];" << std::endl;

    file << "z = [ ";
    for (int i = 0; i < size_of_signal+second_size-1; ++i) {
        file << i << ", ";
    }
    file << "];" << std::endl;

    file << "y = [ ";
    for (auto w : random_signal) {
        file << w << ", ";
    }
    file << "];" << std::endl;
    
    ///checking operator *
    auto l = (*lp) * random_signal;
    if(!l) {
        std::cout << toString(l.error());
    }

    file << "lowpass = [ ";
    for(auto w : *l) {
        file << w << ", ";
    }
    file << "];" << std::endl;

    auto b = bp -> convolve(random_signal);
    if(!b) {
        std::cout << toString(b.error());
    }

    file << "bandpass = [ ";
    for(auto w : *b) {
        file << w << ", ";
    }
    file << "];" << std::endl;

    auto h = hp -> convolve(random_signal);
    if(!h) {
        std::cout << toString(h.error());
    }

    file << "highpass = [ ";
    for(auto w : *h) {
        file << w << ", ";
    }
    file << "];" << std::endl;

    auto f = fs -> convolve(random_signal);
    if(!f) {
        std::cout << toString(f.error());
    }

    file << "frequency_sampling = [ ";
    for(auto w : *f) {
        file << w << ", ";
    }
    file << "];" << std::endl;




    file << "figure(1);" << std::endl;
    file << "plot(x, y, '-.b');" << std::endl;
    file << "hold on;" << std::endl;
    file << "plot(z, lowpass, '-.r');" << std::endl;
    file << "title('Lowpass FIR');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;

    file << "figure(2);" << std::endl;
    file << "plot(x, y, '-.b');" << std::endl;
    file << "hold on;" << std::endl;
    file << "plot(z, bandpass, '-.r');" << std::endl;
    file << "title('Bandpass FIR');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;

    file << "figure(3);" << std::endl;
    file << "plot(x, y, '-.b');" << std::endl;
    file << "hold on;" << std::endl;
    file << "plot(z, highpass, '-.r');" << std::endl;
    file << "title('Highpass FIR');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;

    file << "figure(4);" << std::endl;
    file << "plot(x, y, '-.b');" << std::endl;
    file << "hold on;" << std::endl;
    file << "plot(z, frequency_sampling, '-.r');" << std::endl;
    file << "title('FrequencySampling FIR');" << std::endl;
    file << "xlabel('Array Index');" << std::endl;
    file << "ylabel('Value');" << std::endl;
    file << "grid on;" << std::endl;


    std::cout << "done, check filtering.m" << std::endl;

}