#include "Window.hpp"

namespace oh::wnd{

Window::Window(size_t size) : m_type(WindowType::Rectangular), m_coefficients(size, 0.0) {}

Window::Window(WindowType w_type, size_t size) : m_type(w_type), m_coefficients(size, 0.0) {}
        
std::expected <void, WindowError> Window::calculateCoefficients() {
    switch (m_type) {
        case WindowType::Rectangular:
            break;
        case WindowType::Hamming:
            break;
        case WindowType::Hanning:
            break;
        case WindowType::Blackman:
            break;
        default:
            return std::unexpected(WindowError::InvalidType);
    }
};

std::expected <void, WindowError> setCoefficients();

std::expected <void, WindowError> checkSize();

const std::vector <double>& getCoefficients();

std::expected <void, WindowError> setWindowType(WindowType type);

std::expected <Window, WindowError> create(size_t size);

std::expected <Window, WindowError> create(WindowType w_type, size_t size);

}


