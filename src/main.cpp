#include <cstdlib>
class CC {
public:
	CC(int a) {
		this->a = a;
	}

	int a;
};

int main(){
    CC c1(5);

    CC* pc2 = (CC*)malloc(sizeof(CC));

    return 0;
}