#include <fmt/core.h>
#include <fmt/color.h>

#include "Globals.h"




int main() {
    fmt::print("Plains with iron: ");
    fmt::print(bg(PLAINS_C) | fg(IRON_C)," ◉ \n");
    fmt::print("Mountain: ");
    fmt::print(bg(MOUNTAINS_C1) | fg(MOUNTAINS_C2),"^^^\n");
    fmt::print("Ocean: ");
    fmt::print(bg(OCEAN_C1) | fg(OCEAN_C2),"~~~\n");
    fmt::print("Shallow: ");
    fmt::print(bg(SHALLOW_C1) | fg(SHALLOW_C2),"~~~\n");
    fmt::print("Ocean and shallow: ");
    fmt::print(bg(SHALLOW_C1) | fg(SHALLOW_C2),"~~~");
    fmt::print(bg(OCEAN_C1) | fg(OCEAN_C2),"~~~\n");
}