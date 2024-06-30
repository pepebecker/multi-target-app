# Multi-Target C Project

This is a personal project to learn how to create a C API with multiple targets such as native and WebAssembly.

## Prerequisites

- **SDL2**
- **SDL2_gfx**
- **Clang** (Recent version which supports the wasm compilation target)

## Compile & Run Natively

```bash
make
```

## Compile to WebAssembly

```bash
make wasm
```
Now serve the `web` directory locally and open the page in your browser.

### Example Server
```bash
cd web # Navigate into the web directory
python3 -m http.server # Start the server
```
Now navigate to `http://localhost:8000` in your browser.


