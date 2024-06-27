#define MAX_TAG_SIZE 256
#define MAX_HTML_SIZE 3001

class CustomStack
{
public:
  CustomStack() : mHead(nullptr) {}
  ~CustomStack() { clear(); }
  void push(const char * tag)
  {
    ListNode * node = new ListNode{ mHead, strdup(tag) };
    mHead = node;
  }

  void pop()
  {
    if (mHead) {
      ListNode * node = mHead;
      mHead = mHead -> mNext;
      delete[] node -> mData;
      delete node;
    }
  }

  char * top()
  {
    return mHead ? mHead -> mData: nullptr;
  }

  size_t size()
  {
    size_t count = 0;
    ListNode * current = mHead;
    while (current) {
      ++count;
      current = current -> mNext;
    }
    return count;
  }

  bool empty()
  {
    return mHead == nullptr;
  }

  void clear()
  {
    while (!empty())
      pop();
  }

protected:
  ListNode * mHead;
};

bool checkHtml(const char * html)
{
    if (html == nullptr || *html == '\0') {
        return false;
    }

    CustomStack stack;
    for (size_t i = 0; html[i] != '\0'; ++i) {
        if (html[i] == '<') {
            size_t endTag = i;
            while (html[endTag] != '>' && html[endTag] != '\0') {
                ++endTag;
            }
            if (html[endTag] == '\0') {
                return false;
            }

            char tag[MAX_TAG_SIZE];
            size_t j = 0;
            while (i + 1 < endTag && j < MAX_TAG_SIZE - 1) {
                tag[j++] = html[++i];
            }
            tag[j] = '\0';

            if (*tag == '\0' || (tag[0] == '/' && tag[1] == '\0')) {
                return false;
            }

            if (tag[strlen(tag) - 1] == '/') {
                tag[strlen(tag) - 1] = '\0';
            }

            if (strcmp(tag, "br") == 0 || strcmp(tag, "hr") == 0) {
                continue;
            }

            if (tag[0] != '/') {
                stack.push(strdup(tag));
            } else {
                char closingTag[MAX_TAG_SIZE];
                strcpy(closingTag, tag + 1);
                if (stack.empty() || strcmp(stack.top(), closingTag) != 0) {
                    return false;
                }
                stack.pop();
            }

            i = endTag;
        }
    }

    return stack.empty();
}

int main() {
    char* html = new char[MAX_HTML_SIZE];
    cin.getline(html, MAX_HTML_SIZE);
    cout << (checkHtml(html) ? "correct" : "wrong") << endl;
    delete[] html;
    return 0;
}
