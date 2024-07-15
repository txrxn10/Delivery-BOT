#include "CB_Task_1_Sandbox.h"

int main(int argc, char* argv[])
{
	init();
	std::thread t_1(threadCalls);
	_delay_ms(4000);
	
	//e_shape();
	//Task_1_1();
	Task_1_2();
	
	////////////////////////////////////////////////////////////////////////////////////////////
	
	cleanUp();
	t_1.detach();
}
