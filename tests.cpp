#include "matrix.hpp"

int main()
{
    std::cout << "=== TEST MATRIX ===\n\n";

    std::cout << "1. Constructors:\n";
    Matrix<int> m1(2, 3, 5);
    m1.dump(std::cout);
    std::cout << "\n";

    auto it = std::find(m1.begin(), m1.end(), 5);
    if (it != m1.end()) {
        std::cout << "Found: " << *it << "\n";
    }

    Matrix<int> m2(2, 3, { 1, 2, 3, 4, 5, 6 });
    m2.dump(std::cout);
    std::cout << "\n";

    std::vector<int> vec = { 7, 8, 9, 10, 11, 12 };
    Matrix<int> m3(2, 3, vec.begin(), vec.end());
    m3.dump(std::cout);
    std::cout << "\n";

    std::cout << "Testing istream constructor:\n";
    std::istringstream iss("1 2 3 4 5 6 7 8 9");
    try {
        Matrix<int> m4(iss, 3, 3);
        m4.dump(std::cout);
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "2. eye:\n";
    Matrix<int>::eye(3).dump(std::cout);
    std::cout << "\n";
    Matrix<int>::eye(2, 3).dump(std::cout);
    std::cout << "\n";

    std::cout << "3. operator[] with bounds checking:\n";
    Matrix<int> m5(2, 3, { 1, 2, 3, 4, 5, 6 });

    try {
        m5[0][0] = 100;
        std::cout << "m5[0][0] = 100 - OK\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    try {
        m5[1][2] = 200;
        std::cout << "m5[1][2] = 200 - OK\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    try {
        m5[0][4] = 300;
        std::cout << "m5[0][4] = 300 - OK\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    try {
        m5[2][0] = 400;
        std::cout << "m5[2][0] = 400 - OK\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    std::cout << "m5 after tests:\n";
    m5.dump(std::cout);
    std::cout << "\n";

    std::cout << "4. Copy & Move:\n";
    Matrix<int> m6(2, 2, { 1, 2, 3, 4 });
    Matrix<int> m7 = m6;
    std::cout << "m7 (copy of m6):\n";
    m7.dump(std::cout);

    Matrix<int> m8 = std::move(m6);
    std::cout << "m8 (move from m6):\n";
    m8.dump(std::cout);

    std::cout << "5. Matrix multiplication:\n";
    Matrix<int> A(2, 3, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> B(3, 2, { 7, 8, 9, 10, 11, 12 });

    try {
        A.multiply(B).dump(std::cout);
        std::cout << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    std::cout << "Testing invalid multiplication:\n";
    Matrix<int> BadA(2, 2, { 1, 2, 3, 4 });
    Matrix<int> BadB(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    try {
        BadA.multiply(BadB).dump(std::cout);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "6. Scalar multiplication:\n";
    Matrix<int> D(2, 2, { 1, 2, 3, 4 });
    D.scalar_multiply(2).dump(std::cout);
    std::cout << "\n";

    std::cout << "7. Addition:\n";
    Matrix<int> G(2, 2, { 1, 2, 3, 4 });
    Matrix<int> H(2, 2, { 5, 6, 7, 8 });

    try {
        G.add(H).dump(std::cout);
        std::cout << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    std::cout << "Testing invalid addition:\n";
    Matrix<int> BadG(2, 3, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> BadH(3, 2, { 1, 2, 3, 4, 5, 6 });
    try {
        BadG.add(BadH).dump(std::cout);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "8. trace:\n";
    Matrix<int> J(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    try {
        std::cout << "trace = " << J.trace() << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    std::cout << "Testing trace on non-square matrix:\n";
    Matrix<int> BadTrace(2, 3, { 1, 2, 3, 4, 5, 6 });
    try {
        std::cout << "trace = " << BadTrace.trace() << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "9. determinant:\n";
    Matrix<int> K(2, 2, { 4, 7, 2, 6 });
    try {
        std::cout << "det(K) = " << K.determinant() << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    Matrix<int> L(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    try {
        std::cout << "det(L) = " << L.determinant() << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    std::cout << "Testing determinant on non-square matrix:\n";
    Matrix<int> BadDet(2, 3, { 1, 2, 3, 4, 5, 6 });
    try {
        std::cout << "det = " << BadDet.determinant() << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "10. transpose:\n";
    Matrix<int> M(2, 3, { 1, 2, 3, 4, 5, 6 });
    M.transpose().dump(std::cout);
    std::cout << "\n";

    std::cout << "11. negate:\n";
    Matrix<int> N(2, 2, { 1, -2, 3, -4 });
    N.negate().dump(std::cout);
    std::cout << "\n";

    std::cout << "12. swap_rows:\n";
    Matrix<int> O(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    try {
        O.swap_rows(0, 2);
        O.dump(std::cout);
        std::cout << "\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    std::cout << "Testing swap_rows with invalid indices:\n";
    try {
        O.swap_rows(0, 10);
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "13. equal & less:\n";
    Matrix<int> P(2, 2, { 1, 2, 3, 4 });
    Matrix<int> Q(2, 2, { 1, 2, 3, 4 });
    Matrix<int> R(2, 2, { 5, 6, 7, 8 });
    std::cout << "P == Q: " << P.equal(Q) << "\n";
    std::cout << "P == R: " << P.equal(R) << "\n";
    std::cout << "P < R: " << P.less(R) << "\n";
    std::cout << "P < Q: " << P.less(Q) << "\n\n";

    std::cout << "14. compound methods:\n";
    Matrix<int> S(2, 2, { 1, 2, 3, 4 });
    Matrix<int> T(2, 2, { 2, 0, 1, 3 });

    try {
        S.add_assign(T);
        std::cout << "S += T:\n";
        S.dump(std::cout);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    try {
        S.scalar_multiply_assign(2);
        std::cout << "S *= 2:\n";
        S.dump(std::cout);
        std::cout << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught (should not happen): " << e.what() << "\n";
    }

    std::cout << "15. nrows & ncols:\n";
    Matrix<int> U(3, 4);
    std::cout << "rows = " << U.nrows() << ", cols = " << U.ncols() << "\n\n";

    std::cout << "16. Testing with double:\n";
    Matrix<double> mDouble(3, 3, { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0 });
    mDouble.dump(std::cout);
    std::cout << "det = " << mDouble.determinant() << "\n";
    std::cout << "trace = " << mDouble.trace() << "\n";

    Matrix<double> mDouble2(3, 3, { 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5 });
    std::cout << "mDouble2:\n";
    mDouble2.dump(std::cout);
    std::cout << "mDouble + mDouble2:\n";
    mDouble.add(mDouble2).dump(std::cout);
    std::cout << "\n";

    std::cout << "17. Testing with float:\n";
    Matrix<float> mFloat(2, 2, { 1.1f, 2.2f, 3.3f, 4.4f });
    mFloat.dump(std::cout);
    std::cout << "det = " << mFloat.determinant() << "\n";
    std::cout << "trace = " << mFloat.trace() << "\n";
    std::cout << "\n";

    std::cout << "18. STL algorithms:\n";
    Matrix<int> mStl(3, 3, { 5, 2, 8, 1, 9, 3, 7, 4, 6 });
    std::cout << "mStl (original):\n";
    mStl.dump(std::cout);

    std::cout << "std::find (search for 9):\n";
    auto findIt = std::find(mStl.begin(), mStl.end(), 9);
    if (findIt != mStl.end()) {
        std::cout << "Found: " << *findIt << "\n";
    }
    std::cout << "\n";

    std::cout << "std::count_if (count > 5):\n";
    int cnt = std::count_if(mStl.begin(), mStl.end(), [](int x) { return x > 5; });
    std::cout << "Count = " << cnt << "\n\n";

    std::cout << "std::for_each (multiply by 2):\n";
    std::for_each(mStl.begin(), mStl.end(), [](int& x) { x *= 2; });
    mStl.dump(std::cout);
    std::cout << "\n";

    std::cout << "std::accumulate (sum):\n";
    int sum = std::accumulate(mStl.begin(), mStl.end(), 0);
    std::cout << "Sum = " << sum << "\n\n";

    std::cout << "std::min_element / std::max_element:\n";
    auto minIt2 = std::min_element(mStl.begin(), mStl.end());
    auto maxIt2 = std::max_element(mStl.begin(), mStl.end());
    std::cout << "Min = " << *minIt2 << ", Max = " << *maxIt2 << "\n\n";

    std::cout << "std::transform (add 10):\n";
    std::transform(mStl.begin(), mStl.end(), mStl.begin(), [](int x) { return x + 10; });
    mStl.dump(std::cout);
    std::cout << "\n";

    std::cout << "std::replace (replace 15 with 0):\n";
    std::replace(mStl.begin(), mStl.end(), 15, 0);
    mStl.dump(std::cout);
    std::cout << "\n";

    std::cout << "19. Range-based for:\n";
    Matrix<int> mRange(2, 3, { 1, 2, 3, 4, 5, 6 });
    std::cout << "mRange (original):\n";
    mRange.dump(std::cout);

    std::cout << "Range-based for (read): ";
    for (const int& val : mRange) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    std::cout << "Range-based for (multiply by 2):\n";
    for (int& val : mRange) {
        val *= 2;
    }
    mRange.dump(std::cout);
    std::cout << "\n";

    std::cout << "20. Const range-based for:\n";
    const Matrix<int>& mConst = mRange;
    std::cout << "mConst (read-only): ";
    for (const int& val : mConst) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";

    std::cout << "=== ALL TESTS PASSED ===\n";

    return 0;
}
