#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HashTable 100  // 設定HashTable的大小

// 定義一個單字結構，用於存儲單字及其出現次數
typedef struct Word_Entry {
    char* word;  // 單字字串
    int count;   // 出現次數
    struct Word_Entry* next;  // 指向下一個單字結構，為了解決hash碰撞
} Word_Entry;

// 設置函數
int hash_function(char* key);
void insert(char* key, Word_Entry** hash_table);
void show(Word_Entry** hash_table);

int main() {
    FILE* file;
    char word[100];
    int different_word = 0;
    Word_Entry* hash_table[HashTable] = { 0 };  // 初始化HashTable為空指針
    file = fopen("hw2_data.txt", "r");  // 打開文件
    if (file == 0) {  // 是否能打開文件
        printf("無法打開文件\n");
        return 0;
    }
    while (fscanf(file, "%s", word) != EOF) {  // 讀取文件中的單字直到EOF (End of File)
        insert(word, hash_table); // 將單字插入HashTable 
    }
    show(hash_table);  // 顯示HashTable中的所有單字及其出現次數
    for (int i = 0; i < HashTable; i++) {
        Word_Entry* entry = hash_table[i];
        while (entry != 0) {
            different_word++;
            entry = entry->next;
        }
    }
    printf("\n總共有多少個不重複的英文字: %d\n", different_word); 
    return 0;
}

// hash_function，將字串轉換成HashTable的index值
int hash_function(char* key) {
    int hash_value = 0;
    while (*key != '\0') {
        hash_value = hash_value + *key; // 將 hash_value 加上 key 的 ASCII 編碼值
        key++;
    }
    return hash_value % HashTable;  // 模運算將hash_value映射到HashTable的合法索引範圍內
}

// 將單字插入到HashTable中
void insert(char* key, Word_Entry** hash_table) {
    int hash_index = hash_function(key);  // 得到HashTable的index
    // 是否已經存在該單字
    Word_Entry* entry = hash_table[hash_index];
    while (entry != 0) {
        if (strcmp(entry->word, key) == 0) {  //  用來檢查HashTable中的當前單字結構中的單字是否與欲插入的單字相同
            entry->count++;
            return;
        }
        entry = entry->next;  // 沒有相同的單字，繼續查找下一個單字
    }
	// 若是沒有找到該單字，創建一個新的單字結構，並插入到HashTable中
    Word_Entry* new_entry = (Word_Entry*)malloc(sizeof(Word_Entry));
    new_entry->word = (char*)malloc(strlen(key) + 1);  //malloc指定內存空間為WordEntry 結構體大小
    strcpy(new_entry->word, key);  // 複製單字字串到單字結構中
    new_entry->count = 1;  
    new_entry->next = hash_table[hash_index];  // 將創立後的單字結構插入到HashTable中
    hash_table[hash_index] = new_entry;
}

void show(Word_Entry** hash_table) {
    printf("Word:   ");
    for (int i = 0; i < HashTable; i++) {  // for loop 查看所有HashTable中的index
        Word_Entry* entry = hash_table[i];
        while (entry != 0) {   
            printf("%-8s", entry->word);  // 輸出單字及其出現次數
            entry = entry->next;  // 繼續查找下一個單字結構
        }
    }
    printf("\nCount:   ");
    for (int i = 0; i < HashTable; i++) {  // for loop 查看所有HashTable中的index
        Word_Entry* entry = hash_table[i];
        while (entry != 0) {   
            printf("%-8d", entry->count);  // 輸出單字及其出現次數
            entry = entry->next;  // 繼續查找下一個單字結構
        }
    }
} 
