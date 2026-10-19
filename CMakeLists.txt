cmake_minimum_required(VERSION 3.15)
project(SchoolGame CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собираем все исходники проекта (Ali.cpp и Classes.h)
# TXLib.h компилятор подтянет сам, так как он лежит в этой же папке
add_executable(${PROJECT_NAME} 
    Ali.cpp 
    Classes.h
)

# Настройки для компилятора MSVC (Visual Studio)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE 
        /permissive-    # Отключает строгий режим соответствия стандартам для старого кода
        /W3             # Уровень предупреждений
    )
    
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
        _CRT_SECURE_NO_WARNINGS    # Отключает ругань на sprintf/strcpy
        _MBCS                      # Многобайтовая кодировка для корректного русского текста
    )
endif()
# Автоматически копируем картинки в папку сборки, чтобы игра их видела
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/diamond.bmp"
    "${CMAKE_CURRENT_BINARY_DIR}/diamond.bmp"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/smile.bmp"
    "${CMAKE_CURRENT_BINARY_DIR}/smile.bmp"
)