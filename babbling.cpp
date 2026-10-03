#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct word{
    string speak;
    int length;
    char start;
    bool compare(string s, int start){
        if (s.size() < start + length) {
            cout << "lack char number: "<< s.size()<<"<"<<start+length<<endl;
        };
        int start_idx = 0;
        cout << "Start compare: " << speak << " with "<< s<<" start: "<< start <<  endl;
        for ( int i = start ; i < start + length ; i++ ){
            if (speak[i - start] != s[i]) {
                cout << "failed : " << speak[i] << " " << s[i] << endl;
                cout << "length " << length << " char size "<< s.size() << endl;
                return false;
            }
            cout << speak[i] << " " << s[i] << "passed | ";
        }
        cout << endl;
        return true;
    }
};


int solution(vector<string> babbling) {
    int answer = 0;
    
    word aya;
    std::vector<word> vocabulary;
    aya.speak = "aya";
    aya.length = 3;
    aya.start = 'a';
    vocabulary.push_back(aya);
    
    word ye;
    ye.speak = "ye";
    ye.length = 2;
    ye.start = 'y';
    vocabulary.push_back(ye);
    
    word woo;
    woo.speak = "woo";
    woo.length = 3;
    woo.start = 'w';
    vocabulary.push_back(woo);
    
    word ma;
    ma.speak = "ma";
    ma.length = 2;
    ma.start = 'm';
    vocabulary.push_back(ma);
    
    
    for (string w : babbling){
        
        int char_len =  w.size();
        for (const auto& c : w){
            cout << c << " ";
        }
        cout << endl;
        
        bool can_speak = false;
        for (int char_idx = 0 ; char_idx < char_len ; char_idx +=0 ){
            can_speak = false;
            int selected_vocab_idx = -1;
            cout << "char_len: "<< char_len << " char_idx start: " << char_idx << endl;

            for (int vocab_idx = 0 ; vocab_idx < vocabulary.size() ; vocab_idx ++){
                word& v = vocabulary[vocab_idx];
                if (v.start == w[char_idx]) {
                    if (!v.compare(w, char_idx)) break;
                    selected_vocab_idx = vocab_idx;
                    break;
                }
            }
            
            if (selected_vocab_idx == -1) break; 
            can_speak = true;
            char_idx += vocabulary[selected_vocab_idx].length;
            cout << "char_idx end: " << char_idx<< "\n" << endl;
        }
        if (can_speak) {
            std::cout << "can sepak : "<< w<<endl;
            answer++ ;
        }
    }
    return answer;
}