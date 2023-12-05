export JUCE_PATH="${HOME}/JUCE"
cmake -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
cmake --build build -j4 --target FrangiTest
