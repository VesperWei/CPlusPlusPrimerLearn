// floatnum.cpp -- floating-point types
#include <iostream>

int main()
{
    using namespace std;

    // ============================================================
    // Floating-Point Output Format Flags & Precision in C++
    // ============================================================
    //
    // 1. DEFAULT BEHAVIOR (no format flag set):
    //    - When neither ios_base::fixed nor ios_base::scientific is set,
    //      the stream uses "default float format".
    //    - It automatically chooses between fixed-point and scientific notation
    //      based on the magnitude of the number and the current precision.
    //    - Example: 1234567.89 may print as 1.23457e+06
    //
    // 2. AVAILABLE FORMAT FLAGS (in <iomanip> / ios_base):
    //    - ios_base::fixed:      always use fixed-point (e.g., 3.141593)
    //    - ios_base::scientific:  always use scientific (e.g., 3.141593e+00)
    //    - defaultfloat (C++11): restore default behavior
    //
    // 3. HOW TO CLEAR/UNSET FORMAT FLAGS:
    //    - Method A: cout.unsetf(ios_base::fixed);
    //               clears ONLY the fixed flag (may leave scientific set)
    //    - Method B: cout.setf(ios_base::fmtflags(0), ios_base::floatfield);
    //               clears BOTH fixed and scientific (restores default)
    //    - Method C (C++11): cout << defaultfloat;
    //               modern and recommended way to restore default
    //
    // 4. floatfield is a "flag group":
    //    - It includes both ios_base::fixed and ios_base::scientific.
    //    - These two flags are MUTUALLY EXCLUSIVE; setting one clears the other.
    //    - Using setf(new_flag, flag_group) ensures the group is cleared first.
    //
    // 5. FLOATING-POINT PRECISION (cout.precision(), default = 6):
    //    a) Default mode (no fixed/scientific):
    //       precision  =  number of TOTAL significant digits displayed.
    //       Example: cout.precision(6), value=3.33333 → "3.33333"   (6 sig. digits)
    //                                    value=3333333 → "3.33333e+06" (switches to scientific)
    //
    //    b) Fixed mode:
    //       precision  =  number of digits AFTER the decimal point.
    //       Example: cout.precision(6), value=3.14159 → "3.141590" (2 extra trailing zeros)
    //
    //    c) Scientific mode:
    //       precision  =  number of digits AFTER decimal in mantissa.
    //       Example:  cout.precision(6), value=3.14159 → "3.141590e+00"
    //
    // 6. FLOATING-POINT TYPE PRECISION LIMITS:
    //    TYPE      | Typical Size | Significant Digits | Example Inaccuracy
    //    ----------|-------------|--------------------|--------------------
    //    float     |    4 bytes  |    ~6-7 digits     |  tub = 10/3 = 3.333333...
    //              |             |                     |  (precise only to 6-7 digits)
    //    double    |    8 bytes  |   ~15-16 digits    |  mint = 10/3 = 3.33333333333333...
    //              |             |                     |  (precise to 15-16 digits)
    //    long double | 10/16 bytes|  ~18-19 digits    |  even more precise
    //
    //    Tub is declared as 'float', so multiplying by large values (e.g., 1e6)
    //    quickly exceeds the ~6-7 significant digits that float can accurately
    //    represent, leading to visible rounding errors (e.g., .250000 instead of .333333).
    //    If tub were 'double', the results would be more accurate.
    // ============================================================

    // Set floating-point output format to fixed-point notation
    // This ensures floats are displayed as decimal numbers (e.g., 3.333333)
    // instead of scientific notation (e.g., 3.333333e+00)
    //
    // Parameters:
    //   - ios_base::fixed:     the format flag to set (use fixed-point notation)
    //   - ios_base::floatfield: the flag group to clear first (avoids conflict
    //                           with ios_base::scientific if previously set)
    //
    // Alternative modern approach (C++11):
    //   #include <iomanip>
    //   cout << fixed;  // equivalent to the setf() call below
    cout.setf(ios_base::fixed, ios_base::floatfield);

    float tub = 10.0 / 3.0;
    double mint = 10.0 / 3.0;
    const float million = 1.0e6;

    cout << "tub = " << tub;
    cout << ", a million tubs = " << million * tub;
    cout << ", and ten million tubs = " << million * 10 * tub << endl;

    // ---- Example: restoring default format ----
    // Uncomment below to see the difference:
    cout.setf(ios_base::fmtflags(0), ios_base::floatfield);  // clear floatfield -> default behavior
    cout << "tub = " << tub;
    cout << ", a million tubs = " << million * tub;
    cout << ", and ten million tubs = " << million * 10 * tub << endl;

    return 0;
}