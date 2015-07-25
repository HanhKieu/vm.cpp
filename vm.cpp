#include <iostream>
#include <string>
#include <bitset>
#include <fstream>



// void printRam(ram,use);printRam(unsigned int ram[])
// {
// 	for(int i = 0; i < 3; i++){	
// 		if(ram[i] != 0)
// 			std::cout << std::hex << ram[i]<< "000" << " ";
// 	}
// 	if(ram[3] != 0)
// 		std::cout << std::hex << ram[3] << "000";
// 	std::cout << std::endl;

// }
int fullUseChecker(unsigned int use[]){
	int full = 1;
	for(int i = 0;i < 4; i++){
		if(use[i] == 0){	
			full = 0;
			break;
		}

	}
	return full;
}

void printRamUse(unsigned int ram[], unsigned int use[])
{
	for(int i = 0; i < 3; i++){	
		if(ram[i] != 0)
			std::cout << std::hex << ram[i]<< "000" << " ";
	}
	if(ram[3] != 0)
		std::cout << std::hex << ram[3] << "000";
	std::cout << std::endl;
	for(int i = 0; i < 3; i++){	
			std::cout << use [i] << " ";
	}
	
	std::cout << use[3];
	std::cout << std::endl;
	
}


int main(){



	unsigned int ram[4];
	unsigned int use[4];//use_bit
	for(int i = 0; i < (4); i++){
		use[i] = 0;
		ram[i] = 0;
	}


	// unsigned int table[16][2];//i = virtual page number; table[i] = physical page number
	// for(i=0; i < 16; i++)
	// 	for(j = 0; j < 2; j++)
	// 		table[i][j] = 0;

	/*page write and read*/

	std::ifstream fs;
	fs.open("test20.txt");
	unsigned info, nutsack, full = 0, fullUse = 0, useIndex = 0;
	int counter = 0;

	
	while(fs >> std::hex >> info)
	{

		// offset = info & 0xFFF;
		nutsack	= (info & 0xFFFFF000) >> 12;

		if(counter > 15){


			if(full == 0){

				for(int i = 0; i < 4; i++){
					if(ram[i] == 0){
						ram[i] = nutsack;
						full = 0;
						use[i] = 1;
						fullUseChecker(use);
						//printRamUse(ram,use);printRam(ram);
						break;
					}
					full = 1;
				}
			}//if its not full find a place to put it





			else if(full == 1){

				if(fullUse == 0){

					for(int i = useIndex; i < 4; i++){
						if(ram[i] != nutsack){
							if(use[i] == 0){
								use[i] = 1;
								fullUse = 0;
								useIndex = i;
								ram[i] = nutsack;
								//printRamUse(ram,use);
								//printRam(ram);
								break;
							}
							else if(use[i] == 1){
								use[i] = 0;
								fullUse = 1;

							}
						}
						
					}//for 
				}
				else if(fullUse == 1){
					useIndex = 0;
					for(int i = 0;i < 4; i++)
						use[i] = 0;
					use[0] = 1;
					ram[0] = nutsack;
					fullUse = 0;
					//printRamUse(ram,use);
					//printRam(ram);

 

				}

			}//start implementing clock replacement when everything is full
		printRamUse(ram,use);
		//printRam(ram);
		}//if counter
		counter++;
	}//while

	fs.close();

	return 0;
}



