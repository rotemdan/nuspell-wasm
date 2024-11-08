PROJ=nuspell

EMCCFLAGS=-s ALLOW_MEMORY_GROWTH=1 -s STACK_SIZE=1MB -s USE_ICU=1 -s EXPORTED_FUNCTIONS="['_malloc', '_free', '_Nuspell_create', '_Nuspell_testSpelling', '_Nuspell_getSpellingSuggestions', '_Nuspell_freeSpellingSuggestions', '_Nuspell_destroy']" -s EXPORTED_RUNTIME_METHODS="[]" -s MODULARIZE=1 -s EXPORT_ES6=1 -s EXPORT_NAME="Nuspell"

all: lib/nuspell/aff_data.cxx lib/nuspell/checker.cxx lib/nuspell/dictionary.cxx lib/nuspell/finder.cxx lib/nuspell/suggester.cxx lib/nuspell/utils.cxx lib/nuspell/nuspell.cpp
	emcc $(EMCCFLAGS) -O3 -o wasm/$(PROJ).js $^

.PHONY: clean
clean:
	rm -f wasm/$(PROJ).js wasm/$(PROJ).wasm
