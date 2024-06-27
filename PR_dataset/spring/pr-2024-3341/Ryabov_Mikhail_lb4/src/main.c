#define END_STR '\0'
#define SIZE_BUFFER 3000

class CustomStack{

    size_t sizeStack = 0;

    public:

        CustomStack(){
            this->mHead = NULL;
        }

        void push(const char* tag){
            this->sizeStack += 1;
            if (this->sizeStack - 1 == 0){
                this->mHead = createNode(tag);
                return;
            }
            
            
            ListNode* newElem = createNode(tag); 
            newElem->mNext = this->mHead;
            this->mHead = newElem;
            return;
        }

        void pop(){       
            if(this->sizeStack == 0)
                return;
            
            if(this->sizeStack == 1){
                free(mHead);
                this->mHead == NULL;
                this->sizeStack -= 1;
                return;
            }

            ListNode* tmp = this->mHead;
            this->mHead = this->mHead->mNext;
            this->sizeStack -= 1;
            free(tmp);
            return;
        }

        char* top(){
            if(sizeStack == 0)
                return NULL;
            
            return this->mHead->mData;
        }

        size_t size(){
            return this->sizeStack;
        }

        bool empty(){
            if(this->sizeStack == 0)
                return true;
            else
                return false;
        }

        void print(){
            cout << "\n\nStack have " << this->sizeStack << " elements" << endl;

            if(this->sizeStack == 0)
                return;
            
            ListNode* cur = this->mHead;
            
            while(cur->mNext != NULL){
                cout << cur->mData << endl;
                cur = cur->mNext;
            }
            cout << cur->mData << endl;
        }

    private:
        ListNode* createNode(const char* data){
            ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
            tmp->mNext = NULL;
            tmp->mData = (char*)data;
            return tmp;
        }

    protected:
        ListNode* mHead;

};

char** getTags(char* str, int* capacityTags){
    char** tags = (char**)malloc(sizeof(char*)*100);
    char* tag;
    
    int sizeStr = strlen(str);
    for(int i = 0; i < sizeStr; i++)
    {
 
        if(str[i] == '<')
        {
            int j = i;
            int size = 0, capacity = 1;
            char* tag = (char*)malloc(sizeof(char) * capacity);

            while(str[j] != '>')
            {
                tag[size++] = str[j];
                if(size >= capacity)
                {
                    capacity *= 2;
                    tag = (char*)realloc(tag, sizeof(char)*capacity);
                }
                
                j++;
            }
            tag[size++] = str[j];
            tag[size] = '\0';
            tags[(*capacityTags)++] = tag;
        }
    }
    return tags;
}

int checkStatusTag(char* tag){
    if(!strcmp(tag, "<br>") || !strcmp(tag, "<hr>"))
        return 2; //<br> or <hr>
    
    char backSlash = '/';
    char* isClose = strchr(tag, backSlash);
    if(isClose != NULL)
        return 1; // close
    else
        return 0; // open
}

int compareTags(char* stackTag, char* tag){
    if(stackTag == NULL)
        return -1;
    
    int sizeTag = strlen(tag);
    int size = 0;
    char* newTag = (char*)malloc(sizeof(char) * (sizeTag - 1));
    
    for(int i = 0; i < sizeTag; i++){
        if(tag[i] == '/')
            continue;
        newTag[size++] = tag[i];     
    }
    newTag[size] = '\0';
    return strcmp(stackTag, newTag);
}

int successHTML(char* str){
    int size = 0;
    int status;
    char** tags = getTags(str, &size);
    CustomStack stack;

    for(int i = 0; i < size; i++){
        status = checkStatusTag(tags[i]);
        if(status == 0)
            stack.push(tags[i]);
        
        else if(status == 1 && compareTags(stack.top(), tags[i]) == 0)
            stack.pop();
        
        else if (status == 1 && compareTags(stack.top(), tags[i]) != 0)
            return 0;   
    }

    if(stack.empty())
        return 1;
    else
        return 0;
}

int main(){
    char* str = (char*)malloc(sizeof(char) * SIZE_BUFFER);
    cin.getline(str, 3000);
    int success = successHTML(str);
    if(success)
        cout << "correct" << endl;
    else
        cout << "wrong" << endl;  
}
