#pragma once
#include <systemc.h>
#include "util.h"
#include "Convolution.h"

// Define specific values for the template parameters
const int el1 = 0;
const int el2 = -1;
const int el3 = 0;
const int el4 = -1;
const int el5 = 5;
const int el6 = -1;
const int el7 = 0;
const int el8 = -1;
const int el9 = 0;
const int DATA_WIDTH = 8;
const int KERNEL_WIDTH = 3;
const int IMAGE_WIDTH = 4;
const int STRIDE = 1;
const int BIAS = 5;

// Define the testbench module
SC_MODULE(Convolution_TB) {
	// Clock and reset signals
	sc_signal<bool> clk;
	sc_signal<bool> rst;
	sc_signal<bool> conv_start;
	sc_signal<bool> conv_done;
	sc_signal<sc_lv<DATA_WIDTH>> output0;
	sc_signal<sc_lv<DATA_WIDTH>> output1;
	sc_signal<sc_lv<DATA_WIDTH>> output2;
	sc_signal<sc_lv<DATA_WIDTH>> output3;
	sc_signal<bool> read_img;
	sc_signal<sc_lv<4>> address;
	sc_signal<sc_lv<4>> state_show;
	sc_signal<sc_lv<DATA_WIDTH>> input;
	//sc_signal<sc_lv<8>> count_i;
	//sc_signal<sc_lv<8>> count_j;

	sc_signal<sc_lv<8>> img1;
	sc_signal<sc_lv<8>> img2;
	sc_signal<sc_lv<8>> img3;
	sc_signal<sc_lv<8>> img4;
	sc_signal<sc_lv<8>> img5;
	sc_signal<sc_lv<8>> img6;
	sc_signal<sc_lv<8>> img7;
	sc_signal<sc_lv<8>> img8;
	sc_signal<sc_lv<8>> img9;
	sc_signal<sc_lv<8>> img10;
	sc_signal<sc_lv<8>> img11;
	sc_signal<sc_lv<8>> img12;
	sc_signal<sc_lv<8>> img13;
	sc_signal<sc_lv<8>> img14;
	sc_signal<sc_lv<8>> img15;
	sc_signal<sc_lv<8>> img16;

	// Convolution module instantiation
	Convolution < el1, el2, el3,
		el4, el5, el6,
		el7, el8, el9,
		DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS> *conv;

	SC_CTOR(Convolution_TB)

	{
		// Bind signals to the convolution module
		conv = new Convolution < el1, el2, el3,
			el4, el5, el6,
			el7, el8, el9,
			DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS>("Convolution1");
		conv->clk(clk);
		conv->rst(rst);
		conv->conv_start(conv_start);
		conv->conv_done(conv_done);
		conv->output0(output0);
		conv->output1(output1);
		conv->output2(output2);
		conv->output3(output3);
		conv->read_img(read_img);
		conv->address(address);
		conv->input(input);
		//conv->state_show(state_show);
		//conv->count_i(count_i);
		//conv->count_j(count_j);

		conv->img1(img1);
		conv->img2(img2);
		conv->img3(img3);
		conv->img4(img4);
		conv->img5(img5);
		conv->img6(img6);
		conv->img7(img7);
		conv->img8(img8);
		conv->img9(img9);
		conv->img10(img10);
		conv->img11(img11);
		conv->img12(img12);
		conv->img13(img13);
		conv->img14(img14);
		conv->img15(img15);
		conv->img16(img16);

		SC_THREAD(clockGeneration);
		SC_THREAD(data_gen);
		//sensitive << clk.posedge_event();
		SC_THREAD(generate_signals);
		sensitive << clk.posedge_event();

		SC_THREAD(monitor_signals);
		sensitive << clk.posedge_event();


	}
	void generate_signals();
	void monitor_signals();
	void clockGeneration();
	void data_gen();
};
