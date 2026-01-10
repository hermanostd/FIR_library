#pragma once

#include "FIR.hpp"

///<    work in progress, mutable window class

namespace oh::wnd{

enum WindowType {
    Rectangular,
    Hamming,
    Hanning,
    Blackman
};

enum WindowError {
    InvalidSize,
    InvalidType
};

class Window {

    private:

        WindowType m_type;

        std::vector <double> m_coefficients;
        
        std::expected <void, WindowError> calculateCoefficients();
    
    protected:

        Window(size_t size);

        Window(WindowType w_type, size_t size);

        std::expected <void, WindowError> setCoefficients();

        static std::expected <void, WindowError> checkSize();

    public:

        const std::vector <double>& getCoefficients() const;

        std::expected <void, WindowError> setWindowType(WindowType type);

        static std::expected <Window, WindowError> create(size_t size);

        static std::expected <Window, WindowError> create(WindowType w_type, size_t size);

};


}