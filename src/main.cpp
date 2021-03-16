#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>

constexpr uint8_t callInstruction_format[] = {0xe8, 0x29, 00, 00, 00};


class CC {
public:
	inline static void* constructor = nullptr;
	CC(int num) {
		if(!constructor){
			void* rbp_value;
			__asm__(
				"mov %%rbp, %%rax":"=a"(rbp_value)
			);
		

			uintptr_t stack_pos_return = (uintptr_t)rbp_value + sizeof(void*);

			uintptr_t return_dist_instruction_address = (uintptr_t)*((void**)stack_pos_return);
			uintptr_t call_instruction_address = return_dist_instruction_address - sizeof(callInstruction_format);
			uintptr_t call_instruction = *((uintptr_t*)call_instruction_address) & 0xFF'FF'FF'FF'FF;
			if((call_instruction&0xFF) == callInstruction_format[0]){
				int32_t call_offset_address;
				memcpy((void*)&call_offset_address, (void*)((uint8_t*)&call_instruction + 1), sizeof(int32_t));
				constructor = (void*)(return_dist_instruction_address + call_offset_address);
			}else{
				printf("call not use a relative address\n");
			}
			
		}
		
		this->num = num;
	}

	static void init(){
		CC c(0);
	}

	void log(){
		printf("this->a is %d\n", this->num);
	}

	

private:

	int num;
};

typedef CC* (*CC_Constructor)(CC* cc, int num);


int main(){

	CC::init();
	//CC* c1 = new CC(5);

    CC* c2 = (CC*)malloc(sizeof(CC));

	if(CC::constructor){
			CC_Constructor cc_constructor = (CC_Constructor)CC::constructor;

			cc_constructor(c2, 10);
	}

	c2->log();

    return 0;
}