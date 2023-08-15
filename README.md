# Gatery Template

![Gatery logo](https://github.com/synogate/gatery/raw/master/doc/gatery_logo_500.svg)

This is a basic template to quickly get going with gatery.

## Getting Started

The quickest way to get started is to start this project in a github codespace. You will need a github account. The automated process to set up the VM takes about 20 minutes.

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://github.com/codespaces/new?hide_repo_select=true&ref=github_codespace_test&repo=368247767)

Alternatively, you can clone this repository locally and follow the instructions in the [main gatery repository](https://github.com/synogate/gatery) to set up the dependencies.

Assuming you launched in a github codespace, you will eventually be presented with a browser based instance of VS Code.
Any changes made to files will persist in the Codespace until it is deleted.
A Codespace can be restarted from the "Codespaces" tab on github and these subsequent restarts do not require rebuilding the VM.

Files can be downloaded by right-clicking them in the Explorer view and selecting "Download". Additionally, changes can be committed and pushed from the Source Control view as in a regular git repository (in case you want to work on a cloned repository or add your repository as an additional remote).

Press F5 to compile and run. Any compilation errors will be shown in the Terminal tab, as well as (mixed with other less important "problems") in the Problems tab. In the absence of compilation errors, the code will run and simulate. The Output tab will show information such as detected failures.

A `.vcd` waveform of the simulation will be written to bin/linux-x86_64-Debug/waveform.vcd. It can be downloaded and inspected locally, or opened in VS Code by double clicking (does not work in firefox).

## Gatery Syntax Cheat Sheet

This is a list of the most important syntax constructs in gatery. See the documentation or [tutorial](https://synogate.com/gatery/gatery/tutorial/part1.html) for details.

### Elementary Signals

| Type | Description | Width | VHDL | Verilog |
|---|---|---|---|---|
| `Bit`  | single boolean or bit | 1 | `std_logic` | `wire` |
| `BVec` | untyped bit vector | variable, >= 0 | `std_logic_vector` | - |
| `SInt` | signed integer | variable, >= 0 | `signed` | `wire signed [...]` |
| `UInt` | unsigned integer | variable, >= 0 | `unsigned` | `wire[...]` |
| `Enum<c>` | Enum type signal based on a C/C++ enum `c` | Depends on `c` | custom type | - |


### Initialization

```cpp
	UInt undefined_8_wide_uint = 8_b;
	UInt undefined_10_wide_uint = BitWidth(10);
	UInt undefined_12_wide_uint(12_b);
	UInt undefined_16_wide_uint;
	undefined_16_wide_uint = BitWidth(16);
	
	UInt another_16_wide_uint = undefined_16_wide_uint.width(); // Only copies the width, but does not connect the signals.
```

### Signal Naming

```cpp
    UInt v = 32_b;
    v = ...;

    // name the current state of v "initial_v" in the VHDL code and in the waveform
    setName(v, "initial_v");

    v += 2;

    // name this new, incremented state of v "modified_v" in the VHDL code and in the waveform
    setName(v, "modified_v");

    UInt some_other_vector = v;

    // name some_other_vector "some_other_vector" in the VHDL code and in the waveform
    HCL_NAMED(some_other_vector);
```

### Literals

```cpp
	Bit b;

	b = '1'; // true
	b = '0'; // false
	b = 'X'; // undefined

	b = true;  // true
	b = false; // false
```

```cpp
	UInt bv_1, bv_2, bv_3, bv_4, bv_5;

	bv_1 = "b1010"; // Binary, 4_b wide
	bv_2 = "xff0f0"; // Hex, 20_b wide
	bv_3 = "d42"; // Decimal, 6_b wide
	bv_4 = "64b0"; // 64 zero bits
	bv_5 = "6b00xx00"; // Mixture of zeros and undefined bits
```

### Bit vector member functions

```cpp
	UInt vec = "32b0";
```

| Method | Type | Description |
|---|---|---|
| `vec.width()` | `BitWidth` | Width of the vector (i.e. 32). |
| `vec.size()` | `size_t` | Width of the vector (i.e. 32). |
| `vec[i]` | `Bit` | `i`th bit, assignable. |
| `vec.lsb()` | `Bit` | Least significant bit, assignable. Same as `vec[0]`. |
| `vec.msb()` | `Bit` | Most significant bit, assignable. Same as `vec[-1]`. |
| `vec(offset, size)` | `UInt` | Slice from bit `offset` to bit `offset+size`, assignable. |
| `vec.lower(size)` | `UInt` | Lower `size` bits, assignable. Same as `vec(0, size)`. |
| `vec.upper(size)` | `UInt` | Upper `size` bits, assignable. |


### Logical and Arithmetic Operators


```cpp
    Bit a, b;
    a = ...;
    b = ...;

    // Logical and bitwise negation both do the same
    Bit not_a = ~a;
    Bit also_not_a = !a;

    // And, or, xor as usual
    Bit a_and_b = a & b;
    Bit a_or_b = a | b;
    Bit a_xor_b = a ^ b;

    // Composition and bracketing as usual
    Bit a_nand_b = ~(a & b);
    Bit a_nor_b = ~(a | b);
```

```cpp
    UInt a = 8_b;
    UInt b = 8_b;
    a = ...;
    b = ...;

    // Bitwise negation
    UInt not_a = ~a;

    // And, or, xor as usual
    UInt a_and_b = a & b;
    UInt a_or_b = a | b;
    UInt a_xor_b = a ^ b;

    // Composition and bracketing as usual
    UInt a_nand_b = ~(a & b);
    UInt a_nor_b = ~(a | b);

    UInt c = 5_b;
    c = ...;
    // UInt illegal = a & c; <-- Illegal because c is 5 bits and a is 8 bits

    UInt a_plus_b = a + b;
    UInt a_minus_b = a - b;
    UInt a_times_b = a * b;
    UInt a_div_b = a / b;

    // Less / greater
    Bit a_lt_b = a < b;
    Bit a_gt_b = a > b;
    
    // Less or equal / greater or equal
    Bit a_le_b = a <= b;
    Bit a_ge_b = a >= b;

    // Equal / not equal
    Bit a_eq_b = a == b;
    Bit a_ne_b = a != b;    
```

```cpp
    UInt mantissa = 23_b;
    mantissa = ...;
    UInt exponent = 8_b;
    exponent = ...;
    Bit sign = ...;

    // Concatenates all arguments, putting the last
    // argument (mantissa) into the least significant bits.
    UInt ieee_float_32 = cat(sign, exponent, mantissa);

    // Packs all arguments, putting the first
    // argument (mantissa) into the least significant bits.
    UInt same_ieee_float_32 = pack(mantissa, exponent, sign);
```
```cpp
    UInt value = 10_b;
    value = ...;

    UInt value_times_4 = value << 2;
    UInt value_div_4 = value >> 2;
    UInt value_rotated_left_2 = rotl(value, 2);
    UInt value_rotated_right_2 = rotr(value, 2);    
```

### Vector extension

```cpp
	UInt unsigned_8_wide = "8b0";
	// Zero extends by 2 bits
	UInt unsigned_10_wide = ext(unsigned_8_wide, +2_b);

	SInt signed_8_wide = (SInt) "8b0";
	// Sign extends by 2 bits
	SInt signed_10_wide = ext(signed_8_wide, +2_b);
```

```cpp
	UInt unsigned_8_wide = "8b0";
	// Zero extend unsigned integer
	UInt unsigned_10_wide = zext(unsigned_8_wide, +2_b);

	UInt signed_8_wide = "8b0";
	// Sign extend integer
	UInt signed_10_wide = sext(signed_8_wide, +2_b);

	UInt mask_8_wide = "8b0";
	// Extend with ones
	UInt mask_10_wide_one_extended = oext(mask_8_wide, +2_b);
```

```cpp
    Bit bit = '1';
    // Sign extends by 9 bits
    UInt ten_1 = sext(bit, +9_b);
```

```cpp
    UInt a = "10b0";
    UInt b = "8b0";

    // This would be illegal because a nd b have different sizes:
    // UInt c = a & b;

    // This zero-extends b to the width of a (10-bits) and then performs the element wise or
    UInt a_or_b = a | zext(b);
    
    // The same works for sext and oext.
    UInt a_and_b = a & oext(b);
```

### Condition Scopes / Multiplexer

```cpp
    UInt value = 4_b;
    value = ...;

    Bit some_condition = ...;

    IF (some_condition) {
        value <<= 1;
    } ELSE {
        value += 1;
    }
```

### Clock Scopes

```cpp
void functionA()
{
	// registers, memory, and code created here can automatically
	// use clockA by accessing it from the innermost active ClockScope
}

void functionB()
{
	// Build a clock
	Clock clockA{{.absoluteFrequency = 1'000'000}}; // 1 MHz
	// Use this clock while the clockScope variable exists
	ClockScope clockScope{ clockA };

	functionA();
}
```

### Registers

```cpp
    UInt a = ...;
    a_delayed = reg(a);

    Bit b = ...;
    b_delayed_w_reset = reg(b, '0'); // reset to zero

    // Use loop semantics to build state:
    Bit enableCounter = ...;
    UInt counter_10b = 10_b;
    IF (enableCounter)
        counter_10b += 1;
    counter_10b = reg(counter_10b, 0);
```


## Further Information

For more information, visit [the Gatery website](https://synogate.com/gatery.html), where a [tutorial](https://synogate.com/gatery/gatery/tutorial/part1.html) is also available.

