extern crate vm;

use std::io::{Seek, Write};
use vm::*;

const INPUT_DATA: [u32; 63] = [
    66, 82, 66, 117, 75, 91, 86, 87, 31, 51, 222, 187, 112, 236, 9, 98, 34, 69, 0, 198, 150, 29,
    96, 10, 69, 26, 253, 225, 164, 8, 110, 67, 102, 108, 103, 162, 209, 1, 173, 130, 186, 5, 123,
    109, 187, 215, 86, 232, 23, 215, 184, 79, 171, 232, 128, 67, 138, 153, 251, 92, 4, 94, 93,
];
struct Vm {
    f: std::fs::File,
    registers: [u32; 256],
    stack: [u32; 64 * 1024],
    flag: bool,
    sp: usize,
}

impl Vm {
    fn new<T: AsRef<std::path::Path>>(path: T) -> std::io::Result<Self> {
        let f = std::fs::File::open(path.as_ref())?;
        Ok(Self {
            f,
            registers: [0u32; 256],
            stack: [0u32; 64 * 1024],
            flag: false,
            sp: 0,
        })
    }

    fn step(&mut self) -> std::io::Result<()> {
        let instruction = Instruction::read(&mut self.f)?;
        //println!("Display: {}", instruction);

        /*
        let pos = self.f.stream_position()?;
        println!(
            "{:04X} | sp={:04} | flg={} | {:?}",
            pos, self.sp, self.flag, instruction,
        );

        for (idx, v) in self.registers.iter().enumerate() {
            if *v > 0 {
                println!("{:?} -> {}", idx, v);
            }
        }
        */


        use Instruction::*;
        match instruction {
            Nop => {}
            MovConst { reg, v } => self.registers[reg as usize] = v,
            MovReg { reg, reg2 } => self.registers[reg as usize] = self.registers[reg2 as usize],
            MathOp {
                reg_out,
                reg,
                op,
                reg2,
            } => {
                let r1 = self.registers[reg as usize];
                let r2 = self.registers[reg2 as usize];
                self.registers[reg_out as usize] = match op {
                    3 => r1 + r2,
                    4 => r1 - r2,
                    5 => r1 * r2,
                    6 => r1 / r2,
                    _ => unimplemented!(),
                };
            }
            PushReg(reg) => {
                self.stack[self.sp] = self.registers[reg as usize];
                self.sp += 1;
            }
            PopReg(reg) => {
                self.registers[reg as usize] = self.stack[self.sp - 1];
                self.sp -= 1;
            }
            PushConst(c) => {
                self.stack[self.sp] = c;
                self.sp += 1
            }
            JmpConst(c) => {
                self.f.seek(std::io::SeekFrom::Start(c as u64))?;
            }
            PopPc => {
                self.f
                    .seek(std::io::SeekFrom::Start(self.stack[self.sp - 1] as u64))?;
                self.sp -= 1;
            }
            Test { reg, op, reg2 } => {
                self.flag = match op {
                    0 => self.registers[reg as usize] < self.registers[reg2 as usize],
                    1 => self.registers[reg as usize] <= self.registers[reg2 as usize],
                    _ => unimplemented!(),
                }
            }
            JmpCond(c) => {
                if !self.flag {
                    self.f.seek(std::io::SeekFrom::Start(c as u64))?;
                }
            }
            Call(v) => {
                self.stack[self.sp] = self.f.stream_position().unwrap() as u32;
                self.sp += 1;
                self.f.seek(std::io::SeekFrom::Start(v as u64))?;
            }

            Strlen => {
                self.registers[REG_RV as usize] = INPUT_DATA.len() as u32;
            }
            CharAt => {
                let arg2 = self.registers[REG_ARG1 as usize];
                self.registers[REG_RV as usize] = INPUT_DATA
                    .iter()
                    .nth(arg2 as usize)
                    .map(|v| *v as u32)
                    .unwrap_or(0_u32);
                //println!("CharAt: {}", self.registers[REG_RV as usize]);
            }
            Print => {
                let stdout = std::io::stdout();
                let mut lock = stdout.lock();
                lock.write_all(&[self.registers[REG_ARG0 as usize] as u8])?;
                lock.flush()?;
            }
            Exit => {
                std::process::exit(0);
            }
        };
        Ok(())
    }
}

fn main() -> std::io::Result<()> {
    if let Some(path) = std::env::args().nth(1) {
        let mut vm = Vm::new(path)?;
        loop {
            vm.step()?;
        }
    } else {
        println!("Missing ROM");
        Ok(())
    }
}
