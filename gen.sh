#!/bin/bash

# execute only in src path!

conan install . --output-folder=build --build=missing --profile=debug
(cd build && meson setup --native-file conan_meson_native.ini .. meson-src)

conan install . --output-folder=build-rel --build=missing --profile=default
(cd build-rel && meson setup --native-file conan_meson_native.ini .. meson-src)
