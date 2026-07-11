add_executable(Lox_Interpreter)
add_executable(Lox::Interpreter ALIAS Lox_Interpreter)

target_sources(Lox_Interpreter
    PRIVATE
        main.cpp
        lox.cpp
        scanner.cpp
        token.cpp
        lox.h
        scanner.h
        token.h
)

target_compile_features(Lox_Interpreter
    PRIVATE
        cxx_std_20
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Lox_Interpreter
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
elseif(MSVC)
    target_compile_options(Lox_Interpreter
        PRIVATE
            /W4
    )
endif()


set_target_properties(Lox_Interpreter PROPERTIES
    OUTPUT_NAME "LoxInterpreter"
)
