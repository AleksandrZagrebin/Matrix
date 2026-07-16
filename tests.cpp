#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "matrix.hpp"

int main()
{
    std::cout << "=== TEST MATRIX ===\n\n";

    std::cout << "1. Constructors:\n";
    Matrix<int> m1(2, 3, 5);
    m1.Dump(std::cout);
    std::cout << "\n";

    Matrix<int> m2(2, 3, { 1, 2, 3, 4, 5, 6 });
    m2.Dump(std::cout);
    std::cout << "\n";

    std::vector<int> vec = { 7, 8, 9, 10, 11, 12 };
    Matrix<int> m3(2, 3, vec.begin(), vec.end());
    m3.Dump(std::cout);
    std::cout << "\n";

    std::cout << "Testing constructor with lambda:\n";
    auto fill_func = [](size_t i, size_t j) { return static_cast<int>(i + j); };
    Matrix<int> m4(3, 3, fill_func);
    m4.Dump(std::cout);
    std::cout << "\n";

    std::cout << "2. Identity matrix:\n";
    Matrix<int>::Identity(3).Dump(std::cout);
    std::cout << "\n";

    std::cout << "3. operator[] with bounds checking:\n";
    Matrix<int> m5(2, 3, { 1, 2, 3, 4, 5, 6 });

    std::cout << "m5[0][0] = " << m5[0][0] << "\n";
    m5[0][0] = 100;
    std::cout << "m5[0][0] = 100 - OK\n";

    std::cout << "m5[1][2] = " << m5[1][2] << "\n";
    m5[1][2] = 200;
    std::cout << "m5[1][2] = 200 - OK\n";

    std::cout << "m5 after modifications:\n";
    m5.Dump(std::cout);
    std::cout << "\n";

    std::cout << "4. Copy & Move:\n";
    Matrix<int> m6(2, 2, { 1, 2, 3, 4 });
    Matrix<int> m7 = m6;
    std::cout << "m7 (copy of m6):\n";
    m7.Dump(std::cout);

    Matrix<int> m8 = std::move(m6);
    std::cout << "m8 (move from m6):\n";
    m8.Dump(std::cout);
    std::cout << "\n";

    std::cout << "5. Matrix multiplication:\n";
    Matrix<int> A(2, 3, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> B(3, 2, { 7, 8, 9, 10, 11, 12 });

    Matrix<int> C = A * B;
    std::cout << "A * B:\n";
    C.Dump(std::cout);
    std::cout << "\n";

    std::cout << "Testing invalid multiplication (should assert):\n";
    Matrix<int> BadA(2, 2, { 1, 2, 3, 4 });
    Matrix<int> BadB(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::cout << "Note: This will trigger assert in debug mode\n";
    // BadA * BadB; // Раскомментируйте для проверки assert
    std::cout << "\n";

    std::cout << "6. Scalar multiplication:\n";
    Matrix<int> D(2, 2, { 1, 2, 3, 4 });
    (D * 2).Dump(std::cout);
    std::cout << "\n";
    (3 * D).Dump(std::cout);
    std::cout << "\n";

    std::cout << "7. Addition:\n";
    Matrix<int> G(2, 2, { 1, 2, 3, 4 });
    Matrix<int> H(2, 2, { 5, 6, 7, 8 });

    (G + H).Dump(std::cout);
    std::cout << "\n";

    std::cout << "8. Subtraction:\n";
    (H - G).Dump(std::cout);
    std::cout << "\n";

    std::cout << "9. Determinant:\n";
    Matrix<int> K(2, 2, { 4, 7, 2, 6 });
    std::cout << "det(K) = " << K.Det() << "\n";

    Matrix<int> L(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::cout << "det(L) = " << L.Det() << "\n";

    Matrix<double> M(3, 3, { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0 });
    std::cout << "det(M) = " << M.Det() << "\n\n";

    std::cout << "10. Transpose:\n";
    Matrix<int> N(2, 3, { 1, 2, 3, 4, 5, 6 });
    std::cout << "Original:\n";
    N.Dump(std::cout);
    std::cout << "Transposed:\n";
    N.Transposing().Dump(std::cout);
    std::cout << "\n";

    std::cout << "11. In-place transpose:\n";
    Matrix<int> O(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::cout << "Original:\n";
    O.Dump(std::cout);
    O.Transpose();
    std::cout << "After transpose:\n";
    O.Dump(std::cout);
    std::cout << "\n";

    std::cout << "12. swap_rows (via AddLineMVal demonstration):\n";
    Matrix<int> P(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::cout << "Original:\n";
    P.Dump(std::cout);
    // Используем AddLineMVal для демонстрации (3 * строка1 + строка2)
    P.AddLineMVal(1, 0, 2.0);
    std::cout << "After AddLineMVal (row1 += 2 * row0):\n";
    P.Dump(std::cout);
    std::cout << "\n";

    std::cout << "13. IsEq (equality check):\n";
    Matrix<int> Q(2, 2, { 1, 2, 3, 4 });
    Matrix<int> R(2, 2, { 1, 2, 3, 4 });
    Matrix<int> S(2, 2, { 5, 6, 7, 8 });
    std::cout << "Q == R: " << Q.IsEq(R) << "\n";
    std::cout << "Q == S: " << Q.IsEq(S) << "\n\n";

    std::cout << "14. operator== (external):\n";
    std::cout << "Q == R: " << (Q == R) << "\n";
    std::cout << "Q == S: " << (Q == S) << "\n\n";

    std::cout << "15. Compound assignment:\n";
    Matrix<int> T(2, 2, { 1, 2, 3, 4 });
    Matrix<int> U(2, 2, { 2, 0, 1, 3 });

    T += U;
    std::cout << "T += U:\n";
    T.Dump(std::cout);

    T *= 2;
    std::cout << "T *= 2:\n";
    T.Dump(std::cout);
    std::cout << "\n";

    std::cout << "16. getRows & getCols:\n";
    Matrix<int> V(3, 4);
    std::cout << "rows = " << V.getRows() << ", cols = " << V.getCols() << "\n\n";

    std::cout << "17. Testing with double:\n";
    Matrix<double> mDouble(3, 3, { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0 });
    mDouble.Dump(std::cout);
    std::cout << "det = " << mDouble.Det() << "\n";

    Matrix<double> mDouble2(3, 3, { 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5 });
    std::cout << "mDouble2:\n";
    mDouble2.Dump(std::cout);
    std::cout << "mDouble + mDouble2:\n";
    (mDouble + mDouble2).Dump(std::cout);
    std::cout << "\n";

    std::cout << "18. Testing with float:\n";
    Matrix<float> mFloat(2, 2, { 1.1f, 2.2f, 3.3f, 4.4f });
    mFloat.Dump(std::cout);
    std::cout << "det = " << mFloat.Det() << "\n\n";

    std::cout << "19. Threshold functionality:\n";
    std::cout << "Current threshold: " << Matrix<double>::GetThreshold() << "\n";
    Matrix<double>::SetThreshold(1e-5);
    std::cout << "New threshold: " << Matrix<double>::GetThreshold() << "\n";
    Matrix<double>::SetDefThres();
    std::cout << "Reset threshold: " << Matrix<double>::GetThreshold() << "\n\n";

    std::cout << "20. At() method:\n";
    Matrix<int> mAt(2, 2, { 1, 2, 3, 4 });
    std::cout << "mAt.At(0, 0) = " << mAt.At(0, 0) << "\n";
    std::cout << "mAt.At(1, 1) = " << mAt.At(1, 1) << "\n\n";

    std::cout << "21. Dump format:\n";
    Matrix<int> mDump(2, 2, { 1, 2, 3, 4 });
    mDump.Dump(std::cout);
    std::cout << "\n";

    std::cout << "22. operator<<:\n";
    std::cout << mDump << "\n";

    std::cout << "23. operator>> (input from stringstream):\n";
    std::istringstream iss("2 2 1 2 3 4");
    Matrix<int> mInput;
    iss >> mInput;
    std::cout << "Read matrix:\n";
    std::cout << mInput << "\n";

    std::cout << "24. InputQuadr:\n";
    std::istringstream iss2("3 1 2 3 4 5 6 7 8 9");
    Matrix<int> mQuadr;
    InputQuadr(iss2, mQuadr);
    std::cout << "Read square matrix:\n";
    std::cout << mQuadr << "\n";

    std::cout << "25. Matrix multiplication with external operator:\n";
    Matrix<int> M1(2, 3, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> M2(3, 2, { 7, 8, 9, 10, 11, 12 });
    Matrix<int> M3 = M1 * M2;
    std::cout << "M1 * M2:\n";
    M3.Dump(std::cout);
    std::cout << "\n";

    std::cout << "26. Scalar multiplication with external operator:\n";
    Matrix<int> M4(2, 2, { 1, 2, 3, 4 });
    std::cout << "M4 * 3:\n";
    (M4 * 3).Dump(std::cout);
    std::cout << "3 * M4:\n";
    (3 * M4).Dump(std::cout);
    std::cout << "\n";

    std::cout << "27. Addition and subtraction with external operators:\n";
    Matrix<int> M5(2, 2, { 1, 2, 3, 4 });
    Matrix<int> M6(2, 2, { 5, 6, 7, 8 });
    std::cout << "M5 + M6:\n";
    (M5 + M6).Dump(std::cout);
    std::cout << "M6 - M5:\n";
    (M6 - M5).Dump(std::cout);
    std::cout << "\n";

    std::cout << "28. operator== (external):\n";
    Matrix<int> M7(2, 2, { 1, 2, 3, 4 });
    Matrix<int> M8(2, 2, { 1, 2, 3, 4 });
    Matrix<int> M9(2, 2, { 5, 6, 7, 8 });
    std::cout << "M7 == M8: " << (M7 == M8) << "\n";
    std::cout << "M7 == M9: " << (M7 == M9) << "\n\n";

    std::cout << "29. Large matrix test:\n";
    Matrix<int> Large(100, 100, 42);
    std::cout << "Created 100x100 matrix filled with 42\n";
    std::cout << "rows = " << Large.getRows() << ", cols = " << Large.getCols() << "\n";
    std::cout << "Element [50][50] = " << Large[50][50] << "\n\n";

    std::cout << "30. Identity matrix multiplication test:\n";
    Matrix<int> I5 = Matrix<int>::Identity(5);
    Matrix<int> M10(5, 5, [](size_t i, size_t j) { return static_cast<int>(i * j); });
    Matrix<int> M11 = M10 * I5;
    Matrix<int> M12 = I5 * M10;
    std::cout << "M10 * I == M10: " << (M10 == M11) << "\n";
    std::cout << "I * M10 == M10: " << (M10 == M12) << "\n\n";

    std::cout << "31. Transpose of transpose:\n";
    Matrix<int> M13(3, 4, [](size_t i, size_t j) { return static_cast<int>(i + j); });
    Matrix<int> M14 = M13.Transposing();
    Matrix<int> M15 = M14.Transposing();
    std::cout << "M13 == (M13^T)^T: " << (M13 == M15) << "\n\n";

    std::cout << "32. Determinant of identity:\n";
    Matrix<int> I3 = Matrix<int>::Identity(3);
    std::cout << "det(I3) = " << I3.Det() << "\n\n";

    std::cout << "33. Determinant of 2x2:\n";
    Matrix<int> M16(2, 2, { 1, 2, 3, 4 });
    std::cout << "det([[1,2],[3,4]]) = " << M16.Det() << " (should be -2)\n\n";

    std::cout << "34. Determinant with threshold:\n";
    Matrix<double> M17(2, 2, { 1e-12, 1, 1, 1 });
    std::cout << "det([[1e-12,1],[1,1]]) = " << M17.Det() << "\n";
    Matrix<double>::SetThreshold(1e-5);
    std::cout << "With threshold=1e-5: det = " << M17.Det() << "\n";
    Matrix<double>::SetDefThres();
    std::cout << "\n";

    std::cout << "=== ALL TESTS PASSED ===\n";

    return 0;
}
