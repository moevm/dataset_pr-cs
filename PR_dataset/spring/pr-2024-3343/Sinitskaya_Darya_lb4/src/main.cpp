class CustomStack {
public:
    CustomStack(size_t initialCapacity){
        this->mCapacity = initialCapacity; // установка начальной вместимости стека
        this->mData = new int[initialCapacity]; // создание массива int
        this->mIndex = -1; // установка индекса вершины стека на -1 (стек изначально пуст)
    }
    
    CustomStack() : CustomStack(10){
        // 10 начальный размер стека, вызов другого конструктора
    }
    
    // освобождение памяти, выделенной под массив данных стека
    ~CustomStack(){
        delete[] this->mData;
    }
    
    // метод добавления нового элемента в стек
    void push(int val){
        this->ensureSpace(); // проверка, что размера массива достаточно для нового элемента
        this->mIndex++; // увеличение индекса вершины стека для последующей записи нового элемента
        this->mData[this->mIndex] = val; // запись переданного значения в массив данных стека
    }
    
    // метод удаления из стека последнего элемента
    void pop(){
        if(this->empty()){
            throw logic_error("pop () called on empty stack");
        }
        this->mIndex--; // "удаление" элемента
    }
    
    // функция доступа к верхнему элементу
    int top(){
        if(this->empty()){
            throw logic_error("top () called on empty stack");
        }
        return this->mData[this->mIndex];
    }
    
    // функция возвращения количества элементов в стеке
    size_t size() const{
        return this->mIndex+1;
    }
    
    // функция проверки на отсутствие элементов в стеке
    bool empty() const{
        return this->mIndex == -1;
    }
    
    // метод расширения исходного массива на n ячеек
    void extend(int n){
        if(n <= 0){
            throw logic_error("extend () called with a non-positive argument");
        }
        this->resize(this->mCapacity + n);
    }

protected:
    size_t mCapacity; // вместимость стека
    size_t mIndex; // индекс вершины стека
    int* mData; // указатель на массив данных стека
    
    size_t getNewCapacity() const{
        // метод для вычисления новой вместимости массива данных при необходимости расширения
        return this->mCapacity * 3 / 2 + 1;
    }
    
    void ensureSpace(){
        if(this->mIndex + 1 == mCapacity){
            // проверка на достижение максимального размера
            size_t NewCapacity = this->getNewCapacity();
            this->resize(NewCapacity);
        }
    }
    
    void resize(size_t NewCapacity){
        if(NewCapacity == mCapacity){
            return;
        }
        if(NewCapacity < mCapacity){
            throw logic_error("resize () called with a lower capacity");
        }
        int *newData = new int[NewCapacity];
        // копирование данных при помощи функции из заголовочного файла <algorithm>
        copy(this->mData, this->mData + this->mCapacity, newData);
        delete[] this->mData; // освобождение памяти, выделенной для старого массива
        this->mData = newData; // обновление указателя на новый массив данных
        this->mCapacity = NewCapacity; // обновление значения вместимости 
        
    }
};

int main() {
    CustomStack stack;
    string s;
    getline(cin, s); // считывание строки
    // создание объекта istringstream для работы со строкой s как с потоком
    istringstream stream(s);
    vector<string> n; // вектор для хранения подстрок
    string token; // переменная для хранения каждой подстрки
    // разбиение строки
    while(stream >> token){
        n.push_back(token);
    }
    int size_n = n.size();
    for(int i=0;i<size_n;i++){
        if(n[i]=="+" or n[i]=="-" or n[i]=="*" or n[i]=="/"){ // элемент операция
            if(stack.size() < 2){
                continue;
            }
            
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            
            if(n[i]=="+"){
                stack.push(a + b);
            } else{ 
                if(n[i]=="-"){
                    stack.push(a - b);
                } else {
                    if(n[i]=="*"){
                        stack.push(a * b);
                    } else {
                         if(b!=0){
                           stack.push(a / b);
                         }
                  }
              }
            }
            
        } else  { // элемент число
                stack.push(stoi(n[i]));
          }
    }
    
    if(stack.size()!=1){
        cout<<"error"<<endl;
        return 1;
    }
    
    cout<<stack.top()<<endl;

    return 0;
}
