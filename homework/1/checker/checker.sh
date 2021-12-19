echo "===== CHECK SOURCE CODES ====="
cppcheck --language=c++ --enable=all ./src/algo.h
cppcheck --language=c++ --enable=all ./src/main.cpp
cppcheck --language=c++ --enable=all ./src/lca_disjoint-set.cpp
cppcheck --language=c++ --enable=all ./src/lca_rmq.cpp
make clean
make build

echo
echo "===== CHECK LCA_DISJOINT-SET ====="
echo "Test folder: ./in"
./checker/check_tests.sh lca_disjoint-set in out ok 0 9

echo
echo "===== CHECK LCA_RMQ-SPARSE-TABLE ====="
echo "Test folder: ./in"
./checker/check_tests.sh lca_rmq in out ok 0 9

make clean
rm -rf out/*