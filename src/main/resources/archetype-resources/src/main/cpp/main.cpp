set( $H = '#' )
$Hinclude <iostream>
$Hinclude "Calculator.hpp"
using namespace std;

int main(){
	Calculator calc;
	cout << calc.sum(2,2);
	return 0;
}
