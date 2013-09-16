project(hooke)
add_executable(hooke serialib.cpp vars.cpp setup.cpp jog.cpp motor.cpp main.cpp)
target_link_libraries(hooke menu)
target_link_libraries(hooke ncurses)