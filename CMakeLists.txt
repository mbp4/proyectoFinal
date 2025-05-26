cmake_minimum_required(VERSION 3.30.5)
project(proyectoFinal C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(proyectoFinal
        main.c
        utilidades.c
        difusion_secuencial.c
        difusion_paralela.c
)

if(APPLE)
    target_compile_options(proyectoFinal PUBLIC
            -Xpreprocessor -fopenmp
            -I/opt/homebrew/opt/libomp/include)

    target_link_libraries(proyectoFinal PUBLIC
            -L/opt/homebrew/opt/libomp/lib -lomp)
else()
    # En Linux o Windows con soporte OpenMP
    find_package(OpenMP REQUIRED)
    if(OpenMP_C_FOUND)
        target_link_libraries(proyectoFinal PUBLIC OpenMP::OpenMP_C)
        target_compile_options(proyectoFinal PUBLIC ${OpenMP_C_FLAGS})
    endif()
endif()
