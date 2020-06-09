


typedef enum class KeyCode
{
    // From glfw3.h
    Space               = 32,
    Apostrophe          = 39, /* ' */
    Comma               = 44, /* , */
    Minus               = 45, /* - */
    Period              = 46, /* . */
    Slash               = 47, /* / */

    D0                  = 48, /* 0 */
    D1                  = 49, /* 1 */
    D2                  = 50, /* 2 */
    D3                  = 51, /* 3 */
    D4                  = 52, /* 4 */
    D5                  = 53, /* 5 */
    D6                  = 54, /* 6 */
    D7                  = 55, /* 7 */
    D8                  = 56, /* 8 */
    D9                  = 57, /* 9 */

    Semicolon           = 59, /* ; */
    Equal               = 61, /* = */

    A                   = 65,
    B                   = 66,
    C                   = 67,
    D                   = 68,
    E                   = 69,
    F                   = 70,
    G                   = 71,
    H                   = 72,
    I                   = 73,
    J                   = 74,
    K                   = 75,
    L                   = 76,
    M                   = 77,
    N                   = 78,
    O                   = 79,
    P                   = 80,
    Q                   = 81,
    R                   = 82,
    S                   = 83,
    T                   = 84,
    U                   = 85,
    V                   = 86,
    W                   = 87,
    X                   = 88,
    Y                   = 89,
    Z                   = 90,

    LeftBracket         = 91,  /* [ */
    Backslash           = 92,  /* \ */
    RightBracket        = 93,  /* ] */
    GraveAccent         = 96,  /* ` */

    World1              = 161, /* non-US #1 */
    World2              = 162, /* non-US #2 */

    /* Function keys */
    Escape              = 256,
    Enter               = 257,
    Tab                 = 258,
    Backspace           = 259,
    Insert              = 260,
    Delete              = 261,
    Right               = 262,
    Left                = 263,
    Down                = 264,
    Up                  = 265,
    PageUp              = 266,
    PageDown            = 267,
    Home                = 268,
    End                 = 269,
    CapsLock            = 280,
    ScrollLock          = 281,
    NumLock             = 282,
    PrintScreen         = 283,
    Pause               = 284,
    F1                  = 290,
    F2                  = 291,
    F3                  = 292,
    F4                  = 293,
    F5                  = 294,
    F6                  = 295,
    F7                  = 296,
    F8                  = 297,
    F9                  = 298,
    F10                 = 299,
    F11                 = 300,
    F12                 = 301,
    F13                 = 302,
    F14                 = 303,
    F15                 = 304,
    F16                 = 305,
    F17                 = 306,
    F18                 = 307,
    F19                 = 308,
    F20                 = 309,
    F21                 = 310,
    F22                 = 311,
    F23                 = 312,
    F24                 = 313,
    F25                 = 314,

    /* Keypad */
    KP0                 = 320,
    KP1                 = 321,
    KP2                 = 322,
    KP3                 = 323,
    KP4                 = 324,
    KP5                 = 325,
    KP6                 = 326,
    KP7                 = 327,
    KP8                 = 328,
    KP9                 = 329,
    KPDecimal           = 330,
    KPDivide            = 331,
    KPMultiply          = 332,
    KPSubtract          = 333,
    KPAdd               = 334,
    KPEnter             = 335,
    KPEqual             = 336,

    LeftShift           = 340,
    LeftControl         = 341,
    LeftAlt             = 342,
    LeftSuper           = 343,
    RightShift          = 344,
    RightControl        = 345,
    RightAlt            = 346,
    RightSuper          = 347,
    Menu                = 348
} Key;

inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
{
    os << static_cast<int32_t>(keyCode);
    return os;
}


// From glfw3.h
#define KEY_VALUE_SPACE           ::Hazel::Key::Space
#define KEY_VALUE_APOSTROPHE      ::Hazel::Key::Apostrophe    /* ' */
#define KEY_VALUE_COMMA           ::Hazel::Key::Comma         /* , */
#define KEY_VALUE_MINUS           ::Hazel::Key::Minus         /* - */
#define KEY_VALUE_PERIOD          ::Hazel::Key::Period        /* . */
#define KEY_VALUE_SLASH           ::Hazel::Key::Slash         /* / */
#define KEY_VALUE_0               ::Hazel::Key::D0
#define KEY_VALUE_1               ::Hazel::Key::D1
#define KEY_VALUE_2               ::Hazel::Key::D2
#define KEY_VALUE_3               ::Hazel::Key::D3
#define KEY_VALUE_4               ::Hazel::Key::D4
#define KEY_VALUE_5               ::Hazel::Key::D5
#define KEY_VALUE_6               ::Hazel::Key::D6
#define KEY_VALUE_7               ::Hazel::Key::D7
#define KEY_VALUE_8               ::Hazel::Key::D8
#define KEY_VALUE_9               ::Hazel::Key::D9
#define KEY_VALUE_SEMICOLON       ::Hazel::Key::Semicolon     /* ; */
#define KEY_VALUE_EQUAL           ::Hazel::Key::Equal         /* = */
#define KEY_VALUE_A               ::Hazel::Key::A
#define KEY_VALUE_B               ::Hazel::Key::B
#define KEY_VALUE_C               ::Hazel::Key::C
#define KEY_VALUE_D               ::Hazel::Key::D
#define KEY_VALUE_E               ::Hazel::Key::E
#define KEY_VALUE_F               ::Hazel::Key::F
#define KEY_VALUE_G               ::Hazel::Key::G
#define KEY_VALUE_H               ::Hazel::Key::H
#define KEY_VALUE_I               ::Hazel::Key::I
#define KEY_VALUE_J               ::Hazel::Key::J
#define KEY_VALUE_K               ::Hazel::Key::K
#define KEY_VALUE_L               ::Hazel::Key::L
#define KEY_VALUE_M               ::Hazel::Key::M
#define KEY_VALUE_N               ::Hazel::Key::N
#define KEY_VALUE_O               ::Hazel::Key::O
#define KEY_VALUE_P               ::Hazel::Key::P
#define KEY_VALUE_Q               ::Hazel::Key::Q
#define KEY_VALUE_R               ::Hazel::Key::R
#define KEY_VALUE_S               ::Hazel::Key::S
#define KEY_VALUE_T               ::Hazel::Key::T
#define KEY_VALUE_U               ::Hazel::Key::U
#define KEY_VALUE_V               ::Hazel::Key::V
#define KEY_VALUE_W               ::Hazel::Key::W
#define KEY_VALUE_X               ::Hazel::Key::X
#define KEY_VALUE_Y               ::Hazel::Key::Y
#define KEY_VALUE_Z               ::Hazel::Key::Z
#define KEY_VALUE_LEFT_BRACKET    ::Hazel::Key::LeftBracket   /* [ */
#define KEY_VALUE_BACKSLASH       ::Hazel::Key::Backslash     /* \ */
#define KEY_VALUE_RIGHT_BRACKET   ::Hazel::Key::RightBracket  /* ] */
#define KEY_VALUE_GRAVE_ACCENT    ::Hazel::Key::GraveAccent   /* ` */
#define KEY_VALUE_WORLD_1         ::Hazel::Key::World1        /* non-US #1 */
#define KEY_VALUE_WORLD_2         ::Hazel::Key::World2        /* non-US #2 */

/* Function keys */
#define KEY_VALUE_ESCAPE          ::Hazel::Key::Escape
#define KEY_VALUE_ENTER           ::Hazel::Key::Enter
#define KEY_VALUE_TAB             ::Hazel::Key::Tab
#define KEY_VALUE_BACKSPACE       ::Hazel::Key::Backspace
#define KEY_VALUE_INSERT          ::Hazel::Key::Insert
#define KEY_VALUE_DELETE          ::Hazel::Key::Delete
#define KEY_VALUE_RIGHT           ::Hazel::Key::Right
#define KEY_VALUE_LEFT            ::Hazel::Key::Left
#define KEY_VALUE_DOWN            ::Hazel::Key::Down
#define KEY_VALUE_UP              ::Hazel::Key::Up
#define KEY_VALUE_PAGE_UP         ::Hazel::Key::PageUp
#define KEY_VALUE_PAGE_DOWN       ::Hazel::Key::PageDown
#define KEY_VALUE_HOME            ::Hazel::Key::Home
#define KEY_VALUE_END             ::Hazel::Key::End
#define KEY_VALUE_CAPS_LOCK       ::Hazel::Key::CapsLock
#define KEY_VALUE_SCROLL_LOCK     ::Hazel::Key::ScrollLock
#define KEY_VALUE_NUM_LOCK        ::Hazel::Key::NumLock
#define KEY_VALUE_PRINT_SCREEN    ::Hazel::Key::PrintScreen
#define KEY_VALUE_PAUSE           ::Hazel::Key::Pause
#define KEY_VALUE_F1              ::Hazel::Key::F1
#define KEY_VALUE_F2              ::Hazel::Key::F2
#define KEY_VALUE_F3              ::Hazel::Key::F3
#define KEY_VALUE_F4              ::Hazel::Key::F4
#define KEY_VALUE_F5              ::Hazel::Key::F5
#define KEY_VALUE_F6              ::Hazel::Key::F6
#define KEY_VALUE_F7              ::Hazel::Key::F7
#define KEY_VALUE_F8              ::Hazel::Key::F8
#define KEY_VALUE_F9              ::Hazel::Key::F9
#define KEY_VALUE_F10             ::Hazel::Key::F10
#define KEY_VALUE_F11             ::Hazel::Key::F11
#define KEY_VALUE_F12             ::Hazel::Key::F12
#define KEY_VALUE_F13             ::Hazel::Key::F13
#define KEY_VALUE_F14             ::Hazel::Key::F14
#define KEY_VALUE_F15             ::Hazel::Key::F15
#define KEY_VALUE_F16             ::Hazel::Key::F16
#define KEY_VALUE_F17             ::Hazel::Key::F17
#define KEY_VALUE_F18             ::Hazel::Key::F18
#define KEY_VALUE_F19             ::Hazel::Key::F19
#define KEY_VALUE_F20             ::Hazel::Key::F20
#define KEY_VALUE_F21             ::Hazel::Key::F21
#define KEY_VALUE_F22             ::Hazel::Key::F22
#define KEY_VALUE_F23             ::Hazel::Key::F23
#define KEY_VALUE_F24             ::Hazel::Key::F24
#define KEY_VALUE_F25             ::Hazel::Key::F25

/* Keypad */
#define KEY_VALUE_KP_0            ::Hazel::Key::KP0
#define KEY_VALUE_KP_1            ::Hazel::Key::KP1
#define KEY_VALUE_KP_2            ::Hazel::Key::KP2
#define KEY_VALUE_KP_3            ::Hazel::Key::KP3
#define KEY_VALUE_KP_4            ::Hazel::Key::KP4
#define KEY_VALUE_KP_5            ::Hazel::Key::KP5
#define KEY_VALUE_KP_6            ::Hazel::Key::KP6
#define KEY_VALUE_KP_7            ::Hazel::Key::KP7
#define KEY_VALUE_KP_8            ::Hazel::Key::KP8
#define KEY_VALUE_KP_9            ::Hazel::Key::KP9
#define KEY_VALUE_KP_DECIMAL      ::Hazel::Key::KPDecimal
#define KEY_VALUE_KP_DIVIDE       ::Hazel::Key::KPDivide
#define KEY_VALUE_KP_MULTIPLY     ::Hazel::Key::KPMultiply
#define KEY_VALUE_KP_SUBTRACT     ::Hazel::Key::KPSubtract
#define KEY_VALUE_KP_ADD          ::Hazel::Key::KPAdd
#define KEY_VALUE_KP_ENTER        ::Hazel::Key::KPEnter
#define KEY_VALUE_KP_EQUAL        ::Hazel::Key::KPEqual

#define KEY_VALUE_LEFT_SHIFT      ::Hazel::Key::LeftShift
#define KEY_VALUE_LEFT_CONTROL    ::Hazel::Key::LeftControl
#define KEY_VALUE_LEFT_ALT        ::Hazel::Key::LeftAlt
#define KEY_VALUE_LEFT_SUPER      ::Hazel::Key::LeftSuper
#define KEY_VALUE_RIGHT_SHIFT     ::Hazel::Key::RightShift
#define KEY_VALUE_RIGHT_CONTROL   ::Hazel::Key::RightControl
#define KEY_VALUE_RIGHT_ALT       ::Hazel::Key::RightAlt
#define KEY_VALUE_RIGHT_SUPER     ::Hazel::Key::RightSuper
#define KEY_VALUE_MENU            ::Hazel::Key::Menu