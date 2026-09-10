#include "arbFloat.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wreturn-local-addr"

int cons_debugging = 0;
int comp_debugging = 0;
int arith_debugging = 0;
int misc_debugging = 0;

int prec = MAX_PREC - 5;


//Vector functions
vector<int> vec_truncate(vector<int> vec, int exp){
    int size = vec.size();
    int store = vec.size() - 1;

    if (vec[store] != 0){
        return vec;
    }

    for (int i = vec.size() - 1; i >= 0; i--){
        if (vec[i] != 0){
            store = i;
            i = 0;
        }
    }
    int stop = max(exp + 1, store + 1);

    vector<int> newDigits(stop);
    for(int i = 0; i < stop; i++){
        newDigits[i] = vec[i];
    }

    return newDigits;
}

vector<int> vec_round(vector<int> vec, int num, int &exp){
    int size = vec.size();
    if (size <= num){
        return vec;
    }
    int lastDig = vec[num];
    vector<int> newVec(num);
    for(int i = 0; i < num; i++){
        newVec[i] = vec[i];
    }
    if (lastDig >= 5){
        newVec[num - 1] += 1;
        for(int i = num - 1; i > 0; i--){
            if (newVec[i] > 9){
                newVec[i] = newVec[i] % 10;
                newVec[i - 1] += 1;
            }
        }
    }
    if (newVec[0] > 9){
        newVec[0] = newVec[0] % 10;
        newVec.insert(newVec.begin(),1);
        exp += 1;
    }
    return newVec;
}

vector<int> digitsProduct(vector<int> vec1, vector<int> vec2, int& overflow){

    if (arith_debugging == 1){
        cout << "Debugging Product algorithm:" << endl;
    }
    int size1 = vec1.size();
    int size2 = vec2.size();

    int newSize = size1 + size2 - 1;

    vector<int> newVec(newSize + 1, 0);
    if (arith_debugging == 1){
        cout << "Made a new vector of length vec1.size() + vec2.size():\n";
    }
    for(int i = 0; i < size1; i++){
        if (arith_debugging == 1){
            cout << "Accessing " << i << "th value of vector1 = " << vec1[i] << endl;
        }
        for(int j = 0; j < size2; j++){
            if (arith_debugging == 1){ 
            cout << "Accessing " << j << "th value of vector2 = " << vec2[i] << endl;
            }
            int value = vec1[size1 - 1 - i] * vec2[size2 - 1 - j];
            newVec[newSize - (i+j)] += value;
            if (arith_debugging == 1){
                cout << "Product vector entry " << newSize - (i+j) << " += " << value << endl;
            }
        }
    }
    
    if (arith_debugging == 1){
        cout << "Taking the carry of every entry\n";
    }
    for(int i = newSize; i > 0; i--){
        int num = newVec[i];
        if (arith_debugging == 1){
            cout << "Product vector entry" << i << "th = " << num << endl;
        }
        if (num > 9){
            int carry = num / 10;
            newVec[i] = num % 10;
            if (arith_debugging == 1){
                cout << "Value after modding by 10" << newVec[i] << endl << "Adding one to the left digit value" << endl;
            }
            newVec[i - 1] += carry;
        }
    }

    while (newVec[0] > 9){
        int carry = newVec[0] / 10;
        newVec[0] = newVec[0] % 10;
        newVec.insert(newVec.begin(), carry);
        overflow++;
    }


    return newVec;
};



//Constructors
void arbFloat::initialize(){
    digits;
    sign = 0;
    exp = 0;
}

arbFloat::arbFloat(){
    arbFloat::initialize();
}

arbFloat::arbFloat(int p){
    arbFloat::initialize();
    vector<int> v(p);
    digits = v;
}

arbFloat::arbFloat(int p, int num){
    if (p > prec){
        throw invalid_argument("Precision p = " + to_string(p) + " is too large for the current maximum precision. PREC = " + to_string(prec));
    }
    arbFloat::initialize();
    string number;
    int posNum;
    if (num < 0){
        sign = 1;
        posNum = -1 * num;
        number = to_string(posNum);
    }
    else{
        sign = 0;
        number = to_string(num);
        posNum = num;
    }
    int numSize = number.size();
    if (p < numSize){
        throw invalid_argument("Precision " + to_string(p) + " is too small for the number " + to_string(num) + ".\n Error occured when trying to initialize an arbFloat with int value: " + to_string(num));
    }
    else{
        vector<int> v(p);
        int n = 1;
        exp = -1;
        int val;
        int intermed = p - numSize;
        for (int i = 0; i < numSize; i++){
            val = (posNum / n) % 10;
            n = n * 10;
            v[p - 1 - intermed - i] = val;
            exp++;
        }
        digits = v;
    }
}

arbFloat::arbFloat(int p, long int num){
    if (p > prec){
        throw invalid_argument("Precision p = " + to_string(p) + " is too large for the current maximum precision. PREC = " + to_string(prec));
    }
    arbFloat::initialize();
    string number;
    int posNum;
    if (num < 0){
        sign = 1;
        posNum = -1 * num;
        number = to_string(posNum);
    }
    else{
        sign = 0;
        number = to_string(num);
        posNum = num;
    }
    int numSize = number.size();
    if (p < numSize){
        throw invalid_argument("Precision " + to_string(p) + " is too small for the number " + to_string(num) + ".\n Error occured when trying to initialize an arbFloat with int value: " + to_string(num));
    }
    else{
        vector<int> v(p);
        int n = 1;
        exp = -1;
        int val;
        int intermed = p - numSize;
        for (int i = 0; i < numSize; i++){
            val = (posNum / n) % 10;
            n = n * 10;
            v[p - 1 - intermed - i] = val;
            exp++;
        }
        digits = v;
    }
}

arbFloat::arbFloat(int p, long long int num){
    if (p > prec){
        throw invalid_argument("Precision p = " + to_string(p) + " is too large for the current maximum precision. PREC = " + to_string(prec));
    }
    arbFloat::initialize();
    string number;
    int posNum;
    if (num < 0){
        sign = 1;
        posNum = -1 * num;
        number = to_string(posNum);
    }
    else{
        sign = 0;
        number = to_string(num);
        posNum = num;
    }
    int numSize = number.size();
    if (p < numSize){
        throw invalid_argument("Precision " + to_string(p) + " is too small for the number " + to_string(num) + ".\n Error occured when trying to initialize an arbFloat with int value: " + to_string(num));
    }
    else{
        vector<int> v(p);
        int n = 1;
        exp = -1;
        int val;
        int intermed = p - numSize;
        for (int i = 0; i < numSize; i++){
            val = (posNum / n) % 10;
            n = n * 10;
            v[p - 1 - intermed - i] = val;
            exp++;
        }
        digits = v;
    }
}

arbFloat::arbFloat(int p, string s){
    if (p > prec){
        throw invalid_argument("Precision p = " + to_string(p) + " is too large for the current maximum precision. PREC = " + to_string(prec));
    }
    arbFloat::initialize();
    string num = s;
    char neg = num[0];
    int negInt = neg;
    if (negInt == 45){
        sign = 1;
        num.erase(0,1);
    }

    int numSize = num.size();
    int  expVal = numSize - 1;
    for (int i = 0; i < numSize; i++){
        if (num[0] == '0'){
            num.erase(num.begin());
            i = 0;
            numSize = num.size();
        }
        else if (num[i] == 46){
            expVal = i;
            i = numSize;
        }
    }

    if (expVal != numSize){
        num.erase(expVal, 1);
        numSize = num.size();
    }

    exp = expVal - 1;

    if (p <= numSize){
        throw invalid_argument("Precision " + to_string(p) + " is too small for the number " + num + ".\nError occured when trying to initalize an arbFloat with the string: " + s);
    }

    vector<int> v(p);

    for(int i = 0; i < numSize; i++){
        char character = num[i];
        int nextDigit = character - '0';
        v[i] = nextDigit;
    }
    
    digits = v;
}

arbFloat::arbFloat(int p, double d){
    arbFloat::initialize();
    string s = to_string(d);
    char end = s.back();
    while (end == '0'){
        s.pop_back();
        end = s.back();
    }
    int strSize = s.size();
    int expVal = strSize;

    for (int i = 0; i < strSize; i++){
        if (s[i] == 46){
            expVal = i;
            i = strSize;
        }
    }
    if (expVal != strSize){
        s.erase(expVal, 1);
        strSize = s.size();
    }

    char beg = s[0];
    if (beg == '-'){
        sign = 1;
        s.erase(0,1);
        strSize = s.size();
        expVal -= 1;
    }
    beg = s[0];
    strSize = s.size();
    while(beg == '0' && strSize > 1){
        s.erase(0,1);
        expVal -= 1;
        beg = s[0];
        strSize = s.size();
    }

    if (p < strSize){
        throw invalid_argument("Precision " + to_string(p) + " is too small for the number " + s + ".\nError occured when trying to initalize an arbFloat with the double value " + s);
    }

    vector<int> v(p);


    for(int i = 0; i < strSize; i++){
        char character = s[i];
        int nextDigit = character - '0';
        v[i] = nextDigit;
    }
    digits = v;
    exp = expVal - 1;
}

// Need to fix issue with machine epsilon

// arbFloat::arbFloat(int p, float f){
//     double newf = f;
//     string s = to_string(newf);
//     char end = s.back();
//     while (end == '0'){
//         s.pop_back();
//         end = s.back();
//     }
//     int strSize = s.size();
//     int expVal = strSize;

//     for (int i = 0; i < strSize; i++){
//         if (s[i] == 46){
//             expVal = i;
//             i = strSize;
//         }
//     }
//     if (expVal != strSize){
//         s.erase(expVal, 1);
//         strSize = s.size();
//     }

//     char beg = s[0];
//     if (beg == '-'){
//         sign = 1;
//         s.erase(0,1);
//         strSize = s.size();
//         expVal -= 1;
//     }
//     beg = s[0];
//     strSize = s.size();
//     while(beg == '0' && strSize > 1){
//         s.erase(0,1);
//         expVal -= 1;
//         beg = s[0];
//         strSize = s.size();
//     }

//     if (p < strSize){
//         throw invalid_argument("Precision " + to_string(p) + " is too small for the number " + s + ".\nError occured when trying to initalize an arbFloat with the double value " + s);
//     }

//     vector<int> v(p);


//     for(int i = 0; i < strSize; i++){
//         char character = s[i];
//         int nextDigit = character - '0';
//         v[i] = nextDigit;
//     }
//     digits = v;
//     exp = expVal - 1;

// }

arbFloat::arbFloat(int p, long double d){
    arbFloat::initialize();
    ostringstream s1;
    s1 << setprecision(16) << d;
    string s = s1.str();
    char end = s.back();

    while (end == '0'){
        s.pop_back();
        end = s.back();
    }

    int strSize = s.size();
    int expVal = strSize;

    for (int i = 0; i < strSize; i++){
        if (s[i] == 46){
            expVal = i;
            i = strSize;
        }
    }

    if (expVal != strSize){
        s.erase(expVal, 1);
        strSize = s.size();
    }

    char beg = s[0];
    if (beg == '-'){
        sign = 1;
        s.erase(0,1);
        strSize = s.size();
        expVal -= 1;
    }
    beg = s[0];
    strSize = s.size();
    while(beg == '0' && strSize > 1){
        s.erase(0,1);
        expVal -= 1;
        beg = s[0];
        strSize = s.size();
    }

    if (p < strSize){
        throw invalid_argument("Precision " + to_string(p) + " is too small for the number " + s + ".\nError occured when trying to initalize an arbFloat with the double value " + s);
    }

    vector<int> v(p);

    for(int i = 0; i < strSize; i++){
        char character = s[i];
        int nextDigit = character - '0';
        v[i] = nextDigit;
    }
    
    digits = v;
    exp = expVal - 1;
}

arbFloat::arbFloat(const arbFloat& x){
    digits = x.digits;
    sign = x.sign;
    exp = x.exp;
};

//Special constants
const arbFloat arbFloat::ZERO(1,0);
const arbFloat arbFloat::ONE(1,1);
const arbFloat arbFloat::TWO(1,2);

//Comparison Operators

bool operator==(const arbFloat& l, const arbFloat& r){
    arbFloat left = l;
    arbFloat right = r;

    left.truncate();
    right.truncate();

    if (left.digits.size() != right.digits.size()){
        return false;
    }

    if (right.exp != left.exp && left.digits[0] != 0 && right.digits[0] != 0){
        return false;
    }

    if (l.sign == r.sign){
        if (left.digits == right.digits){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if (right.digits == arbFloat::ZERO.digits && left.digits == arbFloat::ZERO.digits){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}


bool operator!=(const arbFloat& l, const arbFloat& r){
    if (comp_debugging == 1){
        cout << "Debugging comparison !=\n Calling the == operator for the following if statement\n";
    }
    if (l == r){
        if (comp_debugging == 1){
            cout << "Found that the left value == the right value. Returning false.\n";
        }
        return false;
    }
    else {
        if (comp_debugging == 1){
            cout << "Did not find that the left value == the right value. Returning true.\n";
        }
        return true;
    }
};

bool operator<(const arbFloat& l, const arbFloat& r){
    arbFloat left = l;
    arbFloat right = r;

    if (l.digits.empty() || r.digits.empty()){
        throw invalid_argument("One of the values is empty in the < operator.");
        return false;
    }

    if (left.sign < right.sign){
        return false;
    }
    else if (left.sign > right.sign){
        return true;
    }

    //outlier case for the algorithm
    if (left.digits.size() == 1 && right.digits.size() == 1){
        if (left.digits[0] >= right.digits[0]){
            return false;
        }
    }

    left.truncate();
    right.truncate();

    if (left.sign == 0 && right.sign == 0){
        if (left.exp < right.exp){
            return true;
        }
        else if (left.exp > right.exp){
            return false;
        }

        if (left.digits.size() > right.digits.size()){
            return true;
        }
        else if (left.digits.size() < right.digits.size()){
            return false;
        }

        int compare = 0;
        for (int i = 0; i < min(left.digits.size(), right.digits.size()); i++){
            if (left.digits[i] < right.digits[i]){
                compare = 1;
                i = left.digits.size();
            }
            else if (left.digits[i] > right.digits[i]){
                compare = -1;
                i = left.digits.size();
            }
        }

        if (compare == 1){
            return true;
        }
        else if (compare == -1){
            return false;
        }
        else{
            return false;
        }
    }
    else if (left.sign == 1 && right.sign == 1){
        if (left.exp > right.exp){
            return true;
        }
        else if (left.exp < right.exp){
            return false;
        }

        if (left.digits.size() > right.digits.size()){
            return true;
        }
        else if (left.digits.size() < right.digits.size()){
            return false;
        }

        int compare = 0;
        for (int i = 0; i < min(left.digits.size(), right.digits.size()); i++){
            if (left.digits[i] > right.digits[i]){
                compare = 1;
                i = left.digits.size();
            }
            else if (left.digits[i] < right.digits[i]){
                compare = -1;
                i = left.digits.size();
            }
        }

        if (compare == 1){
            return true;
        }
        else if (compare == -1){
            return false;
        }
        else{
            return false;
        }
    }
    return false;
}

bool operator>(const arbFloat& l, const arbFloat& r){
    if (l.digits.empty() || r.digits.empty()){
        throw invalid_argument("One of the values is empty in the > operator.");
        return false;
    }

    return (r < l);
};

bool operator<=(const arbFloat& l, const arbFloat& r){
    if (l.digits.empty() || r.digits.empty()){
        throw invalid_argument("One of the values is empty in the <= operator.");
        return false;
    }

    return !(r < l);
};

bool operator>=(const arbFloat& l, const arbFloat& r){
    if (l.digits.empty() || r.digits.empty()){
        throw invalid_argument("One of the values is empty in the >= operator.");
        return false;
    }

    return !(l < r);
};
//Useful functions

void arbFloat::abs_val(){
    sign = 0;
}

void arbFloat::negate(){
    if (sign == 1){
        sign = 0;
    }
    else {
        sign = 1;
    }
}

void arbFloat::truncate(){
    vector<int> newDigits = vec_truncate(digits, exp);
    digits = newDigits;
}

double arb_to_double(arbFloat num){
    double val = 0;
    int store = 17;
    if (num.digits.size() < 17){
        store = num.digits.size();
    }
    for (int i = 0; i < store; i++){
        val += num.digits[i] * pow(10, num.exp - i);
    }
    if (num.sign == 1){
        val *= -1;
    }
    return val;
}


//only prints values of the vector, without any care about where the decimal is 
void arbFloat::print_digits(){
    for (int i = 0; i < digits.size(); i++){
        cout << digits[i];
    }
    cout << endl;
}

//prints number with decimal
void arbFloat::print_number(){

    vector<int> printer = digits;
    printer = vec_round(printer, prec, exp);
    printer = vec_truncate(printer, exp);
    if (digits.empty() == true){
        cout << "Number has no digits\n";
        return;
    }
    if (sign == 1){
        cout << "-";
    }
    if (exp < 0){
        cout << "0.";
        int absExp = exp * -1;
        for(int i = 0; i < absExp - 1; i++){
            cout << "0";
        }
    }
    for (int i = 0; i < printer.size(); i++){
        if (i == exp + 1 && exp >= 0){
            cout << ".";
        }
        cout << printer[i];
    }
    cout << endl;
}

bool arbFloat::is_pos(){
    if(sign == 0){
        return true;
    }
    else {
        return false;
    }
    return false;
}

vector<int> arbFloat::get_digits(){
    return digits;
}

int arbFloat::get_exp(){
    return exp;
}

int arbFloat::get_sign(){
    return sign;
}

//Arithmetic operators

arbFloat operator+(const arbFloat& x, const arbFloat& y){
    if (x.digits.empty() || y.digits.empty()){
        throw invalid_argument("One of the values is empty. Error occured in + operator.");
    }

    //get rid of these and use vec_truncate()
    arbFloat left = x;
    arbFloat right = y;
    left.truncate();
    right.truncate();

    arbFloat sum;

    int maxExp = max(left.exp, right.exp) + 1;
    
    int maxFloat = max(left.digits.size() - left.exp, right.digits.size() - right.exp);


    vector<int> leftDigits = left.digits;
    int diff = maxExp - left.exp;
    leftDigits.insert(leftDigits.begin(), diff, 0);

    diff = maxFloat - (left.digits.size() - left.exp);
    if (diff > 0){
        leftDigits.insert(leftDigits.end(), diff, 0);
    }

    vector<int> rightDigits = right.digits;
    diff = maxExp - right.exp;
    rightDigits.insert(rightDigits.begin(), diff, 0);

    diff = maxFloat - (right.digits.size() - right.exp);
    if (diff > 0){
        rightDigits.insert(rightDigits.end(), diff, 0);
    }

    sum.exp = maxExp;


    //need to add the same for the right digits

    if (right.sign == left.sign){
        sum.sign = left.sign;
        int vecSize = leftDigits.size();
        for(int i = vecSize - 1; i >= 0; i--){
            leftDigits[i] += rightDigits[i];
            if (leftDigits[i] > 9 && i != 0){
                leftDigits[i] = leftDigits[i] % 10;
                leftDigits[i - 1] += 1;
            }
        }
        sum.exp = maxExp;
        if (leftDigits[0] > 0){
            sum.exp += 1;
        }
        else {
            int firstDigit = leftDigits[0];
            while (firstDigit == 0 && !leftDigits.empty()){
                leftDigits.erase(leftDigits.begin());
                firstDigit = leftDigits[0];
                sum.exp -= 1;
        }
        }
    }

    else if (right.sign != left.sign){
        if (leftDigits == rightDigits && left.exp == right.exp){
            return arbFloat::ZERO;
        }

        int vecSize = leftDigits.size();
        for(int i = vecSize - 1; i >= 0; i--){
            leftDigits[i] -= rightDigits[i];
        }

        bool posCheck = false;
        for(int i = 0; i < vecSize; i++){
            if (leftDigits[i] > 0){
                posCheck = true;
                i = vecSize;
            }
            else if (leftDigits[i] < 0){
                i = vecSize;
            }
        }
        
        if (posCheck == true){
            sum.sign = left.sign;
            for(int i = vecSize - 1; i >= 0; i--){
                if (leftDigits[i] < 0 && i != 0){
                    leftDigits[i] += 10;
                    leftDigits[i - 1] -= 1;
                }
            }
        }
    
        else {
            sum.sign = right.sign;
            for(int i = vecSize - 1; i >= 0; i--){
                if (leftDigits[i] > 0 && i != 0){
                    leftDigits[i] -= 10;
                    leftDigits[i - 1] += 1;
                }
                if (leftDigits[i] < 0){
                    leftDigits[i] *= -1;
                }
            }
        }
        int firstDigit = leftDigits[0];
        int digSize = leftDigits.size();
        while (firstDigit == 0 && digSize > 1){
            leftDigits.erase(leftDigits.begin());
            firstDigit = leftDigits[0];
            digSize = leftDigits.size();
            sum.exp -= 1;
        }
    }
    sum.digits = leftDigits;
    sum.truncate();
    return sum;
}

arbFloat operator-(const arbFloat& x, const arbFloat& y){
    if (x.digits.empty() || y.digits.empty()){
        throw invalid_argument("One of the values is empty. Error occured in - operator.");
    }
    arbFloat negY = y;
    negY.negate();

    arbFloat difference = x + negY;

    return difference;
}


//Needs minor tweaks
arbFloat operator*(const arbFloat& x, const arbFloat& y){
    if (x.digits.empty() || y.digits.empty()){
        throw invalid_argument("One of the values is empty. Error occured in - operator.");
    }

    if (x == arbFloat::ZERO || y == arbFloat::ZERO){
        return arbFloat::ZERO;
    }

    vector<int> leftDigits = x.digits;
    vector<int> rightDigits = y.digits;
    vector<int> productDigits;

    int overflow = 0;
    productDigits = digitsProduct(leftDigits, rightDigits, overflow);

    arbFloat product;
    product.digits = productDigits;
    if (x.sign == y.sign){
        product.sign = 0;
    }
    else {
        product.sign = 1;
    }
    
    product.exp = x.exp + y.exp + 1 + overflow;
    product.truncate();

    int digSize = product.digits.size();
    int firstDig = product.digits[0];

    while(digSize > 1 && firstDig == 0){
        product.digits.erase(product.digits.begin());
        product.exp -= 1;
        digSize = product.digits.size();
        firstDig = product.digits[0];
    }
    return product;
}

arbFloat operator/(const arbFloat& x, const arbFloat& y){
    if (x.digits.empty() || y.digits.empty()){
        throw invalid_argument("One of the values is empty. Error occured in - operator.");
    }
    if (y == arbFloat::ZERO){
        throw invalid_argument("Division by zero");
    }
    if (x == arbFloat::ZERO){
        return arbFloat::ZERO;
    }

    arbFloat num = x;
    arbFloat den = y;
    den.sign = 0;
    arbFloat d = den;

    //Haven't checked/debugged vec_cut();
    if (d.digits.size() > 17){
        d.digits = vec_round(d.digits, 17, d.exp);
        if (d.digits.size() > 17){
            d.exp += 1;
        }
    }
    double val = arb_to_double(d);
    val = 1 / val;
    arbFloat reciprocal(18, val);
    reciprocal.sign = 0;
    int recSize = reciprocal.digits.size();
    arbFloat check = arbFloat::ZERO;
    while (recSize <= MAX_PREC && check != reciprocal){
        check = reciprocal;
        reciprocal = reciprocal * (arbFloat::TWO - (den * reciprocal));
        reciprocal.truncate();
        if (reciprocal.digits.size() > MAX_PREC){
            reciprocal.digits = vec_round(reciprocal.digits, MAX_PREC, reciprocal.exp);
            if (reciprocal.digits.size() > MAX_PREC){
                reciprocal.exp += 1;
            }
        }
        recSize = reciprocal.digits.size();
    }
    reciprocal = x * reciprocal;

    if (x.sign == y.sign){
        reciprocal.sign = 0;        
    }
    else {
        reciprocal.sign = 1;
    }

    return reciprocal;
}