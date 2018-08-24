///
//  main.cpp
//  Raid
//
//  Created by Petros Maliotis on 03/05/2018.
//  Copyright © 2018 Petros Maliotis. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <fstream>
#include <iomanip>

using namespace std;

string raidx,position,b,value,answer;
int SIZE,N;
int i,j;
float counterSimilarity,gotIt,percent;
ifstream inputFile,updates;
fstream backup,allData;
fstream *arrayFile;
char a,c,l;
int holder;
int thesi;
int hjj;
int x=-1;
unsigned int ui;
unsigned int previ = 0;
unsigned int apot = 0;
int mod;
string ii,concat1;
string ip,bc,up,ad;
string concat,toS;
int counter=0,updateInt,valueInt,raidInt;

void closeFiles(){
    for(i = 0; i < N; i++){
        arrayFile[i].close();
    }
    inputFile.close();
    updates.close();
    backup.close();
    allData.close();
    delete[] arrayFile;
}

void initializeArray() {
    arrayFile = new fstream[N];
    for(i = 0; i < N; i++){
        toS = to_string(i);
        concat = "RAIDX_"+toS+".txt";
        arrayFile[i].open(concat,ios::out);
        if(!arrayFile[i].is_open()){
            cout << "Problem creating files" << endl;
            exit(3);
        }
        for(j = 0; j < SIZE; j++){
            arrayFile[i] << '0';
        }
    }
}

void checkSimilarity(){
    backup.close();
    allData.close();
    backup.open(bc,ios::in);
    allData.open(ad,ios::in);
    counterSimilarity = 0;
    gotIt = 0;
    while(true){
        if(allData.get(c)){
            if(backup.get(a)){
                ++counterSimilarity;
                if(a==c){
                    ++gotIt;
                }
            }
            else{
                break;
            }
        }
        else{
            break;
        }
    }
    float div = 100/(float)counterSimilarity;
    percent = gotIt * div / (counterSimilarity * div);
    percent *=100;
    cout << "The similarity of the files is " << setprecision(4) << percent << "%" << endl;
}

void checkIfFilesAreOpen(){
    if(!inputFile.is_open() || !updates.is_open() || !backup.is_open() || !allData.is_open()){
        cout << "Something went wrong with the files !!! " << endl;
        exit(1);
    }
}

void raid1E(){
    for(i = 0; i < N; i++){
        arrayFile[i].seekp(0,ios::beg);
    }
    
    while(inputFile.get(a)){
        for(i = 0; i < 2 ; i++){
            x++;
            mod = x%N;
            cout << "Putting: " << a << endl;
            cout << "In file: " << mod <<endl;
            arrayFile[mod].put(a);
        }
        cout << "New character.."<<endl;
    }
    while(updates >> position){
        updates >> value;
        stringstream t(position);
        t >> updateInt;
        if(updateInt >= x/2){
            cout << "Wrong position you exceeded the number of data in the file " << updateInt << endl;
        }
        else{
            stringstream v(value);
            v >> valueInt;
            
            for(i = 0; i < 2 ; i++){
                holder = (updateInt*2+i) % N;
                thesi = (updateInt*2+i) / N;
                arrayFile[holder].seekp(thesi);
                cout << "File: "<<holder<<"with pos: "<<arrayFile[holder].tellg() <<endl;
                arrayFile[holder].get(c);
                stringstream hj(c);
                hj >> raidInt;
                arrayFile[holder].clear();
                if(raidInt != valueInt ){
                    arrayFile[holder].seekp(thesi);
                    arrayFile[holder] << valueInt;
                    arrayFile[holder].clear();
                    if(i==0){
                        backup.seekp(updateInt);
                        backup << valueInt;
                        backup.clear();
                    }
                }
            }
        }
    }
}

int raid5SupportFunction(int number){
    int var = 0;
    for(int i = 0; i <= number; i++){
        var += i;
    }
    return var;
}

void closeOpenArrayFile() {
    for(i = 0; i < N; i++){
        arrayFile[i].close();
    }
    for(i = 0; i < N; i++){
        ii = to_string(i);
        concat1 = "RAIDX_" + ii +".txt";
        arrayFile[i].open(concat1);
    }
}

void raid1ERecration(int test){
    cin.ignore();
    cin.ignore();
    int tempTest = test;
    arrayFile[test].open(concat,ios::out);
    arrayFile[test].seekp(0,ios::beg);
    arrayFile[(test+1)%N].close();
    arrayFile[(test+N-1)%N].close();
    ii = to_string((test+1)%N);
    concat1 = "RAIDX_" + ii +".txt";
    arrayFile[(test+1)%N].open(concat1,ios::in);
    ii = to_string((test+N-1)%N);
    concat1 = "RAIDX_" + ii +".txt";
    arrayFile[(test+N-1)%N].open(concat1,ios::in);
    if(!arrayFile[test].is_open()){
        cout << "RAID1E problem recreating file (open)" <<endl;
    }
    cout << arrayFile[test].tellp()<<endl;
    int eve;
    for(i = 0 ; i < SIZE ; i++){
        //Seek to the right file and and position
        if(tempTest % 2 == 0){
            eve = tempTest +1;
        }
        else{
            eve = tempTest - 1;
        }
        arrayFile[eve%N].seekg(eve/N);
        arrayFile[eve%N].get(a);
        arrayFile[eve%N].clear();
        arrayFile[test].put(a);
        
        tempTest += N;
    }
    closeOpenArrayFile();
    char tt;
    for(i = 0; i <= x/2; i++){
        holder = i*2 % N;
        thesi = i*2 / N;
        cout << "Holder: " << holder <<endl;
        cout << "Thesi: " << thesi << endl;
        //arrayFile[holder].clear();
        arrayFile[holder].seekg(thesi);
        arrayFile[holder].get(tt);
        cout << "allDAta : " << tt << endl;
        allData.put(tt);
        
    }
    
}

void raid1(){
    for(i = 0; i < N; i++){
        arrayFile[i].seekp(0,ios::beg);
    }
    while(inputFile.get(a)){
        for(i = 0; i < N; i++){
            arrayFile[i] << a;
        }
    }
    while(updates >> position){
        updates >> value;
        stringstream t(position);
        t >> updateInt;
        if(updateInt >= SIZE){
            cout << "Wrong position you exceeded the number data in the file "<< updateInt << endl;
        }
        else{
            stringstream v(value);
            v >> valueInt;
            for(i = 0; i < N; i++){
                arrayFile[i].seekp(updateInt);
                //cout <<"File " << i << ":  "<<arrayFile[i].tellp()<<endl;
                arrayFile[i].get(a);
                stringstream m(a);
                m >> raidInt;
                arrayFile[i].clear();
                if(raidInt != valueInt){
                    arrayFile[i].seekp(updateInt);
                    arrayFile[i] << valueInt;
                    arrayFile[i].clear();
                    if(i==0){
                        backup.seekp(updateInt);
                        backup << valueInt;
                        backup.clear();
                    }
                }
            }
        }
    }
    
}

void raid1Recration(int test) {
    cin.ignore();
    cin.ignore();
    for(i = 0; i < N; i++){
        if(i!=test){
            arrayFile[i].close();
            string ii = to_string(i);
            string concat1 = "RAIDX_" + ii + ".txt";
            arrayFile[i].open(concat1,ios::in);
            cout << "Position" << arrayFile[i].tellp()<<endl;
            arrayFile[test].open(concat,ios::out);
            arrayFile[test].seekp(0);
            cout << "test" << arrayFile[test].tellp() <<endl;
            if(!arrayFile[test].is_open()){
                cout << "Problem creating file!"<<endl;
            }
            while(arrayFile[i].get(a)){
                arrayFile[test].put(a);
                //cout << "test" << arrayFile[test].tellp() <<endl;
                allData << a;
                
            }
            break;
        }
    }
}

void raid4(){
    for(i = 0; i < N; i++){
        arrayFile[i].seekp(0,ios::beg);
    }
    x = 0;
    while(inputFile.get(a)){
        mod = x % (N-1);
        arrayFile[mod].put(a);
        x++;
    }
    
    apot = 0;
    int raidInt=0;
    closeOpenArrayFile();
    for(j = 0; j < SIZE; j++){
        apot = 0;
        for(i = 0; i < N-1; i++){
            arrayFile[i].get(a);
            if(a == '1'){
                raidInt = 1;
            }
            else{
                raidInt = 0;
            }
            ui = (unsigned int) raidInt;
            apot = apot xor ui;
            
        }
        raidInt =  apot;
        arrayFile[N-1] << raidInt;
    }
    //update phase
    closeOpenArrayFile();
    while(updates >> updateInt){
        updates >> valueInt;
        if(updateInt >= x){
            cout << "Wrong position you exceeded the number data in the file "<< updateInt << endl;
        }
        else{
            holder = updateInt % (N-1);
            thesi  = updateInt / (N-1);
            arrayFile[holder].seekp(thesi);
            arrayFile[holder].get(a);
            if(a == '1'){
                raidInt = 1;
            }
            else{
                raidInt = 0;
            }
            if(valueInt!=raidInt){
                arrayFile[holder].clear();
                arrayFile[holder].seekp(thesi);
                arrayFile[holder] << valueInt;
                backup.seekp(updateInt);
                backup << valueInt;
                backup.clear();
                arrayFile[N-1].seekg(thesi);
                arrayFile[N-1].get(l);
                if(l == '1'){
                    l = '0';
                }
                else{
                    l = '1';
                }
                arrayFile[N-1].clear();
                arrayFile[N-1].seekp(thesi);
                arrayFile[N-1] << l;
            }
        }
    }
}

void getFilesToZeroIndex(){
    for(i = 0; i < N; i++) {
        arrayFile[i].seekp(0,ios::beg);
    }
}

void raid4raid5Helper(int test) {
    cin.ignore();
    cin.ignore();
    int raidInt;
    arrayFile[test].open(concat,ios::out);
    arrayFile[test].seekp(0,ios::beg);
    cout << "Test:  " << arrayFile[test].tellp() << endl;;
    //arrayFile[test].clear();
    //closeOpenArrayFile();
    getFilesToZeroIndex();
    apot = 0;
    for(i = 0; i < SIZE; i++){
        apot = 0;
        for(j = 0; j < N; j++){
            if(j != test){
                arrayFile[j].get(a);
                if(a == '1'){
                    raidInt = 1;
                }
                else{
                    raidInt = 0;
                }
                ui = (unsigned int)raidInt;
                apot = apot xor ui;
            }
        }
        raidInt = (int) apot;
        arrayFile[test] << raidInt;
    }
    closeOpenArrayFile();
}

void raid4Recration(int test){
    raid4raid5Helper(test);
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < N-1; j++){
            arrayFile[j].get(a);
            allData << a;
        }
    }
    closeOpenArrayFile();
}

void raid5(){
    for(i = 0; i < N; i++){
        arrayFile[i].seekp(0,ios::beg);
    }
    int check=0;
    j = 0;
    int parity=N-1;
    while(inputFile.get(a)){
        //apot = 0;
        check++;
        for(j ; j < N; j++){
            if(j != parity){
                arrayFile[j].put(a);
                cout << "Value of j : " << j << endl;
                if(a == '1'){
                    raidInt = 1;
                }else{
                    raidInt = 0;
                }
                ui = (unsigned int)raidInt;
                apot = apot xor ui;
                break;
            }
        }
        j = ++j % N;
        if(check%(N-1)==0){
            j=0;
            raidInt = (int) apot;
            arrayFile[parity] << raidInt;
            cout << "Value of parity check: " << parity << endl;
            parity += N - 1;
            parity = parity % N;
            apot = 0;
        }
    }
    //update phase!!
    int parityCheck;
    int supp;
    closeOpenArrayFile();
    while(updates >> updateInt){
        updates >> valueInt;
        if(updateInt >= counter){
            cout << "Wrong position you exceeded the number data in the file "<< updateInt << endl;
        }
        else{
            thesi = updateInt / (N - 1);
            //holder = (updateInt + raid5SupportFunction(thesi)) % N;
            supp = updateInt + raid5SupportFunction(thesi);
            holder = supp % N;
            arrayFile[holder].clear();
            arrayFile[holder].seekp(thesi);
            arrayFile[holder].get(a);
            if(a == '1'){
                raidInt = 1;
            }
            else{
                raidInt = 0;
            }
            if(valueInt != raidInt){
                //arrayFile[holder].clear();
                arrayFile[holder].seekp(thesi);
                cout << "update thesi: "<< "holder : "<< holder << ", thesi : " <<arrayFile[holder].tellp()<<endl;
                arrayFile[holder] << valueInt;
                backup.seekp(updateInt);
                //cout << "backup tellp  " << backup.tellp() << endl;
                backup << valueInt;
                backup.clear();
                parityCheck = N - 1 - (thesi % N);
                cout << "PArity check: " << parityCheck << endl;
                arrayFile[parityCheck].seekp(thesi);
                arrayFile[parityCheck].get(l);
                if(l == '1'){
                    l = '0';
                }else{
                    l = '1';
                }
                arrayFile[parityCheck].clear();
                arrayFile[parityCheck].seekp(thesi);
                arrayFile[parityCheck] << l;
            }
        }
    }
    closeOpenArrayFile();
}

void raid5Recreation(int test){
    raid4raid5Helper(test);
    int parityCheckk;
    for(i = 0; i < SIZE; i++){
        parityCheckk = N - 1 - (i % N);
        for(j = 0; j < N; j++){
            if(j != parityCheckk){
                //cout << "j: " << j <<", " ;
                arrayFile[j].get(l);
                //cout << l << endl;
                allData.put(l);
            }
        }
    }
    closeOpenArrayFile();
}

int promptUserToDeleteFile(){
    int test;
    cout << "Select a file to delete allowed values to enter: " << "[0 ... " << N-1 <<"]" << endl;
    cin >> answer;
    stringstream r(answer);
    r >> test;
    if(test > N-1){
        cout << "I warned you about the allowed values !!. Terminating" << endl;
    }
    concat = "RAIDX_"+answer+".txt";
    arrayFile[test].close();
    if(remove(concat.c_str())!=0){
        cout << "Error deleting the file!" << endl;
    }
    else{
        cout << "Deletion was a succes" << endl;
    }
    //Recreate the file and its content!
    cout << "Press enter to proceed with the recreation of the file." <<endl;
    return test;
    
}

void typeOfRaid(){
    transform(raidx.begin(), raidx.end(),raidx.begin(), ::toupper);
    if(raidx.compare("RAID1") == 0){
        if(N < 2){
            cout << "The number of disks must be at least 2. (Terminating)" << endl;
            exit(4);
        }
        initializeArray();
        raid1();
        int test = promptUserToDeleteFile();
        raid1Recration(test);
        checkSimilarity();
        closeFiles();
    }
    else if(raidx.compare("RAID1E") == 0){
        if (N * SIZE < counter * 2) {
            cout << "Not enough space ...change N or Size to fit the cpacity of input!!" << endl;
        }
        if(N < 3){
            cout << "The number of disks must be at least 3. (Terminating)" << endl;
            exit(5);
        }
        initializeArray();
        raid1E();
        int test = promptUserToDeleteFile();
        raid1ERecration(test);
        checkSimilarity();
        closeFiles();
    }
    else if(raidx.compare("RAID4") == 0){
        if ((N-1) * SIZE < counter) {
            cout << "Not enough space ...change N or Size to fit the cpacity of input!!" << endl;
        }
        //Call function for raid4
        if(N < 3){
            cout << "The number of disks must be at least 3. (Terminating)" << endl;
        }
        initializeArray();
        raid4();
        int test = promptUserToDeleteFile();
        raid4Recration(test);
        checkSimilarity();
        closeFiles();
    }
    else if(raidx.compare("RAID5") == 0){
        //Call function for raid5
        if ((N-1) * SIZE < counter) {
            cout << "Not enough space ...change N or Size to fit the cpacity of input!!" << endl;
        }
        if(N < 3){
            cout << "The number of disks must be at least 3. (Terminating)" << endl;
        }
        initializeArray();
        raid5();
        int test = promptUserToDeleteFile();
        raid5Recreation(test);
        checkSimilarity();
        closeFiles();
    }
}

//./ergasia3 RAIDX SIZE N inputFile.txt updates.txt backup.txt allData.txt

int main(int argc,char * argv[]) {
    
    //Check the number of args
    if( argc != 8 ){
        cout << "The arguments are more or less! Enter the correct number of args" << endl;
        exit(-1);
    }
    else{
        raidx = argv[1];
        istringstream iss(argv[2]);
        iss >> SIZE;
        istringstream iss1(argv[3]);
        iss1 >> N;
        ip = argv[4];
        up = argv[5];
        bc = argv[6];
        ad = argv[7];
        inputFile.open(ip);
        updates.open(up);
        backup.open(bc,ios::out);
        allData.open(ad,ios::out|ios::in);
        checkIfFilesAreOpen();
    }
    //This is where the fun begins...!!
    while(inputFile.get(a)){
        counter++;
        backup << a;
    }
    backup.close();
    backup.open(bc,ios::in|ios::out);
    inputFile.clear();
    inputFile.seekg(0,ios::beg);
    cout << "Counter of input: "<<counter << endl;
    if(SIZE > counter){
        cout << "The size you entered is bigger than the size of the inputfile" << endl;
        exit(2);
    }
    //Determine the type of raid and do the necessary checks!!
    typeOfRaid();
    return 0;
}

