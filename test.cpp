#include "arbFloat.h"
#include <chrono>
#include <random>

using namespace std;


int test_constructors(){
    cout << "TESTING CONSTRUCTORS\n";
    cout << "----------------------------------------" << endl;
    cout << "a1" << endl;
    cout << "     Create an empty arbFloat" << endl;
    cout << "----------------------------------------" << endl;

    //NEED TO FIX PRINT NUMBER FOR THIS TEST CASE
    arbFloat a1;
    cout << "SUCCESS" << endl;
    cout << "----------------------------------------" << endl;
    cout << "a2" << endl;
    cout << "     Create an arbFloat with a positive integer" << endl;
    cout << "----------------------------------------" << endl;
    arbFloat a2(5,450);
    a2.print_number();

    cout << "----------------------------------------" << endl;
    cout << "a3" << endl;
    cout << "     Create an arbFloat with a negative integer" << endl;
    cout << "----------------------------------------" << endl;
    arbFloat a3(5,-450);
    a3.print_number();

    cout << "----------------------------------------" << endl;
    cout << "a4" << endl;
    cout << "     Create an arbFloat with a positive double" << endl;
    cout << "----------------------------------------" << endl;
    arbFloat a4(7,186.5198);
    a4.print_number();
    
    cout << "----------------------------------------" << endl;
    cout << "a5" << endl;
    cout << "     Create an arbFloat with a negative double" << endl;
    cout << "----------------------------------------" << endl;
    arbFloat a5(7,-48.6981);
    a5.print_number();
    cout << "----------------------------------------" << endl;

    // cout << "----------------------------------------" << endl;
    // cout << "a6" << endl;
    // cout << "     Create an arbFloat with a positive float" << endl;
    // cout << "----------------------------------------" << endl;
    // float f = 68.597;
    // arbFloat a6(7,f);
    // a6.print_number();
    // cout << "----------------------------------------" << endl;
    // cout << "a7" << endl;
    // cout << "     Create an arbFloat with a positive float" << endl;
    // cout << "----------------------------------------" << endl;
    // float f2 = -35.891;
    // arbFloat a7(7,f2);
    // a7.print_number();
    cout << "----------------------------------------" << endl;
    cout << "a6" << endl;
    cout << "     Create an arbFloat with a long double" << endl;
    cout << "----------------------------------------" << endl;
    long double ld = -49.513897151649786315L;
    arbFloat a6(20,ld);
    a6.print_number();
    cout << "----------------------------------------" << endl;
    cout << "a7" << endl;
    cout << "     Create an arbFloat with a long int" << endl;
    cout << "----------------------------------------" << endl;
    long double li = 3153156485L;
    arbFloat a7(20,li);
    a7.print_number();
    cout << "----------------------------------------" << endl;
    cout << "a7" << endl;
    cout << "     Create an arbFloat with a string" << endl;
    cout << "----------------------------------------" << endl;
    string s = "-16839.05549103";
    int strSize = s.size();
    arbFloat a8(strSize,s);
    a8.print_number();

    cout << "CONSTRUCTOR TEST END" << endl;
    cout << "----------------------------------------" << endl << endl << endl;
    return 0;
}

int test_arithmetic(){
    cout << "TESTING ARITHMETIC\n";
    cout << "----------------------------------------" << endl;
    cout << "     Create two positive and two negative numbers and test all arithmetic operators between them\n";
    cout << "----------------------------------------" << endl;
    arbFloat p1(5, 480.31);
    arbFloat p2(6,8.69816);
    arbFloat n1(8, -893.15);
    arbFloat n2(5,-.605);
    arbFloat store;
    cout << "Positive numbers:\n";
    cout << "p1 = ";
    p1.print_number();
    cout << "p2 = ";
    p2.print_number();


    cout << "Negative numbers:\n";

    cout << "n1 = ";
    n1.print_number();
    cout << "n2 = ";
    n2.print_number();

    cout << "----------------------------------------" << endl;
    cout << " + operator\n";
    store = p1 + p2;
    cout << "p1 + p2 = ";
    store.print_number();
    store = n1 + n2;
    cout << "n1 + n2 = ";
    store.print_number();
    store = p1 + n1;
    cout << "p1 + n1 = ";
    store.print_number();
    cout << "----------------------------------------" << endl;
    cout << " - operator\n";
    store = p1 - p2;
    cout << "p1 - p2 = ";
    store.print_number();
    store = n1 - n2;
    cout << "n1 - n2 = ";
    store.print_number();
    store = p1 - n1;
    cout << "p1 - n1 = ";
    store.print_number();
    cout << "----------------------------------------" << endl;
    cout << " * operator\n";
    store = p1 * p2;
    cout << "p1 * p2 = ";
    store.print_number();
    store = n1 * n2;
    cout << "n1 * n2 = ";
    store.print_number();
    store = p1 * n1;
    cout << "p1 * n1 = ";
    store.print_number();
    cout << "----------------------------------------" << endl;
    cout << " / operator\n";
    store = p1 / p2;
    cout << "p1 / p2 = ";
    store.print_number();
    store = n1 / n2;
    cout << "n1 / n2 = ";
    store.print_number();
    store = p1 / n1;
    cout << "p1 / n1 = ";
    store.print_number();

    return 0;
}


int test_timings(int num, double range){
    cout << "----------------------------------------" << endl;
    cout << "TEST TIMINGS\nTaking an average of " << num << " different cases." << endl;
    cout << "Range of numbers = +/-" << range << endl;
    cout << "----------------------------------------" << endl << endl;
    cout << " + operator\n";

    int negRange = -1 * range;

    uniform_real_distribution<double> dist(negRange,range);
    arbFloat store;

    double totalTime = 0;
    random_device r;
    for (int i = 0; i < num; i++){
        //generate two arbFloats randomly
        mt19937 r1(r());
        mt19937 r2(r())
;       double randNum1 = dist(r1);
        double randNum2 = dist(r2);

        string s1 = to_string(randNum1);
        string s2 = to_string(randNum2);

        arbFloat rand1(s1.size(), randNum1);
        arbFloat rand2(s2.size(), randNum2);

        //time the function
        auto start = chrono::steady_clock::now();
        store = rand1 + rand2;
        auto end = chrono::steady_clock::now();

        chrono::duration<double, milli> time = end - start;
        totalTime += time.count();

        //add the time to a double value
    }
    //take the total time and divide it by num

    double avgTime = totalTime / num;

    cout << "...\naverage time for + is " << avgTime << " milliseconds.\n";
    cout << "----------------------------------------" << endl << endl;
    cout << " - operator\n";

    totalTime = 0;
    
    for (int i = 0; i < num; i++){
        mt19937 r1(r());
        mt19937 r2(r())
;       double randNum1 = dist(r1);
        double randNum2 = dist(r2);

        string s1 = to_string(randNum1);
        string s2 = to_string(randNum2);

        arbFloat rand1(s1.size(), randNum1);
        arbFloat rand2(s2.size(), randNum2);

        auto start = chrono::steady_clock::now();
        store = rand1 - rand2;
        auto end = chrono::steady_clock::now();

        chrono::duration<double, milli> time = end - start;
        totalTime += time.count();
    }
    avgTime = totalTime / num;
    cout << "...\naverage time for - is " << avgTime << " milliseconds.\n";
    cout << "----------------------------------------" << endl << endl;
    cout << " * operator\n";

    totalTime = 0;
    
    for (int i = 0; i < num; i++){
        mt19937 r1(r());
        mt19937 r2(r())
;       double randNum1 = dist(r1);
        double randNum2 = dist(r2);

        string s1 = to_string(randNum1);
        string s2 = to_string(randNum2);

        arbFloat rand1(s1.size(), randNum1);
        arbFloat rand2(s2.size(), randNum2);

        auto start = chrono::steady_clock::now();
        store = rand1 * rand2;
        auto end = chrono::steady_clock::now();

        chrono::duration<double, milli> time = end - start;
        totalTime += time.count();
    }
    avgTime = totalTime / num;
    cout << "...\naverage time for * is " << avgTime << " milliseconds.\n";
    cout << "----------------------------------------" << endl << endl;
    cout << " / operator\n";

    totalTime = 0;
    
    for (int i = 0; i < num; i++){
        mt19937 r1(r());
        mt19937 r2(r())
;       double randNum1 = dist(r1);
        double randNum2 = dist(r2);

        string s1 = to_string(randNum1);
        string s2 = to_string(randNum2);

        arbFloat rand1(s1.size(), randNum1);
        arbFloat rand2(s2.size(), randNum2);

        auto start = chrono::steady_clock::now();
        store = rand1 / rand2;
        auto end = chrono::steady_clock::now();

        chrono::duration<double, milli> time = end - start;
        totalTime += time.count();
    }
    avgTime = totalTime / num;
    cout << "...\naverage time for / is " << avgTime << " milliseconds.\n";
    return 0;
}
vector<int> vec_truncate2(vector<int> vec, int exp){
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


int main(){

    test_constructors();

    test_arithmetic();

    test_timings(1000, 1e20);


    vector<int> vec {1, 0, 0, 0, 0};
    vec = vec_truncate2(vec, 0);

    cout << "vec.size = " << vec.size() << endl;


    cout << endl << endl << endl << "Additional test to ensure that division and multiplication behave properly\n";
    arbFloat v(1,1);
    arbFloat v2(1,3);
    v = v / v2;
    v.print_number();
    v = v * v2;
    v.print_number();

    arbFloat rt;
    rt = rt2(arbFloat::TWO);
    rt.print_number();
    cout << "Finished testing" << endl;

    arbFloat smallrt(1, 4);
    smallrt = rt2(smallrt);
    smallrt.print_number();
    arbFloat smallrt2(2, 10);
    smallrt2 = rt2(smallrt2);
    smallrt2.print_number();

    // cout << "testing pi\n";

    // arbFloat p = arbFloat::PI;
    // p.print_number();
    return 0;
}


// int main(){
//     arbFloat e = arbFloat::E;
//     e.print_number();

//     cout << endl;

//     arbFloat o(6, 362880);
//     arbFloat o2(7, 3628800);
//     o = arbFloat::ONE / o;
//     o2 = arbFloat::ONE / o2;
//     if (o == o2){
//         cout << "equal" << endl;
//     }
//     else {
//         cout << "not equal" << endl;
//     }
//     o.print_number();
//     o2.print_number();

//     arbFloat nine(1,-9);
//     nine.print_number();
//     nine = nine - arbFloat::ONE;
//     nine.print_number();


//     // arbFloat one(18, 1.0);
//     // arbFloat big(18, 3628800.0);
//     // arbFloat result = one / big;
//     // result.print_number();  // Should print: 2.755731922398589e-6 (not 0)

//     return 0;
// }


// int main(){
//     arbFloat tw(1,2);
//     arbFloat r = pow(tw, 2);
//     r.print_number();
//     r = rt2(r);
//     r.print_number();
//     r = pow(tw, 0);
//     r.print_number();
//     r = pow(tw, -4);
//     r.print_number();
// }