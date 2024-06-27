void mem_error(){
	cout << "Memory error!" << endl;
	exit(1);
}
class CustomStack{
    public:
        CustomStack(){
            mData=nullptr;
            mSize=0;
            mCap=0;
        }
        void push(const char* val){
            if(mSize==mCap){
                extend(1);
            }
            mData[mSize++]=(char*)val;
        }
        void pop(){
            if(mSize!=0){
                mSize--;
            }
        }
        char * top(){
            return mData[mSize-1];
        }
        size_t size(){
            return mSize;
        }
        bool empty(){
            return mSize==0;
        }
        void extend(int n){
	    char** newData;
            mCap=mCap+n;
            newData=new char* [mCap];
            if(newData==nullptr){mem_error;}
            for(int i=0; i<mSize; i++){
                newData[i]=mData[i];
            }
            delete [] mData;
            mData=newData;
        }
        ~CustomStack(){
        	delete [] mData;
        }
    private:
    int mSize;
    int mCap;
    protected:
    char ** mData;
};
int main(){
    char * tmps;
    tmps = new char [51];
    if(tmps==nullptr){mem_error;}
    bool swit = false;
    CustomStack stack;
    string line;
    int size=0; int curr=0;
    getline(cin, line);
    char ** tags;
    tags = new char * [100];
    if(tags==nullptr){mem_error;}
    for(int i=0; i<3000; i++){
        if(line[i]=='<'){
            swit=true;
            i++;
            tags[size]=new char [51];
            if(tags[size]==nullptr){mem_error;}
            }
        if(line[i]=='>'){swit=false;size++;curr=0;}
        if(swit){tags[size][curr++]=line[i];}
    }
    for(int i=0; i<size; i++){
        if(tags[i][0]=='/'){
            char * tmpf;
            tmpf = new char [51];
            if(tmpf==nullptr){mem_error;}
            for(int j=0; tags[i][j+1]; j++){
                tmpf[j]=tags[i][j+1];
            }
            if(stack.empty()){
                cout << "incorrect";
                stack.push(tmpf);
                cout <<"a\n";
                break;
            }
            if(strcmp(stack.top(), tmpf)!=0){
                cout <<"wrong";
                break;
            }
            if(strcmp(stack.top(), tmpf)==0){
                stack.pop();
            }
            delete [] tmpf;
        }
        else{
            if(strcmp(tags[i], "br")==0 || strcmp(tags[i], "hr")==0){}
            else{
                stack.extend(1);
                stack.push(tags[i]);
            }
        }
    }
    if(stack.empty()){
        cout << "correct";
    }
    delete [] tags;
    delete [] tmps;
    return 0;
}
