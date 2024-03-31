#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HashTable 100  // �]�wHashTable���j�p

// �w�q�@�ӳ�r���c�A�Ω�s�x��r�Ψ�X�{����
typedef struct Word_Entry {
    char* word;  // ��r�r��
    int count;   // �X�{����
    struct Word_Entry* next;  // ���V�U�@�ӳ�r���c�A���F�ѨMhash�I��
} Word_Entry;

// �]�m���
int hash_function(char* key);
void insert(char* key, Word_Entry** hash_table);
void show(Word_Entry** hash_table);

int main() {
    FILE* file;
    char word[100];
    int different_word = 0;
    Word_Entry* hash_table[HashTable] = { 0 };  // ��l��HashTable���ū��w
    file = fopen("hw2_data.txt", "r");  // ���}���
    if (file == 0) {  // �O�_�ॴ�}���
        printf("�L�k���}���\n");
        return 0;
    }
    while (fscanf(file, "%s", word) != EOF) {  // Ū����󤤪���r����EOF (End of File)
        insert(word, hash_table); // �N��r���JHashTable 
    }
    show(hash_table);  // ���HashTable�����Ҧ���r�Ψ�X�{����
    for (int i = 0; i < HashTable; i++) {
        Word_Entry* entry = hash_table[i];
        while (entry != 0) {
            different_word++;
            entry = entry->next;
        }
    }
    printf("\n�`�@���h�֭Ӥ����ƪ��^��r: %d\n", different_word); 
    return 0;
}

// hash_function�A�N�r���ഫ��HashTable��index��
int hash_function(char* key) {
    int hash_value = 0;
    while (*key != '\0') {
        hash_value = hash_value + *key; // �N hash_value �[�W key �� ASCII �s�X��
        key++;
    }
    return hash_value % HashTable;  // �ҹB��Nhash_value�M�g��HashTable���X�k���޽d��
}

// �N��r���J��HashTable��
void insert(char* key, Word_Entry** hash_table) {
    int hash_index = hash_function(key);  // �o��HashTable��index
    // �O�_�w�g�s�b�ӳ�r
    Word_Entry* entry = hash_table[hash_index];
    while (entry != 0) {
        if (strcmp(entry->word, key) == 0) {  //  �Ψ��ˬdHashTable������e��r���c������r�O�_�P�����J����r�ۦP
            entry->count++;
            return;
        }
        entry = entry->next;  // �S���ۦP����r�A�~��d��U�@�ӳ�r
    }
	// �Y�O�S�����ӳ�r�A�Ыؤ@�ӷs����r���c�A�ô��J��HashTable��
    Word_Entry* new_entry = (Word_Entry*)malloc(sizeof(Word_Entry));
    new_entry->word = (char*)malloc(strlen(key) + 1);  //malloc���w���s�Ŷ���WordEntry ���c��j�p
    strcpy(new_entry->word, key);  // �ƻs��r�r����r���c��
    new_entry->count = 1;  
    new_entry->next = hash_table[hash_index];  // �N�Х᪺߫��r���c���J��HashTable��
    hash_table[hash_index] = new_entry;
}

void show(Word_Entry** hash_table) {
    printf("Word:   ");
    for (int i = 0; i < HashTable; i++) {  // for loop �d�ݩҦ�HashTable����index
        Word_Entry* entry = hash_table[i];
        while (entry != 0) {   
            printf("%-8s", entry->word);  // ��X��r�Ψ�X�{����
            entry = entry->next;  // �~��d��U�@�ӳ�r���c
        }
    }
    printf("\nCount:   ");
    for (int i = 0; i < HashTable; i++) {  // for loop �d�ݩҦ�HashTable����index
        Word_Entry* entry = hash_table[i];
        while (entry != 0) {   
            printf("%-8d", entry->count);  // ��X��r�Ψ�X�{����
            entry = entry->next;  // �~��d��U�@�ӳ�r���c
        }
    }
} 
