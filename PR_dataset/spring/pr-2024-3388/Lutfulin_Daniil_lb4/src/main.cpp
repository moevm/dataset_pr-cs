#define MAX_TEXT_LEN 3000
#define MAX_TAG_LEN 100
#define BLOCK_SIZE 10
#define STR_END '\0'
#define OPEN_TAG_START_INDEX 1
#define CLOSE_TAG_START_INDEX 2
#define CLOSE_TAG_MARK_INDEX 1
#define CLOSE_TAG_MARK '/'


class CustomStack {

    public:

        CustomStack(){
            this->mCapacity = 1;
            this->mLastIndex = -1;
            this->mData = new char*[this->mCapacity*BLOCK_SIZE];
        }

        void push(const char *str){
            this->mLastIndex++;
            this->mData[mLastIndex] = new char[MAX_TAG_LEN];
            strcpy(this->mData[mLastIndex], str);
            if (this->size() == mCapacity*BLOCK_SIZE)
                extend();
        }

        size_t size(){
            return this->mLastIndex+1;
        }

        bool empty(){
            return this->size() == 0;
        }

        void pop(){
            if (this->empty())
                return;
            delete this->mData[mLastIndex];
            this->mLastIndex--;
        }

        char *top(){
            if (empty())
                return nullptr;
            return this->mData[mLastIndex];
        }

        ~CustomStack(){
            while(!empty())
                pop();
            delete[] this->mData;
        }
    

    private:
    
        int mCapacity;
        int mLastIndex;

        void extend(){
            this->mCapacity++;
            char **newData = new char*[mCapacity*BLOCK_SIZE];
            copy(this->mData, this->mData + this->mCapacity*BLOCK_SIZE, newData);
            delete[] this->mData;
            this->mData = newData;
        }

    protected:  

        char** mData;
};

bool compareTags(char* open_tag, char *close_tag){
    return !strcmp(open_tag+OPEN_TAG_START_INDEX, close_tag + CLOSE_TAG_START_INDEX);
}

void getTag(char *dst, const char *src_text){
    char new_tag[MAX_TAG_LEN];
    int tag_last_index = -1;
    while(new_tag[tag_last_index] != '>'){
        tag_last_index++;
        if(src_text[tag_last_index] == '\0')
            throw "Text ends before tag ends!";
        new_tag[tag_last_index] = src_text[tag_last_index];
    }
    tag_last_index++;
    new_tag[tag_last_index] = STR_END;
    strcpy(dst, new_tag);
}

bool checkTag(char *text){
    CustomStack tag_stack;
    char* cur_tag;
    for(size_t i = 0; i <strlen(text); i++){
        if (text[i] == '<'){
            cur_tag = new char[MAX_TAG_LEN];
            getTag(cur_tag, text + i);
            if(strcmp(cur_tag, "<br>") && strcmp(cur_tag, "<hr>")){
                if(cur_tag[CLOSE_TAG_MARK_INDEX] == CLOSE_TAG_MARK){
                    if(tag_stack.empty() || !compareTags(tag_stack.top(), cur_tag)){
                        delete[] cur_tag;
                        return 0;
                    }
                    else{
                        tag_stack.pop();
                    }
                }
                else{
                    tag_stack.push(cur_tag);
                }
            }
            delete[] cur_tag;
        }
    }
    return tag_stack.empty();
}


int main(){
    char *text = new char[MAX_TEXT_LEN];
    fgets(text, MAX_TEXT_LEN, stdin);
    if(checkTag(text))
        cout << "correct";
    else
        cout << "wrong";
    return 0;
}
