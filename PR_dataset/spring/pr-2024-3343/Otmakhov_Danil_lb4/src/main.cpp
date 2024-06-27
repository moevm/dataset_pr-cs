class CustomStack{
    public:
        CustomStack(){
            mIndex = -1;
            mCapacity = 0;
            mData = new int[mCapacity];
        }

        ~CustomStack(){
            delete[] mData;
        }

        void push(int val){
            if (mIndex + 1 == mCapacity){
                resize(mCapacity + 1);
            }
            mIndex++;
            mData[mIndex] = val;
        }

        void pop(){
            if (empty()){
                cout << "error";
                exit(0);
            }
            mIndex--;
        }

        size_t size(){
            return mIndex + 1;
        }

        bool empty(){
            return mIndex == -1;
        }

        int top(){
            if (empty()){
                cout << "error";
                exit(0);
            }
            return mData[mIndex];
        }

        void extend(int n){
            if (n <= 0){
                cout << "error";
                exit(0);
            }
            resize(mCapacity + n);
        }
    protected:
        int* mData;
        size_t mIndex;
        size_t mCapacity;

        void resize(size_t newCapacity){
            if (newCapacity == mCapacity){
                return;
            }

            if (newCapacity < mCapacity){
                cout << "error";
                exit(0);
            }

            int* newData = new int[newCapacity];
            copy(mData, mData + mCapacity, newData);
            delete[] mData;
            mCapacity = newCapacity;
            mData = newData;
        }
};


int main(){
    CustomStack stack;
    string line("");
    string element;
    getline(cin, line);
    stringstream ss(line);
    while (ss >> element)
    {
        if (element == "-" || element == "+" || element == "*" || element == "/")
        {
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            if (element == "-"){
                stack.push(a - b);
            }
            else if (element == "+"){
                stack.push(a + b);
            }
            else if (element == "*"){
                stack.push(a * b);
            }
            else if (element == "/"){
                stack.push(a / b);
            }
        }
        else{
            int i = stoi(element);
            stack.push(i);
        }
    }

    if (stack.size() == 1)
        cout << stack.top() << endl;
    else
        cout << "error";

    return 0;
}
