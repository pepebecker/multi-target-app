WASM_FLAGS = --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all

run: native
	./bin/game

native: clean
	mkdir -p bin
	clang -o bin/game native/*.c src/*.c -I./include -lSDL2 -lSDL2_gfx

wasm: clean
	mkdir -p web
	clang $(WASM_FLAGS) -o web/game.wasm src/*.c -I./include

clean:
	rm -rf bin
	rm -rf web/game.wasm
