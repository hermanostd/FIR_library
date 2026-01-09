#pragma once

#include <vector>

///<    work in progress, mutable window class

namespace oh::wnd{

enum WindowType {
    Rectangular,
    Hamming,
    Hanning,
    Blackman
};

enum WindowError {
    InvalidSize
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

    public:

        std::expected <void, WindowError> setWindowType(WindowType type);

        std::expected <Window, WindowError> create();

    


};


}