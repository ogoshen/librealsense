# Emscripten port

## Notes

Synchronous blocking on the main isn't allowed, so things like `condition_variable::wait_for` or `thread::join` should be rewritten to be asynchronous.

Using the [Asyncify](https://emscripten.org/docs/porting/asyncify.html#asyncify) module, you can call `emscripten_sleep` which is transformed in codengen to suspendable function.


## Building

Install EMSDK, build using CMake with the toolkit file:

`emscripten/cmake/Modules/Platform/Emscripten.cmake`

CXX_FLAGS:

`
-s ASYNCIFY -s USE_PTHREADS=1 -s PTHREADS_DEBUG=1 -s PTHREAD_POOL_SIZE=1 -s FORCE_FILESYSTEM=1 -s EXPORTED_FUNCTIONS=@exported_functions.json -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap', 'setValue', 'getValue', 'FS', 'addFunction', 'AsciiToString']" -s INITIAL_MEMORY=256MB -s ALLOW_TABLE_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=0 --source-map-base http://localhost:8000/ -O3 -g4
`

## TODO

* Implement WebUSB backend
* Resolve multithreading issues
    
    * Avoid [blocking the main thread](https://emscripten.org/docs/porting/pthreads.html#blocking-on-the-main-browser-thread) (deadlocks), use alternatives and [Asyncify](https://emscripten.org/docs/porting/asyncify.html#asyncify)

* Use [embind](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html) \ [WebIDL](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/WebIDL-Binder.html#webidl-binder) for js glue

