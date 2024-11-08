import { WasmMemoryManager } from './WasmMemoryManager.js'

export async function createNuspellFromFiles(affixesFilePath: string, dictionaryFilePath: string) {
	const { readFile } = await import('fs/promises')

	const affixes = await readFile(affixesFilePath, 'utf-8')
	const dictionary = await readFile(dictionaryFilePath, 'utf-8')

	return createNuspellFromStrings(affixes, dictionary)
}

export async function createNuspellFromStrings(affixes: string, dictionary: string) {
	const wasmModule = await getWasmModule()

	const nuspell = new Nuspell(wasmModule, affixes, dictionary)

	return nuspell
}

export class Nuspell {
	private readonly wasmModule: any
	private wasmMemory: WasmMemoryManager
	private nuspellHandle: number
	private disposed = false

	constructor(wasmModule: any, affixes: string, dictionary: string) {
		if (this.isDisposed) {
			throw new Error(`Nuspell instance has been disposed. It cannot be re-initialized.`)
		}

		this.wasmModule = wasmModule
		const m = wasmModule

		this.wasmMemory = new WasmMemoryManager(m)

		const affixesRef = this.wasmMemory.allocNullTerminatedUtf8String(affixes)
		const dictionaryRef = this.wasmMemory.allocNullTerminatedUtf8String(dictionary)

		this.nuspellHandle = m._Nuspell_create(affixesRef.address, dictionaryRef.address)

		affixesRef.free()
		dictionaryRef.free()

		if (this.nuspellHandle === 0) {
			throw new Error(`Failed to create nuspell instance`)
		}
	}

	testSpelling(word: string) {
		this.ensureNotDisposed()

		const m = this.wasmModule
		const wasmMemory = this.wasmMemory
		const nuspellHandle = this.nuspellHandle

		const wordRef = wasmMemory.allocNullTerminatedUtf8String(word)

		const result = m._Nuspell_testSpelling(nuspellHandle, wordRef.address)

		wordRef.free()

		return Boolean(result)
	}

	getSpellingSuggestions(word: string) {
		this.ensureNotDisposed()

		const m = this.wasmModule
		const wasmMemory = this.wasmMemory
		const nuspellHandle = this.nuspellHandle

		const wordRef = wasmMemory.allocNullTerminatedUtf8String(word)

		const suggestionListRef = wasmMemory.allocPointer()

		const count = m._Nuspell_getSpellingSuggestions(nuspellHandle, wordRef.address, suggestionListRef.address)

		const suggestionList = this.readStringList(suggestionListRef.value, count)

		m._Nuspell_freeSpellingSuggestions(suggestionListRef.value, count)

		wordRef.free()
		suggestionListRef.free()

		return suggestionList
	}

	dispose() {
		if (this.isDisposed) {
			return
		}

		const m = this.wasmMemory.wasmModule

		m._Nuspell_destroy(this.nuspellHandle)

		if (this.wasmMemory) {
			this.wasmMemory.freeAll()
		}

		this.nuspellHandle = undefined as any
		this.disposed = true
	}

	private readStringList(address: number, count: number) {
		if (count === 0 || address === 0) {
			return []
		}

		const wasmMemory = this.wasmMemory

		const pointerArrayRef = wasmMemory.wrapUint32Array(address, count).detach()
		const pointerArrayElements = pointerArrayRef.view

		const values: string[] = []

		for (let i = 0; i < count; i++) {
			const wrappedString = wasmMemory.wrapNullTerminatedUtf8String(pointerArrayElements[i]).detach()

			values.push(wrappedString.value)
		}

		return values
	}

	private ensureNotDisposed() {
		if (this.isDisposed) {
			throw new Error(`Nuspell instance has been disposed`)
		}
	}

	get isDisposed() {
		return this.disposed
	}
}

let nuspellWasmInstance: any

export async function getWasmModule() {
	if (!nuspellWasmInstance) {
		const { default: initializer } = await import('../wasm/nuspell.js')

		nuspellWasmInstance = await initializer()
	}

	return nuspellWasmInstance
}
