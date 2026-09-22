/*
 * Kasane Teto VS Code Theme
 * C++ Syntax & Semantic Highlighting Laboratory
 *
 * Este archivo existe para probar colores del tema.
 *
 * TODO: comprobar comentarios normales.
 * FIXME: comprobar resaltado especial de extensiones.
 * NOTE: este comentario debería ser discreto.
 */

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

// ============================================================================
// PREPROCESSOR Y MACROS
// ============================================================================

#define APP_NAME "Kasane Teto Theme Lab"
#define APP_VERSION 1

#define SQUARE(x) ((x) * (x))

#define LOG_VALUE(name, value) \
    std::cout << name << ": " << value << '\n'

#ifdef __linux__
constexpr std::string_view PLATFORM = "Linux";
#elif defined(_WIN32)
constexpr std::string_view PLATFORM = "Windows";
#else
constexpr std::string_view PLATFORM = "Unknown";
#endif

// ============================================================================
// VARIABLES GLOBALES / CONSTANTES
// ============================================================================

constinit int g_launchCount = 0;

constexpr double PI = 3.14159265358979323846;
constexpr bool DEBUG_MODE = true;

static const std::string GLOBAL_MESSAGE = "Teto Theme";

// ============================================================================
// NAMESPACES
// ============================================================================

namespace teto::theme {

inline namespace v1 {

// ============================================================================
// ENUM
// ============================================================================

enum class Accent : std::uint8_t {
    Navy,
    Rose,
    Cream,
    Gold,
    Green
};

// ============================================================================
// STRUCT
// ============================================================================

struct Color {
    int red {};
    int green {};
    int blue {};

    [[nodiscard]]
    std::string hex() const
    {
        std::ostringstream stream;

        stream
            << '#'
            << std::uppercase
            << std::hex
            << std::setfill('0')
            << std::setw(2) << red
            << std::setw(2) << green
            << std::setw(2) << blue;

        return stream.str();
    }

    auto operator<=>(const Color&) const = default;
};

// ============================================================================
// UNION
// ============================================================================

union NumberRepresentation {
    std::uint32_t raw;
    float decimal;
};

// ============================================================================
// TYPE ALIASES
// ============================================================================

using ColorList = std::vector<Color>;

using ColorMap = std::unordered_map<
    std::string,
    Color
>;

using Formatter = std::function<
    std::string(const Color&)
>;

// ============================================================================
// INTERFACE / POLYMORPHISM
// ============================================================================

class Printable {
public:
    virtual ~Printable() = default;

    virtual void print() const = 0;
};

// ============================================================================
// CLASE
// ============================================================================

class Theme final : public Printable {
public:
    static constexpr std::string_view NAME = "Kasane Teto";

    explicit Theme(std::string name)
        : name_(std::move(name))
    {
        ++g_launchCount;
    }

    ~Theme() override = default;

    [[nodiscard]]
    const std::string& name() const noexcept
    {
        return name_;
    }

    void addColor(
        const std::string& name,
        Color color
    )
    {
        colors_[name] = color;
    }

    [[nodiscard]]
    std::optional<Color> findColor(
        const std::string& name
    ) const
    {
        const auto iterator = colors_.find(name);

        if (iterator == colors_.end()) {
            return std::nullopt;
        }

        return iterator->second;
    }

    [[nodiscard]]
    std::size_t colorCount() const noexcept
    {
        return colors_.size();
    }

    void print() const override
    {
        std::cout
            << "Theme: "
            << name_
            << '\n';

        for (const auto& [name, color] : colors_) {
            std::cout
                << "  "
                << name
                << " -> "
                << color.hex()
                << '\n';
        }
    }

    explicit operator bool() const noexcept
    {
        return !colors_.empty();
    }

private:
    std::string name_;
    ColorMap colors_;
};

// ============================================================================
// HERENCIA
// ============================================================================

class BaseComponent {
public:
    virtual ~BaseComponent() = default;

protected:
    int componentId_ = 0;
};

class EditorComponent final : public BaseComponent {
public:
    explicit EditorComponent(int id)
    {
        componentId_ = id;
    }

    [[nodiscard]]
    int id() const noexcept
    {
        return componentId_;
    }
};

// ============================================================================
// CONCEPTS
// ============================================================================

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

// ============================================================================
// TEMPLATES
// ============================================================================

template<Arithmetic T>
constexpr T clampValue(
    T value,
    T minimum,
    T maximum
)
{
    if (value < minimum) {
        return minimum;
    }

    if (value > maximum) {
        return maximum;
    }

    return value;
}

template<typename T, std::size_t Size>
void printArray(const std::array<T, Size>& values)
{
    for (const auto& value : values) {
        std::cout << value << ' ';
    }

    std::cout << '\n';
}

// ============================================================================
// CONSTEXPR / CONSTEVAL
// ============================================================================

constexpr int doubleValue(int value) noexcept
{
    return value * 2;
}

consteval int compileTimeSquare(int value)
{
    return value * value;
}

// ============================================================================
// FUNCIÓN OBSOLETA
// ============================================================================

[[deprecated("Use modernFunction() instead")]]
void legacyFunction()
{
    std::cout << "Legacy function\n";
}

void modernFunction()
{
    std::cout << "Modern function\n";
}

// ============================================================================
// EXCEPCIONES
// ============================================================================

double divide(double numerator, double denominator)
{
    if (denominator == 0.0) {
        throw std::invalid_argument(
            "Division by zero"
        );
    }

    return numerator / denominator;
}

// ============================================================================
// VARIANT
// ============================================================================

using DynamicValue = std::variant<
    int,
    double,
    std::string
>;

void printVariant(const DynamicValue& value)
{
    std::visit(
        [](const auto& item) {
            std::cout << item << '\n';
        },
        value
    );
}

// ============================================================================
// SWITCH
// ============================================================================

std::string_view accentName(Accent accent)
{
    switch (accent) {
        case Accent::Navy:
            return "Navy";

        case Accent::Rose:
            return "Rose";

        case Accent::Cream:
            return "Cream";

        case Accent::Gold:
            return "Gold";

        case Accent::Green:
            return "Green";
    }

    return "Unknown";
}

} // namespace v1

} // namespace teto::theme

// ============================================================================
// NAMESPACE ALIAS
// ============================================================================

namespace kt = teto::theme;

// ============================================================================
// FUNCIÓN ESTÁTICA
// ============================================================================

static int staticCounter()
{
    static int counter = 0;

    return ++counter;
}

// ============================================================================
// MAIN
// ============================================================================

int main()
{
    // ------------------------------------------------------------------------
    // PRIMITIVOS
    // ------------------------------------------------------------------------

    bool enabled = true;

    char letter = 'T';
    wchar_t wideLetter = L'T';

    signed int signedNumber = -42;
    unsigned int unsignedNumber = 42U;

    short smallNumber = 12;
    long long largeNumber = 9'223'372'036LL;

    float decimal32 = 3.14F;
    double decimal64 = 123.456;
    long double decimalExtended = 3.141592653589793238L;

    // ------------------------------------------------------------------------
    // DISTINTOS FORMATOS NUMÉRICOS
    // ------------------------------------------------------------------------

    int decimal = 255;
    int hexadecimal = 0xFF;
    int binary = 0b11111111;
    int octal = 0377;

    double scientific = 1.25e-4;

    // ------------------------------------------------------------------------
    // STRINGS
    // ------------------------------------------------------------------------

    std::string normalString =
        "Kasane Teto";

    std::string escapedString =
        "Line 1\nLine 2\tTabbed";

    std::string rawString = R"(
This is a raw string.
"Quotes" do not need escaping.
\n is not interpreted here.
)";

    std::string_view stringView =
        "Dark relaxing theme";

    // ------------------------------------------------------------------------
    // NULLPTR / POINTERS / REFERENCES
    // ------------------------------------------------------------------------

    int value = 42;

    int* pointer = &value;
    int& reference = value;

    int* nullPointer = nullptr;

    [[maybe_unused]]
    const int* const constantPointer = &value;

    // Solo para probar colores de new/delete.

    int* dynamicNumber = new int(99);
    delete dynamicNumber;
    dynamicNumber = nullptr;

    // ------------------------------------------------------------------------
    // AUTO / DECLTYPE
    // ------------------------------------------------------------------------

    auto automaticInteger = 100;
    auto automaticDouble = 5.5;

    decltype(automaticInteger) copiedType = 200;

    // ------------------------------------------------------------------------
    // CASTS
    // ------------------------------------------------------------------------

    double converted =
        static_cast<double>(automaticInteger);

    const auto integerAgain =
        static_cast<int>(converted);

    // ------------------------------------------------------------------------
    // SIZEOF / ALIGNOF
    // ------------------------------------------------------------------------

    const auto integerSize = sizeof(int);
    const auto integerAlignment = alignof(int);

    // ------------------------------------------------------------------------
    // OBJETOS
    // ------------------------------------------------------------------------

    kt::Theme theme("Kasane Teto Dark");

    theme.addColor(
        "background",
        kt::Color { 26, 34, 48 }
    );

    theme.addColor(
        "rose",
        kt::Color { 201, 138, 149 }
    );

    theme.addColor(
        "cream",
        kt::Color { 228, 214, 201 }
    );

    theme.addColor(
        "blue",
        kt::Color { 142, 164, 191 }
    );

    // ------------------------------------------------------------------------
    // OPTIONAL
    // ------------------------------------------------------------------------

    const std::optional<kt::Color> rose =
        theme.findColor("rose");

    if (rose.has_value()) {
        std::cout
            << "Rose: "
            << rose->hex()
            << '\n';
    }

    // ------------------------------------------------------------------------
    // IF / ELSE
    // ------------------------------------------------------------------------

    if (enabled && theme) {
        std::cout << "Theme enabled\n";
    } else {
        std::cout << "Theme disabled\n";
    }

    // ------------------------------------------------------------------------
    // TERNARIO
    // ------------------------------------------------------------------------

    const std::string status =
        enabled
            ? "Active"
            : "Inactive";

    // ------------------------------------------------------------------------
    // OPERADORES
    // ------------------------------------------------------------------------

    int a = 10;
    int b = 3;

    int addition = a + b;
    int subtraction = a - b;
    int multiplication = a * b;
    int division = a / b;
    int remainder = a % b;

    bool equal = a == b;
    bool different = a != b;

    bool greater = a > b;
    bool smaller = a < b;

    bool greaterEqual = a >= b;
    bool smallerEqual = a <= b;

    bool logicalAnd = enabled && greater;
    bool logicalOr = enabled || smaller;
    bool logicalNot = !enabled;

    int bitAnd = a & b;
    int bitOr = a | b;
    int bitXor = a ^ b;

    int shiftLeft = a << 1;
    int shiftRight = a >> 1;

    a += 1;
    b -= 1;

    ++a;
    --b;

    // ------------------------------------------------------------------------
    // STD::COUT / STD::ENDL
    //
    // ESTA SECCIÓN ES MUY IMPORTANTE PARA NUESTRO TEMA.
    // Queremos comparar cuánto llaman la atención:
    //
    // cout
    // <<
    // strings
    // endl
    // ------------------------------------------------------------------------

    std::cout
        << "Testing std::endl"
        << std::endl;

    std::cout
        << "Testing newline"
        << '\n';

    std::cout
        << "Value: "
        << value
        << ", status: "
        << status
        << '\n';

    // ------------------------------------------------------------------------
    // VECTOR
    // ------------------------------------------------------------------------

    std::vector<int> numbers {
        10,
        50,
        20,
        90,
        30
    };

    numbers.push_back(100);

    std::ranges::sort(numbers);

    // ------------------------------------------------------------------------
    // RANGE FOR
    // ------------------------------------------------------------------------

    for (const int number : numbers) {
        std::cout
            << number
            << ' ';
    }

    std::cout << '\n';

    // ------------------------------------------------------------------------
    // FOR TRADICIONAL
    // ------------------------------------------------------------------------

    for (
        std::size_t index = 0;
        index < numbers.size();
        ++index
    ) {
        std::cout
            << "Index "
            << index
            << " = "
            << numbers[index]
            << '\n';
    }

    // ------------------------------------------------------------------------
    // WHILE
    // ------------------------------------------------------------------------

    int whileCounter = 0;

    while (whileCounter < 3) {
        ++whileCounter;
    }

    // ------------------------------------------------------------------------
    // DO WHILE
    // ------------------------------------------------------------------------

    int doCounter = 0;

    do {
        ++doCounter;
    } while (doCounter < 3);

    // ------------------------------------------------------------------------
    // BREAK / CONTINUE
    // ------------------------------------------------------------------------

    for (const int number : numbers) {
        if (number < 20) {
            continue;
        }

        if (number > 90) {
            break;
        }

        std::cout << number << '\n';
    }

    // ------------------------------------------------------------------------
    // ARRAY
    // ------------------------------------------------------------------------

    constexpr std::array<int, 5> grades {
        95,
        87,
        100,
        76,
        91
    };

    kt::printArray(grades);

    // ------------------------------------------------------------------------
    // TEMPLATE + CONCEPT
    // ------------------------------------------------------------------------

    const double clamped =
        kt::clampValue(
            150.0,
            0.0,
            100.0
        );

    // ------------------------------------------------------------------------
    // COMPILE-TIME
    // ------------------------------------------------------------------------

    constexpr int doubled =
        kt::doubleValue(10);

    constexpr int squared =
        kt::compileTimeSquare(8);

    static_assert(
        doubled == 20,
        "Unexpected result"
    );

    static_assert(
        squared == 64
    );

    // ------------------------------------------------------------------------
    // LAMBDA
    // ------------------------------------------------------------------------

    const auto multiply = [](
        int left,
        int right
    ) -> int {
        return left * right;
    };

    const int lambdaResult =
        multiply(6, 7);

    // ------------------------------------------------------------------------
    // LAMBDA CON CAPTURE
    // ------------------------------------------------------------------------

    int externalValue = 5;

    auto captureLambda =
        [externalValue](int number) {
            return number + externalValue;
        };

    // ------------------------------------------------------------------------
    // MUTABLE LAMBDA
    // ------------------------------------------------------------------------

    int startingValue = 0;

    auto nextValue =
        [startingValue]() mutable {
            return ++startingValue;
        };

    nextValue();
    nextValue();

    // ------------------------------------------------------------------------
    // SMART POINTERS
    // ------------------------------------------------------------------------

    auto uniqueTheme =
        std::make_unique<kt::Theme>(
            "Unique Theme"
        );

    auto sharedColor =
        std::make_shared<kt::Color>(
            kt::Color {
                142,
                164,
                191
            }
        );

    std::weak_ptr<kt::Color> weakColor =
        sharedColor;

    // ------------------------------------------------------------------------
    // FUNCTION
    // ------------------------------------------------------------------------

    kt::Formatter formatter =
        [](const kt::Color& color) {
            return std::string("Color = ")
                + color.hex();
        };

    std::cout
        << formatter(*sharedColor)
        << '\n';

    // ------------------------------------------------------------------------
    // VARIANT
    // ------------------------------------------------------------------------

    kt::DynamicValue dynamicValue =
        std::string("Teto");

    kt::printVariant(dynamicValue);

    dynamicValue = 39;
    kt::printVariant(dynamicValue);

    dynamicValue = 39.5;
    kt::printVariant(dynamicValue);

    // ------------------------------------------------------------------------
    // SWITCH + ENUM
    // ------------------------------------------------------------------------

    const kt::Accent accent =
        kt::Accent::Navy;

    std::cout
        << "Accent: "
        << kt::accentName(accent)
        << '\n';

    // ------------------------------------------------------------------------
    // TRY / CATCH / THROW
    // ------------------------------------------------------------------------

    try {
        const double result =
            kt::divide(10.0, 0.0);

        std::cout << result << '\n';
    }
    catch (const std::invalid_argument& exception) {
        std::cerr
            << "Error: "
            << exception.what()
            << '\n';
    }
    catch (...) {
        std::cerr
            << "Unknown error"
            << '\n';
    }

    // ------------------------------------------------------------------------
    // VOLATILE
    // ------------------------------------------------------------------------

    volatile int hardwareValue = 42;

    [[maybe_unused]]
    const int copiedHardwareValue =
        hardwareValue;

    // ------------------------------------------------------------------------
    // CLASE DERIVADA
    // ------------------------------------------------------------------------

    kt::EditorComponent editor(100);

    std::cout
        << "Editor ID: "
        << editor.id()
        << '\n';

    // ------------------------------------------------------------------------
    // MACROS
    // ------------------------------------------------------------------------

    const int macroResult =
        SQUARE(8);

    LOG_VALUE(
        "Macro result",
        macroResult
    );

    // ------------------------------------------------------------------------
    // STATIC LOCAL
    // ------------------------------------------------------------------------

    std::cout
        << staticCounter()
        << '\n';

    std::cout
        << staticCounter()
        << '\n';

    // ------------------------------------------------------------------------
    // BIBLIOTECA ESTÁNDAR
    // ------------------------------------------------------------------------

    std::cout
        << APP_NAME
        << " v"
        << APP_VERSION
        << '\n';

    std::cout
        << "Platform: "
        << PLATFORM
        << '\n';

    // ------------------------------------------------------------------------
    // FINAL
    // ------------------------------------------------------------------------

    theme.print();

    return 0;
}