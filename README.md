# samsung-riscv
Samsung RISC-V program

## My Details

**Name:** SAMARTHA H M  
**College:** Srinivas Institute of Technology  
**Email ID:** samarth.h.m.gadikal@gmail.com  
**GitHub Profile:** [samartha-hm](https://github.com/samartha-hm)  
**LinkedIN Profile:** [samartha.hm](https://www.linkedin.com/in/samarthahm/)  

----------------------------------------------------------------------------------------------------------------

<details>
<summary><b>Task 1:</b> Task is to install all the essential tools required for this internship such as Ubuntu on VMBox, leafpad and did a small code to find the sum from 1 to n numbers</summary>   
<br>

**1. Ubuntu on VMBox, leafpad**  
![task 1/installation of VM and leafpad](https://github.com/samartha-hm/samsung-riscv/blob/main/task%201/installation%20of%20VM%20and%20leafpad%20.png)  

**2. sum1ton file code**  
![task 1/sum1ton file code](https://github.com/samartha-hm/samsung-riscv/blob/main/task%201/sum1ton%20file%20code.png)  

**3. running sum1ton c file**  
![task 1/running sum1ton c file](https://github.com/samartha-hm/samsung-riscv/blob/main/task%201/running%20sum1ton%20c%20file.png)  

**4. operations**  
![task 1/doing some operations](https://github.com/samartha-hm/samsung-riscv/blob/main/task%201/doing%20some%20operations.png)  
</details>
----------------------------------------------------------------------------------------------------------------
<details>
<summary><b>Task 2:</b> SPIKE Simulation</summary>  

**1. Before Debugging**  
![task 2/before debugging](https://github.com/samartha-hm/samsung-riscv/blob/e04f2bacbbcc7a6e35dbb42c0919963f19da62b2/task%202/before%20debuging%20.png)  

**2. Debugging**  
![task 2/debugging](https://github.com/samartha-hm/samsung-riscv/blob/e04f2bacbbcc7a6e35dbb42c0919963f19da62b2/task%202/debugging.png)  
</details>
----------------------------------------------------------------------------------------------------------------
<details>
<summary><b>Task 3:</b> RISC-V Instruction Encoding Overview</summary>   
<br>
  
**Task 3: RISC-V Instruction Encoding Overview**  
 
</details>
----------------------------------------------------------------------------------------------------------------
<details>
<summary><b>Task 4:</b> Functional Simulation of RISC-V Core</summary>   
<br>

**Task 4: Functional Simulation of RISC-V Core**  

### Steps
1. Installed simulation tools:  
   ```
   sudo apt install iverilog gtkwave
   ```  
2. Compiled the Verilog netlist and testbench:  
   ```
   iverilog -o riscv_sim riscv_core.v riscv_tb.v
   ./riscv_sim
   gtkwave riscv_sim.vcd
   ```  
3. Observed waveforms in GTKWave showing a 5-stage pipelined architecture.  

### Outputs
-  
  ![task 4/GKTWave installation](https://github.com/samartha-hm/samsung-riscv/blob/main/Task%204/GKTWave%20installation%20.png)  
-  
  ![task 4/GKTWave](https://github.com/samartha-hm/samsung-riscv/blob/main/Task%204/GKTWave.png) 
-  
  ![task 4/Waveform](https://github.com/samartha-hm/samsung-riscv/blob/main/Task%204/Waveform%20.png)
-
  ![task 4/Waveform](https://github.com/samartha-hm/samsung-riscv/blob/main/Task%204/runing%20GKTWave.png) 
-
  ![task 4/Waveform](https://github.com/samartha-hm/samsung-riscv/blob/main/Task%204/task4_rv32i.v.png) 
  


</details>

----------------------------------------------------------------------------------------------------------------

<details>
<summary><b>Task 5:</b> Implement a Digital Circuit using VSDSquadron Mini RISC-V SoC device, referring to CH32V003F4U6</summary>   
<br>

## Full Adder Implementation

### Overview
Implemented a full adder circuit using the VSDSquadron Mini (CH32V003F4U6). It adds three binary inputs (A, B, Carry-in) and outputs Sum and Carry-out via LEDs.

### Components
- VSDSquadron Mini RISC-V SoC (CH32V003F4U6)  
- 3 Switches (Inputs: A, B, Carry-in)  
- 2 LEDs (Outputs: Sum, Carry-out)  
- Resistors (10Ω for switches, 220Ω for LEDs)  
- Breadboard & Jumper Wires  

### Pin Connections
| Signal     | Pin | Connection         |  
|------------|-----|--------------------|  
| A          | PA1 | Switch 1           |  
| B          | PA2 | Switch 2           |  
| Carry-in   | PC4 | Switch 3           |  
| Sum        | PC6 | LED 1             |  
| Carry-out  | PC7 | LED 2             |  

### C Code
```c
#include <ch32v00x.h>

void GPIO_Config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // Inputs: A (PA1), B (PA2), Carry-in (PC4)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Outputs: Sum (PC6), Carry-out (PC7)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int main(void) {
    GPIO_Config();
    while (1) {
        uint8_t a = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
        uint8_t b = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
        uint8_t cin = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4);
        uint8_t sum = a ^ b ^ cin;              // XOR for Sum
        uint8_t cout = (a & b) | (b & cin) | (a & cin); // OR-AND for Carry-out
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, sum);
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, cout);
        Delay_Ms(100);
    }
}
```

### Circuit Diagram
![task 5/circuit](https://github.com/samartha-hm/samsung-riscv/blob/main/Task%205/full_adder_circuit.png) *(To be uploaded)*  
</details>

----------------------------------------------------------------------------------------------------------------

<details>
<summary><b>Task 6:</b> Application Video of a Digital Circuit using VSDSquadron Mini RISC-V SoC device</summary>   
<br>

## Full Adder Demo

### Overview
Demonstrated the full adder on the VSDSquadron Mini. Inputs (A, B, Carry-in) are toggled via switches, and outputs (Sum, Carry-out) are displayed via LEDs.

### Components
- VSDSquadron Mini RISC-V SoC (CH32V003F4U6)  
- 3 Switches  
- 2 LEDs  
- Resistors (10Ω for switches, 220Ω for LEDs)  
- Breadboard & Jumper Wires  

### Video
![task 6/video](https://github.com/samartha-hm/samsung-riscv/blob/main/Task%206/Vsd.mp4)  
*Description:* The video shows the full adder in action, with switches toggling inputs and LEDs indicating Sum and Carry-out.
 
</details>

----------------------------------------------------------------------------------------------------------------

