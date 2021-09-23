use std::io::{Read, Write};

pub type Register = char;
pub const REG_RV: Register = 0 as Register;
pub const REG_ARG0: Register = 1 as Register;
pub const REG_ARG1: Register = 2 as Register;
pub const REG_FLAG: Register = 0xFF as Register;

// Instructions
#[derive(Copy, Clone, Debug)]
pub enum Instruction {
    Nop,
    MovConst {
        reg: Register,
        v: u32,
    },
    MovReg {
        reg: Register,
        reg2: Register,
    },
    MathOp {
        reg_out: Register,
        reg: Register,
        op: u8,
        reg2: Register,
    },
    PushReg(Register),
    PopReg(Register),
    PushConst(u32),
    JmpConst(u32),
    PopPc,
    Test {
        reg: Register,
        op: u8,
        reg2: Register,
    },
    JmpCond(u32),
    Call(u32),

    Strlen,
    CharAt,
    Print,
    Exit,
}

impl Instruction {
    pub fn read(f: &mut std::fs::File) -> std::io::Result<Self> {
        let mut opcode = [0u8];
        f.read_exact(&mut opcode)?;

        let read_u32 = |f: &mut std::fs::File| -> std::io::Result<u32> {
            let mut buf = [0u8; 4];
            f.read_exact(&mut buf)?;
            let res: u32 = unsafe { std::mem::transmute(buf) };
            Ok(res)
        };

        let read_u8 = |f: &mut std::fs::File| -> std::io::Result<u8> {
            let mut buf = [0u8];
            f.read_exact(&mut buf)?;
            Ok(buf[0])
        };

        let read_reg = |f: &mut std::fs::File| read_u8(f).map(|x| x as char);

        Ok(match opcode[0] {
            0 => Instruction::Nop,
            1 => Instruction::MovConst {
                reg: read_reg(f)?,
                v: read_u32(f)?,
            },
            2 => Instruction::MovReg {
                reg: read_reg(f)?,
                reg2: read_reg(f)?,
            },
            3 => Instruction::MathOp {
                reg_out: read_reg(f)?,
                reg: read_reg(f)?,
                op: read_u8(f)?,
                reg2: read_reg(f)?,
            },
            4 => Instruction::PushReg(read_reg(f)?),
            5 => Instruction::PopReg(read_reg(f)?),
            6 => Instruction::PushConst(read_u32(f)?),
            7 => Instruction::JmpConst(read_u32(f)?),
            8 => Instruction::PopPc,
            9 => Instruction::Test {
                reg: read_reg(f)?,
                op: read_u8(f)?,
                reg2: read_reg(f)?,
            },
            10 => Instruction::JmpCond(read_u32(f)?),
            11 => Instruction::Call(read_u32(f)?),

            0xFC => Instruction::Strlen,
            0xFD => Instruction::CharAt,
            0xFE => Instruction::Print,
            0xFF => Instruction::Exit,
            _ => unreachable!(),
        })
    }

    pub fn write(&self, f: &mut std::fs::File) -> std::io::Result<()> {
        f.write_all(&[(*self).into()])?;

        use Instruction::*;
        match self {
            MovConst { reg, v } => {
                let v_raw: [u8; 4] = unsafe { std::mem::transmute(*v) };
                f.write_all(&[*reg as u8])?;
                f.write_all(&v_raw)?;
            }
            MovReg { reg, reg2 } => {
                f.write_all(&[*reg as u8, *reg2 as u8])?;
            }
            MathOp {
                reg_out,
                reg,
                op,
                reg2,
            } => {
                f.write_all(&[*reg_out as u8, *reg as u8, *op, *reg2 as u8])?;
            }
            PushReg(reg) => {
                f.write_all(&[*reg as u8])?;
            }
            PopReg(reg) => {
                f.write_all(&[*reg as u8])?;
            }
            PushConst(c) => {
                let c_raw: [u8; 4] = unsafe { std::mem::transmute(*c) };
                f.write_all(&c_raw)?;
            }
            JmpConst(c) => {
                let c_raw: [u8; 4] = unsafe { std::mem::transmute(*c) };
                f.write_all(&c_raw)?;
            }
            Test { reg, op, reg2 } => {
                f.write_all(&[*reg as u8, *op, *reg2 as u8])?;
            }
            JmpCond(c) => {
                let c_raw: [u8; 4] = unsafe { std::mem::transmute(*c) };
                f.write_all(&c_raw)?;
            }
            Call(c) => {
                let c_raw: [u8; 4] = unsafe { std::mem::transmute(*c) };
                f.write_all(&c_raw)?;
            }
            PopPc | Strlen | CharAt | Print | Exit | Nop => {}
        }

        Ok(())
    }
}

impl std::fmt::Display for Instruction {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        use Instruction::*;
        match self {
            MovConst { reg, v } => write!(f, "mov {:?}, 0x{:08X}", *reg, v),
            MovReg { reg, reg2 } => write!(f, "mov {:?}, {:?}", *reg, *reg2),
            MathOp {
                reg_out,
                reg,
                op,
                reg2,
            } => write!(f, "{:?} = alu({:?}, {}, {:?}", *reg_out, *reg, *op, *reg2),
            PushReg(reg) => write!(f, "push {:?}", *reg),
            PopReg(reg) => write!(f, "pop {:?}", *reg),
            PushConst(c) => write!(f, "push 0x{:X}", *c),
            JmpConst(c) => write!(f, "jmp 0x{:X}", *c),
            Test { reg, op, reg2 } => write!(f, "test {:?}, {}, {:?}", *reg, *op, *reg2),
            JmpCond(c) => write!(f, "jmpc 0x{:X}", *c),
            Call(c) => write!(f, "call 0x{:X}", *c),
            PopPc => write!(f, "ret"),
            Strlen => write!(f, "call Strlen"),
            CharAt => write!(f, "call CharAt"),
            Print => write!(f, "chall Print"),
            Exit => write!(f, "exit"),
            Nop => write!(f, "nop"),
        }
    }
}

impl Into<u8> for Instruction {
    fn into(self) -> u8 {
        use Instruction::*;
        match self {
            Nop => 0,
            MovConst { .. } => 1,
            MovReg { .. } => 2,
            MathOp { .. } => 3,
            PushReg(_) => 4,
            PopReg(_) => 5,
            PushConst(_) => 6,
            JmpConst(_) => 7,
            PopPc => 8,
            Test { .. } => 9,
            JmpCond(_) => 10,
            Call(_) => 11,

            Strlen => 0xFC,
            CharAt => 0xFD,
            Print => 0xFE,
            Exit => 0xFF,
        }
    }
}
