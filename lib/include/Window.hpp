#pragma once

#include <vector>
#include <numbers>
#include <expected>
#include <cmath>
#include <cstddef>
#include <string>

namespace oh::wnd{

/// @brief enum used to represent window type
enum class WindowType {
    Rectangular,
    Hamming,
    Hanning,
    Blackman
};

/// @brief enum used for error handling
enum class WindowError {
    InvalidSize,
    InvalidType,
    MismatchedSize
};

/// @brief used to translate WindowType to std::string
/// @param win_type window type
/// @return string
std::string toString(WindowType win_type);

/// @brief used to translate WindowError to std::string
/// @param win_error window error
/// @return string
std::string toString(WindowError win_error);

/// @brief a class for windows
class Window {

    private:

        WindowType m_type;

        std::vector <double> m_coefficients;
        
        /// @brief used to calculate coefficients of window
        /// @return void on success, WindowError on failure
        std::expected <void, WindowError> calculateCoefficients();
    
    protected:

        /// @brief constructor, default window Rectangular
        /// @param size size of window
        Window(size_t size);

        
        /// @brief constructor
        /// @param w_type type of window
        /// @param size size of window
        Window(WindowType w_type, size_t size);


        /// @brief protected setter for coefficients
        /// @param coefficients the coefficients to be set
        /// @return void on success, WindowError on failure
        std::expected <void, WindowError> setCoefficients(const std::vector <double>& coefficients);

        /// @brief helper used to check if the entered size is nonzero and odd
        /// @param size size of the desired filter (order+1)
        /// @return void on success, WindowError on failure
        static std::expected <void, WindowError> checkSize(size_t size);

    public:

        /// @brief getter for coefficientss
        /// @return coefficients
        const std::vector <double>& getCoefficients() const;

        /// @brief change type of window
        /// @param type type of window
        /// @return void on success, WindowError on failure
        std::expected <void, WindowError> setWindowType(WindowType type);

        /// @brief apply a window (copy)
        /// @param signal signal to aplly a window on
        /// @return vector of doubles on success, WindowError on failure
        std::expected <std::vector <double>, WindowError> apply(const std::vector <double>& signal) const;

        /// @brief apply a window
        /// @param signal signal to apply a window on
        /// @return void on success, WindowError on failure
        std::expected <void, WindowError> applyInPlace(std::vector <double>& signal) const;

        /// @brief getter for WindowType
        /// @return WindowType enum
        const WindowType getType() const noexcept;

        const size_t getSize() const noexcept;

        /// @brief creates object Window default: Rectangular
        /// @param size size of window
        /// @return Window on success, Window Error on failure
        static std::expected <Window, WindowError> create(size_t size);

        /// @brief creates object Window
        /// @param w_type type of window
        /// @param size size of window
        /// @return Window on success, Window Error on failure
        static std::expected <Window, WindowError> create(WindowType w_type, size_t size);

        bool operator==(const Window& other) const;
        bool operator!=(const Window& other) const;
        std::expected <std::vector <double>, WindowError> operator*(const std::vector <double>& signal) const;

};


}