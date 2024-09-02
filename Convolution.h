
#include <systemc.h>
#include "util.h"
//typedef std::array<std::array<int, 3>, 3> integer_matrix;
template<int el1, int el2, int el3,
		 int el4,int el5, int el6,
		 int el7, int el8, int el9, 
		 int DATA_WIDTH, int KERNEL_WIDTH, int IMAGE_WIDTH, int STRIDE, int BIAS>
class Convolution : public sc_module {
public:

	// Ports
	sc_in<bool> clk;
	sc_in<bool> rst;
	sc_in<bool> conv_start;
	sc_out<bool> conv_done;
	sc_out<sc_lv<DATA_WIDTH>> output0;
	sc_out<sc_lv<DATA_WIDTH>> output1;
	sc_out<sc_lv<DATA_WIDTH>> output2;
	sc_out<sc_lv<DATA_WIDTH>> output3;
	sc_out<bool> read_img;
	sc_out<sc_lv<4>> address;
	//sc_out<sc_lv<4>> state_show;
	sc_in<sc_lv<DATA_WIDTH>> input;

	sc_out<sc_lv<8>> img1;
	sc_out<sc_lv<8>> img2;
	sc_out<sc_lv<8>> img3;
	sc_out<sc_lv<8>> img4;
	sc_out<sc_lv<8>> img5;
	sc_out<sc_lv<8>> img6;
	sc_out<sc_lv<8>> img7;
	sc_out<sc_lv<8>> img8;
	sc_out<sc_lv<8>> img9;
	sc_out<sc_lv<8>> img10;
	sc_out<sc_lv<8>> img11;
	sc_out<sc_lv<8>> img12;
	sc_out<sc_lv<8>> img13;
	sc_out<sc_lv<8>> img14;
	sc_out<sc_lv<8>> img15;
	sc_out<sc_lv<8>> img16;


	// Internal signals
	
	
	//int kernel[KERNEL_WIDTH][KERNEL_WIDTH];
	std::array<std::array<sc_lv<DATA_WIDTH>, IMAGE_WIDTH>, IMAGE_WIDTH> input_image;
	std::array<std::array<sc_lv<DATA_WIDTH>, ((IMAGE_WIDTH - KERNEL_WIDTH) / STRIDE + 1)>, ((IMAGE_WIDTH - KERNEL_WIDTH) / STRIDE + 1)> output_image;

	sc_signal<bool> address_generation;
	sc_signal<bool> Image_ACQUISITION_done;
	sc_signal<bool> conv_cal_start;
	sc_signal<bool> conv_cal_done;
	sc_signal<bool> img_ACQUISITION_init;
	sc_signal<bool> conv_init;
	sc_signal<bool> read_img_signal;
	sc_signal<sc_lv<4>> address_signal;

	// State Machine
	enum State_type { IDLE, INITIALIZE, IMAGE_ACQUISITION, CONVOLUTION_CAL };
	sc_signal<State_type> state;

	void State_CONTROL();
	void img_ACQUISITION();
	void conv_calculation();
	void update_outputs();
	SC_HAS_PROCESS(Convolution);
	Convolution(sc_module_name);
};

template<int el1, int el2, int el3,
	int el4, int el5, int el6,
	int el7, int el8, int el9,
	int DATA_WIDTH, int KERNEL_WIDTH, int IMAGE_WIDTH, int STRIDE, int BIAS>
Convolution < el1,  el2,  el3,
				   el4,  el5,  el6,
				   el7,  el8,  el9,
				   DATA_WIDTH,  KERNEL_WIDTH,  IMAGE_WIDTH,  STRIDE,  BIAS> ::Convolution(sc_module_name){
	

	SC_METHOD(State_CONTROL);
	sensitive << clk.pos() << rst;

	SC_METHOD(img_ACQUISITION);
	sensitive << clk.pos() << rst;

	SC_METHOD(conv_calculation);
	sensitive << clk.pos() << rst;

	SC_METHOD(update_outputs);
	sensitive << conv_done<<rst;
	//sensitive << clk.pos() << rst;


}


template<int el1, int el2, int el3,
	int el4, int el5, int el6,
	int el7, int el8, int el9,
	int DATA_WIDTH, int KERNEL_WIDTH, int IMAGE_WIDTH, int STRIDE, int BIAS>

void Convolution < el1,  el2,  el3,
				   el4,  el5,  el6,
				   el7,  el8,  el9,
				   DATA_WIDTH,  KERNEL_WIDTH,  IMAGE_WIDTH,  STRIDE,  BIAS> ::State_CONTROL() {
	if (rst.read() == true) {
		img_ACQUISITION_init.write(false);
		conv_init.write(false);
		address_generation.write(false);
		conv_cal_start.write(false);
		state.write(IDLE);
	}
	else if (clk.posedge()) {
		img_ACQUISITION_init.write(false);
		conv_init.write(false);
		address_generation.write(false);
		conv_cal_start.write(false);

		switch (state.read()) {
			
		case IDLE:
			//std::cout << "\nstate =IDLE";
			//std::cout << "\n@" << sc_time_stamp();
			if (conv_start.read() == 1) {
				state.write(INITIALIZE);
			}
			break;

		case INITIALIZE:
			//std::cout << "\nstate =INITIALIZE";
			//std::cout << "\n@" << sc_time_stamp();
			img_ACQUISITION_init.write(true);
			conv_init.write(true);
			if (conv_start.read() == false) {
				state.write(IMAGE_ACQUISITION);
			}
			break;

		case IMAGE_ACQUISITION:
			//std::cout << "\nstate =IMAGE_ACQUISITION";
			//std::cout << "\n@" << sc_time_stamp();
			address_generation.write(true);
			if (Image_ACQUISITION_done.read() == true) {
				state.write(CONVOLUTION_CAL);
				address_generation.write(false);
			}
			break;

		case CONVOLUTION_CAL:
			//std::cout << "\nstate =CONVOLUTION_CAL";
			//std::cout << "\n@" << sc_time_stamp();
			conv_cal_start.write(true);
			if (conv_cal_done.read() == true) {
				state.write(IDLE);
				conv_cal_start.write(false);
			}
			break;
		}
	}
}
template<int el1, int el2, int el3,
	int el4, int el5, int el6,
	int el7, int el8, int el9,
	int DATA_WIDTH, int KERNEL_WIDTH, int IMAGE_WIDTH, int STRIDE, int BIAS>

void Convolution < el1, el2, el3,
	el4, el5, el6,
	el7, el8, el9,
	DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS> ::img_ACQUISITION() {
	static int address_counter_i = 0;
	static int address_counter_j = 0;
	static int temp = 0;
	//kernel = { { el1, el2, el3 }, { el4, el5, el6 }, { el7, el8, el9 } };
	if (rst.read() == true) {
		for (auto& row : input_image) {
			for (auto& elem : row) {
				elem = 0;
			}
		}
		Image_ACQUISITION_done.write(false);
		//address_signal.write(0);
		address.write(0);
		//read_img_signal.write(false);
		read_img.write(false);
		address_counter_i = 0;
		address_counter_j = 0;
	}
	else if (clk.posedge()) {
		//Image_ACQUISITION_done.write(false);
		//read_img_signal.write(false);
		if (img_ACQUISITION_init.read() == true) {
			for (auto& row : input_image) {
				for (auto& elem : row) {
					elem = 0;
				}
			}
			//Image_ACQUISITION_done.write(false);
			//address_signal.write(0);
			//address.write(0);
			//address_counter_j = 0;
			//address_counter_i = 0;
			//read_img_signal.write(true);
			//read_img.write(false);
			 temp=0;
		}
		else if (address_generation.read() == true && Image_ACQUISITION_done.read()== false) {
			//std::cout << "address_counter is" << address;
			//read_img_signal.write(true);
			//read_img.write(true);
			if (temp > 0){
				input_image[address_counter_j][address_counter_i] = input.read();
				//cout << "input=" << input.read() << endl;
				//cout << "addr=" << address.read() << endl;
				//address_signal.write(address_counter_i + address_counter_j * IMAGE_WIDTH);
				address.write(address_counter_i + address_counter_j * IMAGE_WIDTH);
				//cout << "address=" << address.read();
				address_counter_i++;
				read_img.write(true);
			}
			temp++;
			read_img.write(true);
			if (address_counter_i == IMAGE_WIDTH) {
				address_counter_i = 0;
				address_counter_j++;
				if (address_counter_j == IMAGE_WIDTH) {
					Image_ACQUISITION_done.write(true);
					address_counter_j = 0;
				}
			}
		}
	}
}
template<int el1, int el2, int el3,
	int el4, int el5, int el6,
	int el7, int el8, int el9,
	int DATA_WIDTH, int KERNEL_WIDTH, int IMAGE_WIDTH, int STRIDE, int BIAS>

void Convolution < el1, el2, el3,
	el4, el5, el6,
	el7, el8, el9,
	DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS> ::conv_calculation() {
	static int kernel[KERNEL_WIDTH][KERNEL_WIDTH] = { { el1, el2, el3 }, { el4, el5, el6 }, { el7, el8, el9 } };
	static int index_i_conv = 0;
	static int index_j_conv = 0;
	static int output_position_i = 0;
	static int output_position_j = 0;
	static int temp_conv_value = 0;

	if (rst.read() == true) {
		for (auto& row : output_image) {
			for (auto& elem : row) {
				elem = 0;
			}
		}
		conv_cal_done.write(false);
		conv_done.write(false);
		index_i_conv = 0;
		index_j_conv = 0;
		output_position_i = 0;
		output_position_j = 0;
		temp_conv_value = 0;
	}
	else if (clk.posedge()) {
		conv_cal_done.write(false);
		conv_done.write(false);
		if (conv_init.read() == true) {
			for (auto& row : output_image) {
				for (auto& elem : row) {
					elem = 0;
				}
			}
			conv_cal_done.write(false);
			conv_done.write(false);
			index_i_conv = 0;
			index_j_conv = 0;
			output_position_i = 0;
			output_position_j = 0;
			temp_conv_value = 0;
		}
		else if (conv_cal_start.read() == true) {
			//count_i.write(index_i_conv);
			//count_j.write(index_j_conv);

			img1.write(input_image[0][0]);
			img2.write(input_image[0][1]);
			img3.write(input_image[0][2]);
			img4.write(input_image[0][3]);
			img5.write(input_image[1][0]);
			img6.write(input_image[1][1]);
			img7.write(input_image[1][2]);
			img8.write(input_image[1][3]);
			img9.write(input_image[2][0]);
			img10.write(input_image[2][1]);
			img11.write(input_image[2][2]);
			img12.write(input_image[2][3]);
			img13.write(input_image[3][0]);
			img14.write(input_image[3][1]);
			img15.write(input_image[3][2]);
			img16.write(input_image[3][3]);

			//std::cout << "\ncounter i is " << count_i.read() << endl;
			//std::cout << "\ncounter j is " << count_j.read() << endl;
			
			
			temp_conv_value += input_image[index_i_conv + output_position_i][index_j_conv + output_position_j].to_int() * kernel[index_i_conv][index_j_conv];
			//count_j.write(temp_conv_value);
			//std::cout << "\conv value  is " << count_j.read() << endl;
			index_i_conv++;
			if (index_i_conv == KERNEL_WIDTH) {
				index_i_conv = 0;
				index_j_conv++;
				if (index_j_conv == KERNEL_WIDTH) {
					index_j_conv = 0;
					temp_conv_value += BIAS;
					output_image[output_position_i][output_position_j] = temp_conv_value;
					temp_conv_value = 0;
					output_position_i++;
					if (output_position_i == ((IMAGE_WIDTH - KERNEL_WIDTH) / STRIDE) + 1) {
						output_position_i = 0;
						output_position_j++;
						if (output_position_j == ((IMAGE_WIDTH - KERNEL_WIDTH) / STRIDE) + 1) {
							conv_cal_done.write(true);
							conv_done.write(true);
							output_position_j = 0;
							/*
				cout << "\n Image is\n" <<
								img1.read().to_int() << endl<<
								img2.read().to_int() << endl <<
								img3.read().to_int() << endl <<
								img4.read().to_int() << endl <<
								img5.read().to_int() << endl <<
								img6.read().to_int() << endl <<
								img7.read().to_int() << endl <<
								img8.read().to_int() << endl <<
								img9.read().to_int() << endl <<
								img10.read().to_int() << endl <<
								img11.read().to_int() << endl <<
								img12.read().to_int() << endl <<
								img13.read().to_int() << endl <<
								img14.read().to_int() << endl <<
								img15.read().to_int() << endl <<
								img16.read().to_int();
								*/

						}
					}
				}
			}
		}
	}
}
template<int el1, int el2, int el3,
	int el4, int el5, int el6,
	int el7, int el8, int el9,
	int DATA_WIDTH, int KERNEL_WIDTH, int IMAGE_WIDTH, int STRIDE, int BIAS>

void Convolution < el1, el2, el3,
	el4, el5, el6,
	el7, el8, el9,
	DATA_WIDTH, KERNEL_WIDTH, IMAGE_WIDTH, STRIDE, BIAS> ::update_outputs() {
	//read_img.write(read_img_signal.read());
	//address.write(address_signal.read());
	//conv_done.write(conv_cal_done.read());
	if (rst.read() == true) {
		output0.write(0);
		output1.write(0);
		output2.write(0);
		output3.write(0);
	}
	else{

		output0.write(output_image[0][0]);
		output1.write(output_image[0][1]);
		output2.write(output_image[1][0]);
		output3.write(output_image[1][1]);
	}


}