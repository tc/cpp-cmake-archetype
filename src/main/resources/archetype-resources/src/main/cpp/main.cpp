#set( $H = '#' )
${H}include <iostream>
${H}include "Calculator.h"
using namespace std;

int main(){
	Calculator calc;
	cout << calc.sum(2,2);
	return 0;
}
