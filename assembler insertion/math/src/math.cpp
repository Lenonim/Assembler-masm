#include <iostream>
#include <typeinfo>

int global_func(int x, int y, int z) {
    int b_fir = 9;
    int b_sec = -1;

    int temp = int();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int f = 6;

    __asm {
        finit
        fild x
        fiadd y

        ficom b_fir; x + y ? > 9
        fstsw ax
        sahf
        jnc _ch_fir_fl
        fistp temp

        fild x
        fiadd y

        ficom b_sec; x + y ? < -1
        fstsw ax
        sahf
        jc _ch_sec_fl
        fistp temp

;//------------ third_func
                fild y; st0 = y
                fimul b; st0 = 2y
                fistp temp; temp = st0

                fild x; st0 = x
                fimul x; st0 = x2
                fimul c; st0 = 3x2
                fisub temp; st0 = 3x2 - 2y
                fiadd f; st0 = 3x2 - 2y + 6

                fistp z; z = st0
;//------------ end third_func

        jmp _out_fir_ch
            _ch_sec_fl :
        fistp temp

;//---------------- second_func
                    ; знаменатель
                    fild y; st0 = y
                    fimul y; st0 = y2
                    fimul c; st0 = 3y2 
                    fistp temp; temp = st0

                    fild x; st0 = x
                    fimul x; st0 = x2
                    fiadd temp; st0 = x2 + 3y2 
                    fiadd a; st0 = x2 + 3y2 + 1

                    fistp z; z = st0

                    ; числитель
                    fild x; st0 = x
                    fimul y; st0 = xy
                    fimul b; st0 = 2xy
                    fiadd c; st0 = 2xy + 3
                    fiadd x; st0 = 2xy + 3 + x

                    ; результат
                    fidiv z; st0 = st0 / z
                    fistp z; z = st0
;//---------------- end second_func

        jmp _out_fir_ch

            _ch_fir_fl :
        fistp temp

;//------------ first_func 
                fild y; st0 = y
                fimul d; st0 = 4y
                fistp temp; temp = st0

                fild x; st0 = x
                fimul y; st0 = xy
                fimul f; st0 = 6xy
                fisub temp; st0 = 6xy - 4y

                fistp z; z = st0
;//------------ end first_func

    _out_fir_ch:
    }
    return z;
}

double global_func(double x, double y, double z) {
    double b_fir = 9.0;
    double b_sec = -1.0;

    double temp = double();

    double a = 1.0;
    double b = 2.0;
    double c = 3.0;
    double d = 4.0;
    double f = 6.0;

    __asm {
        fld x
        fadd y

        fcom b_fir; x + y ? > 9
        fstsw ax
        sahf
        jnc _ch_fir_fl
        fstp temp

        fld x
        fadd y

        fcom b_sec; x + y ? < -1
        fstsw ax
        sahf
        jc _ch_sec_fl
        fstp temp

;//------------ third_func
                fld y; st0 = y
                fmul b; st0 = 2y
                fstp temp; temp = st0

                fld x; st0 = x
                fmul x; st0 = x2
                fmul c; st0 = 3x2
                fsub temp; st0 = 3x2 - 2y
                fadd f; st0 = 3x2 - 2y + 6

                fstp z; z = st0
;//------------ end third_func

        jmp _out_fir_ch
            _ch_sec_fl :
        fstp temp

;//---------------- second_func
                    ; знаменатель
                    fld y; st0 = y
                    fmul y; st0 = y2
                    fmul c; st0 = 3y2 
                    fstp temp; temp = st0

                    fld x; st0 = x
                    fmul x; st0 = x2
                    fadd temp; st0 = x2 + 3y2 
                    fadd a; st0 = x2 + 3y2 + 1

                    fstp z; z = st0

                    ; числитель
                    fld x; st0 = x
                    fmul y; st0 = xy
                    fmul b; st0 = 2xy
                    fadd c; st0 = 2xy + 3
                    fadd x; st0 = 2xy + 3 + x

                    ; результат
                    fdiv z; st0 = st0 / z
                    fstp z; z = st0
;//---------------- end second_func

        jmp _out_fir_ch

            _ch_fir_fl :
        fstp temp

;//------------ first_func 
                fld y; st0 = y
                fmul d; st0 = 4y
                fstp temp; temp = st0

                fld x; st0 = x
                fmul y; st0 = xy
                fmul f; st0 = 6xy
                fsub temp; st0 = 6xy - 4y

                fstp z; z = st0
;//------------ end first_func

    _out_fir_ch:
    }
    return z;
}

int main() {
    double x;
    std::cout << "Enter x: ";
    std::cin >> x;

    double y;
    std::cout << "Enter y: ";
    std::cin >> y;

    double z = double();
    z = global_func(x, y, z);
    std::cout << "Result: " << z << " type: " << typeid(z).name() << "\n";

    return 0;
}

