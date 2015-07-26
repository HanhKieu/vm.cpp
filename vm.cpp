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

int ifInRam(unsigned int ram[], unsigned int nutsack){
	for(int i = 0; i < 4; i++){	
		if(ram[i] == nutsack)
			return 1;
	}

	return 0;

}
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

void printRamUse(unsigned int ram[], unsigned int use[], int lineCounter, unsigned int useIndex, unsigned int nutsack)
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
	std::cout << std::dec << " line: " << lineCounter << " Index is : " << useIndex ;
	std::cout << std::hex << " was Trying to add: " << nutsack << std::endl;
	
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
	unsigned int info, nutsack, full = 0, useIndex = 0;
	int counter = 0;
	int lineCounter = 1;

	
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
						if(fullUseChecker(ram))
						{
							full = 1;
							useIndex = 0;
							use[i] = 1;
							
							break;
						}
						use[i] = 1;
						//printRamUse(ram,use,lineCounter));printRam(ram);
						break;
					}
					full = 1;
				}
				printRamUse(ram,use,lineCounter, useIndex, nutsack);
				if(full == 1){
					for(int j = 0;j < 4; j++)
						use[j] = 0;

				}
			}//if its not full find a place to put it



			else if(full == 1){

				for(int i = useIndex; i < 4; i++){

					if(!ifInRam(ram,nutsack)){
						if(use[i] == 0){
							std::cout << "Use at current: 0";
							std::cout << std::endl;
							if(fullUseChecker(use))
							{
								useIndex = 0;
								for(int j = 0;j < 4; j++)
									use[j] = 0;
								std::cout << "went into fulluse checker";
								std::cout << std::endl;
								break;
							}
							use[i] = 1;
							if(i == 3){
								useIndex = 0;
							}
							else{
								useIndex = i + 1;
							}
							
							ram[i] = nutsack;
						
							//printRamUse(ram,use,lineCounter));
							//printRam(ram);
							break;
						}
						else if(use[i] == 1)
						{
							if(fullUseChecker(use))
							{
								useIndex = 0;
								i = -1;
								for(int j = 0;j < 4; j++)
									use[j] = 0;
								std::cout << "went into fulluse checker for 1";
								std::cout << std::endl;

							}
							else{
								use[i] = 0; 
								std::cout << "Use at current: 1";
							std::cout << std::endl;

							}
							
						}
					}
					if(useIndex == 3 && !fullUseChecker(use)){
						std::cout << " I looped";
						std::cout << std::endl;
						useIndex = -1;
					}

				}//for 
		

						
				
					//printRamUse(ram,use,lineCounter));
					//printRam(ram);

 
				printRamUse(ram,use,lineCounter, useIndex, nutsack);

			}//start implementing clock replacement when everything is full
	
		//printRam(ram);
		lineCounter++;
		}//if counter
		
		counter++;
	}//while

	fs.close();

	return 0;
}



