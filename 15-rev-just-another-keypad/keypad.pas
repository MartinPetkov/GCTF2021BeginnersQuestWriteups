type
  DigitType = array[1..16] of SmallInt;

function CheckKeyPadCode(code : DigitType) : Boolean;
var
  digit : SmallInt;
  i : SmallInt;
  x, a, b, c, d : QWord;

begin
  x := 0;
  i := 0;

  For digit In code Do
  Begin
    If (digit < 0) or (digit > 9) then
    begin
      CheckKeyPadCode := False;
      Exit;
    end;

    x := x or (QWord(digit) shl i);
    i += 4;
  End;

  x := x xor &1275437152437512431354;
  x := RolQWord(x, 10);

  a := x and 1229782938247303441;
  b := x and &0210421042104210421042;
  c := x and RolQWord(1229782938247303441, 2);
  d := x and RolQWord(&0210421042104210421042, 2);

  if ((a = $0100101000011110) and (b = $2002220020022220) and
      (c = $4444040044044400) and (d = QWord($8880008080000880))) then
    CheckKeyPadCode := True
  else
    CheckKeyPadCode := False;
end;
