const base65536 = require('base65536')
const fs = require('fs')

try {
  const data = fs.readFileSync('chall.txt', 'utf8');
  fs.writeFileSync('chall.base65536_decoded', base65536.decode(data));
} catch (err)  {
  console.error(err);
}

