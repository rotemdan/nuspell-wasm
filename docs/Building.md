# Building the Nuspell WebAssembly module

**Note**: Emscripten is only likely to work correctly on Linux (or possibly macOS). Use WSL if on Windows.

Clone the EMSDK repository:
```
git clone https://github.com/emscripten-core/emsdk --depth 1
```

Install and activate EMSDK:
```
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ..
```

Clone [`nuspell-wasm` repository](https://github.com/rotemdan/nuspell-wasm):
```
git clone https://github.com/rotemdan/nuspell-wasm
```

Enter directory and build:
```
cd nuspell-wasm
npm install
make clean
make
```

Output files:
```
wasm/nuspell.js
wasm/nuspell.wasm
```
