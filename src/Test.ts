import { createNuspellFromFiles } from './Nuspell.js'

const log = console.log

export async function testEnglish() {
	const nuspell = await createNuspellFromFiles('dict/en-US.aff', 'dict/en-US.dic')

	log(nuspell.testSpelling('Hello'))
	log(nuspell.testSpelling('Hellow'))
	log(nuspell.getSpellingSuggestions('Hellow'))

	nuspell.dispose()
}

export async function testKorean() {
	const nuspell = await createNuspellFromFiles('dict/ko-KO.aff', 'dict/ko-KO.dic')

	log(nuspell.testSpelling('우물거려'))
	log(nuspell.testSpelling('우물된려'))
	log(nuspell.getSpellingSuggestions('우물된려'))

	nuspell.dispose()
}

export async function testSpeed() {
	const nuspell = await createNuspellFromFiles('dict/ko-KO.aff', 'dict/ko-KO.dic')

	for (let i = 0; i < 10000000; i++) {
		nuspell.testSpelling('우물거려')

		if (i % 1000 === 0) {
			log(i)
		}
	}

	for (let i = 0; i < 10; i++) {
		log(nuspell.getSpellingSuggestions('우물된려'))
	}

	nuspell.dispose()
}

testKorean()
