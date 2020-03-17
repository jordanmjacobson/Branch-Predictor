/* Example
 * Parsing Branch Traces
 */

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"Branch.h"
#include<fstream>


using namespace std;
//function declarations:
//ofstream out(argv[2]);
int always_taken(vector<Branch>);
int always_nonTaken(vector<Branch>);
int single_bimodal(vector<Branch>,int);
int double_bimodal(vector<Branch>,int);
int move_state(Branch, int);
string change_state(string, string);
int gshare(vector<Branch>, int);
void gshare2(vector<Branch>);
int update(bool,int);
void bimodal2(vector<Branch>);
int tournament(vector<Branch>);
vector<int> btb(vector<Branch>);
//ofstream out;
int main(int argc, char *argv[]) {
	//wofstream out(argv[2]);
	//out<<"Test"<<endl;
	ofstream out(argv[2],ofstream::out);
  // Temporary variables
  unsigned long long addr;
  string behavior;
  unsigned long long target;
  //vector of branches
  vector<Branch> branches;

  // Open file for reading
  ifstream infile(argv[1]);

  // The following loop will read a hexadecimal number and
  // a string each time and then output them
  while(infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    //cout << addr;
    Branch temp = Branch();
    temp.setTarget(target);
    if(behavior == "T") {
      //cout << " -> taken, ";
      //char* var = (char*) behavior;
      temp.setBehavior(behavior);
    }else {
      //cout << " -> not taken, ";
    }
    	temp.setAddress(addr);
	//cout << "target=" << target << endl;
        branches.push_back(temp);


  }
   //this is just to test branch class....
 /* cout<<"-------Testing branch class-------"<<endl;
  for (int i=0; i<branches.size();i++){
	  cout<<"Address: "<<branches[i].getAddress()<<" Branch #: "<<i+1<<" behavior: "<<branches[i].getBehavior()<<" target: "<<branches[i].getTarget()<<endl;
  }*/
  //cout<<"-------Predictor Outputs-------"<<endl;
  //function calls:
	out<<"Test"<<endl;
  out<<always_taken(branches)<<","<<branches.size()<<"; "<<endl;
  out<<always_nonTaken(branches)<<","<<branches.size()<<"; "<<endl;
  //single bimodal
  out<<single_bimodal(branches,16)<<","<<branches.size()<<"; ";
  out<<single_bimodal(branches,32)<<","<<branches.size()<<"; ";
  out<<single_bimodal(branches,128)<<","<<branches.size()<<"; ";
  out<<single_bimodal(branches,256)<<","<<branches.size()<<"; ";
  out<<single_bimodal(branches,512)<<","<<branches.size()<<"; ";
  out<<single_bimodal(branches,1024)<<","<<branches.size()<<"; ";
  out<<single_bimodal(branches,2048)<<","<<branches.size()<<"; ";
	out<<endl;
  //double bimodal
  out<<double_bimodal(branches,16)<<","<<branches.size()<<"; ";
  out<<double_bimodal(branches,32)<<","<<branches.size()<<"; ";
  out<<double_bimodal(branches,128)<<","<<branches.size()<<"; ";
  out<<double_bimodal(branches,256)<<","<<branches.size()<<"; ";
  out<<double_bimodal(branches,512)<<","<<branches.size()<<"; ";
  out<<double_bimodal(branches,1024)<<","<<branches.size()<<"; ";
  out<<double_bimodal(branches,2048)<<","<<branches.size()<<"; ";
	out<<endl;
  //gshare
	out<<gshare(branches,3)<<","<<branches.size()<<"; "<<endl;
  /*for (int i=3;i<12;i++){
	  out<<gshare(branches,i)<<","<<branches.size()<<"; ";
  }*/
	out<<"Test"<<endl;
	out<<endl;
  //tournament
	out<<"Test"<<endl;
  out<<tournament(branches)<<","<<branches.size()<<"; "<<endl;
	//BTB
	out<<"Test before"<<endl;
	vector<int> BTB = btb(branches);
	out<<BTB[0]<<","<<BTB[1]<<"; "<<endl;
	//fclose(stdout);
	out.close();
  return 0;
}
int always_taken(vector<Branch> v){
	int accurate = 0;
       for (int i = 0; i< v.size(); i++){
	       if (v[i].getBehavior() == "T"){
		       accurate++;
	       }
       }
       //will be changed to writing to output file, just printing for now...
       //cout<<"Always Taken: "<<accurate<<","<<v.size()<<endl;
			 //out<<"accurate"<<","<<v.size()<<";"<<endl;
			 cout<<"Always taken ran"<<endl;
	return accurate;
}
int always_nonTaken(vector<Branch> v){
	int accurate = 0;
	for (int i = 0; i<v.size(); i++){
		if (v[i].getBehavior() == "NT"){
			accurate++;
		}
	}
	//will be changed to writing to output file, just printing for now...
	//cout<<"Always Non-Taken: "<<accurate<<","<<v.size()<<endl;
	//out<<"accurate"<<","<<v.size()<<";"<<endl;
	cout<<"Always non-taken ran"<<endl;
	return accurate;

}
int single_bimodal(vector<Branch> v, int size){
	//string previous = "T";
	int accurate = 0;
	//creating table

	string table[size];
	for (int i = 0; i<size;i++){
		table[i] = "T"; // initialize all values in table to "T" - taken
	}

	unsigned long long index = 0;
	switch(size){
		case 16:
			for (int i = 0; i<v.size();i++){
				index = v[i].getAddress() & 0x0000000F; //15 in hex
				if (v[i].getBehavior() == table[index]){
					accurate++;
				}

				table[index] = v[i].getBehavior();

			}
		break;
		case 32:
			for (int i=0;i<v.size();i++){
				index = v[i].getAddress() & 0x0000001F; //31 in hex
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index] = v[i].getBehavior();
			}
		break;
		case 128:
			for(int i=0;i<v.size();i++){
				index = v[i].getAddress()&0x0000007F; //127 in hex
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;
		case 256:
			for (int i=0;i<v.size();i++){
				index = v[i].getAddress()&0x000000FF; //255
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;
		case 512:
			for(int i=0;i<v.size();i++){
				index=v[i].getAddress()&0x000001FF;//511
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;
		case 1024:
			for(int i=0;i<v.size();i++){
				index=v[i].getAddress()&0x000003FF;
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;
		case 2048:
			for(int i=0;i<v.size();i++){
				index=v[i].getAddress()&0x000007FF;
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;

	}
	//cout<<"Single bimodal"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
	//out<<accurate<<","<<v.size()<<": "
	cout<<"Single bimodal ran"<<endl;
	return accurate;
}
int double_bimodal(vector<Branch>v, int size){
	int predictions[size];
	//initialize all values in table to strongly taken:
	for(int i = 0;i<size;i++){
		predictions[i] = 11;
	}
	int accurate = 0;
	unsigned long long index = 0;
	switch(size){
		case 16:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x0000000F;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 32:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x0000001F;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 128:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x0000007F;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 256:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x000000FF;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 512:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x000001FF;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 1024:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x000003FF;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 2048:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x000007FF;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;


	}

	//cout<<"Double bimodal"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
	//out<<accurate<<","<<v.size()<<"; ";
	cout<<"Double bimodal ran"<<endl;
	return accurate;



}
int move_state(Branch b,int state){
	switch(state){
		case 11: //strongly taken
			if(b.getBehavior() == "T"){
				return 11;//stay at strongly taken
			}
			else{
				return 10;//move to weakly taken
			}
		break;
		case 10: //weakly taken
			if(b.getBehavior() == "T"){
				return 11;//move to strongly taken
			}
			else{
				return 1;//move to weakly non-taken
			}
		break;
		case 1: //weakly non-taken
			if(b.getBehavior() == "T"){
				return 10;//move to weakly taken
			}
			else{
				return 0;//move to strongly non-taken
			}
		break;
		case 0: //strongly non-taken
			if(b.getBehavior() == "T"){
				return 1;//move to weakly non-taken
			}
			else{
				return 0;//stay at strongly non-taken
			}
		break;
	}

}
string change_state(string pred, string outcome){
	if (pred == "TT"){//strongly taken
		if (outcome == "T"){
			return "TT";//stay at strongly taken
		}
		else if (outcome == "NT"){
			return "T"; //go to weakly taken
		}
	}
	else if(pred == "T"){//weakly taken
		if(outcome == "T"){
			return "TT"; //go to strongly taken
		}
		else if(outcome == "NT"){
			return "NT"; //go to weakly non-taken
		}
	}
	else if(pred == "NT"){//weakly non-taken
		if(outcome == "T"){
			return "T"; //go to weakly taken
		}
		else if(outcome == "NT"){
			return "NTNT";// go to strongly non-taken
		}
	}
	else if(pred == "NTNT"){ //strongly non-taken
		if (outcome == "T"){
			return "NT"; // go to weakly non-taken
		}
		else if(outcome =="NT"){
			return "NTNT"; //stay at strongly non-taken
		}
	}


}
int gshare(vector<Branch>v, int size){
	int accurate  = 0;
	string predictions[2048];
	int index = 0;
	unsigned long long GHR = 0;
	//initialize all table values to strongly taken
	for (int i = 0; i<2048; i++){
		predictions[i] = "TT";
	}
	cout<<"gshare initialized properly"<<endl;
	switch (size){
		case 3:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					//cout<<predictions[index]<<endl;
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x00000007;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());

					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					//cout<<"index calculated properly"<<endl;
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x00000007;
				}
			}
			cout<<"index and gshare calculated properly"<<endl;
			//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		break;
		case 4:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x0000000F;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());

					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x0000000F;
				}
			}
			//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		break;
		case 5:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x0000001F;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());

					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x0000001F;
				}
			}
			//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		break;
		case 6:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x0000003F;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());

					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x0000003F;
				}
			}
			//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		break;
		case 7:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x0000007F;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());

					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x0000007F;
				}
			}
			//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		break;
		case 8:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x000000FF;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());

					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x000000FF;
				}
			}
			//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		break;
		case 9:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x000001FF;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());

					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x000001FF;
				}
			}
			//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		break;
		case 10:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x000003FF;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());

					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x000003FF;
				}
			}
			//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		break;
		case 11:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x000007FF;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());

					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x000007FF;
				}
			}
			//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		break;
	}
	//cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
	//out<<accurate<<","<<v.size()<<"; ";
	cout<<"Gshare ran"<<endl;
	return accurate;


}
void bimodal2(vector<Branch>v){ //bimodal predictor participating in the tournament
	//0 = strongly non-taken
	//1 = weakly non-taken
	//10 = weakly taken
	//11 = strongly taken
	int prediction = 11;
	int table[2048];
	int index = 0;
	for(int i = 0; i<2048; i++){ //initialize everything to strongly taken
		table[i] = 11;
	}
	for(int i = 0; i<v.size();i++){
		index = v[i].getAddress() & 0x000007FF;
		if(v[i].getBehavior() == "T"){
			if (table[index]==11 || table[index] == 10){
				v[i].setbimodal(true);
			}
		}
		else if(v[i].getBehavior() == "NT"){
			if(table[index] == 0 || table[index] == 1){
				v[i].setbimodal(true);
			}
		}
		table[index] = move_state(v[i],table[index]);
	}
}
void gshare2(vector<Branch>v){	//gshare predictor participating in the tournamet
	string table[2048];
	int index = 0;
	unsigned long long GHR = 0;
	for (int i=0; i<2048;i++){
		table[i] = "TT";
	}
	for(int i=0;i<v.size();i++){
		int addr_mod = v[i].getAddress() % 2048;
		index = addr_mod^GHR;
		if(v[i].getBehavior() == "T"){
			if(table[index] =="TT"||table[index] == "T"){
				v[i].setgshare(true);
				table[index] = change_state(table[index],v[i].getBehavior());
			}
			else if(table[index] == "NTNT" || table[index] == "NT"){
				table[index] = change_state(table[index],v[i].getBehavior());
			}
			unsigned long long temp = GHR<<1;
			unsigned long long temp2 = temp | 0x00000001;
			GHR = temp2 & 0x000007FF;
		}
		else if(v[i].getBehavior() =="NT"){
			if(table[index] == "NTNT" || table[index] == "NT"){
				v[i].setgshare(true);
				table[index] = change_state(table[index],v[i].getBehavior());
			}
			else if(table[index] == "TT" || table[index] == "T"){
				table[index] = change_state(table[index],v[i].getBehavior());
			}

			unsigned long long temp = GHR<<1;
			GHR = temp & 0x000007FF;
		}
	}
}
/*int update(bool b, int state){
	switch (state){
		case 3:
			if (b == true){
				return 3; //stay at strongly gshare
			}
			else{
				return 2;//go to weakly gshare
			}
		break;
		case 2:
			if (b == true){
				return 3; // go to strongly gshare
			}
			else{
				return 1; //go to weakly bimodal
			}
		break;
		case 1:
			if (b== true){
				return 2; //go to weakly gshare
			}
			else{
				return 0; // go to strongly bimodal
			}
		case 0:
			if (b == true){
				return 1; //go to weakly bimodal
			}
			else{
				return 0; //stay in strongly bimodal
			}
	}
}*/

/*void tournament(vector<Branch>v){
	//3 - strongly prefer gshare
	//2-weakly prefer gshare
	//1 - weakly prefer bimodal
	//0 - strongly prefer bimodal
	int accurate = 0;
	int selector[2048];
	int index = 0;
	for (int i = 0; i<2048; i++){
		selector[i]= 3;
	}
	bimodal2(v);
	gshare2(v);
	for (int i = 0; i< v.size(); i++){
		index = v[i].getAddress() & 0x000007FF;
		//cout<<index<<endl;
		if(v[i].getgshare() == true && v[i].getbimodal() == false){
			cout<<"in if statement 1"<<endl;
				if (selector[index]>=2){
					accurate++;
					cout<<"in if statement 2"<<endl;
				}
				selector[index] = update(true, selector[index]);
		}
		else if(v[i].getgshare() == false && v[i].getbimodal() == true){
			cout<<"in if statement 3"<<endl;
			if (selector[index] <2){
				cout<<"in if statement 4"<<endl;
				accurate++;
				//cout<<accurate<<endl;
			}
			selector[index] = update(false,selector[index]);
		}
		else if (v[i].getgshare() == v[i].getbimodal()){
			continue;
		}
	}
	cout<<"tournament: "<<accurate<<endl;
}*/
int select(int input,int val){
	if(val == 1){ // gshare was right
		if (input < 3){
			input++;
		}
	}
	else if(val ==0){ // gshare was wrong
		if (input>0){
			input--;
		}
	}
	return input;
}
int tournament(vector<Branch>v){
	int accurate = 0;
	int selector [2048];
	bool g = false; //if gshare gets it right
	bool b = false; //if bimodal gets it right
	unsigned long long sindex = 0; //selector index
	unsigned long long bindex = 0;//bimodal index
	unsigned long long gindex = 0;//gshare index
	unsigned long long GHR = 0;//GHR
	int btable [2048]; //bimodal table
	string gtable [2048]; //gshare table
	for(int i = 0; i<2048; i++){ //initialize all table values
		selector[i] = 3; // strongly prefer gshare
		btable[i] = 11;//strongly taken
		gtable[i] = "TT";//strongly taken
	}
	for (int i = 0; i< v.size(); i++){

		int addr_mod = v[i].getAddress()%2048;
		gindex = addr_mod^GHR; // set gshare index
		bindex = v[i].getAddress() & 0x000007FF;//set bimodal index
		sindex = v[i].getAddress() & 0x000007FF;
		if(v[i].getBehavior() == "T"){
			//first run gshare...
			if(gtable[gindex]=="TT"||gtable[gindex] =="T"){ // gshare is right
				//accurate++;
				//gtable[gindex] = change_state(gtable[gindex],v[i].getBehavior());
				g = true;
			}
			else if(gtable[gindex] == "NT"||gtable[gindex]=="NTNT"){ //gshare is wrong
				//gtable[gindex] = change_state(gtable[gindex], v[i].getBehavior());
				g = false;
			}
			unsigned long long temp = GHR<<1;
			unsigned long long temp2 = temp | 0x00000001;
			GHR = temp2 & 0x000007FF;

			//now run bimodal...
			if (btable[bindex] == 11 || btable[bindex] == 10){ // bimodal is right
				b = true;
			}
			else if(btable[bindex] == 0||btable[bindex] ==1){//bimodal is wrong
				b = false;
			}


		}
		else if(v[i].getBehavior() == "NT"){
			//run gshare
			if(gtable[gindex] =="NT" || gtable[gindex] == "NTNT"){//gshare is right
				//gtable[gindex] = change_state(gtable[gindex], v[i].getBehavior());
				g = true;
			}
			else if (gtable[gindex] == "T"||gtable[gindex] == "TT"){//gshare is wrong
				//gtable[gindex]= change_state(gtable[gindex],v[i],getBehavior());
				g = false;
			}
			unsigned long long temp = GHR<<1;
			GHR=temp & 0x000007FF;

			//run bimodal
			if(btable[bindex] == 0|| btable[bindex]==1){ //bimodal is right
				b = true;
			}
			else if(btable[bindex] == 10||btable[bindex] == 11){//bimodal is wrong
				b = false;
			}
		}
		gtable[gindex] = change_state(gtable[gindex],v[i].getBehavior());
		btable[bindex] = move_state(v[i],btable[bindex]);

		switch (selector[sindex]){
			case 3: //predict g
				if (g && b){ // if both predictors are right
					accurate++;
				}
				else if(g && !b){ // g wins
					accurate++;
					//selector[sindex] = select(selector[i],1);
				}
				else if (!g && b){ // g loses
					//selector[sindex] = select(selector[i],0);
					selector[sindex]--;
				}
				break;
				case 2:
				if (g && b){ // if both predictors are right
					accurate++;
				}
				else if(g && !b){ // g wins
					accurate++;
					//selector[sindex] = select(selector[sindex],1);
					selector[sindex]++;
				}
				else if (!g && b){ // g loses
					//selector[sindex] = select(selector[sindex],0);
					selector[sindex]--;
				}
				break;
				case 1:
					if (g && b){
						accurate++;
					}
					else if (g&& !b){
						selector[sindex]++; //= (selector[sindex], 0);
					}
					else if(!g && b){
						accurate++;
						selector[sindex]--; //= (selector[sindex],1);
					}
				break;
				case 0:
					if (g && b){
						accurate++;
					}
					else if (g&& !b){
						selector[sindex]++;//= (selector[sindex], 0);
					}
					else if(!g && b){
						accurate++;
						//selector[sindex]++;// = (selector[sindex],1);
					}
				break;


		}


	}
  //cout<<"Tournament: "<<accurate<<endl;
	//out<<accurate<<","<<v.size()<<";"<<endl;
	cout<<"Tournament ran"<<endl;
	return accurate;
}

vector<int> btb(vector<Branch>v){
	vector<int> retval;
	int attempts = 0;
	int accurate = 0;
	string table [512];
	unsigned long long index = 0;
	unsigned long long target_buf[512];
	for (int i=0;i<512;i++){
		table[i] = "T";
		target_buf[i] = 0;
	}
	for(int i=0; i<v.size();i++){
		index =v[i].getAddress() & 0x000001FF;
		if(table[index] == "T"){
			attempts++;
			if(v[i].getTarget() == target_buf[index]){
				accurate++;
			}
			if(v[i].getBehavior() == "T"){
				target_buf[index] = v[i].getTarget();
			}
		}
		else if(table[index]== "NT"){
			if(v[i].getBehavior() == "T"){
				target_buf[index] = v[i].getTarget();
			}
		}
		table[index] = v[i].getBehavior();
	}
	//cout<<"BTB: "<<accurate<<","<<attempts<<endl;
	//cout<<accurate<<","<<attempts<<";"<<endl;
	retval.push_back(accurate);
	retval.push_back(attempts);
	cout<<"BTB ran"<<endl;
	return retval;
}
