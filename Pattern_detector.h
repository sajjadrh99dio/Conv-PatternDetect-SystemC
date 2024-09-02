#pragma once
#include <systemc.h>
#include "Img_RAM.h"
#include "Convolution.h"
#include "Relu.h"
#include "MaxPool.h"
#include "Result.h"


const int DATA_WIDTH = 8;
const int KERNEL_WIDTH = 3;
const int IMAGE_WIDTH = 4;
const int STRIDE = 1;


const int el11 = 0;
const int el21 = 1;
const int el31 = 0;
const int el41 = 1;
const int el51 = 1;
const int el61 = 1;
const int el71 = 0;
const int el81 = 1;
const int el91 = 0;
const int BIAS1 = -1;

const int el12 = 1;
const int el22 = 1;
const int el32 = 1;
const int el42 = 1;
const int el52 = 0;
const int el62 = 0;
const int el72 = 1;
const int el82 = 1;
const int el92 = 1;
const int BIAS2 = -2;

const int el13 = 1;
const int el23 = 1;
const int el33 = 1;
const int el43 = 0;
const int el53 = 1;
const int el63 = 0;
const int el73 = 0;
const int el83 = 1;
const int el93 = 0;
const int BIAS3 = -2;

SC_MODULE(Pattern_detector) {
	sc_signal<bool> clk;
	sc_signal<bool> rst;
	sc_signal<bool> conv_start, conv_start2, conv_start3;
	sc_signal<sc_lv<8>> data_in;
	sc_signal<sc_lv<4>> addr_wr;
	sc_signal<bool> write_enable;
	sc_signal<bool> done;
	sc_signal<sc_lv<3>> Final_Result;

	// Internal signals
	sc_signal<sc_lv<8>> data_rd1, data_rd2, data_rd3;
	sc_signal<sc_lv<4>> addr_rd1, addr_rd2, addr_rd3;
	sc_signal<bool> read1, read2, read3;
	sc_signal<sc_lv<8>> output_conv1_0, output_conv1_1, output_conv1_2, output_conv1_3;
	sc_signal<sc_lv<8>> output_conv2_0, output_conv2_1, output_conv2_2, output_conv2_3;
	sc_signal<sc_lv<8>> output_conv3_0, output_conv3_1, output_conv3_2, output_conv3_3;
	sc_signal<bool> conv_done1, conv_done2, conv_done3;
	sc_signal<sc_lv<8>> relu1_out0, relu1_out1, relu1_out2, relu1_out3;
	sc_signal<sc_lv<8>> relu2_out0, relu2_out1, relu2_out2, relu2_out3;
	sc_signal<sc_lv<8>> relu3_out0, relu3_out1, relu3_out2, relu3_out3;
	sc_signal<sc_lv<8>> MaxPool1_out, MaxPool2_out, MaxPool3_out;
	sc_signal<sc_lv<3>> result_out;

	sc_signal<sc_lv<8>> img11;
	sc_signal<sc_lv<8>> img21;
	sc_signal<sc_lv<8>> img31;
	sc_signal<sc_lv<8>> img41;
	sc_signal<sc_lv<8>> img51;
	sc_signal<sc_lv<8>> img61;
	sc_signal<sc_lv<8>> img71;
	sc_signal<sc_lv<8>> img81;
	sc_signal<sc_lv<8>> img91;
	sc_signal<sc_lv<8>> img101;
	sc_signal<sc_lv<8>> img111;
	sc_signal<sc_lv<8>> img121;
	sc_signal<sc_lv<8>> img131;
	sc_signal<sc_lv<8>> img141;
	sc_signal<sc_lv<8>> img151;
	sc_signal<sc_lv<8>> img161;

	sc_signal<sc_lv<8>> img12;
	sc_signal<sc_lv<8>> img22;
	sc_signal<sc_lv<8>> img32;
	sc_signal<sc_lv<8>> img42;
	sc_signal<sc_lv<8>> img52;
	sc_signal<sc_lv<8>> img62;
	sc_signal<sc_lv<8>> img72;
	sc_signal<sc_lv<8>> img82;
	sc_signal<sc_lv<8>> img92;
	sc_signal<sc_lv<8>> img102;
	sc_signal<sc_lv<8>> img112;
	sc_signal<sc_lv<8>> img122;
	sc_signal<sc_lv<8>> img132;
	sc_signal<sc_lv<8>> img142;
	sc_signal<sc_lv<8>> img152;
	sc_signal<sc_lv<8>> img162;

	sc_signal<sc_lv<8>> img13;
	sc_signal<sc_lv<8>> img23;
	sc_signal<sc_lv<8>> img33;
	sc_signal<sc_lv<8>> img43;
	sc_signal<sc_lv<8>> img53;
	sc_signal<sc_lv<8>> img63;
	sc_signal<sc_lv<8>> img73;
	sc_signal<sc_lv<8>> img83;
	sc_signal<sc_lv<8>> img93;
	sc_signal<sc_lv<8>> img103;
	sc_signal<sc_lv<8>> img113;
	sc_signal<sc_lv<8>> img123;
	sc_signal<sc_lv<8>> img133;
	sc_signal<sc_lv<8>> img143;
	sc_signal<sc_lv<8>> img153;
	sc_signal<sc_lv<8>> img163;

	// Component instantiation
	Img_RAM* ram1;
	Relu* relu1;
	Relu* relu2;
	Relu* relu3;
	MaxPool* maxpool1;
	MaxPool* maxpool2;
	MaxPool* maxpool3;
	Result* result1;
	Convolution<el11, el21, el31, el41, el51, el61, el71, el81, el91, DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS1>* conv1;
	Convolution<el12, el22, el32, el42, el52, el62, el72, el82, el92, DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS2>* conv2;
	Convolution<el13, el23, el33, el43, el53, el63, el73, el83, el93, DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS3>* conv3;

	SC_CTOR(Pattern_detector) {
		
		ram1 = new Img_RAM("RAM1");
		ram1->clk(clk);
		ram1->rst(rst);
		ram1->data_in(data_in);
		ram1->addr_wr(addr_wr);
		ram1->write_enable(write_enable);
		ram1->data_rd1(data_rd1);
		ram1->addr_rd1(addr_rd1);
		ram1->read1(read1);
		ram1->data_rd2(data_rd2);
		ram1->addr_rd2(addr_rd2);
		ram1->read2(read2);
		ram1->data_rd3(data_rd3);
		ram1->addr_rd3(addr_rd3);
		ram1->read3(read3);
		
		conv1 = new Convolution<el11, el21, el31, el41, el51, el61, el71, el81, el91, DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS1>("Convolution1");
		conv1->clk(clk);
		conv1->rst(rst);
		conv1->conv_start(conv_start);
		conv1->conv_done(conv_done1);
		conv1->output0(output_conv1_0);
		conv1->output1(output_conv1_1);
		conv1->output2(output_conv1_2);
		conv1->output3(output_conv1_3);
		conv1->read_img(read1);
		conv1->address(addr_rd1);
		conv1->input(data_rd1);

		conv1->img1(img11);
		conv1->img2(img21);
		conv1->img3(img31);
		conv1->img4(img41);
		conv1->img5(img51);
		conv1->img6(img61);
		conv1->img7(img71);
		conv1->img8(img81);
		conv1->img9(img91);
		conv1->img10(img101);
		conv1->img11(img111);
		conv1->img12(img121);
		conv1->img13(img131);
		conv1->img14(img141);
		conv1->img15(img151);
		conv1->img16(img161);

		conv2 = new Convolution<el12, el22, el32, el42, el52, el62, el72, el82, el92, DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS2>("Convolution2");
		conv2->clk(clk);
		conv2->rst(rst);
		conv2->conv_start(conv_start2);
		conv2->conv_done(conv_done2);
		conv2->output0(output_conv2_0);
		conv2->output1(output_conv2_1);
		conv2->output2(output_conv2_2);
		conv2->output3(output_conv2_3);
		conv2->read_img(read2);
		conv2->address(addr_rd2);
		conv2->input(data_rd2);

		conv2->img1(img12);
		conv2->img2(img22);
		conv2->img3(img32);
		conv2->img4(img42);
		conv2->img5(img52);
		conv2->img6(img62);
		conv2->img7(img72);
		conv2->img8(img82);
		conv2->img9(img92);
		conv2->img10(img102);
		conv2->img11(img112);
		conv2->img12(img122);
		conv2->img13(img132);
		conv2->img14(img142);
		conv2->img15(img152);
		conv2->img16(img162);

		conv3 = new Convolution<el13, el23, el33, el43, el53, el63, el73, el83, el93, DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS3>("Convolution3");
		conv3->clk(clk);
		conv3->rst(rst);
		conv3->conv_start(conv_start3);
		conv3->conv_done(conv_done3);
		conv3->output0(output_conv3_0);
		conv3->output1(output_conv3_1);
		conv3->output2(output_conv3_2);
		conv3->output3(output_conv3_3);
		conv3->read_img(read3);
		conv3->address(addr_rd3);
		conv3->input(data_rd3);

		conv3->img1(img13);
		conv3->img2(img23);
		conv3->img3(img33);
		conv3->img4(img43);
		conv3->img5(img53);
		conv3->img6(img63);
		conv3->img7(img73);
		conv3->img8(img83);
		conv3->img9(img93);
		conv3->img10(img103);
		conv3->img11(img113);
		conv3->img12(img123);
		conv3->img13(img133);
		conv3->img14(img143);
		conv3->img15(img153);
		conv3->img16(img163);

		relu1 = new Relu("Relu1");
		relu1->input0(output_conv1_0);
		relu1->input1(output_conv1_1);
		relu1->input2(output_conv1_2);
		relu1->input3(output_conv1_3);
		relu1->output0(relu1_out0);
		relu1->output1(relu1_out1);
		relu1->output2(relu1_out2);
		relu1->output3(relu1_out3);

		relu2 = new Relu("Relu2");
		relu2->input0(output_conv2_0);
		relu2->input1(output_conv2_1);
		relu2->input2(output_conv2_2);
		relu2->input3(output_conv2_3);
		relu2->output0(relu2_out0);
		relu2->output1(relu2_out1);
		relu2->output2(relu2_out2);
		relu2->output3(relu2_out3);

		relu3 = new Relu("Relu3");
		relu3->input0(output_conv3_0);
		relu3->input1(output_conv3_1);
		relu3->input2(output_conv3_2);
		relu3->input3(output_conv3_3);
		relu3->output0(relu3_out0);
		relu3->output1(relu3_out1);
		relu3->output2(relu3_out2);
		relu3->output3(relu3_out3);

		maxpool1 = new MaxPool("MaxPool1");
		maxpool1->input0(relu1_out0);
		maxpool1->input1(relu1_out1);
		maxpool1->input2(relu1_out2);
		maxpool1->input3(relu1_out3);
		maxpool1->output(MaxPool1_out);

		maxpool2 = new MaxPool("MaxPool2");
		maxpool2->input0(relu2_out0);
		maxpool2->input1(relu2_out1);
		maxpool2->input2(relu2_out2);
		maxpool2->input3(relu2_out3);
		maxpool2->output(MaxPool2_out);

		maxpool3 = new MaxPool("MaxPool3");
		maxpool3->input0(relu3_out0);
		maxpool3->input1(relu3_out1);
		maxpool3->input2(relu3_out2);
		maxpool3->input3(relu3_out3);
		maxpool3->output(MaxPool3_out);

		result1 = new Result("Result1");
		result1->input0(MaxPool1_out);
		result1->input1(MaxPool2_out);
		result1->input2(MaxPool3_out);
		result1->output(result_out);

		SC_THREAD(clockGeneration);

		SC_THREAD(ram_store);
		sensitive << clk.posedge_event();

		SC_THREAD(generate_signals);
		sensitive << clk.posedge_event();

		SC_THREAD(monitor_signals);
		sensitive << clk.posedge_event();

		//SC_THREAD(done_process3);
		//SC_THREAD(done_process2);
		SC_THREAD(done_process);
		//sensitive << conv_done1 << conv_done2 << conv_done3;

		SC_METHOD(final_result_process);
		sensitive << result_out;
		//SC_THREAD(data_gen1);
		//SC_THREAD(data_gen2);
		//SC_THREAD(data_gen3);
		sc_trace_file* vcd;
		vcd = sc_create_vcd_trace_file("Waveforms_6");
		vcd->set_time_unit(1, SC_NS);

		sc_trace(vcd, clk, "clk");
		sc_trace(vcd, rst, "rst");
		sc_trace(vcd, conv_start, "start");
		sc_trace(vcd, done, "done");

		sc_trace(vcd, relu1_out0, "relu1_out0_val");
		sc_trace(vcd, relu1_out1, "relu1_out1_val");
		sc_trace(vcd, relu1_out2, "relu1_out2_val");
		sc_trace(vcd, relu1_out3, "relu1_out3_val");

		sc_trace(vcd, relu2_out0, "relu2_out0_val");
		sc_trace(vcd, relu2_out1, "relu2_out1_val");
		sc_trace(vcd, relu2_out2, "relu2_out2_val");
		sc_trace(vcd, relu2_out3, "relu2_out3_val");


		sc_trace(vcd, relu3_out0, "relu3_out0_val");
		sc_trace(vcd, relu3_out1, "relu3_out1_val");
		sc_trace(vcd, relu3_out2, "relu3_out2_val");
		sc_trace(vcd, relu3_out3, "relu3_out3_val");


		sc_trace(vcd, MaxPool1_out, "MaxPool1_val");
		sc_trace(vcd, MaxPool2_out, "MaxPool2_val");
		sc_trace(vcd, MaxPool3_out, "MaxPool3_val");

		sc_trace(vcd, result_out, "final_result");
	}

	void clockGeneration();
	void ram_store();
	void generate_signals();
	void monitor_signals();
	void done_process();
	//void done_process2();
	//void done_process3();
	void final_result_process();
	//void data_gen1();
	//void data_gen2();
	//void data_gen3();
};
