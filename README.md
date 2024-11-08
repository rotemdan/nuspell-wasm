# Nuspell (WebAssembly port)

WebAssembly port of the [Nuspell](https://github.com/nuspell/nuspell) spell-checking library.

Includes an easy-to-use wrapper written in TypeScript.

## Installation

```
npm install nuspell-wasm
```

## Usage

```ts
// Import
import { createNuspellFromFiles } from 'nuspell-wasm'

// Create instance (dictionary paths are illustrative)
const nuspell = await createNuspellFromFiles('dict/en-US.aff', 'dict/en-US.dic')

console.log(nuspell.testSpelling('Hello'))
// Output: true

console.log(nuspell.testSpelling('Hellow'))
// Output: false

console.log(nuspell.getSpellingSuggestions('Hellow'))
// Output: [ 'Hello', 'Hell ow', 'Hello w', 'Howell', 'Lowell' ]

// Dispose instance
nuspell.dispose()
```

## License

LGPL-3.0
