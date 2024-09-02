#include "Relu.h"

SC_MODULE(Relu_TB)
{
	sc_in<sc_lv<8>> input0;
	sc_in<sc_lv<8>> input1;
	sc_in<sc_lv<8>> input2;
	sc_in<sc_lv<8>> input3;
	sc_out<sc_lv<8>> output0;
	sc_out<sc_lv<8>> output1;
	sc_out<sc_lv<8>> output2;
	sc_out<sc_lv<8>> output3;

	Relu* R1;

	SC_CTOR(Relu_TB)
	{
		R1 = new Relu("Relu_Instance");
		R1->input0(input0);
		R1->input1(input1);
		R1->input2(input2);
		R1->input3(input3);
		R1->output0(output0);
		R1->output1(output1);
		R1->output2(output2);
		R1->output3(output3);

	}
};