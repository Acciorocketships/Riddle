#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

size_t writecallback(char*, size_t, size_t, void*);
string writetostring(string);
string data;
CURL* curl;
const string firsturl = "http://www.cartalk.com/content/puzzlers";

int main(){
    string tempriddle = "";
    string riddle = "";
    string text = writetostring(firsturl);
    int pos = (int)text.find("Read the Puzzler");
    char c;
    int i;
    string newurl = "www.cartalk.com";
    while (c != '.'){
        c = text[pos - i];
        i++;
    }
    for (int j = pos - i + 2; j <= pos - 3; j++){
        newurl += text[j];
    }
    cout << newurl << endl;
    text = writetostring(newurl);
    pos = (int)text.find("<strong>RAY</strong>");
    int pos2 = (int)text.find("Drop Ray a note");
    for (int j = pos + 22; j <= pos2-33; j++){
        tempriddle += text[j];
    }
    for (int i = 0; i < tempriddle.length()-31; i++){
        if (tempriddle[i] == '<'){
            while (tempriddle[i] != '>'){
                i++;
            }
        }
        else {
            riddle += tempriddle[i];
        }
    }
    cout << string(15, '\n');
    cout << riddle << endl;
}

string writetostring(string url){
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writecallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_perform(curl);
    return data;
}

size_t writecallback(char* buf, size_t size, size_t nmemb, void* up){
    for (int c = 0; c<size*nmemb; c++){
        data.push_back(buf[c]);
    }
    return size*nmemb;
}