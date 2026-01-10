#include "Window.hpp"

namespace oh::wnd{

Window::Window(size_t size) : m_type(WindowType::Rectangular), m_coefficients(size, 0) {}

Window::Window(WindowType w_type, size_t size) : m_type(w_type), m_coefficients(size, 0) {}
        
std::expected <void, WindowError> Window::calculateCoefficients() {
    const size_t N = m_coefficients.size();
    std::vector <double> coefficients(N, 1.0);

    switch (m_type) {
        case WindowType::Rectangular:
            if(auto w = setCoefficients(coefficients); !w) {
                return std::unexpected(w.error());
            } else {
                return {};
            }

        case WindowType::Hamming:
            const double a = 0.54;
            const double b = 0.46;
            for (size_t n = 0; n < N; n++) {
                coefficients[n] = a - b * std::cos(2.0 * std::numbers::pi * n / (N - 1));
            }
            if(auto w = setCoefficients(coefficients); !w) {
                return std::unexpected(w.error());
            } else {
                return {};
            }

        case WindowType::Hanning:
            for (size_t n = 0; n < N; n++) {
                coefficients[n] = 0.5 * (1.0 - std::cos(2.0 * std::numbers::pi * n / (N - 1)));
            }
            if(auto w = setCoefficients(coefficients); !w) {
                return std::unexpected(w.error());
            } else {
                return {};
            }

        case WindowType::Blackman:
            const double a = 0.42;
            const double b = 0.50;
            const double c = 0.08;
            const double denominator = N - 1;
            for (size_t n = 0; n < N; ++n) {
                const double x = 2.0 * std::numbers::pi * n / denominator;
                coefficients[n] = a - b * std::cos(x) + c * std::cos(2.0 * x);
            }
            if(auto w = setCoefficients(coefficients); !w) {
                return std::unexpected(w.error());
            } else {
                return {};
            }

        default:
            return std::unexpected(WindowError::InvalidType);
    }
};

std::expected <void, WindowError> Window::setCoefficients(const std::vector <double>& coefficients) {
    if(coefficients.size() == m_coefficients.size()) {
        m_coefficients = coefficients;
        return {};
    } else {
        return std::unexpected(WindowError::MismatchedSize);
    }
}

std::expected <void, WindowError> Window::checkSize(size_t size) {
    if(size < 3 || size % 2 == 0) {
        return std::unexpected(WindowError::InvalidSize);
    } else {
        return {};
    }
}

const std::vector <double>& Window::getCoefficients() const {
    return m_coefficients;
};

std::expected <void, WindowError> Window::setWindowType(WindowType type) {
    m_type = type;
    if (auto w = calculateCoefficients(); !w) {
        return std::unexpected(w.error());
    } else {
        return {};
    }
}

std::expected <Window, WindowError> Window::create(size_t size) {
    if(auto w = checkSize(size); !w) {          
        return std::unexpected(w.error());
    }

    Window win(size);

    if(auto w = win.calculateCoefficients(); !w) {          
        return std::unexpected(w.error());
    }

    return win;
}

std::expected <Window, WindowError> Window::create(WindowType w_type, size_t size) {
    if(auto w = checkSize(size); !w) {          
        return std::unexpected(w.error());
    }

    Window win(w_type, size);

    if(auto w = win.calculateCoefficients(); !w) {          
        return std::unexpected(w.error());
    }

    return win;
}

}


