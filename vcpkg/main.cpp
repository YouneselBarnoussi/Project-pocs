#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <fmt/core.h>
#include <zlib.h>

int main() {
    printf("%s\n", sqlite3_libversion());

    fmt::print("fmt version is {}\n"
               "zlib version is {}\n",
               FMT_VERSION, ZLIB_VERSION);
    return 0;
}
