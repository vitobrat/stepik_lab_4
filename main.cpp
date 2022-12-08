#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int checkInput(){
    int input;
    try {
        cin >> input;
        if (cin.fail()) {
            throw 1;
        }
    } catch (int exeption) {
        cout << "ERROR!!!";
        exit(0);
    }
    cin.sync();
    return input;
}
//1.С клавиатуры или с файла (*) (пользователь сам может выбрать способ ввода) вводится последовательность,
// содержащая от 1 до 50 слов, в каждом из которых от 1 до 10 строчных латинских букв и цифр.
// Между соседними словами произвольное количество пробелов. За последним символом стоит точка.
string function1(){
    incorrect:
    cout << "Which type of input do you prefer?(1 - file; 2 - keyboard):";
    int input = checkInput();
    string str = "";
    if (input == 1){
        ifstream File;
        File.open("C:\\FirstCursProgramm\\C++\\stepik_lab_4\\lab_4.txt");
        if(File.is_open()){
            while(!File.eof()){
                string str1;
                getline(File, str1);
                str += str1;
            }
        } else{
            cout << "file could not be opened";
            return "";
        }
        File.close();
    } else if (input == 2){
        getline(cin, str);
    }else{
        goto incorrect;
    }
    return str;
}
//2. Необходимо отредактировать входной текст:
//·удалить лишние пробелы;
//·удалить лишние знаки препинания (под «лишними» подразумевается несколько подряд идущих знаков;
//·исправить регистр букв, если это требуется (пример некорректного использования регистра букв: пРиМЕр);
string function2(string str){
    string strRes = "";
    cout << "String before editing:" << "\n" << str << "\n";
    bool flag = true;
    for (int i = 0; i < str.length(); i++){
        if (str[i] == ' '){
            if (flag){
                continue;
            }else {
                flag = true;
                strRes+=str[i];
            }
        }else if(str[i]>='a' && str[i]<='z' || str[i]>='A' && str[i]<='Z'){
            if (str[i]>='A' && str[i]<='Z' && !flag){
                strRes+=str[i]+32;
            }else{
                strRes+=str[i];
            }
            flag = false;
        }else{
            flag = false;
            if(str[i] == '.' && str[i+1] == '.' && str[i+2] == '.'){
                i+=2;
                strRes += "...";
                continue;
            }else if(str[i] == '.') {
                strRes += '.';
                break;
            }
            if(str[i] != str[i-1]){
                strRes += str[i];
            }
        }
    }
    cout << "String after editing:" << "\n" << strRes;
    return strRes;
}

void function5(string str){
    string subString = "", strRes = "not exist";
    int count = 0;
    cout << "Input the substring you want to find in the string:";
    getline(cin, subString);
    cout << "Linear search:" << "\n";
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    for(int i = 0; i < str.length() - subString.length(); i++){
        string str1 = "";
        for(int j = i; j < subString.length() + i; j++){
            if (str[j] == subString[j-i]){
                str1 += str[j];
            } else {
                continue;
            }
        }
        if (subString == str1){
            strRes = "exist";
            count += 1;
        }
    }
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "SubString - " << strRes << "; There is(are) " << count << " substring(s);" << "Spent time: " << end - start << "ns\n";
    cout << "Boyer moore algorithm:" << "\n";
    strRes = "not exist"; count = 0;
    int arr[subString.length()];
    start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    for(int i = 0; i < subString.length(); i++){
        if(i != subString.length() - 1){
            arr[i] = subString.length() - 1 - i;
        }else{
            bool flag = false;
            for (int j = i - 1; j >= 0; j--){
                if (subString[j] == subString[i]){
                    flag = true;
                    arr[i] = arr[j];
                    break;
                }
            }
            if(!flag){
                arr[i] = subString.length();
            }
        }
    }
    for(int i = subString.length() - 1; i < str.length();){
        string str1 = "";
        bool flag = true;
        if(subString.find(str[i]) != std::string::npos){
            if (str[i] == subString[subString.length() - 1]){
                for(int j = i; j > i - subString.length(); j--){
                    if(str[j] == subString[subString.length() - 1 - i + j]){
                        str1 = str[j] + str1;
                    }else{
                        flag = false;
                        continue;
                    }
                }
                if(flag){
                    strRes = "exist";
                    count += 1;
                }
                i += arr[subString.length() - 1];
            }else{
                i += arr[subString.find_last_of(str[i])];
            }
        }else{
            i += subString.length();
        }
    }
    end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "SubString - " << strRes << "; There is(are) " << count << " substring(s);" << "Spent time: " << end - start << "ns\n";
}

int main() {
    string str;
    //1.С клавиатуры или с файла (*) (пользователь сам может выбрать способ ввода) вводится последовательность,
    // содержащая от 1 до 50 слов, в каждом из которых от 1 до 10 строчных латинских букв и цифр.
    // Между соседними словами произвольное количество пробелов. За последним символом стоит точка.
    str = function1();
    //2. Необходимо отредактировать входной текст:
    //·удалить лишние пробелы;
    //·удалить лишние знаки препинания (под «лишними» подразумевается несколько подряд идущих знаков;
    //·исправить регистр букв, если это требуется (пример некорректного использования регистра букв: пРиМЕр);
    str = function2(str);
    cout << "\n";
    //3.

    //4.

    //5.
    function5(str);
    return 0;
}
