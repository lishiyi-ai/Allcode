try {

    co_await promise_type.initial_suspend();

    //协程函数体的代码...
}
catch (...) {

    promise_type.unhandled_exception();
}

co_await promise_type.final_suspend();

// 协程主要的执行代码都被 try - catch 包裹，假如抛出了未处理的异常， 
//promise_type 的 unhandled_exception() 函数会被调用，
//我们可以在这个函数里面做对应的异常处理。
// 由于这个函数是在 catch 语句中调用的，
// 我们可以在函数内调用 std::current_exception() 函数获取异常对象，
// 也可以调用 throw 重新抛出异常。

// 调用了 unhandled_exception() 之后，协程就结束了，
// 接下来会继续调用 final_suspend() ，与正常结束协程的流程一样。
// C++规定 final_suspend() 必须定义成 noexcept ，
// 也就是说它不允许抛出任何异常。