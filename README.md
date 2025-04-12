# 2025 Update to Metal and Swift 5
ChatGPT - Passing Swift structs directly to Metal Shading Language (MSL) can be problematic due to a few core issues stemming from how Swift and Metal differ in memory layout, type compatibility, and alignment. Let’s break it down:

🚧 Problem 1: Memory Layout Mismatch
Swift structs don't guarantee a C-compatible layout by default. This means:

The order of fields, padding, and alignment in memory may not match how Metal expects them.
Metal Shading Language uses a layout that's predictable and closely mirrors C/C++ struct layout rules.
🛑 What happens if the layout is wrong?

Your shaders will read garbage data or misaligned values.
You may not even see errors — just incorrect rendering results or subtle bugs.
✅ Workaround: Use @frozen and @aligned properly in Swift or better, use Metal-friendly C structs or simd types.

⚖️ Problem 2: Alignment Requirements
Metal has strict alignment requirements for its types, especially when using float4, matrix_float4x4, etc.

Example:

A float4 in MSL expects 16-byte alignment.
Swift might not align its struct members the same way unless you’re very careful.

# Writing a Modern Metal App from Scratch

This repository accompanies the tutorial series "Writing a Modern Metal App from Scratch," available [here]( http://metalbyexample.com/modern-metal-1/).

## How to use this repository

The content in this repository is developed step-by-step throughout the articles in the series. The articles contain references to Git tags that correspond to significant milestones. To view the code as it appears at a particular step, you can use the `git checkout` command. For example, to view the project template before any Metal code is added, you can say:

    $ git checkout start

To view the state of the project at a particular checkpoint, use the tag name specified in the article. For example:

    $ git checkout step1_1


