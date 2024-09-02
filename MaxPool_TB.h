#include "MaxPool.h"

SC_MODULE(MaxPool_TB)
{
	sc_in<sc_lv<8>> input0, input1, input2, input3;
	sc_out<sc_lv<8>> output;

	MaxPool* M1;

	SC_CTOR(MaxPool_TB)
	{
		M1 = new MaxPool("MaxPool_Instance");
		M1->input0(input0);
		M1->input1(input1);
		M1->input2(input2);
		M1->input3(input3);
		M1->output(output);


	}
};