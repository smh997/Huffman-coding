#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
using namespace std;

class node{    
public:
    string event_name;
    long double probability;
    node* left;
    node* right;
    string code_word;
    
    node(string name, long double p){
        this->event_name = name;
        this->probability = p;
        this->left = nullptr;
        this->right = nullptr;
        this->code_word = "";
    }
    
    bool operator <(const node* other) const{
        return this->event_name.length() < other->event_name.length();
    }
};

priority_queue<pair<long double, node*>,
                vector<pair<long double, node*>>,
                greater<pair<long double, node*>>> pq;

pair<long double, node*> left_node, right_node;

map<string, pair<long double, string>> code_words;

string name;
long double probability;
int n = 0; unsigned int max_name_length = 0, max_code_word_length = 0;

void tree_track(node* current_node, string code){
    if(current_node->left == nullptr && current_node->right == nullptr){
        code_words[current_node->event_name] = {current_node->probability, code};
        max_code_word_length = max(max_code_word_length, code.length());
        return;
    }
    if(current_node->left != nullptr)
        tree_track(current_node->left, code + "1");
    if(current_node->right != nullptr)
        tree_track(current_node->right, code + "0");
    current_node->code_word = code;
}

int main()
{
    while(n < 1 || n > 1000){
        cout << "Enter number of the events (0 < n < 1001): ";
        cin >> n;
        if (n < 1 || n > 1000)
            cout << "It must be between 1 and 1000." << endl;
    }
    cout << "Enter " << n << " events name and probability (ex: event1 0.002):" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> name >> probability;
        max_name_length = max(max_name_length, name.length());
        node* pointer = new node(name, probability);
        pq.push({probability, pointer});
    }
    
    node * root;
    
    while(!pq.empty()){
        right_node = pq.top(); pq.pop();
        
        if(pq.empty()){
            root = right_node.second;
            break;
        }
        
        left_node = pq.top(); pq.pop();
        
        name = "(" + left_node.second->event_name + ", " + right_node.second->event_name + ")";
        node* pointer = new node(name, right_node.first + left_node.first);
        pointer->right = right_node.second;
        pointer->left = left_node.second;
        
        pq.push({pointer->probability, pointer});
    }
    
    tree_track(root, "");
    
    string filler (max(4, (int)max_name_length-1), ' ');
    string filler2 (3 , ' ');
    string filler4 (4, ' ');
    int len = max(6 + (int)filler.length() + 11 + (int)filler2.length() + max((int)max_code_word_length, 9) + 4, 54);
    string borderfiller (len, '-');
    string padfiller (max(max(4, (int)max_code_word_length - 5), len - (6 + (int)filler.length() + 11 + (int)filler2.length() + max((int)max_code_word_length, 9))), ' ');
    string padfiller1 (len - 50, ' ');
    
    cout << "+" << borderfiller << "+" << endl;
    cout << "| Huffman code-words of the events are like bellow:" << padfiller1 << "|" << endl;
    
    cout << "| Event" << filler << "Probability" << filler2 << "Code-Word" << padfiller << "|" << endl; 
    
    for(auto answer: code_words){
        string filler3 ((int)(filler.length() + 5 - answer.first.length()), ' ');
        string padfiller2 (len - (1 + answer.first.length() + filler3.length() + 10 + filler4.length() + answer.second.second.length()), ' ');
        cout << "| " << answer.first << filler3 << fixed << setprecision(8) << answer.second.first << filler4 << answer.second.second << padfiller2 << "|" << endl;
    }
    
    cout << "+" << borderfiller << "+" << endl;
    
    return 0;
}
