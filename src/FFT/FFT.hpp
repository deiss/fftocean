/*

Project: Ocean
Author: DEISS Olivier

This software is offered under the GPL license. See COPYING for more information.

*/

#include <iostream>
#include <vector>

class FFT {

    public :
    
        FFT()                                                             { }
        FFT(int, std::vector<double>, std::vector<double>);
        void calculD()                                                     { sort(); radixDirect(); }
        void calculR()                                                     { sort(); radixReverse(); }
        void getResult(std::vector<double> *xR, std::vector<double> *xI) { *xR = _xR; *xI = _xI; }
    
    private :
    
        void radixDirect();
        void radixReverse();
        void sort();

        double                _cos;
        int                    _index1;
        int                    _index2;
        int                    _n;
        int                    _p;
        double                _sin;
        double                _var1;
        double                _var2;
        double                _var3;
        double                _var4;
        double                _var5;
        std::vector<double> _vectR;
        std::vector<double> _vectI;
        std::vector<double> _vectRp;
        std::vector<double> _vectIp;
        std::vector<double> _vectRi;
        std::vector<double> _vectIi;
        std::vector<double> _xR;
        std::vector<double> _xI;
    
};
