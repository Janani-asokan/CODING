C++ gives you more control, but less abstraction.


constructor call once and automatically called 
 normal fn calls manually many time

| Feature              | Pointer                                                       | Reference                                        |
| -------------------- | ------------------------------------------------------------- | ------------------------------------------------ |
| What it is           | A variable that stores the memory address of another variable | An alias (another name) for an existing variable |
| Symbol               | `*`                                                           | `&`                                              |
| Can be null?         | ✅ Yes                                                         | ❌ No                                             |
| Can be reassigned?   | ✅ Yes                                                         | ❌ No (must bind once)                            |
| Needs dereferencing? | ✅ Yes (`*ptr`)                                                | ❌ No (used like normal variable)                 |
