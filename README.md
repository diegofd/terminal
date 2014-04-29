terminal
========

Arduino terminal library


How to use:

```
Terminal *terminal;

void test_function(short argc, char* argv[]) {
  terminal->write("test_function");

  for(int i = 0; i < argc; i++) {
    terminal->write("argv " + String(i) + " : " + argv[i]);
  }
}

void setup() {
  terminal = new Terminal();

  // Register command
  terminal->register_command("test", &test_function);
}

// Main loop
void loop() {
  // Needed in the loop to read serial line. 
  terminal->read();
  
}
```

Using this code you can write "test param param" in your serial line and
when you push enter the function "test_funcion" will be executed.
