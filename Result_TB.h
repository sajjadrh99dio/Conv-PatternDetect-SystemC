#include "Result.h"

SC_MODULE(Result_TB)
{
	sc_in<sc_lv<8>> input0;
	sc_in<sc_lv<8>> input1;
	sc_in<sc_lv<8>> input2;
	sc_out<sc_lv<3>> output;

	Result* R1;

	SC_CTOR(Result_TB)
	{
		R1 = new Result("Result1_Instance");
		R1->input0(input0);
		R1->input1(input1);
		R1->input2(input2);
		R1->output(output);

	}
};