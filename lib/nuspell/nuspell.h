#ifndef NUSPELL_H
#define NUSPELL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Nuspell Nuspell;

Nuspell* Nuspell_create(const char* affixFileContent, const char* dictionaryFileContent);

int Nuspell_testSpelling(Nuspell* instance, const char* word);

int Nuspell_getSpellingSuggestions(Nuspell* instance, const char* word, char*** suggestions);

void Nuspell_freeSpellingSuggestions(char** suggestions, int count);

void Nuspell_destroy(Nuspell* instance);

#ifdef __cplusplus
}
#endif

#endif
