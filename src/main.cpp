#include <cstdlib>
#include <cstdint>
#include <cstdio>

constexpr uint8_t callInstruction_format[] = {0xe8, 0x29, 00, 00, 00};
void* constructor_address = nullptr;


class CC {
public:
	CC(int a) {
		if(!constructor_address){
			void* rbp_value;
			__asm__(
				"mov %%rbp, %%rax":"=a"(rbp_value)
			);
		

			uintptr_t stack_pos_return = (uintptr_t)rbp_value + sizeof(void*);

			uintptr_t return_dist_instruction_address = (uintptr_t)*((void**)stack_pos_return);
			uintptr_t call_instruction_address = return_dist_instruction_address - sizeof(callInstruction_format);
			uintptr_t call_instruction = *((uintptr_t*)call_instruction_address) & 0xFF'FF'FF'FF'FF;
			if((call_instruction&0xFF) == callInstruction_format[0]){
				uintptr_t call_offset_address = call_instruction >>8;
				constructor_address = (void*)(return_dist_instruction_address + call_offset_address);
			}else{
				printf("call not use a relative address\n");
			}
			
		}
		
		this->a = a;
	}

	void log(){
		printf("this->a is %d\n", this->a);
	}

	

private:

	int a;
};

typedef CC* (*CC_Constructor)(CC* cc, int num);

int main(){
    CC* c1 = new CC(5);

    CC* c2 = (CC*)malloc(sizeof(CC));

	if(constructor_address){
			CC_Constructor cc_constructor = (CC_Constructor)constructor_address;

			cc_constructor(c2, 10);
	}


	c1->log();
	c2->log();

    return 0;
}