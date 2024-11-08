#include <sstream>

#include "nuspell.h"
#include "dictionary.hxx"

Nuspell* Nuspell_create(const char* affixFileContent, const char* dictionaryFileContent) {
	auto dict = new nuspell::Dictionary();

	std::istringstream affixStream(affixFileContent);
	std::istringstream dictionaryStream(dictionaryFileContent);

	dict->load_aff_dic(affixStream, dictionaryStream);

	return reinterpret_cast<Nuspell*>(dict);
}

int Nuspell_testSpelling(Nuspell* instance, const char* word) {
	auto instancePtr = reinterpret_cast<nuspell::Dictionary*>(instance);

	std::string_view wordView(word);

	auto result = instancePtr->spell(wordView);

	return result;
}

int Nuspell_getSpellingSuggestions(Nuspell* instance, const char* word, char*** suggestions) {
	auto instancePtr = reinterpret_cast<nuspell::Dictionary*>(instance);

	std::string_view wordView(word);
	std::vector<std::string> suggestionsVector;

	instancePtr->suggest(wordView, suggestionsVector);

	auto results = new char*[suggestionsVector.size()];

	for (size_t i = 0; i < suggestionsVector.size(); i++) {
		results[i] = new char[suggestionsVector[i].size() + 1]; // +1 for the null terminator

		strcpy(results[i], suggestionsVector[i].c_str());
	}

	(*suggestions) = results;

	return suggestionsVector.size();
}

void Nuspell_freeSpellingSuggestions(char** suggestions, int count) {
	for (size_t i = 0; i < count; i++) {
		delete suggestions[i];
		suggestions[i] = 0;
	}

	delete suggestions;
}

void Nuspell_destroy(Nuspell* instance) {
	auto instancePtr = reinterpret_cast<nuspell::Dictionary*>(instance);

	delete instancePtr;
}
