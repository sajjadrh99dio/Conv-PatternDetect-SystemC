#include <systemc.h>
#include "Result_TB.h"

int sc_main(int argc, char* argv[]) {
	sc_signal<sc_lv<8>> input0;
	sc_signal<sc_lv<8>> input1;
	sc_signal<sc_lv<8>> input2;
	sc_signal<sc_lv<3>> output;
	//sc_signal<sc_lv<8>> output_temp;

	Result_TB result("result");
	result.input0(input0);
	result.input1(input1);
	result.input2(input2);
	result.output(output);

	//result.output_temp(output_temp);

	sc_start(1, SC_NS); 


	input0.write("00000001"); // 10
	input1.write("00000011"); // 5
	input2.write("00000010"); // 12
	sc_start(1, SC_NS); 

	std::cout << "Output: " << output.read() << std::endl;
	//std::cout << "Output_temp: " << output_temp.read() << std::endl;

	input0.write("00000011"); // 5
	input1.write("00000001"); // 10
	input2.write("00000110"); // 12
	sc_start(1, SC_NS); 

	std::cout << "Output: " << output.read() << std::endl;
	//std::cout << "Output_temp: " << output_temp.read() << std::endl;
	return 0;
}
