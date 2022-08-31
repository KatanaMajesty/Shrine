#ifndef __SHRINE_ENGINE_UTILITY_KEYBOARD_H__
#define __SHRINE_ENGINE_UTILITY_KEYBOARD_H__

namespace shrine
{
// Printable keys
#define SHR_KEY_SPACE              32
#define SHR_KEY_APOSTROPHE         39  /* ' */
#define SHR_KEY_COMMA              44  /* , */
#define SHR_KEY_MINUS              45  /* - */
#define SHR_KEY_PERIOD             46  /* . */
#define SHR_KEY_SLASH              47  /* / */
#define SHR_KEY_0                  48
#define SHR_KEY_1                  49
#define SHR_KEY_2                  50
#define SHR_KEY_3                  51
#define SHR_KEY_4                  52
#define SHR_KEY_5                  53
#define SHR_KEY_6                  54
#define SHR_KEY_7                  55
#define SHR_KEY_8                  56
#define SHR_KEY_9                  57
#define SHR_KEY_SEMICOLON          59  /* ; */
#define SHR_KEY_EQUAL              61  /* = */
#define SHR_KEY_A                  65
#define SHR_KEY_B                  66
#define SHR_KEY_C                  67
#define SHR_KEY_D                  68
#define SHR_KEY_E                  69
#define SHR_KEY_F                  70
#define SHR_KEY_G                  71
#define SHR_KEY_H                  72
#define SHR_KEY_I                  73
#define SHR_KEY_J                  74
#define SHR_KEY_K                  75
#define SHR_KEY_L                  76
#define SHR_KEY_M                  77
#define SHR_KEY_N                  78
#define SHR_KEY_O                  79
#define SHR_KEY_P                  80
#define SHR_KEY_Q                  81
#define SHR_KEY_R                  82
#define SHR_KEY_S                  83
#define SHR_KEY_T                  84
#define SHR_KEY_U                  85
#define SHR_KEY_V                  86
#define SHR_KEY_W                  87
#define SHR_KEY_X                  88
#define SHR_KEY_Y                  89
#define SHR_KEY_Z                  90
#define SHR_KEY_LEFT_BRACKET       91  /* [ */
#define SHR_KEY_BACKSLASH          92  /* \ */
#define SHR_KEY_RIGHT_BRACKET      93  /* ] */
#define SHR_KEY_GRAVE_ACCENT       96  /* ` */

// Function keys
#define SHR_KEY_ESCAPE             256
#define SHR_KEY_ENTER              257
#define SHR_KEY_TAB                258
#define SHR_KEY_BACKSPACE          259
#define SHR_KEY_INSERT             260
#define SHR_KEY_DELETE             261
#define SHR_KEY_RIGHT              262
#define SHR_KEY_LEFT               263
#define SHR_KEY_DOWN               264
#define SHR_KEY_UP                 265
#define SHR_KEY_PAGE_UP            266
#define SHR_KEY_PAGE_DOWN          267
#define SHR_KEY_HOME               268
#define SHR_KEY_END                269
#define SHR_KEY_CAPS_LOCK          280
#define SHR_KEY_SCROLL_LOCK        281
#define SHR_KEY_NUM_LOCK           282
#define SHR_KEY_PRINT_SCREEN       283
#define SHR_KEY_PAUSE              284
#define SHR_KEY_F1                 290
#define SHR_KEY_F2                 291
#define SHR_KEY_F3                 292
#define SHR_KEY_F4                 293
#define SHR_KEY_F5                 294
#define SHR_KEY_F6                 295
#define SHR_KEY_F7                 296
#define SHR_KEY_F8                 297
#define SHR_KEY_F9                 298
#define SHR_KEY_F10                299
#define SHR_KEY_F11                300
#define SHR_KEY_F12                301
// Not supported now
// #define SHR_KEY_F13                302
// #define SHR_KEY_F14                303
// #define SHR_KEY_F15                304
// #define SHR_KEY_F16                305
// #define SHR_KEY_F17                306
// #define SHR_KEY_F18                307
// #define SHR_KEY_F19                308
// #define SHR_KEY_F20                309
// #define SHR_KEY_F21                310
// #define SHR_KEY_F22                311
// #define SHR_KEY_F23                312
// #define SHR_KEY_F24                313
// #define SHR_KEY_F25                314
#define SHR_KEY_KP_0               320
#define SHR_KEY_KP_1               321
#define SHR_KEY_KP_2               322
#define SHR_KEY_KP_3               323
#define SHR_KEY_KP_4               324
#define SHR_KEY_KP_5               325
#define SHR_KEY_KP_6               326
#define SHR_KEY_KP_7               327
#define SHR_KEY_KP_8               328
#define SHR_KEY_KP_9               329
#define SHR_KEY_KP_DECIMAL         330
#define SHR_KEY_KP_DIVIDE          331
#define SHR_KEY_KP_MULTIPLY        332
#define SHR_KEY_KP_SUBTRACT        333
#define SHR_KEY_KP_ADD             334
#define SHR_KEY_KP_ENTER           335
#define SHR_KEY_KP_EQUAL           336
#define SHR_KEY_LEFT_SHIFT         340
#define SHR_KEY_LEFT_CONTROL       341
#define SHR_KEY_LEFT_ALT           342
#define SHR_KEY_LEFT_SUPER         343
#define SHR_KEY_RIGHT_SHIFT        344
#define SHR_KEY_RIGHT_CONTROL      345
#define SHR_KEY_RIGHT_ALT          346
#define SHR_KEY_RIGHT_SUPER        347
#define SHR_KEY_MENU               348

// This enum should be preferred over macro definitions
enum Keycode
{
    Space = SHR_KEY_SPACE,
    Apostrophe = SHR_KEY_APOSTROPHE,
    Comma = SHR_KEY_COMMA,
    Minus = SHR_KEY_MINUS,
    Period = SHR_KEY_PERIOD,
    Slash = SHR_KEY_SLASH,
    N0 = SHR_KEY_0, /* decimal (numeric) */
    N1 = SHR_KEY_1, /* decimal (numeric) */
    N2 = SHR_KEY_2, /* decimal (numeric) */
    N3 = SHR_KEY_3, /* decimal (numeric) */
    N4 = SHR_KEY_4, /* decimal (numeric) */
    N5 = SHR_KEY_5, /* decimal (numeric) */
    N6 = SHR_KEY_6, /* decimal (numeric) */
    N7 = SHR_KEY_7, /* decimal (numeric) */
    N8 = SHR_KEY_8, /* decimal (numeric) */
    N9 = SHR_KEY_9, /* decimal (numeric) */
    Semicolon = SHR_KEY_SEMICOLON,
    Equal = SHR_KEY_EQUAL,
    A = SHR_KEY_A,
    B = SHR_KEY_B,
    C = SHR_KEY_C,
    D = SHR_KEY_D,
    E = SHR_KEY_E,
    F = SHR_KEY_F,
    G = SHR_KEY_G,
    H = SHR_KEY_H,
    I = SHR_KEY_I,
    J = SHR_KEY_J,
    K = SHR_KEY_K,
    L = SHR_KEY_L,
    M = SHR_KEY_M,
    N = SHR_KEY_N,
    O = SHR_KEY_O,
    P = SHR_KEY_P,
    Q = SHR_KEY_Q,
    R = SHR_KEY_R,
    S = SHR_KEY_S,
    T = SHR_KEY_T,
    U = SHR_KEY_U,
    V = SHR_KEY_V,
    W = SHR_KEY_W,
    X = SHR_KEY_X,
    Y = SHR_KEY_Y,
    Z = SHR_KEY_Z,
    LeftBracket = SHR_KEY_LEFT_BRACKET,    /* [ */
    Backslash = SHR_KEY_BACKSLASH,   /* \ */
    RightBracket = SHR_KEY_RIGHT_BRACKET,   /* ] */
    GraveAccent = SHR_KEY_GRAVE_ACCENT,    /* ` */
    Escape = SHR_KEY_ESCAPE,
    Enter = SHR_KEY_ENTER,
    Tab = SHR_KEY_TAB,
    Backspace = SHR_KEY_BACKSPACE,
    Insert = SHR_KEY_INSERT,
    Delete = SHR_KEY_DELETE,
    Right = SHR_KEY_RIGHT,
    Left = SHR_KEY_LEFT,
    Down = SHR_KEY_DOWN,
    Up = SHR_KEY_UP,
    PageUp = SHR_KEY_PAGE_UP,
    PageDown = SHR_KEY_PAGE_DOWN,
    Home = SHR_KEY_HOME,
    End = SHR_KEY_END,
    CapsLock = SHR_KEY_CAPS_LOCK,
    ScrollLock = SHR_KEY_SCROLL_LOCK,
    NumLock = SHR_KEY_NUM_LOCK,
    PrintScreen = SHR_KEY_PRINT_SCREEN,
    Pause = SHR_KEY_PAUSE,
    F1 = SHR_KEY_F1,
    F2 = SHR_KEY_F2,
    F3 = SHR_KEY_F3,
    F4 = SHR_KEY_F4,
    F5 = SHR_KEY_F5,
    F6 = SHR_KEY_F6,
    F7 = SHR_KEY_F7,
    F8 = SHR_KEY_F8,
    F9 = SHR_KEY_F9,
    F10 = SHR_KEY_F10,
    F11 = SHR_KEY_F11,
    F12 = SHR_KEY_F12,
    KP0 = SHR_KEY_KP_0, /* keypad */
    KP1 = SHR_KEY_KP_1, /* keypad */
    KP2 = SHR_KEY_KP_2, /* keypad */
    KP3 = SHR_KEY_KP_3, /* keypad */
    KP4 = SHR_KEY_KP_4, /* keypad */
    KP5 = SHR_KEY_KP_5, /* keypad */
    KP6 = SHR_KEY_KP_6, /* keypad */
    KP7 = SHR_KEY_KP_7, /* keypad */
    KP8 = SHR_KEY_KP_8, /* keypad */
    KP9 = SHR_KEY_KP_9, /* keypad */
    KPDecimal = SHR_KEY_KP_DECIMAL, 		/* keypad */
    KPDivide = SHR_KEY_KP_DIVIDE, 			/* keypad */
    KPMultiply = SHR_KEY_KP_MULTIPLY, 		/* keypad */
    KPSubtract = SHR_KEY_KP_SUBTRACT, 		/* keypad */
    KPAdd= SHR_KEY_KP_ADD, 				/* keypad */
    KPEnter = SHR_KEY_KP_ENTER, 			/* keypad */
    KPEqual = SHR_KEY_KP_EQUAL, 			/* keypad */
    LeftShift = SHR_KEY_LEFT_SHIFT,
    LeftCtrl = SHR_KEY_LEFT_CONTROL,
    LeftAlt = SHR_KEY_LEFT_ALT,
    LeftSuper = SHR_KEY_LEFT_SUPER,
    RightShift = SHR_KEY_RIGHT_SHIFT,
    RightCtrl = SHR_KEY_RIGHT_CONTROL,
    RightAlt = SHR_KEY_RIGHT_ALT,
    RightSuper = SHR_KEY_RIGHT_SUPER,
    Menu = SHR_KEY_MENU,
}; // Keycode enum

}; // shrine

#endif // __SHRINE_ENGINE_UTILITY_KEYBOARD_H__