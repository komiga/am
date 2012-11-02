
## What is this?

**All the Maths‽ (AM)** is a general-purpose mathematics C++11 header library which supplies:

* Vectors (yay!) and matrices (also yay!) and all the fancy operations on them that you'd expect from a maths lib
* Hashing algorithms
* *(A whole bunch of other stuff)*

It's, uh, a work-in-progress.

If you want a proper graphics maths lib that works with crappy compilers, please use the lovely [GLM](http://glm.g-truc.net/).

## *All* the maths, you say?

Hence the interrobang.

## Why?

Because I can.

## Requirements

A compiler with support for simpleton C++11 features, such as:

* Aggregate initialization
* Type traits (`<type_traits>` header)
* Lambdas
* `constexpr`
* `static_assert()`

Which essentially means you can't use it with MSVC. Deal with it.\*

\* *Actually, it is probably fairly easy to make it work in MSVC — if you're feeling masochistic enough, by all means.*

## License

**AM** carries the MIT license, which is gracefully plastered below. Some algorithms have separate (MIT-compatible) licenses, copyrights, or are in the public domain. These are indicated in the appropriate sections.

```
Copyright (c) 2012 Tim Howard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
