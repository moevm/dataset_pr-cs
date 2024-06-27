#define BLOCK_SIZE 15
class CustomStack{

public:
        CustomStack(){
                this->count = 0;
                this->capacity = 1;
                this->mData = new int [BLOCK_SIZE];
                if(!mData){
                        printf("error\n");
                        exit(1);
                }
        }


        ~CustomStack(){
                delete[] mData;
        }

        void push(int elem){
                this->mData[count] = elem;
                this->count++;
                if(this->count>capacity*BLOCK_SIZE){
                        this->capacity++;
                        int* new_data = new int[capacity*BLOCK_SIZE*sizeof(int)];
                        if(!new_data){
                                printf("error\n");
                                exit(1);
                        }

                        for(int i = 0; i<count-1; i++){
                                new_data[i] = this->mData[i];                           
                        }
                        delete[] mData;
                        this->mData = new_data;
                        delete[] new_data;
                }

        }

        void pop(){
                if(this->count>0){
                        mData[this->count] = '\0';
                }else{
                        printf("error\n");
                        exit(1);
                }
                this->count--;
        }

        size_t size(){
                return this->count;
        }

        bool empty(){
                return this->count==0;
        }
        int top(){
                if(this->count==0){
                        printf("error");
                        exit(0);
                }
                return(mData[this->count-1]);
        }

        void extend(int n){
                int actual = this->capacity*BLOCK_SIZE;
                actual+=n;
                int* new_data = new int[actual*sizeof(int)];

                if(!new_data){
                        printf("error\n");
                        exit(1);
                }

                for(int i = 0; i<count; i++){
                        new_data[i] = this->mData[i];
                }
                delete[] mData;
                this->mData = new_data;
                delete[] new_data;
        }

private:
        size_t count;
        size_t capacity;

protected:
        int* mData;//тут должен быть обычный указатель
};

int main(){
        CustomStack s;
        char ch = getchar();
        int new_el;
        char buffer[50];
        int idx = 0;
        int first;
        int second;

        while(ch!=EOF&&ch!='\n'){
                while(ch!=' ' && ch!='\n' && ch!=EOF){
                        buffer[idx++] = ch;
                        ch = getchar();
                }
                buffer[idx] = '\0';
                if(isdigit(buffer[idx-1])){
                        new_el = atoi(buffer);
                        s.push(new_el);
                        idx = 0;
                }else{
                        second = s.top();
                        s.pop();
                        first = s.top();
                        s.pop();
                        switch(buffer[idx-1]){
                                case '+':
                                        s.push(first+second);
                                        break;
                                case '-':
                                        s.push(first-second);
                                        break;
                                case '*':
                                        s.push(first*second);
                                        break;
                                case '/':
                                        s.push(first/second);
                                        break;
                                default:
                                        break;
                                //      printf("error\n");
                                //      exit(0);
                        }
                }
                if(ch==' '){
                        ch = getchar();
                        idx = 0;
                }
        }
        if(s.size()==1)
            printf("%d\n",s.top());
        else
            printf("error");

        return 0;
}
