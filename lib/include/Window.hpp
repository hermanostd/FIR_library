#pragma once

#include <vector>
#include <numbers>
#include <expected>
#include <cmath>
#include <cstddef>

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
    InvalidType,
    MismatchedSize
};

class Window {

    private:

        WindowType m_type;

        std::vector <double> m_coefficients;
        
        std::expected <void, WindowError> calculateCoefficients();
    
    protected:

        Window(size_t size);

        Window(WindowType w_type, size_t size);

        std::expected <void, WindowError> setCoefficients(const std::vector <double>& coefficients);

        static std::expected <void, WindowError> checkSize(size_t size);

    public:

        const std::vector <double>& getCoefficients() const;

        std::expected <void, WindowError> setWindowType(WindowType type);

        std::expected <std::vector <double>, WindowError> apply(const std::vector <double>& signal) const;

        std::expected <std::vector <double>, WindowError> applyInPlace(std::vector <double>& signal) const;

        static std::expected <Window, WindowError> create(size_t size);

        static std::expected <Window, WindowError> create(WindowType w_type, size_t size);

};


}