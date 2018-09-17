/*
 *  변수 타입 별 범위
 *
 * - char               : -128 to 127
 * - unsigned char      :    0 to 255
 * - int                : -2,147,483,648 to 2,147,483,647
 * - unsigned int       :              0 to 4,294,967,295
 * - long long          : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
 * - unsigned long long :                          0 to 18,446,744,073,709,551,615
 *
 */


/*
 * 타입 변환
 *
 * - char* to string      : std::string(char*)
 * - int to string        : std::to_string
 * - long long to string  : std::to_string
 * - float to string     : std::to_string
 * - double to string     : std::to_string
 *
 * - string to char*     : std::string::c_str()
 * - string to int       : std::stoi
 * - string to long long : std::stoll
 * - string to float     : std::stof
 * - string to double    : std::stod
 *
*/

/*
 * palind room functions
 *

void palindLoop(LL limit, const function<void(LL)> &f) {
    LL seed = 0;

    while (true) {
        LL p1 = ++seed;
        for (LL div = seed / 10; div; div/=10) {
            p1 = p1*10 + div%10;
        }

        LL p2 = seed;
        for (LL div = seed; div; div/=10) {
            p2 = p2*10 + div%10;
        }

        f(p1); f(p2);

        if (p1 >= limit) break;
    }
}

bool isPalind(const string &pp) {
    int i = 0, j = pp.size() - 1;
    while (i < j) {
        if (pp[i] != pp[j]) return false;
        i++, j--;
    }
    return true;
}

 */
